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
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#include "tensorflow/lite/micro/kernels/ia8201/activations.h"

#define USE_RND_SAT_PACK 1
namespace tflite {
namespace {

void* ReluInit(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(ReluOpDataEx));
}
#if defined (DMX1A_RELU_OPT)

// TODO: VIP
void ReluQuantizedInt8Sat(const ReluOpDataEx* data, const int8_t* input1,
 int8_t* output, int n) {
  vr128 vr_input1;
  int loopLim = n >> 2;
  //
  // ulsr128 ur_input1, ur_input2;

  vr128 vr_offset1;
  // vr128 vr_multiplier_input1, vr_multiplier_input2;
  vr128 vr_multiplier_output;
  vr128 vr_output_offset;
  vr128 vr_shift_input1;
  vr128  vr_output, vr_q7_out;
  ulsr128 UR_input1;
  ulsr128 UR_output;

  replicate_ar(vr_offset1, 0xf, data->input_offset_fr32.fr);  // Afloat
  //replicate_ar(vr_offset2, 0xf, data->input2_offset_fr32.fr);
  replicate_ar(vr_output_offset, 0xf, data->output_offset_fr32.fr);
  // replicate_ar(vr_multiplier_input1, 0xf, data->input1_multiplier_fr32);
  // replicate_ar(vr_multiplier_input2, 0xf, data->input2_multiplier_fr32);

  replicate_ar(vr_multiplier_output, 0xf, data->output_multiplier_fr32.fr);

  UR_input1 = align_8x4_load(input1);
 // UR_input2 = align_8x4_load(input2);

  UR_output = align_8x4_store(output);
  if (loopLim > 0) {
    load_8x4_vr_a(vr_input1, UR_input1, input1);
    //load_8x4_vr_a(vr_input2, UR_input2, input2);

    convert_16I_to_32F_x4(vr_input1, 0);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      //convert_16I_to_32F_x4(vr_input2, 0);
      // add offset each input
      // q7*1<<left
      vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
      //vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

      //vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

      // align to integer type: 14
      vr_output =
        vmacs_adj(vr_output_offset, vr_shift_input1, vr_multiplier_output, 0, 0);
      // convert to 8 bit rndsat-back
      convert_32F_to_16I_x4(vr_output, 0, 1);
#if USE_RND_SAT_PACK
      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
      vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
      store_8x4_vr_a(vr_output, UR_output, output);
#else
      store_8x4_vr_a(vr_output, UR_output, output);
#endif
      // store32x1_vr_postI(vr_q7_out, output, INC1, VRQ0);
      load_8x4_vr_a(vr_input1, UR_input1, input1);
      //load_8x4_vr_a(vr_input2, UR_input2, input2);
      convert_16I_to_32F_x4(vr_input1, 0);
    }
    //convert_16I_to_32F_x4(vr_input2, 0);
    // add offset each input
    // q7*1<<left
    vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
    //vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

   // vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

    // align to integer type: 14
    vr_output =
      vmacs_adj(vr_output_offset, vr_shift_input1, vr_multiplier_output, 0, 0);
    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x4(vr_output, 0, 1);
#if USE_RND_SAT_PACK
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);

    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
    store_8x4_vr_a(vr_output, UR_output, output);
#else
    store_8x4_vr_a(vr_output, UR_output, output);
#endif
    flush_8x4(UR_output, output);
  }
  // reminder
  if (n & 3) {
    load_8x4_vr_a(vr_input1, UR_input1, input1);
   // load_8x4_vr_a(vr_input2, UR_input2, input2);

    convert_16I_to_32F_x4(vr_input1, 0);
    //convert_16I_to_32F_x4(vr_input2, 0);
    // add offset each input
    // q7*1<<left
    vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
    //vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

   // vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

    // align to integer type: 14
    vr_output =
      vmacs_adj(vr_output_offset, vr_shift_input1, vr_multiplier_output, 0, 0);
    // convert to 8 bit rndsat-back

    convert_32F_to_16I_x4(vr_output, 0, 1);
#if USE_RND_SAT_PACK
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
#endif
    for (int32_t ii = 0; ii < (n & 3); ii++) {
      store8x1_vr_postI(vr_output, output, INC1, VRQ0);
      vr_output = vpermsi(vr_output, vr_output, 0, SHR_BY_1_ELEM);
    }
  }
}

#endif
TfLiteStatus ReluEval(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  const ReluOpDataEx& data_ex = *(static_cast<const ReluOpDataEx*>(node->user_data));
  //const ReluOpData& data = data_ex.OpRelu;
  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kActivationsInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kActivationsOutputTensor);

  switch (input->type) {
    case kTfLiteFloat32: {
      ReluFloat(tflite::micro::GetTensorShape(input),
                tflite::micro::GetTensorData<float>(input),
                tflite::micro::GetTensorShape(output),
                tflite::micro::GetTensorData<float>(output));

      return kTfLiteOk;
    }
    case kTfLiteInt8: {
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input),
        ElementCount(*input->dims));
#if defined(DMX1A_RELU_OPT)
      if (data_ex.opt_constraint == RELU_OPT_TYPE1)
      {
        //TODO
        ReluQuantizedInt8Sat(&data_ex, 
          tflite::micro::GetTensorData<int8_t>(input),
          tflite::micro::GetTensorData<int8_t>(output),
          MatchingElementsSize(tflite::micro::GetTensorShape(input),
            tflite::micro::GetTensorShape(output)));

      }
      else 
#endif
      {

        tflite::ReluQuantized(data_ex, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int8_t>(input),
          tflite::micro::GetTensorData<int8_t>(output));
      }
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
        ElementCount(*output->dims));

      return kTfLiteOk;
    }
    default: {
      MicroPrintf("Only float32 is supported currently, got %s",
                  TfLiteTypeGetName(input->type));
      return kTfLiteError;
    }
  }
}

void* Relu6Init(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(Relu6OpData));
}

TfLiteStatus Relu6Eval(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);

  const Relu6OpData& data = *(static_cast<const Relu6OpData*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kActivationsInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kActivationsOutputTensor);

  switch (input->type) {
    case kTfLiteFloat32: {
      Relu6Float(tflite::micro::GetTensorShape(input),
                 tflite::micro::GetTensorData<float>(input),
                 tflite::micro::GetTensorShape(output),
                 tflite::micro::GetTensorData<float>(output));

      return kTfLiteOk;
    }
    case kTfLiteInt8: {
      Relu6Quantized<int8_t>(data.zero, data.six,
                             tflite::micro::GetTensorShape(input),
                             tflite::micro::GetTensorData<int8_t>(input),
                             tflite::micro::GetTensorShape(output),
                             tflite::micro::GetTensorData<int8_t>(output));
      return kTfLiteOk;
    }
    case kTfLiteInt16: {
      Relu6Quantized<int16_t>(data.zero, data.six,
                              tflite::micro::GetTensorShape(input),
                              tflite::micro::GetTensorData<int16_t>(input),
                              tflite::micro::GetTensorShape(output),
                              tflite::micro::GetTensorData<int16_t>(output));
      return kTfLiteOk;
    }
    default: {
      MicroPrintf("Only float32 is supported currently, got %s",
                  TfLiteTypeGetName(input->type));
      return kTfLiteError;
    }
  }
}

}  // namespace

TFLMRegistration Register_RELU() {
  return tflite::micro::RegisterOp(ReluInit, ReluPrepare, ReluEval);
}

TFLMRegistration Register_RELU6() {
  return tflite::micro::RegisterOp(Relu6Init, Relu6Prepare, Relu6Eval);
}

}  // namespace tflite
