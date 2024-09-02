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
//#define KN_DEBUG

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/fully_connected.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/fully_connected.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/ia8201/fully_connected.h" //keep at last
#include "tensorflow/lite/micro/ia8201/debug_helper.h"
namespace tflite {

const int kFullyConnectedInputTensor = 0;
const int kFullyConnectedWeightsTensor = 1;
const int kFullyConnectedBiasTensor = 2;
const int kFullyConnectedOutputTensor = 0;

FullyConnectedParams FullyConnectedParamsQuantized(
    const OpDataFullyConnected& op_data) {
  FullyConnectedParams op_params;
  op_params.input_offset = -op_data.input_zero_point;
  op_params.weights_offset = -op_data.filter_zero_point;
  op_params.output_offset = op_data.output_zero_point;
  op_params.output_multiplier = op_data.output_multiplier;
  op_params.output_shift = op_data.output_shift;
  op_params.quantized_activation_min = op_data.output_activation_min;
  op_params.quantized_activation_max = op_data.output_activation_max;
  return op_params;
}
void FullyConnectedParamsQuantized(
    const OpDataFullyConnectedEx& op_data, FullyConnectedParams *op_params) {
  
  op_params->mapped_filter     = op_data.mapped_filter; // remap address
  op_params->input_offset_int8 = op_data.input_offset_int8;
  op_params->inputOffsetWithW  = op_data.inputOffsetWithW;
  op_params->outputMultipler   = *(uint32_t *)&op_data.outputMultipler;
  op_params->outputOffset       = *(uint32_t *)&op_data.outputOffset;
  op_params->opt_constraint     = op_data.opt_constraint;
  op_params->bias_aflt          = (uint32_t *)op_data.bias_aflt;
}

FullyConnectedParams FullyConnectedParamsFloat(
    TfLiteFusedActivation activation) {
  FullyConnectedParams op_params;
  CalculateActivationRange(activation, &op_params.float_activation_min,
                           &op_params.float_activation_max);
  return op_params;
}
#if 1
TfLiteStatus CalculateOpDataFullyConnected(
    TfLiteContext* context, TfLiteFusedActivation activation,
    TfLiteType data_type, const TfLiteTensor* input, const TfLiteTensor* filter,
    const TfLiteTensor* bias, TfLiteTensor* output,
    OpDataFullyConnected* data) {
  // OpDataFullyConnected* data_ex = data_e
  if (data_type != kTfLiteFloat32) {
    double real_multiplier = 0.0;
    TF_LITE_ENSURE_STATUS(GetQuantizedConvolutionMultipler(
        context, input, filter, bias, output, &real_multiplier));
    QuantizeMultiplier(real_multiplier, &data->output_multiplier,
                       &data->output_shift);

    // afloat
    //->outputMultipler = AScalar(data->output_multiplier);
    // Filter weights will always be symmetric quantized since we only support
    // int8 quantization. See
    // https://github.com/tensorflow/tensorflow/issues/44912 for additional
    // context.
    TFLITE_DCHECK(filter->params.zero_point == 0);

    data->input_zero_point = input->params.zero_point;
    data->filter_zero_point = filter->params.zero_point;
    data->output_zero_point = output->params.zero_point;

    return CalculateActivationRangeQuantized(context, activation, output,
                                             &data->output_activation_min,
                                             &data->output_activation_max);
  }
  return kTfLiteOk;
}
#endif

// ext version 

TfLiteStatus CalculateOpDataFullyConnected(TfLiteContext *context,
                             TfLiteFusedActivation activation,
                             TfLiteType data_type, const TfLiteTensor *input,
                             const TfLiteTensor *filter,
                             const TfLiteTensor *bias, TfLiteTensor *output,
                             OpDataFullyConnectedEx *data_ex) {
  TfLiteStatus status = kTfLiteOk;
  OpDataFullyConnected *data = &data_ex->FcOp;
  // Set buffer index to a reset value
  data_ex->buffer_idx = -1;
  if (data_type != kTfLiteFloat32) {
    double real_multiplier = 0.0;
    TF_LITE_ENSURE_STATUS(GetQuantizedConvolutionMultipler(
        context, input, filter, bias, output, &real_multiplier));
    int exponent;
    data_ex->outputMultipler = AScalar(real_multiplier);  // convert to afloat
    QuantizeMultiplier(real_multiplier, &data->output_multiplier, &exponent);

    // Work around for Int16 use reference ops
    data->output_shift = exponent;  //-exponent;
    TF_LITE_ENSURE_STATUS(CalculateActivationRangeQuantized(
        context, activation, output, &data->output_activation_min,
        &data->output_activation_max));

    data->input_zero_point = input->params.zero_point;
    data->filter_zero_point = filter->params.zero_point;
    data->output_zero_point = output->params.zero_point;

    return CalculateActivationRangeQuantized(context, activation, output,
                                             &data->output_activation_min,
                                             &data->output_activation_max);
    //#endif
  }
  return status;
}
}  // namespace tflite
