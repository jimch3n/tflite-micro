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
#ifndef TENSORFLOW_LITE_IA8201_H_
#define TENSORFLOW_LITE_IA8201_H_
#if defined(DMX1A)
// optimization macros
#define DMX1A_CONV_OPT      // convolution
#define DMX1A_DW_CONV_OPT   // depthwise_conv
#define DMX1A_FC_OPT        // fully_connected
#define DMX1A_MEAN_OPT      // reduce_mean
#define DMX1A_REDUCE_MAX_OPT //reduce_max

#define DMX1A_SUM_OPT // reduce sum
#define DMX1A_SOFTMAX_OPT   // softmax
#define DMX1A_QUANTIZE_OPT  // quantize
#define DMX1A_DEQUANTIZE_OPT // dequantize
#define DMX1A_RESHAPE_OPT   // reshape
#define DMX1A_POOL_OPT      // pooling
#define DMX1A_ADD_OPT       // add
#define DMX1A_MUL_OPT       // mul
#define DMX1A_LOGISTIC_OPT  // logistic
#define DMX1A_SVDF_OPT      // svdf
#define DMX1A_TANH_OPT  // tanh

#define DMX1A_L2NORM_OPT //l2norm

#define DMX1A_STRIDED_SLICE_OPT //strided_slice
#define DMX1A_CONCATENATION_OPT // concatenation
#define DMX1A_SUB_OPT //sub
#define DMX1A_SQUARED_DIFF_OPT //squared_difference float only
// element wise
#define DMX1A_SQRT_OPT
#define DMX1A_RSQRT_OPT
#define DMX1A_SQUARE_OPT

// unidirectional_lstm_sequence
#define DMX1A_LSTM_OPT

// signal kernel optimization
//#define SIG_FB_LOG_OPT   //afloat
//#define SIG_FB_SQRT_OPT  //afloat

#elif defined(HMD1A)

#define HMD1A_CONV_OPT     // convolution
#define HMD1A_DW_CONV_OPT  // depthwise_conv
#define HMD1A_FC_OPT       // fully_connnected
#define HMD1A_MEAN_OPT     // reduce_mean
#define HMD1A_REDUCE_MAX_OPT //reduce_max
#define HMD1A_SUM_OPT         // reduce sum TODO 

#define HMD1A_SOFTMAX_OPT   // softmax
#define HMD1A_QUANTIZE_OPT  // quantize
#define HMD1A_DEQUANTIZE_OPT //dequantize
#define HMD1A_RESHAPE_OPT   // reshape
#define HMD1A_POOL_OPT      // pooling
#define HMD1A_ADD_OPT       // add
#define HMD1A_MUL_OPT       // mul
#define HMD1A_LOGISTIC_OPT  // logistic
#define HMD1A_SVDF_OPT      // svdf
#define HMD1A_TANH_OPT  // tanh

#define HMD1A_STRIDED_SLICE_OPT //strided_slice
#define HMD1A_CONCATENATION_OPT // concatenation

// element wise
#define HMD1A_SQRT_OPT
#define HMD1A_RSQRT_OPT
#define HMD1A_SQUARE_OPT
#define HMD1A_SUB_OPT
#define HMD1A_SQUARED_DIFF_OPT //squared_difference float only
// unidirectional_lstm_sequence
#define HMD1A_LSTM_OPT

// signal kernel optimization
//#define SIG_FB_LOG_OPT   // afloat 
#define SIG_FB_SQRT_OPT  // afloat
#define SIG_ENERGY_OPT   // hifi only
#define SIG_FB_SS_OPT    // hifi only 
#define SIG_FB_OPT       // hifi only
#define SIG_WINDOW_OPT   // hifi only
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

// use Afloat operation to conver parameter for quazation or replacing floating point function to saving code size
#define KN_TFLITE_AFLOAT

// tflite float 16 default conversion
#define TF_FLT16_SIGN 1
#define TF_FLT16_EXP  5
#define TF_FLT16_BIAS 14
//#define RND_NEGATIVE
// for dump correct float
#define TF_LITE_ENSURE_NEAR_AFLOAT(context, a, b, epsilon)                          \
  do {                                                                       \
    AScalar delta = ((a) > (b)) ? ((a) - (b)) : ((b) - (a));                    \
    if (delta > epsilon) {                                                   \
      TF_LITE_KERNEL_LOG((context), "%s:%d %s not near %s (%f != %f)",       \
                         __FILE__, __LINE__, #a, #b, (a).to_double(), \
                         (b).to_double());                            \
      return kTfLiteError;                                                   \
    }                                                                        \
  } while (0)
  
#endif
