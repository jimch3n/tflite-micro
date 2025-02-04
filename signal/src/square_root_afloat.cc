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


#include "signal/src/filter_bank_square_root.h"
#include "signal/src/square_root.h"

#if defined(XTENSA) || defined(IA8201)
#include "tensorflow/lite/micro/ia8201/config.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#include "tensorflow/lite/micro/ia8201/debug_helper.h"
#if defined(HMD1A) && defined(__XTENSA__)
#include <xtensa/config/core-isa.h>
#include <xtensa/tie/xt_core.h>
#include <xtensa/tie/xt_hifi3.h>
#include <xtensa/tie/xt_misc.h>
#endif


#elif defined(IA700)
#include "tensorflow/lite/micro/ia700/config.h"
#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
#include "tensorflow/lite/micro/ia700/debug_helper.h"
#endif
 
namespace tflite {
//#ifndef REMOVE_TFLM_SIGNAL
namespace tflm_signal {
//#endif
uint32_t SqrtAfloat(uint64_t num) {    
    
    int nsa = 32 - AE_NSA64(num);
    uint32_t square_root_out = 0;
    if (nsa < 0) 
        nsa = 0;
    {
      if (0 == (nsa & 1)) nsa += 1;  // MUST ODD
      uint32_t out = (uint32_t)(num >> (nsa));

      int shift = (31 + nsa) >> 1;        //-nsa);
      AScalar ainput = AScalar(out, 31);  // q31

      AScalar asqrt_out = (ainput.f_sqrt());  //>>(scale_down_bits);


    square_root_out = (asqrt_out.to_int(shift));
      //output[i] = (asqrt_out.to_int(shift)) >> scale_down_bits;
    }
    return square_root_out;
}
//#ifndef REMOVE_TFLM_SIGNAL
}
//#endif
}