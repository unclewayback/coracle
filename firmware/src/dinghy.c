/* SPDX-License-Identifier: GPL-3.0-only */
/* Coracle: a Dinghy fork that makes the FM-1 a Pure Data control surface.
 *
 * Two modes, switched by SysEx (0x40 <1|0>, status query 0x7F):
 *   TAKEOVER                  the whole panel belongs to Pure Data
 *   OFF (standalone)          the panel plays the cos3v3 heavy engine:
 *                             keys 0-26 trigger notes 60-86, KNOB1-4 set the
 *                             page's params, SELECT toggles the page
 *                             (host builds boot here; the device, where the
 *                             engine is not linked yet, boots in takeover)
 *
 * Takeover talks on MIDI **channel 13** (0x9C/0xBC/0xEC); channels 1-10 stay
 * free for the future standard-control mode. The FM-1 sends its panel as:
 *   keys 0-26, buttons 27-40   as note on (vel 127) / note off (vel 0)
 *   encoders 1-7               as CC 1-7: 65 = +1 detent, 63 = -1 detent
 *                              (1-4 = KNOB1-4, 5 = SELECT, 6 = PRESETS, 7 = ALGORITHM,
 *                              reading left to right across the panel)
 *   MASTER knob               as pitch bend, the raw 0..1023 of the ADC
 *
 * Pd drives the panel back (channel 13):
 *   notes 0-40: vel 0 = LED off, 1-63 = glow (~1/24), 64-127 = full on
 *   SysEx F0 7D <cmd> <params> F7 draws on the screen (see PROTOCOL)
 *   mode changes and queries are ACKed on CC 121, ch 13 (127 = takeover,
 *   0 = off), the one direction the app can speak until usb.c gains a
 *   SysEx TX path
 *
 * Requires the small usb.c hook (sysex_app_get) that routes non-updater SysEx
 * to the app. No sound yet: in takeover the FM-1 is silent, Pd makes the noise.
 *
 * Rules of the road (the chip has no FPU and no libgcc): integers only, no float,
 * no 64-bit division. tests/run_host.sh runs this file on your computer first;
 * if sysex_app_get is missing there, stub it (see PROTOCOL, "Host mode"). */
#ifndef APP_NAME
#define APP_NAME "CORACLE"                 /* the rescue and crash screens */
#endif
#include "platform.c"

/* ---- the hook the usb.c patch provides: 1 and the next app SysEx byte, or 0.
 *      The host build (tests/run_host.sh, -DDINGHY_HOST) has no usb.c: a stub
 *      returns 0, so the drawing path is inert on the computer; the panel side
 *      still runs. On the device the patched usb.c defines the real thing. */
#ifdef DINGHY_HOST
uint8_t sysex_app_get(uint8_t *b) { (void)b; return 0; }
#define FM1_ADC_MASTER 0u                                  /* no ADC on the host: */
static int32_t fm1_adc_read(uint32_t ch) { (void)ch; return -1; }  /* -1 = not ready */
#else
extern uint8_t sysex_app_get(uint8_t *b);
#endif

/* ---- the mode: 1 = the panel is Pd's (takeover), 0 = the standalone side.
 *      Host builds boot standalone (the engine lives there); the device, where
 *      the heavy engine is not linked yet, boots in takeover. */
#ifdef DINGHY_HOST
static uint8_t takeover = 0;
#else
static uint8_t takeover = 1;
#endif

/* ---- the standalone engine: cos3v3, a Heavy-compiled Pd patch.
 *      Host builds compile it in (engine.c; also the ceiling test); the device
 *      build keeps stubs until the context's C++ and allocator needs are
 *      sorted for the JieLi toolchain. */
#ifdef DINGHY_HOST
#include "engine.c"
#else
static void engine_init(void) { }
static void engine_key(uint32_t key, uint8_t down) { (void)key; (void)down; }
static void engine_knob(uint32_t knob, int32_t delta) { (void)knob; (void)delta; }
static void engine_select(void) { }
static uint8_t engine_page(void) { return 0u; }
static void engine_audio(int32_t *out, uint32_t n) { (void)out; (void)n; }
#endif

/* ---- the sound */
static void app_audio(int32_t *out, uint32_t n)
{
    if (!takeover)
        engine_audio(out, n);
}

#define TAK_CC 121u                        /* mode ACK: CC 121 on ch 13 */
static void mode_reply(void)
{
    midi_send(0xBC, TAK_CC, takeover ? 127u : 0u);
}

/* ---- the panel, out over MIDI (takeover, channel 13) */
static void panel_out(void)
{
    static uint32_t prev = 0;                   /* keys held last time round */
    uint32_t keys, down, up, k;

    if (!takeover) {
        return;                                /* the standalone side owns it */
    }
    keys = fm1_in.notes;                        /* bit k: key k (0 = F3 .. 26 = G5) */
    down = keys & ~prev;
    up = prev & ~keys;
    prev = keys;
    for (k = 0; k < 27u; k++) {
        if (down >> k & 1u) midi_send(0x9C, (uint8_t)k, 127);       /* note on */
            if (up >> k & 1u)   midi_send(0x9C, (uint8_t)k, 0);         /* note off */
    }

    {   /* buttons: note = 27 + button id */
        uint32_t brel, bp = fm1_input_edges(&brel), i;
        for (i = 0; i < 14u; i++) {
            if (bp >> i & 1u)   midi_send(0x9C, (uint8_t)(27u + i), 127);
            if (brel >> i & 1u) midi_send(0x9C, (uint8_t)(27u + i), 0);
        }
    }

    {   /* encoders: CC 1-7, one message per detent: 65 = +1, 63 = -1
        (CC order reads left to right across the panel) */
        static const uint8_t id[7] = {
            ENC_KNOB1, ENC_KNOB2, ENC_KNOB3, ENC_KNOB4,
            ENC_SELECT, ENC_PRESETS, ENC_ALGORITHM
        };
        uint32_t i;
        for (i = 0; i < 7u; i++) {
            int32_t d = fm1_enc_take(id[i]);
            while (d > 0) { midi_send(0xBC, (uint8_t)(i + 1u), 65); d--; }
            while (d < 0) { midi_send(0xBC, (uint8_t)(i + 1u), 63); d++; }
        }
    }

    {   /* MASTER: pitch bend, the raw 0..1023 of the ADC, unscaled. Sent only
        when it moves by >= 4 counts: the ADC jitters by a few counts and a
        hysteresis of 4 keeps the stream quiet without hiding slow turns. */
        static int32_t sent = -1;
        int32_t a = fm1_adc_read(FM1_ADC_MASTER), v;
        if (a >= 0) {
            v = a;
            if (sent < 0 || v - sent >= 4 || sent - v >= 4) {
                sent = v;
                midi_send(0xEC, (uint8_t)(v & 0x7Fu), (uint8_t)((uint32_t)v >> 7));
            }
        }
    }
}

/* ---- MIDI in: notes light the LEDs (keys 0-26, buttons 27-40).
 *      The panel has three real brightness levels: full, the glow layer
 *      (~1/24, fm1_led_dim) and off. vel 0 = off, 1-63 = glow, 64-127 = full. */
#ifdef DINGHY_HOST
static void led_set(int32_t id, int lvl)            /* the host stub is binary */
{
    fm1_led_key((uint32_t)id, lvl != 0);
}
#else
static void led_set(int32_t id, int lvl)            /* HAL id -> column, row bit */
{
    int32_t c, r;
    for (c = 0; c < 11; c++)
        for (r = 0; r < 6; r++)
            if (FM1_KEYMAP[r][c] == (int8_t)id) {
                uint8_t bit = (uint8_t)(1u << r);
                if (lvl >= 2)
                    fm1_led[c] |= bit;
                else
                    fm1_led[c] &= ~bit;
                if (lvl == 1)
                    fm1_led_dim[c] |= bit;
                else
                    fm1_led_dim[c] &= ~bit;
                return;
            }
}
#endif

static void midi_in_leds(void)
{
    uint8_t st, d1, d2;
    while (midi_get(&st, &d1, &d2)) {
        if (st == 0x9Cu && d1 < 41u) {          /* note on, channel 13 only */
            int32_t id = d1 < 27u ? KEY_LED(d1) : (int32_t)(d1 - 27u);
            led_set(id, d2 == 0u ? 0 : d2 < 64u ? 1 : 2);
        }
    }
}

/* ---- SysEx in: the screen. Frames arrive from the usb.c hook as
 *      7D <cmd> <params...> F7  (0x22 frames are the updater's, not ours).
 *      MIDI data bytes are 7-bit: every value that can exceed 127 (x, y, w, h)
 *      is sent as two bytes, low 7 bits first, then the rest. Colours are
 *      R G B, each 0..127. Installer chatter reaching this ring starts with
 *      something other than 0x7D and is ignored. */
static uint16_t v7(const uint8_t *p)               /* two 7-bit bytes -> 0..16383 */
{
    return (uint16_t)((uint16_t)p[1] << 7 | p[0]);
}

static uint16_t rgb565(const uint8_t *p)            /* R G B, each 0..127 */
{
    uint32_t r = (uint32_t)p[0] * 31u / 127u;
    uint32_t g = (uint32_t)p[1] * 63u / 127u;
    uint32_t b = (uint32_t)p[2] * 31u / 127u;
    return (uint16_t)((r << 11) | (g << 5) | b);
}

static void sx_exec(const uint8_t *p, uint32_t n)   /* p[0] = 0x7D, p[1] = the command */
{
    if (n < 2u || p[0] != 0x7Du)
        return;
    switch (p[1]) {
        case 0x40:                                     /* takeover <1|0>: set the mode */
            if (n >= 3u)
                takeover = p[2] != 0u;
        mode_reply();
        break;
        case 0x7F:                                     /* status query: just the ACK */
            mode_reply();
            break;
        case 0x01:                                     /* clear [R G B] */
            if (takeover && n >= 5u)
                lcd_fill(0, 0, 240, 240, rgb565(p + 2));
        break;
        case 0x02: {                                   /* rect [x2 y2 w2 h2 R G B] */
            uint32_t x, y, w, h;
            if (!takeover || n < 13u)
                break;
            x = v7(p + 2);
            y = v7(p + 4);
            w = v7(p + 6);
            h = v7(p + 8);
            if (x > 239u) x = 239u;
            if (y > 239u) y = 239u;
            if (w > 240u - x) w = 240u - x;
            if (h > 240u - y) h = 240u - y;
            if (w && h)
                lcd_fill(x, y, w, h, rgb565(p + 10));
            break;
        }
        case 0x03: {                                   /* text [x2 y2 font R G B chars...] */
            char s[32];
            uint32_t x, y, i, m;
            if (!takeover || n < 11u || p[6] > 1u)
                break;
            x = v7(p + 2);
            y = v7(p + 4);
            if (x > 239u) x = 239u;
            if (y > 239u) y = 239u;
            m = n - 10u;
            if (m > sizeof s - 1u)
                m = sizeof s - 1u;
            for (i = 0; i < m; i++) {
                uint8_t ch = p[10 + i];
                s[i] = (char)(ch < 32u || ch > 126u ? '?' : ch);
            }
            s[m] = 0;
            draw_text_box((int32_t)x, (int32_t)y, (int32_t)(240 - x), p[6] ? &FONT_L : &FONT_S,
                          s, rgb565(p + 7), 0);
            break;
        }
        default:
            break;                                     /* unknown command: ignored */
    }
}

static void sysex_in(void)
{
    static uint8_t f[64];                          /* one frame at a time */
    static uint32_t n = 0;
    static uint8_t bad = 0;
    uint8_t b;
    while (sysex_app_get(&b)) {
        if (b == 0xF7u) {                          /* end: run it */
            if (!bad && n)
                sx_exec(f, n);
            n = 0;
            bad = 0;
            continue;
        }
        if (n < sizeof f)
            f[n++] = b;
        else
            bad = 1;                               /* too long: dropped whole */
    }
}

/* ---- the standalone panel: the engine's controls (not takeover) */
static void standalone_panel(void)
{
    static uint32_t prev = 0;
    static uint8_t pg = 255u;
    uint32_t keys, down, k, brel;
    int32_t d;
    uint8_t i;

    keys = fm1_in.notes;                        /* held keys light their LEDs */
    down = keys & ~prev;
    prev = keys;
    for (k = 0; k < 27u; k++) {
        if (down >> k & 1u) {
            engine_key(k, 1);                   /* one-shot: press triggers */
        }
        fm1_led_key(KEY_LED(k), keys >> k & 1u);
    }
    fm1_input_edges(&brel);                      /* buttons: reserved for menus */
    d = fm1_enc_take(ENC_SELECT);
    if (d)
        engine_select();
    for (i = 0; i < 4u; i++) {
        d = fm1_enc_take(ENC_KNOB1 + i);
        if (d)
            engine_knob(i, d);
    }
    if (pg != engine_page()) {                  /* the page label */
        pg = engine_page();
        draw_text_box(0, 52, 240, &FONT_S,
                      pg ? "DECAY  CLIP  VEL  -" : "F1  F2  SHAPE  MOD",
                      RGB(180, 140, 255), 1);
    }
}

/* ---- main */
static void app_main(void)
{
    engine_init();
    lcd_fill(0, 0, 240, 240, C_BLACK);
    draw_text_box(0, 96, 240, &FONT_L, APP_NAME, RGB(180, 140, 255), 1);
    draw_text_box(0, 140, 240, &FONT_S, "Pd link  v" APP_VER, RGB(90, 90, 90), 1);

    for (;;) {
        platform_poll();                           /* watchdog, USB, the updater */
        if (takeover) {
            panel_out();
            midi_in_leds();
        } else {
            standalone_panel();
        }
        sysex_in();                                /* the mode switch always works */
    }
}
