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
#ifdef IA8201
#include "tensorflow/lite/micro/ia8201/config.h"
#elif defined(IA700)
#include "tensorflow/lite/micro/ia700/config.h"
#endif
#include "tensorflow/lite/micro/kernels/conv_test.h"
#ifdef IA8201
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#elif defined(IA700)
#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
#endif
namespace tflite {
namespace testing {

template <typename T>
TfLiteStatus InvokeConv(TfLiteTensor* tensors, int tensors_size,
                        int output_length, TfLiteConvParams* conv_params,
                        TFLMRegistration registration, T* output_data) {
  int inputs_array_data[] = {3, 0, 1, 2};
  TfLiteIntArray* inputs_array = IntArrayFromInts(inputs_array_data);
  int outputs_array_data[] = {1, 3};
  TfLiteIntArray* outputs_array = IntArrayFromInts(outputs_array_data);

  micro::KernelRunner runner(registration, tensors, tensors_size, inputs_array,
                             outputs_array, conv_params);

  const char* init_data = reinterpret_cast<const char*>(conv_params);
  TfLiteStatus status = runner.InitAndPrepare(init_data);
  if (status != kTfLiteOk) {
    return status;
  }
  return runner.Invoke();
}

template <typename T>
TfLiteStatus ValidateConvGoldens(TfLiteTensor* tensors, int tensors_size,
                                 const T* expected_output_data,
                                 int output_length,
                                 TfLiteConvParams* conv_params,
                                 TFLMRegistration registration, T* output_data,
                                 float tolerance) {
  TfLiteStatus status = InvokeConv(tensors, tensors_size, output_length,
                                   conv_params, registration, output_data);
  if (status != kTfLiteOk) {
    return status;
  }
  for (int i = 0; i < output_length; ++i) {
    TF_LITE_MICRO_EXPECT_NEAR(expected_output_data[i], output_data[i],
                              tolerance);
  }
  return kTfLiteOk;
}

TfLiteStatus InvokeConv(TfLiteTensor* tensors, int tensors_size,
                        int output_length, TfLiteConvParams* conv_params,
                        TFLMRegistration registration, float* output_data) {
  return InvokeConv<float>(tensors, tensors_size, output_length, conv_params,
                           registration, output_data);
}

TfLiteStatus InvokeConv(TfLiteTensor* tensors, int tensors_size,
                        int output_length, TfLiteConvParams* conv_params,
                        TFLMRegistration registration, int8_t* output_data) {
  return InvokeConv<int8_t>(tensors, tensors_size, output_length, conv_params,
                            registration, output_data);
}

TfLiteStatus ValidateConvGoldens(TfLiteTensor* tensors, int tensors_size,
                                 const float* expected_output_data,
                                 int output_length,
                                 TfLiteConvParams* conv_params,
                                 TFLMRegistration registration,
                                 float* output_data, float tolerance) {
  return ValidateConvGoldens<float>(tensors, tensors_size, expected_output_data,
                                    output_length, conv_params, registration,
                                    output_data, tolerance);
}

TfLiteStatus ValidateConvGoldens(TfLiteTensor* tensors, int tensors_size,
                                 const int8_t* expected_output_data,
                                 int output_length,
                                 TfLiteConvParams* conv_params,
                                 TFLMRegistration registration,
                                 int8_t* output_data, float tolerance) {
  return ValidateConvGoldens<int8_t>(
      tensors, tensors_size, expected_output_data, output_length, conv_params,
      registration, output_data, tolerance);
}

TfLiteStatus TestConvFloat(int* input_dims_data, const float* input_data,
                           int* filter_dims_data, const float* filter_data,
                           int* bias_dims_data, const float* bias_data,
                           int* output_dims_data,
                           const float* expected_output_data,
                           TfLiteConvParams* conv_params,
                           TFLMRegistration registration, float* output_data) {
  TfLiteIntArray* input_dims = IntArrayFromInts(input_dims_data);
  TfLiteIntArray* filter_dims = IntArrayFromInts(filter_dims_data);
  TfLiteIntArray* bias_dims = IntArrayFromInts(bias_dims_data);
  TfLiteIntArray* output_dims = IntArrayFromInts(output_dims_data);
  const int output_dims_count = ElementCount(*output_dims);
  constexpr int inputs_size = 3;
  constexpr int outputs_size = 1;
  constexpr int tensors_size = inputs_size + outputs_size;
  TfLiteTensor tensors[tensors_size] = {
      CreateTensor(input_data, input_dims),
      CreateTensor(filter_data, filter_dims),
      CreateTensor(bias_data, bias_dims),
      CreateTensor(output_data, output_dims),
  };

  return ValidateConvGoldens(tensors, tensors_size, expected_output_data,
                             output_dims_count, conv_params, registration,
                             output_data);
}
#if defined(IA8201) || defined(IA700)
TfLiteStatus TestConvFloat16(int* input_dims_data, const float* input_data,
                             int* filter_dims_data, const float* filter_data,
                             int* bias_dims_data, const float* bias_data,
                             int* output_dims_data,
                             const float* expected_output_data,
                             TfLiteConvParams* conv_params,
                             TFLMRegistration registration,
                             float* output_data) {
  TfLiteIntArray* input_dims = IntArrayFromInts(input_dims_data);
  TfLiteIntArray* filter_dims = IntArrayFromInts(filter_dims_data);
  TfLiteIntArray* bias_dims = IntArrayFromInts(bias_dims_data);
  TfLiteIntArray* output_dims = IntArrayFromInts(output_dims_data);
  const int output_dims_count = ElementCount(*output_dims);
  constexpr int inputs_size = 3;
  constexpr int outputs_size = 1;
  constexpr int tensors_size = inputs_size + outputs_size;

  TfLiteFloat16 filter16_data[1024];
  convert_ieee_float_to_afloat16(filter_data, (uint16_t*)filter16_data,
                                 ElementCount(*filter_dims));

  TfLiteTensor tensors[tensors_size] = {
      CreateTensor(input_data, input_dims),
      CreateTensor(filter16_data, filter_dims),
      CreateTensor(bias_data, bias_dims),
      CreateTensor(output_data, output_dims),
  };

  return ValidateConvGoldens(tensors, tensors_size, expected_output_data,
                             output_dims_count, conv_params, registration,
                             output_data);
}
TfLiteStatus TestConvFloatInt8(int* input_dims_data, const float* input_data,
                               int* filter_dims_data, const float* filter_data,
                               int* bias_dims_data, const float* bias_data,
                               int* output_dims_data,
                               const float* expected_output_data,
                               TfLiteConvParams* conv_params,
                               TFLMRegistration registration,
                               float* output_data) {
  TfLiteIntArray* input_dims = IntArrayFromInts(input_dims_data);
  TfLiteIntArray* filter_dims = IntArrayFromInts(filter_dims_data);
  TfLiteIntArray* bias_dims = IntArrayFromInts(bias_dims_data);
  TfLiteIntArray* output_dims = IntArrayFromInts(output_dims_data);
  const int output_dims_count = ElementCount(*output_dims);
  constexpr int inputs_size = 3;
  constexpr int outputs_size = 1;
  constexpr int tensors_size = inputs_size + outputs_size;

  int8_t filter_int8_data[1024];
  float scale;
  convert_ieee_float_to_int8_scale(filter_data, filter_int8_data, &scale,
                                   ElementCount(*filter_dims));

  TfLiteTensor tensors[tensors_size] = {
      CreateTensor(input_data, input_dims),
      CreateTensor(filter_int8_data, filter_dims),
      CreateTensor(bias_data, bias_dims),
      CreateTensor(output_data, output_dims),
  };
  // set scale in param;
  tensors[1].params.scale = scale;
  tensors[1].params.zero_point = 0;
  // allow toralence 0.07
  float tolerance = 0.3;
  return ValidateConvGoldens(tensors, tensors_size, expected_output_data,
                             output_dims_count, conv_params, registration,
                             output_data, tolerance);
}
#endif

template <typename T, typename BiasT>
TfLiteStatus TestConvQuantizedPerChannel(
    int* input_dims_data, const float* input_data, T* input_quantized,
    float input_scale, int input_zero_point, int* filter_dims_data,
    const float* filter_data, int8_t* filter_data_quantized,
    int* bias_dims_data, const float* bias_data, BiasT* bias_data_quantized,
    float* bias_scales, int* bias_zero_points, int* output_dims_data,
    const float* expected_output_data, T* expected_output_data_quantized,
    float output_scale, int output_zero_point, TfLiteConvParams* conv_params,
    TFLMRegistration registration, T* output_data,
    TfLiteType tensor_weight_type = kTfLiteNoType) {
  TfLiteIntArray* input_dims = IntArrayFromInts(input_dims_data);
  TfLiteIntArray* filter_dims = IntArrayFromInts(filter_dims_data);
  TfLiteIntArray* bias_dims = IntArrayFromInts(bias_dims_data);
  TfLiteIntArray* output_dims = IntArrayFromInts(output_dims_data);
  const int output_dims_count = ElementCount(*output_dims);

  int filter_zero_points[5];
  float filter_scales[5];
  TfLiteAffineQuantization filter_quant;
  TfLiteAffineQuantization bias_quant;
  TfLiteTensor input_tensor = CreateQuantizedTensor(
      input_data, input_quantized, input_dims, input_scale, input_zero_point);
  TfLiteTensor filter_tensor = CreateSymmetricPerChannelQuantizedTensor(
      filter_data, filter_data_quantized, filter_dims, filter_scales,
      filter_zero_points, &filter_quant, 0 /* quantized dimension */, false,
      tensor_weight_type);
  TfLiteTensor bias_tensor = CreatePerChannelQuantizedBiasTensor(
      bias_data, bias_data_quantized, bias_dims, input_scale, &filter_scales[1],
      bias_scales, bias_zero_points, &bias_quant, 0 /* quantized dimension */);
  TfLiteTensor output_tensor = CreateQuantizedTensor(
      output_data, output_dims, output_scale, output_zero_point);

  float input_scales[] = {1, input_scale};
  int input_zero_points[] = {1, input_zero_point};
  TfLiteAffineQuantization input_quant = {FloatArrayFromFloats(input_scales),
                                          IntArrayFromInts(input_zero_points),
                                          0};
  input_tensor.quantization = {kTfLiteAffineQuantization, &input_quant};

  float output_scales[] = {1, output_scale};
  int output_zero_points[] = {1, output_zero_point};
  TfLiteAffineQuantization output_quant = {FloatArrayFromFloats(output_scales),
                                           IntArrayFromInts(output_zero_points),
                                           0};
  output_tensor.quantization = {kTfLiteAffineQuantization, &output_quant};

  constexpr int inputs_size = 3;
  constexpr int outputs_size = 1;
  constexpr int tensors_size = inputs_size + outputs_size;
  TfLiteTensor tensors[tensors_size] = {
      input_tensor,
      filter_tensor,
      bias_tensor,
      output_tensor,
  };

  tflite::Quantize(expected_output_data, expected_output_data_quantized,
                   output_dims_count, output_scale, output_zero_point);
  return ValidateConvGoldens(
      tensors, tensors_size, expected_output_data_quantized, output_dims_count,
      conv_params, registration, output_data, 1.0 /* tolerance */);
}

// Test conv with int8 input, int8 weight, int32 bias, int32 accumulator
TfLiteStatus TestConvQuantizedPerChannel(
    int* input_dims_data, const float* input_data, int8_t* input_quantized,
    float input_scale, int input_zero_point, int* filter_dims_data,
    const float* filter_data, int8_t* filter_data_quantized,
    int* bias_dims_data, const float* bias_data, int32_t* bias_data_quantized,
    float* bias_scales, int* bias_zero_points, int* output_dims_data,
    const float* expected_output_data, int8_t* expected_output_data_quantized,
    float output_scale, int output_zero_point, TfLiteConvParams* conv_params,
    TFLMRegistration registration, int8_t* output_data,
    TfLiteType tensor_weight_type) {
  return TestConvQuantizedPerChannel<int8_t, int32_t>(
      input_dims_data, input_data, input_quantized, input_scale,
      input_zero_point, filter_dims_data, filter_data, filter_data_quantized,
      bias_dims_data, bias_data, bias_data_quantized, bias_scales,
      bias_zero_points, output_dims_data, expected_output_data,
      expected_output_data_quantized, output_scale, output_zero_point,
      conv_params, registration, output_data, tensor_weight_type);
}

// Test conv with int16 input, int8 weight, int64 bias, int64 accumulator
TfLiteStatus TestConvQuantizedPerChannel(
    int* input_dims_data, const float* input_data, int16_t* input_quantized,
    float input_scale, int input_zero_point, int* filter_dims_data,
    const float* filter_data, int8_t* filter_data_quantized,
    int* bias_dims_data, const float* bias_data,
    std::int64_t* bias_data_quantized, float* bias_scales,
    int* bias_zero_points, int* output_dims_data,
    const float* expected_output_data, int16_t* expected_output_data_quantized,
    float output_scale, int output_zero_point, TfLiteConvParams* conv_params,
    TFLMRegistration registration, int16_t* output_data) {
  return TestConvQuantizedPerChannel<int16_t, std::int64_t>(
      input_dims_data, input_data, input_quantized, input_scale,
      input_zero_point, filter_dims_data, filter_data, filter_data_quantized,
      bias_dims_data, bias_data, bias_data_quantized, bias_scales,
      bias_zero_points, output_dims_data, expected_output_data,
      expected_output_data_quantized, output_scale, output_zero_point,
      conv_params, registration, output_data);
}

// Test conv with int16 input, int8 weight, int32 bias, int32 accumulator
TfLiteStatus TestConvQuantizedPerChannel(
    int* input_dims_data, const float* input_data, int16_t* input_quantized,
    float input_scale, int input_zero_point, int* filter_dims_data,
    const float* filter_data, int8_t* filter_data_quantized,
    int* bias_dims_data, const float* bias_data, int32_t* bias_data_quantized,
    float* bias_scales, int* bias_zero_points, int* output_dims_data,
    const float* expected_output_data, int16_t* expected_output_data_quantized,
    float output_scale, int output_zero_point, TfLiteConvParams* conv_params,
    TFLMRegistration registration, int16_t* output_data) {
  return TestConvQuantizedPerChannel<int16_t, int32_t>(
      input_dims_data, input_data, input_quantized, input_scale,
      input_zero_point, filter_dims_data, filter_data, filter_data_quantized,
      bias_dims_data, bias_data, bias_data_quantized, bias_scales,
      bias_zero_points, output_dims_data, expected_output_data,
      expected_output_data_quantized, output_scale, output_zero_point,
      conv_params, registration, output_data);
}

}  // namespace testing
}  // namespace tflite
