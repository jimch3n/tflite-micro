/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

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

#include "signal/src/window.h"

#include <cstdint>

#include "tensorflow/lite/micro/ia8201/config.h"
#include "tensorflow/lite/micro/ia8201/debug_helper.h"
#if defined(XTENSA) || defined(HMD1A)
#include <xtensa/config/core-isa.h>
#include <xtensa/tie/xt_core.h>
#include <xtensa/tie/xt_hifi3.h>
#include <xtensa/tie/xt_misc.h>
#endif
// TODO(b/286250473): remove namespace once de-duped libraries
#ifndef REMOVE_TFLM_SIGNAL
namespace tflm_signal {
#endif
void ApplyWindow(const int16_t *__restrict input,
                 const int16_t *__restrict window, int size, int shift,
                 int16_t *__restrict output) {
#if defined(SIG_WINDOW_OPT)

  ae_int16x4 ae_window, ae_input;
  ae_valign align_window, align_input, align_output;
  const ae_int16x4 *pt_inp1, *pt_inp2;
  ae_int16x4 *pt_out;

  pt_inp1 = (const ae_int16x4 *)(input);
  pt_inp2 = (const ae_int16x4 *)(window);
  pt_out = (ae_int16x4 *)(output);
  int loopLim = size >> 2;
  ae_int32x2 ae_output1, ae_output2;
  ae_int16x4 ae_out;

  if (loopLim > 0) {
    align_input = AE_LA64_PP(pt_inp1);
    align_window = AE_LA64_PP(pt_inp2);
    align_output = AE_ZALIGN64();
    AE_LA16X4_IP(ae_input, align_input, pt_inp1);
    AE_LA16X4_IP(ae_window, align_window, pt_inp2);

    for (int i = 0; i < loopLim - 1; i++) {
      AE_MUL16X4(ae_output1, ae_output2, ae_input, ae_window);

      ae_output1 = AE_SRAA32(ae_output1, shift);
      ae_output2 = AE_SRAA32(ae_output2, shift);
      ae_out = AE_SAT16X4(ae_output1, ae_output2);

      AE_SA16X4_IP(ae_out, align_output, pt_out);
      AE_LA16X4_IP(ae_input, align_input, pt_inp1);
      AE_LA16X4_IP(ae_window, align_window, pt_inp2);
    }
    AE_MUL16X4(ae_output1, ae_output2, ae_input, ae_window);

    ae_output1 = AE_SRAA32(ae_output1, shift);
    ae_output2 = AE_SRAA32(ae_output2, shift);

    ae_out = AE_SAT16X4(ae_output1, ae_output2);
    AE_SA16X4_IP(ae_out, align_output, pt_out);
    AE_SA64POS_FP(align_output, pt_out);
  }
  // remain 4
  switch (size & 3) {
    case 1:
      ae_out = AE_SEL16_6543(ae_out, ae_out);
      AE_S16_0_I(ae_out, (ae_int16 *)pt_out, 0);
      break;
    case 2:
      ae_out = AE_SEL16_6543(ae_out, ae_out);
      AE_S16_0_I(ae_out, (ae_int16 *)pt_out, 0);
      ae_out = AE_SEL16_5432(ae_out, ae_out);
      AE_S16_0_I(ae_out, (ae_int16 *)pt_out, sizeof(ae_int16));
      break;
    case 3:
      ae_out = AE_SEL16_6543(ae_out, ae_out);
      AE_S16_0_I(ae_out, (ae_int16 *)pt_out, 0);
      ae_out = AE_SEL16_5432(ae_out, ae_out);
      AE_S16_0_I(ae_out, (ae_int16 *)pt_out, sizeof(ae_int16));
      ae_out = AE_SEL16_5432(ae_out, ae_out);
      AE_S16_0_I(ae_out, (ae_int16 *)pt_out, 2 * sizeof(ae_int16));
      break;
    default:
      break;
  }
#else
  for (int i = 0; i < size; ++i) {
    int32_t raw = (static_cast<int32_t>(input[i]) * window[i]) >> shift;
    if (raw < INT16_MIN) {
      output[i] = INT16_MIN;
    } else if (raw > INT16_MAX) {
      output[i] = INT16_MAX;
    } else {
      output[i] = static_cast<int16_t>(raw);
    }
  }
#endif
}
#ifndef REMOVE_TFLM_SIGNAL
}  // namespace tflm_signal
#endif