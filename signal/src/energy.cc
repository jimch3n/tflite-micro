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
#include "signal/src/complex.h"
#include "signal/src/energy.h"


#ifndef REMOVE_TFLM_SIGNAL
namespace tflite {
namespace tflm_signal {
#endif
void SpectrumToEnergy(const Complex<int16_t> *input, int start_index,
                      int end_index, uint32_t *output) {
#if defined(SIG_ENERGY_OPT)
  int n;
  int N = (end_index - start_index) << 1;  // complex
  // int rsh = 0;
  // ae_f64      vaf;
  ae_int64 vzi;
  ae_int16x4 vxh;
  ae_f24x2 vxf;
  ae_int32x2 vxw, vzw, vzw0, vzw1;
  ae_valign x_align, y_align;
  const ae_int16x4 *px = (const ae_int16x4 *)&input[start_index];
  ae_int32x2 *py = (ae_int32x2 *)&output[start_index];

  vzi = AE_ZERO64();
  vzw = AE_MOVINT32X2_FROMINT64(vzi);

  x_align = AE_LA64_PP(px);
  y_align = AE_ZALIGN64();

  AE_LA16X4_IP(vxh, x_align, px);

  for (n = 0; n < N - 3; n += 4) {
    vxw = AE_SEXT32X2D16_32(vxh);
    vxf = AE_MOVF24X2_FROMINT32X2(vxw);
    vxw = AE_MULP24X2(vxf, vxf);
    vzw0 = AE_ADD32_HL_LH(vxw, vxw);
    vxw = AE_SEXT32X2D16_10(vxh);
    vxf = AE_MOVF24X2_FROMINT32X2(vxw);
    vxw = AE_MULP24X2(vxf, vxf);
    vzw1 = AE_ADD32_HL_LH(vxw, vxw);
    vzw = AE_SEL32_LH(vzw0, vzw1);
    AE_SA32X2_IP(vzw, y_align, py);

    AE_LA16X4_IP(vxh, x_align, px);
  }
  AE_SA64POS_FP(y_align, py);
  switch (N & 3) {
    case 2:
      vxw = AE_SEXT32X2D16_32(vxh);
      vxf = AE_MOVF24X2_FROMINT32X2(vxw);
      vxw = AE_MULP24X2(vxf, vxf);

      vzw = AE_ADD32_HL_LH(vxw, vxw);
      AE_S32_L_I(vzw, (ae_int32 *)py, 0);

      break;
  }

#else
  for (int i = start_index; i < end_index; i++) {
    const int16_t real = input[i].real;  // 15 bits
    const int16_t imag = input[i].imag;  // 15 bits
    // 31 bits
    output[i] = (static_cast<int32_t>(real) * real) +
                (static_cast<int32_t>(imag) * imag);
  }

#endif
}
#ifndef REMOVE_TFLM_SIGNAL
}  // namespace tflm_signal
}  // namespace tflite
#endif
