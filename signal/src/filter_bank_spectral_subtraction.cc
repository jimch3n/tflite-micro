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


#if defined(XTENSA) || defined(HMD1A)
#include "tensorflow/lite/micro/ia8201/config.h"
#ifdef __XTENSA__
#include <xtensa/config/core-isa.h>
#include <xtensa/tie/xt_core.h>
#include <xtensa/tie/xt_hifi3.h>
#include <xtensa/tie/xt_misc.h>
#else
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#endif
#include "tensorflow/lite/micro/ia8201/debug_helper.h"
#endif
#include "signal/src/filter_bank_spectral_subtraction.h"


#ifndef REMOVE_TFLM_SIGNAL

namespace tflite {
namespace tflm_signal {
#endif
void FilterbankSpectralSubtraction(const SpectralSubtractionConfig* config,
                                   const uint32_t* input, uint32_t* output,
                                   uint32_t* noise_estimate) {
  const bool data_clamping = config->clamping;
  const int smoothing_bits = config->smoothing_bits;
  const int num_channels = config->num_channels;
#if defined(SIG_FB_SS_OPT)

  int spectral_subtraction_bits = config->spectral_subtraction_bits;

  ae_int32x2 ae_input;
  ae_int16x4 ae_smooth, ae_asmooth;

  // ae_int32x2 t1 = AE_MOVDA32X2(config->alternate_smoothing,
  // config->smoothing);
  ae_smooth = AE_MOVDA16X2(config->smoothing, config->one_minus_smoothing);
  ae_asmooth = AE_MOVDA16X2(config->alternate_smoothing,
                            config->alternate_one_minus_smoothing);

  ae_int16x4 ae_min_sig =
      AE_MOVDA16X2(config->min_signal_remaining, config->min_signal_remaining);

  ae_int32x2* pInput = (ae_int32x2*)input;
  ae_int32x2* pNoiseEst = (ae_int32x2*)noise_estimate;
  ae_int32x2* pNoiseEst1 = (ae_int32x2*)noise_estimate;
  ae_int32x2* pOutput = (ae_int32x2*)output;

  ae_valign va_input, va_ns0, va_ns1, va_output;

  va_input = AE_LA64_PP(pInput);
  va_ns0 = AE_LA64_PP(pNoiseEst);
  va_ns1 = AE_ZALIGN64();
  va_output = AE_ZALIGN64();

  AE_LA32X2_IP(ae_input, va_input, pInput);
  for (int i = 0; i<(num_channels >> 1); i++) {
    ae_int32x2 ae_noise_est;
    ae_int64 ae_ns_out0, ae_ns_out1;
    AE_LA32X2_IP(ae_noise_est, va_ns0, pNoiseEst);

    // R[0] =  EVEN => input[0] * smoth[0] + noise[0] * oms[1]
    // R[1] = ODD => input[1] * asmoth[0] + noise[1] * aoms[1]
    ae_int32x2 ae_scale_up_input = AE_SLAA32(ae_input, smoothing_bits);

    ae_int32x2 ae_even = AE_SEL32_HH(ae_noise_est, ae_scale_up_input);
    ae_int32x2 ae_odd = AE_SEL32_LL(ae_noise_est, ae_scale_up_input);

    ae_ns_out0 = AE_MULZAAD32X16_H0_L1(ae_even, ae_smooth);

    ae_ns_out1 = AE_MULZAAD32X16_H0_L1(ae_odd, ae_asmooth);
    ae_int32x2 ae_ns_out = AE_TRUNCA32X2F64S(ae_ns_out0, ae_ns_out1,
                                             32 - spectral_subtraction_bits);

    ae_int32x2 ae_ns_out_max = AE_MAX32(ae_scale_up_input, ae_ns_out);

    xtbool2 xt_b = AE_LE32(ae_scale_up_input, ae_ns_out);  // input <= ns
    AE_MOVT32X2(ae_ns_out, ae_ns_out_max, XT_AND(data_clamping, xt_b));

    AE_SA32X2_IP(ae_ns_out, va_ns1, pNoiseEst1);

    // Scale up signal[i] for smoothing filter computation.
    // const uint32_t signal_scaled_up = input[i] << smoothing_bits;
    // noise_estimate[i] =
    //     ((static_cast<uint64_t>(signal_scaled_up) * smoothing) +
    //      (static_cast<uint64_t>(noise_estimate[i]) * one_minus_smoothing)) >>
    //    config->spectral_subtraction_bits;

    ae_int64 ae_f0 = AE_MUL32X16_H0(ae_input, ae_min_sig);  // right shift
    ae_int64 ae_f1 = AE_MUL32X16_L0(ae_input, ae_min_sig);
    ae_int32x2 ae_floor =
        AE_TRUNCA32X2F64S(ae_f0, ae_f1, 32 - spectral_subtraction_bits);

    ae_int32x2 ae_subtracted = AE_SUB32(ae_scale_up_input, ae_ns_out);
    ae_subtracted = AE_SRAA32(ae_subtracted, smoothing_bits);

    ae_int32x2 ae_output = AE_MAX32(ae_subtracted, ae_floor);
    AE_SA32X2_IP(ae_output, va_output, pOutput);

    AE_LA32X2_IP(ae_input, va_input, pInput);
  }

  AE_SA64POS_FP(va_ns1, pNoiseEst1);
  AE_SA64POS_FP(va_output, pOutput);

#else
  for (int i = 0; i < num_channels; ++i) {
    uint32_t smoothing;
    uint32_t one_minus_smoothing;
    if ((i & 1) == 0) {
      smoothing = config->smoothing;
      one_minus_smoothing = config->one_minus_smoothing;
    } else {  // Use alternate smoothing coefficient on odd-index channels.
      smoothing = config->alternate_smoothing;
      one_minus_smoothing = config->alternate_one_minus_smoothing;
    }

    // Scale up signal[i] for smoothing filter computation.
    const uint32_t signal_scaled_up = input[i] << smoothing_bits;
    noise_estimate[i] =
        ((static_cast<uint64_t>(signal_scaled_up) * smoothing) +
         (static_cast<uint64_t>(noise_estimate[i]) * one_minus_smoothing)) >>
        config->spectral_subtraction_bits;

    uint32_t estimate_scaled_up = noise_estimate[i];
    // Make sure that we can't get a negative value for the signal - estimate.
    if (estimate_scaled_up > signal_scaled_up) {
      estimate_scaled_up = signal_scaled_up;
      if (data_clamping) {
        noise_estimate[i] = estimate_scaled_up;
      }
    }
    const uint32_t floor =
        (static_cast<uint64_t>(input[i]) * config->min_signal_remaining) >>
        config->spectral_subtraction_bits;
    const uint32_t subtracted =
        (signal_scaled_up - estimate_scaled_up) >> smoothing_bits;
    output[i] = subtracted > floor ? subtracted : floor;
  }
#endif
}
#ifndef REMOVE_TFLM_SIGNAL
}  // namespace tflm_signal
}  // namespace tflite
#endif
