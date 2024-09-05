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


// afloat opt for both core

#include "signal/src/filter_bank_square_root.h"
#include "signal/src/square_root.h"

#if defined(XTENSA) || defined(HMD1A)
#include "tensorflow/lite/micro/ia8201/config.h"
#ifdef __XTENSA__
#include <xtensa/config/core-isa.h>
#include <xtensa/tie/xt_core.h>
#include <xtensa/tie/xt_hifi3.h>
#include <xtensa/tie/xt_misc.h>
#endif
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"

#include "tensorflow/lite/micro/ia8201/debug_helper.h"
#endif

#ifndef REMOVE_TFLM_SIGNAL
namespace tflite {
namespace tflm_signal {
#endif
void FilterbankSqrt(const uint64_t* input, int num_channels,
                    int scale_down_bits, uint32_t* output) {
  for (int i = 0; i < num_channels; ++i) {
#if defined(SIG_FB_SQRT_OPT)
    int nsa = 32 - AE_NSA64(input[i]);

    if (nsa < 0) nsa = 0;
    {
      if (0 == (nsa & 1)) nsa += 1;  // MUST ODD
      uint32_t out = (uint32_t)(input[i] >> (nsa));

      int shift = (31 + nsa) >> 1;        //-nsa);
      AScalar ainput = AScalar(out, 31);  // q31

      AScalar asqrt_out = (ainput.f_sqrt());  //>>(scale_down_bits);

      output[i] = (asqrt_out.to_int(shift)) >> scale_down_bits;
    }

#else
    uint32_t sqrt_out = Sqrt64(input[i]);
    output[i] = sqrt_out >> scale_down_bits;
#endif
  }
}
#ifndef REMOVE_TFLM_SIGNAL
}  // namespace tflm_signal

}  // namespace tflite
#endif
