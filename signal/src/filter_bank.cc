/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

//#define KN_DEBUG
#include "signal/src/filter_bank.h"


#if defined(XTENSA) || defined(HMD1A)
#include "tensorflow/lite/micro/ia8201/config.h"
#include <xtensa/config/core-isa.h>
#include <xtensa/tie/xt_core.h>
#include <xtensa/tie/xt_hifi3.h>
#include <xtensa/tie/xt_misc.h>

#include "tensorflow/lite/micro/ia8201/debug_helper.h"
#endif
#ifndef REMOVE_TFLM_SIGNAL
namespace tflite {

namespace tflm_signal {
#endif
void FilterbankAccumulateChannels(
    //#ifndef REMOVE_TFLM_SIGNAL
    const FilterbankConfig *config,
    //#else
    // const tflite::tflm_signal::FilterbankConfig* config,
    // #endif
    const uint32_t *input, uint64_t *output) {
  // With a log mel filterbank, the energy at each frequency gets added to
  // two adjacent filterbank filters/channels.
  // For the first filter bank channel, its energy is first multiplied by
  // some weight 'w', then gets accumulated.
  // For the subsequent filter bank, its power is first multiplied by 1-'w'
  // (called unweight here), then gets accumulated.
  // For this reason, we need to calculate (config->num_channels + 1) output
  // where element 0 is only used as scratch storage for the unweights of
  // element 1 (channel 0). The caller should discard element 0.
  // Writing the code like this doesn't save multiplications, but it lends
  // itself better to optimization, because input[freq_start + j] only needs
  // to be loaded once.
#if defined(SIG_FB_OPT)

  ae_int64 ae_w, ae_u;
  ae_w = ae_u = AE_ZERO64();
  for (int i = 0; i < config->num_channels + 1; i++) {
    KN_PRINTD(i);
    const int16_t freq_start = config->channel_frequency_starts[i];
    const int16_t weight_start = config->channel_weight_starts[i];
    ae_int16x4 w0, w1;
    ae_valign vw0, vw1, vx;

    const ae_int16x4 *pw0 = (const ae_int16x4 *)&config->weights[weight_start];
    const ae_int16x4 *pw1 =
        (const ae_int16x4 *)&config->unweights[weight_start];
    const ae_int32x2 *px = (const ae_int32x2 *)&input[freq_start];

    int n = 0;
    int N = config->channel_widths[i];
    ae_int32x2 x0;  // W, U;

    vw0 = AE_LA64_PP(pw0);
    vw1 = AE_LA64_PP(pw1);
    vx = AE_LA64_PP(px);

    AE_LA32X2_IP(x0, vx, px);
    AE_LA16X4_IP(w0, vw0, pw0);
    AE_LA16X4_IP(w1, vw1, pw1);



    KN_PRINTX_AE16X4(w1);
    for (n = 0; n < N - 3; n += 4) {
      AE_MULAAD32X16_H3_L2(ae_w, x0, w0);
      AE_MULAAD32X16_H3_L2(ae_u, x0, w1);

      AE_LA32X2_IP(x0, vx, px);

      AE_MULAAD32X16_H1_L0(ae_w, x0, w0);
      AE_MULAAD32X16_H1_L0(ae_u, x0, w1);
      AE_LA32X2_IP(x0, vx, px);
      AE_LA16X4_IP(w0, vw0, pw0);
      AE_LA16X4_IP(w1, vw1, pw1);
    }

    switch (N - n) {
      case 1:
        AE_MULA32X16_H3(ae_w, x0, w0);
        AE_MULA32X16_H3(ae_u, x0, w1);

        break;
      case 2:
        AE_MULAAD32X16_H3_L2(ae_w, x0, w0);
        AE_MULAAD32X16_H3_L2(ae_u, x0, w1);

        break;
      case 3:
        AE_MULAAD32X16_H3_L2(ae_w, x0, w0);
        AE_MULAAD32X16_H3_L2(ae_u, x0, w1);
        AE_LA32X2_IP(x0, vx, px);
        AE_MULA32X16_H1(ae_w, x0, w0);
        AE_MULA32X16_H1(ae_u, x0, w1);
        break;
      default:
        break;
    }

    output[i] = ae_w;  // weight_accumulator;
    ae_w = ae_u;       // unweight_accumulator;

    ae_u = 0;
  }
#else
  uint64_t weight_accumulator = 0;
  uint64_t unweight_accumulator = 0;
  for (int i = 0; i < config->num_channels + 1; i++) {
    const int16_t freq_start = config->channel_frequency_starts[i];
    const int16_t weight_start = config->channel_weight_starts[i];
    for (int j = 0; j < config->channel_widths[i]; ++j) {
      weight_accumulator += config->weights[weight_start + j] *
                            static_cast<uint64_t>(input[freq_start + j]);
      unweight_accumulator += config->unweights[weight_start + j] *
                              static_cast<uint64_t>(input[freq_start + j]);
    }
    output[i] = weight_accumulator;
    weight_accumulator = unweight_accumulator;
    unweight_accumulator = 0;
  }

#endif

  // KN_PRINT_Q63_SIZE(output, config->num_channels + 1);
}
#ifndef REMOVE_TFLM_SIGNAL
}  // namespace tflm_signal

}  // namespace tflite
#endif