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

#ifndef TENSORFLOW_LITE_IA700_PLATFORM_H_
#define TENSORFLOW_LITE_IA700_PLATFORM_H_

#include "tensorflow/lite/c/common.h"

#define KN_TFL_MODEL_NAME "KTL"  // knowles Tensorflow
#define KN_TFL_MODEL_LEN 3

#ifdef HEMILITE
#define KN_TFL_MODEL_ARCH_NAME "hml"

#define KN_TFL_MODEL_ARCH_NAME2 "hmd"
#endif

#define KN_TFL_MODEL_ARCH_LEN 3

namespace tflite {
// namespace dmx1a{
int check_kn_tflite_model(const char *description, TfLiteContext *ctx);
bool is_coeffs_mapped(TfLiteContext *ctx);
bool is_current_ops_coeffs_mapped(int opIdx, TfLiteContext *ctx);
//	}
}  // namespace tflite
#endif