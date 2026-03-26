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

#include <algorithm>
#include <cstdint>
//#define KN_DEBUG

#include "tensorflow/lite/micro/ia8201/config.h"
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/internal/types.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#include "tensorflow/lite/micro/kernels/ia8201/activations.h"

namespace tflite {

const int kActivationsInputTensor = 0;
const int kActivationsOutputTensor = 0;

void ReluQuantized(const ReluOpDataEx& data_ex, const RuntimeShape& input_shape,
                   const RuntimeShape& output_shape, const int8_t* input_data,
                   int8_t* output_data) {
  const ReluOpData& data = data_ex.OpRelu;
  const int flat_size = MatchingFlatSize(input_shape, output_shape);

  KN_PRINTD(data.params.input_offset);
  KN_PRINTD(data.params.output_multiplier);
  KN_PRINTD(data.params.output_offset);
  KN_PRINTD(data.params.output_shift);
  KN_PRINTX(data.params.quantized_activation_min);
  KN_PRINTX(data.params.quantized_activation_max);
  for (int i = 0; i < flat_size; ++i) {
    const int32_t val = static_cast<int32_t>(input_data[i]);
    KN_PRINTD(val); KN_PRINTD(i);
    int32_t clamped =
        data.params.output_offset +
        MultiplyByQuantizedMultiplier(val - data.params.input_offset,
                                      data.params.output_multiplier,
                                      data.params.output_shift);
    KN_PRINTD(clamped);
    clamped = std::max(data.params.quantized_activation_min, clamped);
    clamped = std::min(data.params.quantized_activation_max, clamped);
    KN_PRINTD(clamped);
    output_data[i] = static_cast<int8_t>(clamped);
    KN_PRINTD(output_data[i]);
  }
}

template <typename T>
void CalculateReluOpData(const TfLiteTensor* input, TfLiteTensor* output,
                         ReluOpDataEx* data_ex) {

  ReluOpData* data = &data_ex->OpRelu;
  float act_min = 0.0;
  float act_max = std::numeric_limits<float>::infinity();
  double real_multiplier =
      static_cast<double>(input->params.scale / output->params.scale);

  const RuntimeShape input_shape = GetTensorShape(input);
  const RuntimeShape output_shape = GetTensorShape(output);

  QuantizeMultiplier(real_multiplier, &data->params.output_multiplier,
                     &data->params.output_shift);

  data->params.quantized_activation_min = std::max(
      static_cast<int32_t>(std::numeric_limits<T>::min()),
      output->params.zero_point +
          static_cast<int32_t>(roundf(act_min / output->params.scale)));
  data->params.quantized_activation_max =
      act_max == std::numeric_limits<float>::infinity()
          ? static_cast<int32_t>(std::numeric_limits<T>::max())
          : std::min(static_cast<int32_t>(std::numeric_limits<T>::max()),
                     output->params.zero_point +
                         static_cast<int32_t>(
                             roundf(act_max / output->params.scale)));
  data->params.input_offset = input->params.zero_point;
  data->params.output_offset = output->params.zero_point;
}

void ReluFloat(const RuntimeShape& input_shape, const float* input_data,
               const RuntimeShape& output_shape, float* output_data) {
  const int flat_size = MatchingFlatSize(input_shape, output_shape);
  for (int i = 0; i < flat_size; ++i) {
    const float val = input_data[i];
    const float lower = 0.0f;
    const float clamped = val < lower ? lower : val;
    output_data[i] = clamped;
  }
}

void Relu6Float(const RuntimeShape& input_shape, const float* input_data,
                const RuntimeShape& output_shape, float* output_data) {
  const int flat_size = MatchingFlatSize(input_shape, output_shape);
  for (int i = 0; i < flat_size; ++i) {
    const float val = input_data[i];
    const float upper = 6.0f;
    const float lower = 0.0f;
    const float clamped = val > upper ? upper : val < lower ? lower : val;
    output_data[i] = clamped;
  }
}

TfLiteStatus ReluPrepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  ReluOpDataEx* data_ex = static_cast<ReluOpDataEx*>(node->user_data);
  ReluOpData* data = &data_ex->OpRelu; //static_cast<ReluOpDataEx*>(node->user_data);
  MicroContext* micro_context = GetMicroContext(context);
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kActivationsInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kActivationsOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);

  int input_count = ElementCount(*input->dims);
  int output_count = ElementCount(*output->dims);

  if (input->type == kTfLiteInt8) {
    CalculateReluOpData<int8_t>(input, output, data_ex);
  }
  data_ex->opt_constraint = 0;
  data_ex->opt_constraint_float = 0;
#if (defined(DMX1A_RELU_OPT) || defined(HMD1A_RELU_OPT))

  //data->input_zero_point = input->params.zero_point;
  //data->output_zero_point = output->params.zero_point;

  if (output->type == kTfLiteInt8) {
    if (input_count == output_count) {
      data_ex->opt_constraint = RELU_OPT_TYPE1;
    }

    // only min = -128 and max=127 acceptable for rnd_sat_pack

    KN_PRINTD(data->params.quantized_activation_min);
    KN_PRINTD(data->params.quantized_activation_max);
    KN_PRINTD(data_ex->opt_constraint);
    if (data_ex->opt_constraint) {
      //tflite::ConvertQ31ToAfloat(data->input_multiplier,
      //data->input_multiplier_fr32, 17);
     // tflite::ConvertQ31ToAfloat(data->input2_multiplier,
     // data->input2_multiplier_fr32,  17);
      tflite::ConvertQ31ToAfloat(data->params.output_multiplier,
        data_ex->output_multiplier_fr32,
        data->params.output_shift);  // 17);//-19
  // NOTE: Input offset is -zero_point for add offset
      tflite::ConvertQ31ToAfloat(-data->params.input_offset,
       data_ex->input_offset_fr32, 31 - 7);

      tflite::ConvertQ31ToAfloat(data->params.output_offset,
        data_ex->output_offset_fr32, 31 -7);//SINCE NO MUL, KEEP Qformat
      KN_PRINTF(data_ex->output_multiplier_fr32);
      KN_PRINTF(data_ex->input_offset_fr32);
      KN_PRINTF(data_ex->output_offset_fr32);
    }


  }
#if 0
  if (output->type == kTfLiteFloat32) {
    int input_shape0 = input1->dims->data[input1->dims->size - 1];
    if (input1_count == input2_count && input2_count == output_count) {
      data->opt_constraint_float = RELU_OPT_TYPE1;
    }
    else if (input_shape0 == input2_count && output_count == input1_count) {
      data->opt_constraint_float =
        RELU_OPT_TYPE2;  // 1: 1,1,3,64 , in2: 64, out: 1,3,64
    }
    else if (1 == input2_count && output_count == input1_count)

    {
      data->opt_constraint_float =
        RELU_OPT_TYPE3;  // FloatNulWithScalarBroadcast
    }
  }


#endif
#endif

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);

  return kTfLiteOk;
}

TfLiteStatus Relu6Prepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);

  Relu6OpData* data = static_cast<Relu6OpData*>(node->user_data);

  MicroContext* micro_context = GetMicroContext(context);
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kActivationsInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);

  if (input->type == kTfLiteInt8) {
    data->zero = input->params.zero_point;
    data->six = FloatToQuantizedType<int8_t>(6.0f, input->params.scale,
                                             input->params.zero_point);
    TF_LITE_ENSURE(context, data->six >= INT8_MIN && data->six <= INT8_MAX);
  } else if (input->type == kTfLiteInt16) {
    data->zero = input->params.zero_point;
    data->six = FloatToQuantizedType<int16_t>(6.0f, input->params.scale,
                                              input->params.zero_point);
    TF_LITE_ENSURE(context, data->six >= INT16_MIN && data->six <= INT16_MAX);
  }

  micro_context->DeallocateTempTfLiteTensor(input);

  return kTfLiteOk;
}

}  // namespace tflite
