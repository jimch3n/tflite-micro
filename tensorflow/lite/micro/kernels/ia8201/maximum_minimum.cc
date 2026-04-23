/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

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
#include <type_traits> //type check
#include "tensorflow/lite/micro/ia8201/config.h"
#include "tensorflow/lite/micro/ia8201/debug_helper.h"
#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/maximum_minimum.h"
#endif
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {

namespace {

// This file has a reference implementation of TFMaximum/TFMinimum.
enum KernelType {
  kReference,
};

constexpr int kInputTensor1 = 0;
constexpr int kInputTensor2 = 1;
constexpr int kOutputTensor = 0;

typedef enum {
  MINMAX_OPT_NONE = 0,
  MINMAX_OPT_TYPE1 = 1,  //,ELEMENT_WISE = 1,
  MINMAX_OPT_TYPE2 = 2,  // INPUT1_LAST_EQ_INPUT2 size, input1 == output 1
  MINMAX_OPT_TYPE3 = 3   // input2 is constat value 1,
} minmax_opt_type;

struct OpDataMinMax {
#if 0
  int32_t output_activation_min;
  int32_t output_activation_max;

  int32_t output_multiplier;
  int output_shift;

  // Cached tensor zero point values for quantized operations.
  int32_t input1_zero_point;
  int32_t input2_zero_point;
  int32_t output_zero_point;
  //	AScalar input1_multiplier_fr32;
  //	AScalar input2_multiplier_fr32;
  AScalar output_multiplier_fr32;

  AScalar input1_offset_fr32;
  AScalar input2_offset_fr32;
  AScalar output_offset_fr32;
#endif
  int opt_constraint;
  int opt_constraint_float;
  //AScalar output_activation_min_fr32;
  //AScalar output_activation_max_fr32;
};

struct OpContext {
  OpContext(TfLiteContext* context, TfLiteNode* node) {
    input1 = tflite::micro::GetEvalInput(context, node, kInputTensor1);
    input2 = tflite::micro::GetEvalInput(context, node, kInputTensor2);
    output = tflite::micro::GetEvalOutput(context, node, kOutputTensor);
  }
  const TfLiteEvalTensor* input1;
  const TfLiteEvalTensor* input2;
  TfLiteEvalTensor* output;
};

struct MaximumOp {
  template <typename data_type>
  static data_type op(data_type el1, data_type el2) {
    return el1 > el2 ? el1 : el2;
  }
};

struct MinimumOp {
  template <typename data_type>
  static data_type op(data_type el1, data_type el2) {
    return el1 < el2 ? el1 : el2;
  }
};

template <typename data_type, typename op_type>
void TFLiteOperation(TfLiteContext* context, TfLiteNode* node,
                     const OpContext& op_context) {
  reference_ops::MaximumMinimumBroadcastSlow(
      tflite::micro::GetTensorShape(op_context.input1),
      tflite::micro::GetTensorData<data_type>(op_context.input1),
      tflite::micro::GetTensorShape(op_context.input2),
      tflite::micro::GetTensorData<data_type>(op_context.input2),
      tflite::micro::GetTensorShape(op_context.output),
      tflite::micro::GetTensorData<data_type>(op_context.output),
      op_type::template op<data_type>);
}

void* InitMinMax(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpDataMinMax));
}

template <typename OpType>
TfLiteStatus PrepareMinMax(TfLiteContext* context, TfLiteNode* node) {
  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input1 =
      micro_context->AllocateTempInputTensor(node, kInputTensor1);
  TF_LITE_ENSURE(context, input1 != nullptr);
  TfLiteTensor* input2 =
      micro_context->AllocateTempInputTensor(node, kInputTensor2);
  TF_LITE_ENSURE(context, input2 != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);

 // if (output->dims->size == 0) {
  //  return AllocateOutputDimensionsFromInput(context, input1, input2, output);
  //}

  //TFLITE_DCHECK(node->builtin_data != nullptr);
  //auto* params = reinterpret_cast<TfLiteMulParams*>(node->builtin_data);
  TFLITE_DCHECK(node->user_data != nullptr);
  OpDataMinMax* data = static_cast<OpDataMinMax*>(node->user_data);
  int input1_count = ElementCount(*input1->dims);
  int input2_count = ElementCount(*input2->dims);
  int output_count = ElementCount(*output->dims);
  KN_PRINTD(input1_count);
  KN_PRINTD(input2_count);
  KN_PRINTD(output_count);
  //CalculateOpData(context, node, params, data);

  data->opt_constraint = 0 ;// MUL_OPT_NONE;
  data->opt_constraint_float = 0; //MUL_OPT_NONE;
#if (defined(DMX1A_MINMAX_OPT) || defined(HMD1A_MINMAX_OPT))
  if (output->type == kTfLiteInt8) {
    // check in run time, broad cast

    //int input_shape0 = input1->dims->data[input1->dims->size - 1];  // Dims(0);
    if (input2_count == input1_count && input1_count == output_count) {
      data->opt_constraint = MINMAX_OPT_TYPE1;
    } /*else if (input_shape0 == input2_count && output_count == input1_count &&
               (input_shape0 & 3) == 0) {
      data->opt_constraint = MINMAX_OPT_TYPE2;  //

    } */
    else if (1 == input2_count && output_count == input1_count)
    {
      const TfLiteEvalTensor* inputEval2 =
        tflite::micro::GetEvalInput(context, node, kInputTensor2);
  const int8_t* input2_data =
    tflite::micro::GetTensorData<int8_t>(inputEval2);
      // check input2 is -128 in max, 127 in mini
  //std::is_same_v<OpType, MinimumOp>

  if ((std::is_same_v<OpType, MinimumOp> && input2_data[0] == 127) ||
    ((std::is_same_v<OpType, MaximumOp> && input2_data[0] == -128)))
  {
    KN_PRINTD(input2_data[0]);
   // FloatNulWithScalarBroadcast
    data->opt_constraint = MINMAX_OPT_TYPE3; //copy ?
  }
    }
  }
  // only min = -128 and max=127 acceptable for rnd_sat_pack

  KN_PRINTD(data->opt_constraint);
#if 0 //TODO Float32 
  if (data->opt_constraint) {
    // tflite::ConvertQ31ToAfloat(data->input1_multiplier,
    // data->input1_multiplier_fr32, 17);
    // tflite::ConvertQ31ToAfloat(data->input2_multiplier,
    // data->input2_multiplier_fr32,  17);
    tflite::ConvertQ31ToAfloat(data->output_multiplier,
                               data->output_multiplier_fr32,
                               7 + data->output_shift);  // 17);//-19
    // NOTE: Input offset is -zero_point for add offset
    tflite::ConvertQ31ToAfloat(-data->input1_zero_point,
                               data->input1_offset_fr32, 31 - 7);
    tflite::ConvertQ31ToAfloat(-data->input2_zero_point,
                               data->input2_offset_fr32, 31 - 7);
    tflite::ConvertQ31ToAfloat(data->output_zero_point,
                               data->output_offset_fr32, 31 - 7);
  }

  if (output->type == kTfLiteFloat32) {
    int input_shape0 = input1->dims->data[input1->dims->size - 1];
    if (input1_count == input2_count && input2_count == output_count) {
      data->opt_constraint_float = MUL_OPT_TYPE1;
    } else if (input_shape0 == input2_count && output_count == input1_count) {
      data->opt_constraint_float =
          MUL_OPT_TYPE2;  // 1: 1,1,3,64 , in2: 64, out: 1,3,64
    } else if (1 == input2_count && output_count == input1_count)

    {
      data->opt_constraint_float =
          MUL_OPT_TYPE3;  // FloatNulWithScalarBroadcast
    }
  }
#endif
#endif

  micro_context->DeallocateTempTfLiteTensor(input1);
  micro_context->DeallocateTempTfLiteTensor(input2);
  micro_context->DeallocateTempTfLiteTensor(output);

  return kTfLiteOk;
}
#if (defined(DMX1A_MINMAX_OPT)) 


void MinMaxQuantizedInt8(const OpDataMinMax* data, const int8_t* input1,
  const int8_t* input2, int8_t* output, int n, int minimum_flag) {
  vr128 vr_input1, vr_input2;
  vr128 vr_q7_out, vr_output;
  int loopLim = n >> 2;

  ulsr128 UR_input1, UR_input2;
  ulsr128 UR_output;

  UR_input1 = align_8x4_load(input1);
  UR_input2 = align_8x4_load(input2);
  UR_output = align_8x4_store(output);

  //load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);
  if (minimum_flag)
  {
    if (loopLim > 0) {
      load_8x4_vr_a(vr_input1, UR_input1, input1);
      convert_16I_to_32F_x4(vr_input1, 0);


      for (int ii = 0; ii < loopLim - 1; ii++) {
        load_8x4_vr_a(vr_input2, UR_input2, input2);
        convert_16I_to_32F_x4(vr_input2, 0);
        vr_output = vmin(vr_input1, vr_input2);
        convert_32F_to_16I_x4(vr_output, 0, 0);
        rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
        vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
        store_8x4_vr_a(vr_output, UR_output, output);
        load_8x4_vr_a(vr_input1, UR_input1, input1);
        convert_16I_to_32F_x4(vr_input1, 0);
      }
      load_8x4_vr_a(vr_input2, UR_input2, input2);
      convert_16I_to_32F_x4(vr_input2, 0);
      vr_output = vmin(vr_input1, vr_input2);
      convert_32F_to_16I_x4(vr_output, 0, 0);
      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
      vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
      store_8x4_vr_a(vr_output, UR_output, output);
      flush_8x4(UR_output, output);
    }
    // reminder
    if (n & 3) {
      load_8x4_vr_a(vr_input1, UR_input1, input1);

      convert_16I_to_32F_x4(vr_input1, 0);

      load_8x4_vr_a(vr_input2, UR_input2, input2);
      convert_16I_to_32F_x4(vr_input2, 0);
      vr_output = vmin(vr_input1, vr_input2);
      convert_32F_to_16I_x4(vr_output, 0, 0);
      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
      vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
      for (int32_t ii = 0; ii < (n & 3); ii++) {
        store8x1_vr_postI(vr_output, output, INC1, VRQ0);
        vr_output = vpermsi(vr_output, vr_output, 0, SHR_BY_1_ELEM);
      }
    }
  }
  else {
    // maximim
    if (loopLim > 0) {
      load_8x4_vr_a(vr_input1, UR_input1, input1);
      convert_16I_to_32F_x4(vr_input1, 0);


      for (int ii = 0; ii < loopLim - 1; ii++) {
        load_8x4_vr_a(vr_input2, UR_input2, input2);
        convert_16I_to_32F_x4(vr_input2, 0);
        vr_output = vmax(vr_input1, vr_input2);
        convert_32F_to_16I_x4(vr_output, 0, 0);
        rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
        vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
        store_8x4_vr_a(vr_output, UR_output, output);
        load_8x4_vr_a(vr_input1, UR_input1, input1);
        convert_16I_to_32F_x4(vr_input1, 0);
      }
      load_8x4_vr_a(vr_input2, UR_input2, input2);
      convert_16I_to_32F_x4(vr_input2, 0);
      vr_output = vmax(vr_input1, vr_input2);
      convert_32F_to_16I_x4(vr_output, 0, 0);
      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
      vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
      store_8x4_vr_a(vr_output, UR_output, output);
      flush_8x4(UR_output, output);
    }
    // reminder
    if (n & 3) {
      load_8x4_vr_a(vr_input1, UR_input1, input1);

      convert_16I_to_32F_x4(vr_input1, 0);

      load_8x4_vr_a(vr_input2, UR_input2, input2);
      convert_16I_to_32F_x4(vr_input2, 0);
      vr_output = vmax(vr_input1, vr_input2);
      convert_32F_to_16I_x4(vr_output, 0, 0);
      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
      vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
      for (int32_t ii = 0; ii < (n & 3); ii++) {
        store8x1_vr_postI(vr_output, output, INC1, VRQ0);
        vr_output = vpermsi(vr_output, vr_output, 0, SHR_BY_1_ELEM);
      }
    }
  }
}

#endif

#ifdef HMD1A_MINMAX_OPT

void MinMaxQuantizedInt8(const OpDataMinMax* data, const int8_t* input1,
                         const int8_t* input2, int8_t* output, int n,
                         int minimum_flag) {
  vr64 vr_input1, vr_input2;
  vr64 vr_q7_out, vr_output;
  int loopLim = n >> 1;

  if (minimum_flag) {
    if (loopLim > 0) {
      load8x2_vr_postI(vr_input1, input1, INC1);
      load8x2_vr_postI(vr_input2, input2, INC1);
      convert_16I_to_32F_x2(vr_input1, 0);
      convert_16I_to_32F_x2(vr_input2, 0);

      for (int ii = 0; ii < loopLim - 1; ii++) {
        vr_output = vmin(vr_input1, vr_input2);
        convert_32F_to_16I_x2(vr_output, 0, 0);
        rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
        store16x1_vr_postI(vr_q7_out, output, INC1, VRQ0);

        load8x2_vr_postI(vr_input1, input1, INC1);
        load8x2_vr_postI(vr_input2, input2, INC1);
        convert_16I_to_32F_x2(vr_input1, 0);
        convert_16I_to_32F_x2(vr_input2, 0);
      }
      vr_output = vmin(vr_input1, vr_input2);
      convert_32F_to_16I_x2(vr_output, 0, 0);
      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
      store16x1_vr_postI(vr_q7_out, output, INC1, VRQ0);
    }
    // reminder
    if (n & 1) {
      load8x1_vr_postI(vr_input1, input1, INC1, VRQ0);
      load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);
      convert_16I_to_32F_x2(vr_input1, 0);
      convert_16I_to_32F_x2(vr_input2, 0);
      vr_output = vmin(vr_input1, vr_input2);
      convert_32F_to_16I_x2(vr_output, 0, 0);
      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
      vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
      store8x1_vr_postI(vr_output, output, INC1, VRQ0);
    }
  } else {
    // maximum
    if (loopLim > 0) {
      load8x2_vr_postI(vr_input1, input1, INC1);
      load8x2_vr_postI(vr_input2, input2, INC1);
      convert_16I_to_32F_x2(vr_input1, 0);
      convert_16I_to_32F_x2(vr_input2, 0);

      for (int ii = 0; ii < loopLim - 1; ii++) {
        vr_output = vmax(vr_input1, vr_input2);
        convert_32F_to_16I_x2(vr_output, 0, 0);
        rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
        store16x1_vr_postI(vr_q7_out, output, INC1, VRQ0);

        load8x2_vr_postI(vr_input1, input1, INC1);
        load8x2_vr_postI(vr_input2, input2, INC1);
        convert_16I_to_32F_x2(vr_input1, 0);
        convert_16I_to_32F_x2(vr_input2, 0);
      }
      vr_output = vmax(vr_input1, vr_input2);
      convert_32F_to_16I_x2(vr_output, 0, 0);
      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
      store16x1_vr_postI(vr_q7_out, output, INC1, VRQ0);
    }
    // reminder
    if (n & 1) {
      load8x1_vr_postI(vr_input1, input1, INC1, VRQ0);
      load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);
      convert_16I_to_32F_x2(vr_input1, 0);
      convert_16I_to_32F_x2(vr_input2, 0);
      vr_output = vmax(vr_input1, vr_input2);
      convert_32F_to_16I_x2(vr_output, 0, 0);
      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
      vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
      store8x1_vr_postI(vr_output, output, INC1, VRQ0);
    }
  }
}

#endif

template <KernelType kernel_type, typename OpType>
TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  OpContext op_context(context, node);

#if (defined(DMX1A_MINMAX_OPT) || defined(HMD1A_MINMAX_OPT))
  const TfLiteEvalTensor* input1 =
    tflite::micro::GetEvalInput(context, node, kInputTensor1);
  const TfLiteEvalTensor* input2 =
    tflite::micro::GetEvalInput(context, node, kInputTensor2);
  TfLiteEvalTensor* output =
    tflite::micro::GetEvalOutput(context, node, kOutputTensor);
  const OpDataMinMax& data = *(static_cast<const OpDataMinMax*>(node->user_data));

#endif

  if (kernel_type == kReference) {
    switch (op_context.output->type) {
      case kTfLiteFloat32:
        KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input1),
          ElementCount(*input1->dims));
        KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input2),
          ElementCount(*input2->dims));
        TFLiteOperation<float, OpType>(context, node, op_context);
        KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
          ElementCount(*output->dims));

        break;
      case kTfLiteInt8:
#if (defined(DMX1A_MINMAX_OPT) || defined(HMD1A_MINMAX_OPT))

        if (data.opt_constraint != 0)
        {
          const int8_t* input1_data =
            tflite::micro::GetTensorData<int8_t>(input1);
          const int8_t* input2_data =
            tflite::micro::GetTensorData<int8_t>(input2);
          int8_t* output_data = tflite::micro::GetTensorData<int8_t>(output);
          int loop_count = tflite::micro::GetTensorShape(input1).FlatSize();

          MatchingElementsSize(tflite::micro::GetTensorShape(input1),
            tflite::micro::GetTensorShape(output));
          // input 1 (size) * scale (1) = output( size) , size equal
          if (data.opt_constraint == MINMAX_OPT_TYPE1) {

            MinMaxQuantizedInt8(&data, input1_data, input2_data, output_data,
              loop_count, std::is_same_v<OpType, MinimumOp> ? 1 : 0);
          }
          else if (data.opt_constraint == MINMAX_OPT_TYPE3)
          {
            // do we need this int8->int8 -128 ~ 127 already ?
            block_copy_bytes(output_data, input1_data, loop_count);
          }
        }
        else
#endif
        {
          TFLiteOperation<int8_t, OpType>(context, node, op_context);
        }
        KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
          ElementCount(*output->dims));

        break;
      case kTfLiteInt16:
        TFLiteOperation<int16_t, OpType>(context, node, op_context);
        break;
      case kTfLiteInt32:
        TFLiteOperation<int32_t, OpType>(context, node, op_context);
        break;
      case kTfLiteInt64:
        TFLiteOperation<int64_t, OpType>(context, node, op_context);
        break;
      default:
        MicroPrintf("Type %s (%d) is not supported by Maximum/Minimum.",
                    TfLiteTypeGetName(op_context.output->type),
                    op_context.output->type);
        return kTfLiteError;
    }
  } else {
    MicroPrintf("Kernel type not supported by Maximum/Minimum.");
    return kTfLiteError;
  }
  return kTfLiteOk;
}

}  // namespace

TFLMRegistration Register_MAXIMUM() {
  return tflite::micro::RegisterOp(InitMinMax, PrepareMinMax<MaximumOp>,
                                   Eval<kReference, MaximumOp>
   // EvalMinimum,
  );
}

TFLMRegistration Register_MINIMUM() {
  return tflite::micro::RegisterOp(InitMinMax, PrepareMinMax< MinimumOp>,
                                   Eval<kReference, MinimumOp>
 // EvalMaximum
    );
}

}  // namespace tflite
