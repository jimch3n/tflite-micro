/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

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
#ifndef TENSORFLOW_LITE_MICRO_KERNELS_FULLY_CONNECTED_IA8201_H_
#define TENSORFLOW_LITE_MICRO_KERNELS_FULLY_CONNECTED_IA8201_H_

#include <cstdint>

#include "tensorflow/lite/micro/kernels/fully_connected.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {
typedef enum {
  FC_OPT_NONE = 0,
  FC_OPT_TYPE1 = 1,
  FC_OPT_TYPE2 = 2,  // input channel align 4
  FC_OPT_TYPE3 = 3,
  FC_OPT_TYPE4 = 4,

  // hybrid using MVMSINE MAP
  FC_OPT_FLT_X_INT8_MVM = 8,
} fc_opt_type;
struct OpDataFullyConnectedEx {
  // The scaling factor from input to output (aka the 'real multiplier') can
  // be represented as a fixed point multiplier plus a left shift.

  OpDataFullyConnected FcOp;

  int buffer_idx;
  int32_t *mapped_filter;  // aligned 4bytes, int8_t data to store pointer for
                           // mapping W
  AScalar outputMultipler;
  AScalar outputOffset;
  uint32_t input_offset_int8;
  int32_t *inputOffsetWithW;
  // int32_t filter_int8_exp;
  AScalar filter_scale;  // for quantized int8 weight
  int opt_constraint;    //
  int opt_constraint_float;

  // afloat converted buffer; for cannot convert inplace
  AScalar *weight_aflt;
  AScalar *bias_aflt;
};
// export Ex api
TfLiteStatus CalculateOpDataFullyConnected(TfLiteContext *context,
                             TfLiteFusedActivation activation,
                             TfLiteType data_type, const TfLiteTensor *input,
                             const TfLiteTensor *filter,
                             const TfLiteTensor *bias, TfLiteTensor *output,
                             OpDataFullyConnectedEx *data_ex);
void FullyConnectedParamsQuantized(const OpDataFullyConnectedEx& op_data_ex,
                                   FullyConnectedParams* op_param);

// eval quantized 8x8 with xor

int FullyConnectedKernel(int32_t *x, const int32_t *A, const AScalar *bias,
                         int8_t *output, int m, int n,
                         const AScalar &outOffsetFr32,
                         const uint32_t input_offset_int8x4,  // xor 128
                         const AScalar &outMultiplerFr32, int signs) ;

}  // namespace tflite

#endif  // TENSORFLOW_LITE_MICRO_KERNELS_FULLY_CONNECTED_H_
