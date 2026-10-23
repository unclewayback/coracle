/**
 * Copyright (c) 2026 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef _HEAVY_CONTEXT_COS3V3_HPP_
#define _HEAVY_CONTEXT_COS3V3_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalPhasor.h"
#include "HvSignalVar.h"
#include "HvControlBinop.h"
#include "HvControlIf.h"
#include "HvSignalDel1.h"
#include "HvControlCast.h"
#include "HvSignalLine.h"
#include "HvMath.h"
#include "HvSignalRPole.h"
#include "HvControlVar.h"
#include "HvControlSystem.h"

class Heavy_cos3v3 : public HeavyContext {

 public:
  Heavy_cos3v3(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_cos3v3();

  const char *getName() override { return "cos3v3"; }
  int getNumInputChannels() override { return 0; }
  int getNumOutputChannels() override { return 1; }

  int process(float **inputBuffers, float **outputBuffer, int n) override;
  int processInline(float *inputBuffers, float *outputBuffer, int n) override;
  int processInlineInterleaved(float *inputBuffers, float *outputBuffer, int n) override;

  int getParameterInfo(int index, HvParameterInfo *info) override;
  struct Parameter {
    struct In {
      enum ParameterIn : hv_uint32_t {
        CLIP = 0x80F12EC1, // clip
        DECAY = 0x4F49BFDF, // decay
        FREQ1 = 0x2394264B, // freq1
        FREQ2 = 0x24A00017, // freq2
        MOD = 0x32396E6F, // mod
        NOTE = 0x6E3449A8, // note
        SHAPE = 0xB063C1EC, // shape
        VELOCITY = 0x853B1BE7, // velocity
      };
    };
  };

 private:
  HvTable *getTableForHash(hv_uint32_t tableHash) override;
  void scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) override;


  /*
  * Code for expr~ implementation
  * Write out the generic header code
  */

  // per class code

  // per object code


  // static sendMessage functions
  static void cBinop_DSiKLnBM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0IAse1ZX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_DLNpQlBK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_61nbd4MS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_qrLcwfsU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_WMVRUJvo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GKqjmBPT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_RWroAxq1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_yxCU9ycO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_n6pg2T7Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ivWHBDwz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_QCCthqlu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0GcdWZ2q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_xm7kv5qf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lw0NAbxl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_DcvpP5aO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_dmPk9PcH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_i4ncRyhv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Jrkhdv38_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_kpJaHKwx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_dQrbAWRH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZtHMISkW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_reo5CwYZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vd5hPl6p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xIRpHYFl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EM2WIwEp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_LbVlztmk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_LlCkYtXG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_NSZuR0xH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_ox2rWONZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_RUWacleb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_NVGmcYhh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_a2CUihhc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_8ah4Fc07_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_zsYJ2jZB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_eflgrgnm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_sdsTQQqi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_q9wGVMh5_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_4HBNMlWb;
  SignalPhasor sPhasor_Z74n59WJ;
  SignalLine sLine_qNPPhxLf;
  SignalPhasor sPhasor_vGLwUHmo;
  SignalRPole sRPole_qvSywCZi;
  SignalDel1 sDel1_XuzDYPKK;
  ControlBinop cBinop_DSiKLnBM;
  ControlBinop cBinop_0IAse1ZX;
  SignalVarf sVarf_nknJZl70;
  ControlVar cVar_DLNpQlBK;
  ControlBinop cBinop_WMVRUJvo;
  ControlBinop cBinop_GKqjmBPT;
  ControlBinop cBinop_yxCU9ycO;
  ControlBinop cBinop_n6pg2T7Q;
  ControlBinop cBinop_ivWHBDwz;
  ControlBinop cBinop_QCCthqlu;
  ControlBinop cBinop_0GcdWZ2q;
  SignalVarf sVarf_AbL327pQ;
  ControlIf cIf_xm7kv5qf;
  ControlBinop cBinop_lw0NAbxl;
  SignalVarf sVarf_HFgm1x5r;
  ControlVar cVar_DcvpP5aO;
  ControlVar cVar_dmPk9PcH;
  SignalVarf sVarf_tOUULxdi;
  SignalVarf sVarf_lAFLszBB;
  SignalVarf sVarf_Ej4uS64z;
  SignalVarf sVarf_GVrDVisv;
  SignalVarf sVarf_xplPC0VR;
  ControlBinop cBinop_i4ncRyhv;
  ControlBinop cBinop_reo5CwYZ;
  ControlBinop cBinop_vd5hPl6p;
  ControlBinop cBinop_xIRpHYFl;
  ControlBinop cBinop_EM2WIwEp;
  ControlBinop cBinop_NSZuR0xH;
  SignalVarf sVarf_YDiQboUg;
};

#endif // _HEAVY_CONTEXT_COS3V3_HPP_
