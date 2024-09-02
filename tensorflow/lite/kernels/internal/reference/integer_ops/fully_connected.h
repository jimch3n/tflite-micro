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
#ifndef TENSORFLOW_LITE_KERNELS_INTERNAL_REFERENCE_INTEGER_OPS_FULLY_CONNECTED_H_
#define TENSORFLOW_LITE_KERNELS_INTERNAL_REFERENCE_INTEGER_OPS_FULLY_CONNECTED_H_

#include <algorithm>
//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#endif
#include "tensorflow/lite/kernels/internal/common.h"

namespace tflite {
namespace reference_integer_ops {

// For per-channel functions, since it is defined in quantization spec that
// weights are symmetric
// (https://www.tensorflow.org/lite/performance/quantization_spec#symmetric_vs_asymmetric),
// zero_point (params.weights_offset) is always 0.
// However, for per-tensor functions, params.weights_offset is still applied for
// backward compatibility.
template <typename InputType, typename WeightType, typename OutputType,
          typename BiasType>
void FullyConnectedPerChannel(
    const FullyConnectedParams& params, const int32_t* output_multiplier,
    const int* output_shift, const RuntimeShape& input_shape,
    const InputType* input_data, const RuntimeShape& filter_shape,
    const WeightType* filter_data, const RuntimeShape& bias_shape,
    const BiasType* bias_data, const RuntimeShape& output_shape,
    OutputType* output_data) {
  const int32_t input_offset = params.input_offset;
  const int32_t output_offset = params.output_offset;
  const int32_t output_activation_min = params.quantized_activation_min;
  const int32_t output_activation_max = params.quantized_activation_max;
  TFLITE_DCHECK_GE(filter_shape.DimensionsCount(), 2);
  TFLITE_DCHECK_EQ(output_shape.DimensionsCount(), 2);

  TFLITE_DCHECK_LE(output_activation_min, output_activation_max);
  const int filter_dim_count = filter_shape.DimensionsCount();
  const int batches = output_shape.Dims(0);
  const int output_depth = output_shape.Dims(1);
  TFLITE_DCHECK_LE(output_depth, filter_shape.Dims(filter_dim_count - 2));
  const int accum_depth = filter_shape.Dims(filter_dim_count - 1);
  for (int b = 0; b < batches; ++b) {
    for (int out_c = 0; out_c < output_depth; ++out_c) {
      BiasType acc = 0;
      for (int d = 0; d < accum_depth; ++d) {
        int32_t input_val = input_data[b * accum_depth + d];
        int32_t filter_val = filter_data[out_c * accum_depth + d];
        acc += filter_val * (input_val + input_offset);
      }
      if (bias_data) {
        acc += bias_data[out_c];
      }
      int32_t acc_scaled = MultiplyByQuantizedMultiplier(
          acc, output_multiplier[out_c], output_shift[out_c]);
      acc_scaled += output_offset;
      acc_scaled = std::max(acc_scaled, output_activation_min);
      acc_scaled = std::min(acc_scaled, output_activation_max);
      output_data[out_c + output_depth * b] =
          static_cast<OutputType>(acc_scaled);
    }
  }
}

template <typename InputType, typename WeightType, typename OutputType,
          typename BiasType>
void FullyConnected(const FullyConnectedParams& params,
                    const RuntimeShape& input_shape,
                    const InputType* input_data,
                    const RuntimeShape& filter_shape,
                    const WeightType* filter_data,
                    const RuntimeShape& bias_shape, const BiasType* bias_data,
                    const RuntimeShape& output_shape, OutputType* output_data) {
  const int32_t input_offset = params.input_offset;
  const int32_t filter_offset = params.weights_offset;
  const int32_t output_offset = params.output_offset;
  const int32_t output_multiplier = params.output_multiplier;
  const int output_shift = params.output_shift;
  const int32_t output_activation_min = params.quantized_activation_min;
  const int32_t output_activation_max = params.quantized_activation_max;
  TFLITE_DCHECK_GE(filter_shape.DimensionsCount(), 2);
  TFLITE_DCHECK_GE(output_shape.DimensionsCount(), 1);

  TFLITE_DCHECK_LE(output_activation_min, output_activation_max);
  const int filter_dim_count = filter_shape.DimensionsCount();
  const int output_dim_count = output_shape.DimensionsCount();
  const int batches = FlatSizeSkipDim(output_shape, output_dim_count - 1);
  const int output_depth = output_shape.Dims(output_dim_count - 1);
  TFLITE_DCHECK_LE(output_depth, filter_shape.Dims(filter_dim_count - 2));
  const int accum_depth = filter_shape.Dims(filter_dim_count - 1);
#ifdef DEBUG
  int debug_lb = 0;
  int debug_up = debug_lb+4;
  int dbg_scale = 1;
  if (128==input_offset)
  {
      dbg_scale = 2;
  }else{
      dbg_scale = 4;
  }
#endif
  for (int b = 0; b < batches; ++b) {
    for (int out_c = 0; out_c < output_depth; ++out_c) {
      BiasType acc = 0;
      #ifdef DEBUG
   int dbg_flag =  out_c >= debug_lb && out_c < debug_up;
   #endif
      for (int d = 0; d < accum_depth; ++d) {
        int32_t input_val = input_data[b * accum_depth + d];
        int32_t filter_val = filter_data[out_c * accum_depth + d];
#ifdef DEBUG
        BiasType acc_o = acc;
        #endif
        acc += (filter_val + filter_offset) * (input_val + input_offset);
#ifdef DEBUG
    if(dbg_flag)
    {        
      printf("acc %08x (scale:%d) = %08x + (filter[%3d] %02x + offset %d) * (input[%3d] %02x + offset %d)\n ", 
    acc*dbg_scale,dbg_scale, acc_o,  //acc, scale, 08x
            out_c * accum_depth + d, filter_val&0xff, filter_offset, //filter
            b * accum_depth + d, input_val&0xff, input_offset);
    }
        #endif
      }
#ifdef DEBUG
      BiasType acc_o = acc;
#endif
      if (bias_data) {

        acc += bias_data[out_c];
#ifdef DEBUG
        if (dbg_flag)
          printf("Bias acc[%3d ] %d = %d + bias_data: %d\n", out_c, acc, acc_o,
                 bias_data[out_c]);
#endif
      }

      int32_t acc_scaled =
          MultiplyByQuantizedMultiplier(acc, output_multiplier, output_shift);

#ifdef DEBUG
    if(dbg_flag)
      printf("Scale acc[%3d ] = %d multipiler:%d shift:%d\n", out_c,
             acc_scaled, output_multiplier,
              output_shift);
#endif
      acc_scaled += output_offset;

#ifdef DEBUG
    if(dbg_flag)
      printf("Out offset acc[%3d ] %d = + output_offset: %d\n", out_c,
             acc_scaled, output_offset);
#endif
      acc_scaled = std::max(acc_scaled, output_activation_min);
      acc_scaled = std::min(acc_scaled, output_activation_max);

#ifdef DEBUG
    if(dbg_flag)
      printf("Min/Max  acc[%3d ] %d = min/max: %dd  %d\n", out_c,
             acc_scaled,
             output_activation_min, output_activation_max);
#endif
      output_data[out_c + output_depth * b] =
          static_cast<OutputType>(acc_scaled);

#ifdef DEBUG
    if(dbg_flag)
      printf("Final acc[%3d ] = %d  \n", out_c + output_depth * b,
             output_data[out_c + output_depth * b]);
#endif
    }
  }
}

}  // namespace reference_integer_ops
}  // namespace tflite

#endif  // TENSORFLOW_LITE_KERNELS_INTERNAL_REFERENCE_INTEGER_OPS_FULLY_CONNECTED_H_
