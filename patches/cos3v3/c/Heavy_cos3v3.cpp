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

#include "Heavy_cos3v3.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_cos3v3 *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_cos3v3_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_cos3v3));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_cos3v3(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_cos3v3_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_cos3v3));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_cos3v3(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_cos3v3_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_cos3v3();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_cos3v3::Heavy_cos3v3(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_init(&sPhasor_4HBNMlWb, sampleRate);
  numBytes += sPhasor_init(&sPhasor_Z74n59WJ, sampleRate);
  numBytes += sLine_init(&sLine_qNPPhxLf);
  numBytes += sPhasor_init(&sPhasor_vGLwUHmo, sampleRate);
  numBytes += sRPole_init(&sRPole_qvSywCZi);
  numBytes += sDel1_init(&sDel1_XuzDYPKK);
  numBytes += sVarf_init(&sVarf_nknJZl70, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_DLNpQlBK, 10.0f);
  numBytes += cBinop_init(&cBinop_0GcdWZ2q, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_AbL327pQ, 0.0f, 0.0f, false);
  numBytes += cIf_init(&cIf_xm7kv5qf, false);
  numBytes += sVarf_init(&sVarf_HFgm1x5r, 0.5f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_DcvpP5aO, 500.0f);
  numBytes += cVar_init_f(&cVar_dmPk9PcH, 0.787402f);
  numBytes += sVarf_init(&sVarf_tOUULxdi, 0.9f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_lAFLszBB, -0.9f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_Ej4uS64z, 1.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_GVrDVisv, 2.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_xplPC0VR, 261.626f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_YDiQboUg, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_cos3v3::~Heavy_cos3v3() {
  // nothing to free
}

HvTable *Heavy_cos3v3::getTableForHash(hv_uint32_t tableHash) {
  return nullptr;
}

void Heavy_cos3v3::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_ox2rWONZ_sendMessage);
      break;
    }
    case 0x80F12EC1: { // clip
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_q9wGVMh5_sendMessage);
      break;
    }
    case 0x4F49BFDF: { // decay
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_a2CUihhc_sendMessage);
      break;
    }
    case 0x2394264B: { // freq1
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_eflgrgnm_sendMessage);
      break;
    }
    case 0x24A00017: { // freq2
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_sdsTQQqi_sendMessage);
      break;
    }
    case 0x32396E6F: { // mod
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_8ah4Fc07_sendMessage);
      break;
    }
    case 0x6E3449A8: { // note
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_RUWacleb_sendMessage);
      break;
    }
    case 0xB063C1EC: { // shape
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_NVGmcYhh_sendMessage);
      break;
    }
    case 0x853B1BE7: { // velocity
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_zsYJ2jZB_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_cos3v3::getParameterInfo(int index, HvParameterInfo *info) {
  if (info != nullptr) {
    switch (index) {
      case 0: {
        info->name = "clip";
        info->hash = 0x80F12EC1;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 10.0f;
        info->maxVal = 100.0f;
        info->defaultVal = 90.0f;
        break;
      }
      case 1: {
        info->name = "decay";
        info->hash = 0x4F49BFDF;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 10.0f;
        info->maxVal = 3000.0f;
        info->defaultVal = 500.0f;
        break;
      }
      case 2: {
        info->name = "freq1";
        info->hash = 0x2394264B;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 1.0f;
        info->maxVal = 4.0f;
        info->defaultVal = 1.0f;
        break;
      }
      case 3: {
        info->name = "freq2";
        info->hash = 0x24A00017;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 1.0f;
        info->maxVal = 4.0f;
        info->defaultVal = 2.0f;
        break;
      }
      case 4: {
        info->name = "mod";
        info->hash = 0x32396E6F;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 100.0f;
        info->defaultVal = 50.0f;
        break;
      }
      case 5: {
        info->name = "note";
        info->hash = 0x6E3449A8;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 127.0f;
        info->defaultVal = 60.0f;
        break;
      }
      case 6: {
        info->name = "shape";
        info->hash = 0xB063C1EC;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 100.0f;
        info->defaultVal = 0.0f;
        break;
      }
      case 7: {
        info->name = "velocity";
        info->hash = 0x853B1BE7;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 127.0f;
        info->defaultVal = 100.0f;
        break;
      }
      default: {
        info->name = "invalid parameter index";
        info->hash = 0;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 0.0f;
        info->defaultVal = 0.0f;
        break;
      }
    }
  }
  return 8;
}



/*
 * Send Function Implementations
 */


void Heavy_cos3v3::cBinop_DSiKLnBM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_0IAse1ZX_sendMessage);
}

void Heavy_cos3v3::cBinop_0IAse1ZX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_WMVRUJvo_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_n6pg2T7Q_sendMessage);
}

void Heavy_cos3v3::cVar_DLNpQlBK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_ivWHBDwz_sendMessage);
}

void Heavy_cos3v3::cMsg_61nbd4MS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_qrLcwfsU_sendMessage);
}

void Heavy_cos3v3::cSystem_qrLcwfsU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0GcdWZ2q, HV_BINOP_DIVIDE, 1, m, &cBinop_0GcdWZ2q_sendMessage);
}

void Heavy_cos3v3::cBinop_WMVRUJvo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_GKqjmBPT_sendMessage);
}

void Heavy_cos3v3::cBinop_GKqjmBPT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_AbL327pQ, m);
}

void Heavy_cos3v3::cMsg_RWroAxq1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_yxCU9ycO_sendMessage);
}

void Heavy_cos3v3::cBinop_yxCU9ycO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_DSiKLnBM_sendMessage);
}

void Heavy_cos3v3::cBinop_n6pg2T7Q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_nknJZl70, m);
}

void Heavy_cos3v3::cBinop_ivWHBDwz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_QCCthqlu_sendMessage);
}

void Heavy_cos3v3::cBinop_QCCthqlu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0GcdWZ2q, HV_BINOP_DIVIDE, 0, m, &cBinop_0GcdWZ2q_sendMessage);
}

void Heavy_cos3v3::cBinop_0GcdWZ2q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_RWroAxq1_sendMessage(_c, 0, m);
}

void Heavy_cos3v3::cIf_xm7kv5qf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 50.0f, 0, m, &cBinop_NSZuR0xH_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_cos3v3::cBinop_lw0NAbxl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_xm7kv5qf, 1, m, &cIf_xm7kv5qf_sendMessage);
}

void Heavy_cos3v3::cVar_DcvpP5aO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Jrkhdv38_sendMessage(_c, 0, m);
}

void Heavy_cos3v3::cVar_dmPk9PcH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ZtHMISkW_sendMessage(_c, 0, m);
}

void Heavy_cos3v3::cBinop_i4ncRyhv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_lAFLszBB, m);
}

void Heavy_cos3v3::cMsg_Jrkhdv38_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  msg_setElementToFrom(m, 1, n, 0);
  sLine_onMessage(_c, &Context(_c)->sLine_qNPPhxLf, 0, m, NULL);
}

void Heavy_cos3v3::cCast_kpJaHKwx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_dmPk9PcH, 0, m, &cVar_dmPk9PcH_sendMessage);
}

void Heavy_cos3v3::cCast_dQrbAWRH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_DcvpP5aO, 0, m, &cVar_DcvpP5aO_sendMessage);
}

void Heavy_cos3v3::cMsg_ZtHMISkW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 0.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_qNPPhxLf, 0, m, NULL);
}

void Heavy_cos3v3::cBinop_reo5CwYZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_tOUULxdi, m);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_i4ncRyhv_sendMessage);
}

void Heavy_cos3v3::cBinop_vd5hPl6p_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_YDiQboUg, m);
}

void Heavy_cos3v3::cBinop_xIRpHYFl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_HFgm1x5r, m);
}

void Heavy_cos3v3::cBinop_EM2WIwEp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_dmPk9PcH, 1, m, &cVar_dmPk9PcH_sendMessage);
}

void Heavy_cos3v3::cCast_LbVlztmk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_xplPC0VR, m);
}

void Heavy_cos3v3::cCast_LlCkYtXG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_kpJaHKwx_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_dQrbAWRH_sendMessage);
}

void Heavy_cos3v3::cBinop_NSZuR0xH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 127.0f, 0, m, &cBinop_EM2WIwEp_sendMessage);
}

void Heavy_cos3v3::cReceive_ox2rWONZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_61nbd4MS_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_DLNpQlBK, 0, m, &cVar_DLNpQlBK_sendMessage);
}

void Heavy_cos3v3::cReceive_RUWacleb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_LlCkYtXG_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_LbVlztmk_sendMessage);
}

void Heavy_cos3v3::cReceive_NVGmcYhh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.0025f, 0, m, &cBinop_vd5hPl6p_sendMessage);
}

void Heavy_cos3v3::cReceive_a2CUihhc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_DcvpP5aO, 1, m, &cVar_DcvpP5aO_sendMessage);
}

void Heavy_cos3v3::cReceive_8ah4Fc07_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.01f, 0, m, &cBinop_xIRpHYFl_sendMessage);
}

void Heavy_cos3v3::cReceive_zsYJ2jZB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1.0f, 0, m, &cBinop_lw0NAbxl_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_xm7kv5qf, 0, m, &cIf_xm7kv5qf_sendMessage);
}

void Heavy_cos3v3::cReceive_eflgrgnm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_Ej4uS64z, m);
}

void Heavy_cos3v3::cReceive_sdsTQQqi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_GVrDVisv, m);
}

void Heavy_cos3v3::cReceive_q9wGVMh5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.01f, 0, m, &cBinop_reo5CwYZ_sendMessage);
}



/*
 * Code for expr~ implementation
 * Write out the generic implementation code
 */

 // per class code

 // per object code


/*
 * Context Process Implementation
 */

int Heavy_cos3v3::process(float **inputBuffers, float **outputBuffers, int n) {
  while (hLp_hasData(&inQueue)) {
    hv_uint32_t numBytes = 0;
    ReceiverMessagePair *p = reinterpret_cast<ReceiverMessagePair *>(hLp_getReadBuffer(&inQueue, &numBytes));
    hv_assert(numBytes >= sizeof(ReceiverMessagePair));
    scheduleMessageForReceiver(p->receiverHash, &p->msg);
    hLp_consume(&inQueue);
  }

  sendBangToReceiver(0xDD21C0EB); // send to __hv_bang~ on next cycle
  const int n4 = n & ~HV_N_SIMD_MASK; // ensure that the block size is a multiple of HV_N_SIMD

  // temporary signal vars
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6, Bf7, Bf8, Bf9, Bf10;

  // input and output vars
  hv_bufferf_t O0;

  // declare and init the zero buffer
  hv_bufferf_t ZERO; __hv_zero_f(VOf(ZERO));

  hv_uint32_t nextBlock = blockStartTimestamp;
  for (int n = 0; n < n4; n += HV_N_SIMD) {

    // process all of the messages for this block
    nextBlock += HV_N_SIMD;
    while (mq_hasMessageBefore(&mq, nextBlock)) {
      MessageNode *const node = mq_peek(&mq);
      node->sendMessage(this, node->let, node->m);
      mq_pop(&mq);
    }

    

    // zero output buffers
    __hv_zero_f(VOf(O0));

    // process all signal functions
    __hv_varread_f(&sVarf_xplPC0VR, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_exp_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f);
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_phasor_f(&sPhasor_4HBNMlWb, VIf(Bf0), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_abs_f(VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf1));
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf4), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf5), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf3), VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_fma_f(VIf(Bf1), VIf(Bf4), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf4), 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f);
    __hv_mul_f(VIf(Bf2), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf2), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_varread_f(&sVarf_Ej4uS64z, VOf(Bf1));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_phasor_f(&sPhasor_Z74n59WJ, VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_abs_f(VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf5), VOf(Bf1));
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf6), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf7), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf3), VIf(Bf7), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf1), VIf(Bf6), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_HFgm1x5r, VOf(Bf6));
    __hv_line_f(&sLine_qNPPhxLf, VOf(Bf1));
    __hv_mul_f(VIf(Bf6), VIf(Bf1), VOf(Bf7));
    __hv_mul_f(VIf(Bf5), VIf(Bf7), VOf(Bf7));
    __hv_var_k_f(VOf(Bf5), 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f);
    __hv_varread_f(&sVarf_GVrDVisv, VOf(Bf3));
    __hv_mul_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_phasor_f(&sPhasor_vGLwUHmo, VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf0), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_abs_f(VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf3), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf0), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf3));
    __hv_mul_f(VIf(Bf0), VIf(Bf3), VOf(Bf8));
    __hv_mul_f(VIf(Bf8), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf9), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf10), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf8), VIf(Bf10), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf3), VIf(Bf9), VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf6), VIf(Bf1), VOf(Bf6));
    __hv_mul_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f);
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf7), VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_add_f(VIf(Bf4), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_tOUULxdi, VOf(Bf5));
    __hv_min_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_lAFLszBB, VOf(Bf0));
    __hv_max_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf4), VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_YDiQboUg, VOf(Bf2));
    __hv_add_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_floor_f(VIf(Bf2), VOf(Bf0));
    __hv_sub_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_abs_f(VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf0));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf0), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf7));
    __hv_mul_f(VIf(Bf7), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf9), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf3), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf4), VIf(Bf3), VOf(Bf3));
    __hv_sub_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_fma_f(VIf(Bf5), VIf(Bf9), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf9), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf7), VIf(Bf9), VOf(Bf9));
    __hv_sub_f(VIf(Bf3), VIf(Bf9), VOf(Bf9));
    __hv_fma_f(VIf(Bf0), VIf(Bf6), VIf(Bf9), VOf(Bf9));
    __hv_varread_f(&sVarf_nknJZl70, VOf(Bf6));
    __hv_rpole_f(&sRPole_qvSywCZi, VIf(Bf9), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf9), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_XuzDYPKK, VIf(Bf6), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf9), VOf(Bf9));
    __hv_sub_f(VIf(Bf6), VIf(Bf9), VOf(Bf9));
    __hv_varread_f(&sVarf_AbL327pQ, VOf(Bf6));
    __hv_mul_f(VIf(Bf9), VIf(Bf6), VOf(Bf6));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf6), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf6), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_mul_f(VIf(Bf1), VIf(Bf6), VOf(Bf6));
    __hv_add_f(VIf(Bf6), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_cos3v3::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 1 channel(s)
  float **const bOut = &outputBuffers;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_cos3v3::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 1 channel(s)
  float *const bOut = outputBuffers;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
