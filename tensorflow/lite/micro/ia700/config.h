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
#ifndef TENSORFLOW_LITE_IA700_H_
#define TENSORFLOW_LITE_IA700_H_

#if defined(HEMILITE)

#define HEMILITE_CONV_OPT        // convolution
#define HEMILITE_DW_CONV_OPT     // depthwise_conv
#define HEMILITE_FC_OPT          // fully_connnected
#define HEMILITE_MEAN_OPT        // reduce_mean
#define HEMILITE_REDUCE_MAX_OPT  // reduce_max

#define HEMILITE_SOFTMAX_OPT        // softmax
#define HEMILITE_QUANTIZE_OPT       // quantize
#define HEMILITE_DEQUANTIZE_OPT     // dequantize
#define HEMILITE_RESHAPE_OPT        // reshape
#define HEMILITE_POOL_OPT           // pooling
#define HEMILITE_ADD_OPT            // add
#define HEMILITE_MUL_OPT            // mul
#define HEMILITE_LOGISTIC_OPT       // logistic
#define HEMILITE_SVDF_OPT           // svdf
#define HEMILITE_TANH_OPT           // tanh
#define HEMILITE_STRIDED_SLICE_OPT  // stridedSlice
#define HEMILITE_PACK_OPT           // pack
#define HEMILITE_SPLITV_OPT         // split_v
#define HEMILITE_UNPACK_OPT         // unpack
#define HEMILITE_SUM_OPT            // reduce sum

#define HEMILITE_CONCATENATION_OPT  // concatenation

#define HEMILITE_L2NORM_OPT
#define HEMILITE_SUB_OPT
#define HEMILITE_ELEMENTWISE_OPT

//#define HEMILITE_SQRT_OPT
//#define HEMILITE_RSQRT_OPT
//#define HEMILITE_SQUARE_OPT
//#define HEMILITE_SUB_OPT
#define HEMILITE_SQUARED_DIFF_OPT  // squared_difference float only

#endif

// compile-out unused code, use for carefully
// remove unsupport input data type ops to save code size
//#define REMOVE_FLOAT_SUPPORT
//#define REMOVE_UINT8_SUPPORT
//#define REMOVE_INT16_SUPPORT

// NOTE: this remove cause kernel unit_test fail, only for known condition
//#define REMOVE_REFOP_SUPPORT // reference ops int8_t type without optimization
//#define REMOVE_REFOP_SUPPORT_INT8
//#define inline

// use Afloat operation to conver parameter for quazation or replacing floating
// point function to saving code size
#define KN_TFLITE_AFLOAT

// tflite float 16 default conversion
#define TF_FLT16_SIGN 1
#define TF_FLT16_EXP 5
#define TF_FLT16_BIAS 14
//#define RND_NEGATIVE
// for dump correct float
#define TF_LITE_ENSURE_NEAR_AFLOAT(context, a, b, epsilon)             \
  do {                                                                 \
    AScalar delta = ((a) > (b)) ? ((a) - (b)) : ((b) - (a));           \
    if (delta > epsilon) {                                             \
      TF_LITE_KERNEL_LOG((context), "%s:%d %s not near %s (%f != %f)", \
                         __FILE__, __LINE__, #a, #b, (a).to_double(),  \
                         (b).to_double());                             \
      return kTfLiteError;                                             \
    }                                                                  \
  } while (0)

#endif
