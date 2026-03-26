/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.

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

#ifndef TENSORFLOW_LITE_MICRO_KERNELS_IA8201_ACTIVATIONS_H_
#define TENSORFLOW_LITE_MICRO_KERNELS_IA8201_ACTIVATIONS_H_

#include "tensorflow/lite/micro/kernels/activations.h"
#include "AVL.h"
namespace tflite {

struct ReluOpDataEx {
  struct ReluOpData OpRelu;

  //AScalar input_multiplier_fr32;
  AScalar output_multiplier_fr32;

  AScalar input_offset_fr32;
  AScalar output_offset_fr32;

  int opt_constraint;
  int opt_constraint_float;
  AScalar output_activation_min_fr32;
  AScalar output_activation_max_fr32;

};

typedef enum {
  RELU_OPT_NONE = 0,
  RELU_OPT_TYPE1 = 1,  //,ELEMENT_WISE = 1,

} relu_opt_type;
void ReluQuantized(const ReluOpDataEx& data, const RuntimeShape& input_shape,
  const RuntimeShape& output_shape, const int8_t* input_data,
  int8_t* output_data);
void CalculateReluOpData(const TfLiteTensor* input, TfLiteTensor* output,
  ReluOpDataEx* data);
}  // namespace tflite

#endif  // TENSORFLOW_LITE_MICRO_KERNELS_ACTIVATIONS_H_
