/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

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

// struct, global flag
#include <stdint.h>
#include <string.h>
//#define KN_DEBUG
#ifdef KN_DEBUG
#include <stdio.h>
#endif

#include "platform.h"

namespace tflite {
// namespace dmx1a{

// static uint32_t mappedCoeffFlag = 0;
// static uint8_t mappedOps[256] = {0};
// static unsigned int mappedOpsCount = 0;
int check_kn_tflite_model(const char *description, TfLiteContext *ctx) {
  //    printf("description: [%s]\n",model_description);
  if (!strncmp(description, KN_TFL_MODEL_NAME,
               KN_TFL_MODEL_LEN)) {  // TODO: get which operator index is mapped
    // dmx1AOptFlag = 0xff;
    int decimals[3] = {1, 10, 100};
    uint8_t *pMappedOps;  // = (uint8_t*)description+KN_TFL_MODEL_LEN;
    int idx = 0;
    // while(*pMappedOps != 0 && idx < 64)
    int opsLength = strlen(description);  // -KN_TFL_MODEL_LEN ;
    // printf("opsLength: %d\n",opsLength);

    // compare ARCH
    const char *current_arch_ptr = description + KN_TFL_MODEL_LEN + 1;
    // printf("current_aech_ptr: %s\n",current_arch_ptr);
    if (!strncmp(current_arch_ptr, KN_TFL_MODEL_ARCH_NAME,
                 KN_TFL_MODEL_ARCH_LEN) ||
        !strncmp(
            current_arch_ptr, KN_TFL_MODEL_ARCH_NAME2,
            KN_TFL_MODEL_ARCH_LEN)  // backword compatible hmd model if true
    )

    {
      pMappedOps = (uint8_t *)current_arch_ptr + opsLength - 1 -
                   KN_TFL_MODEL_ARCH_LEN - 1;
      int opNumber = 0;  // string to integer
      int parse_op_len =
          opsLength - (KN_TFL_MODEL_ARCH_LEN + KN_TFL_MODEL_LEN + 1);
      // while(*pMappedOps == '.') pMappedOps++;
      //       printf("parse_op_len: %d\n",parse_op_len);
      int dec = 0;
      // reverse tracking
      for (int l = 0; l < parse_op_len; pMappedOps--, l++) {
        if (*pMappedOps == '.') {
//    if (opNumber != 0)
#ifdef KN_DEBUG
          printf("Mapped[%d] = %d\n", idx, opNumber);
#endif
          ctx->mappedOps[idx++] = opNumber;
          dec = 0;
          opNumber = 0;
          continue;
          //  printf("Mapped[%d] = %d\n",idx, opNumber);
        }
        opNumber += (*pMappedOps - '0') * decimals[dec];
#ifdef KN_DEBUG
        printf("parsing = %c dec table: %d\n", *pMappedOps, decimals[dec]);
#endif
        dec++;
      }
    }
    ctx->mappedOpsCount = idx;
    return 0;
  } else {
    // reset mopedOps to zero
    memset(ctx->mappedOps, 0, sizeof(ctx->mappedOps));
    return -1;
  }
}

// before prepare
bool is_current_ops_coeffs_mapped(int opIdx, TfLiteContext *ctx) {
  bool result = false;

  ctx->mappedCoeffFlag = false;
  for (unsigned int ii = 0; ii < ctx->mappedOpsCount; ii++) {
    if (opIdx == ctx->mappedOps[ii]) {
      result = true;
#ifdef KN_DEBUG
      printf("MAPPED COEFFS %d, opIdx: %d\n", ii, opIdx);
#endif
      ctx->mappedCoeffFlag = true;
      break;
    }
  }
  return result;
}

bool is_coeffs_mapped(TfLiteContext *ctx) { return (ctx->mappedCoeffFlag); }

}  // namespace tflite