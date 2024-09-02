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
#if defined(XTENSA) || defined(IA8201)
#include "tensorflow/lite/micro/ia8201/config.h"
#include "tensorflow/lite/micro/ia8201/debug_helper.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#endif

#include "signal/src/filter_bank_log.h"
#include "signal/src/log.h"
#ifndef REMOVE_TFLM_SIGNAL
namespace tflite {
namespace tflm_signal {
#endif
void FilterbankLog(const uint32_t* input, int num_channels,
                   int32_t output_scale, uint32_t correction_bits,
                   int16_t* output) {
  for (int i = 0; i < num_channels; ++i) {
    const uint32_t scaled = input[i] << correction_bits;
    if (scaled > 1) {
#if defined(SIG_FB_LOG_OPT)

      AScalar aflt = AScalar((int)scaled);
      AScalar ascale = AScalar(output_scale, 16);
      AScalar aflt_loge = aflt.f_log();
      AScalar log_out = aflt_loge * ascale;

      uint32_t log_value = log_out.to_int(16);

#else
      const uint32_t log_value = Log32(scaled, output_scale);
#endif
      output[i] = ((log_value < static_cast<uint32_t>(INT16_MAX))
                       ? log_value
                       : static_cast<uint32_t>(INT16_MAX));
    } else {
      output[i] = 0;
    }
  }
}
#ifndef REMOVE_TFLM_SIGNAL
}  // namespace tflm_signal
}  // namespace tflite
#endif