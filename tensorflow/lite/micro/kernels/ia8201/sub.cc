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
//#define KN_DEBUG
#include "tensorflow/lite/micro/ia8201/config.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/sub.h"
#endif
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/process_broadcast_shapes.h"
#endif
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/internal/types.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/sub.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {
// namespace ops {
// namespace micro {
// namespace sub {

// constexpr int kSubInputTensor1 = 0;
// constexpr int kSubInputTensor2 = 1;
// constexpr int kSubOutputTensor = 0;

struct OpData {
  OpDataSub SubOp;

  AScalar input1_multiplier_fr32;
  AScalar input2_multiplier_fr32;
  AScalar output_multiplier_fr32;

  AScalar input1_offset_fr32;
  AScalar input2_offset_fr32;
  AScalar output_offset_fr32;

  int opt_constraint;
  int opt_constraint_float;
};

TfLiteStatus CalculateOpData(TfLiteContext* context, TfLiteSubParams* params,
                             const TfLiteTensor* input1,
                             const TfLiteTensor* input2, TfLiteTensor* output,
                             OpData* data_ex) {
  OpDataSub* data = static_cast<OpDataSub*>(&data_ex->SubOp);
  data->requires_broadcast = !HaveSameShapes(input1, input2);

  if (output->type == kTfLiteInt8 || output->type == kTfLiteInt16) {
    // 8bit -> 8bit general quantized path, with general rescalings
    data->input1_offset = -input1->params.zero_point;
    data->input2_offset = -input2->params.zero_point;
    data->output_offset = output->params.zero_point;

    // The shift is set to 15 in case of 16-bit and 20 in case of 8-bit,
    // accordingly. In case of 16-bit we have 65535 << 15 which is less than 1
    // << 31, therefore the addition will still fit in a 32 bit accumulator.
    data->left_shift = output->type == kTfLiteInt16 ? 15 : 20;
    const float twice_max_input_scale =
        2 * std::max(input1->params.scale, input2->params.scale);
    const double real_input1_multiplier =
        static_cast<double>(input1->params.scale / twice_max_input_scale);
    const double real_input2_multiplier =
        static_cast<double>(input2->params.scale / twice_max_input_scale);
    const double real_output_multiplier =
        static_cast<double>(twice_max_input_scale /
                            ((1 << data->left_shift) * output->params.scale));

    QuantizeMultiplierSmallerThanOneExp(
        real_input1_multiplier, &data->input1_multiplier, &data->input1_shift);

    QuantizeMultiplierSmallerThanOneExp(
        real_input2_multiplier, &data->input2_multiplier, &data->input2_shift);

    QuantizeMultiplierSmallerThanOneExp(
        real_output_multiplier, &data->output_multiplier, &data->output_shift);

    TF_LITE_ENSURE_STATUS(CalculateActivationRangeQuantized(
        context, params->activation, output, &data->output_activation_min,
        &data->output_activation_max));
  }

  return kTfLiteOk;
}

#ifdef DMX1A_SUB_OPT

static void SubFloatConstI(float* output, const float* input1,
                           const AScalar& input2, const AScalar& act_min,
                           const AScalar& act_max, int size) {
  //  const int size =
  // MatchingElementsSize( tflite::micro::GetTensorShape(input1),
  // tflite::micro::GetTensorShape(input2),
  // tflite::micro::GetTensorShape(output));

  int loopLim = size >> 2;
  int remain = (size & 3);
  vr128 VR_input1, VR_input2;
  vr128 VR_min, VR_max;

  ulsr128 UR_input1;  //, UR_input2;
  vr128 VR_out;
  UR_input1 = align_32x4_load(input1);
  // UR_input2 = align_32x4_load(input2);
  ulsr128 UR_output = align_32x4_store(output);

  replicate_ar(VR_min, 0xf, act_min.fr);
  replicate_ar(VR_max, 0xf, act_max.fr);
  replicate_ar(VR_input2, 0xf, input2.fr);

  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x4_vr_a(VR_input1, UR_input1, input1);
    //  load_32x4_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x4(VR_input1);

      VR_out = vadds(VR_input1, VR_input2, 0xf0);

      load_32x4_vr_a(VR_input1, UR_input1, input1);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x4(VR_out);

      store_32x4_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x4(VR_input1);

    VR_out = vadds(VR_input1, VR_input2, 0xf0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);

    convert_32F_to_IEEE_float_x4(VR_out);

    store_32x4_vr_a(VR_out, UR_output, output);
    flush_32x4(UR_output, output);
  }
  for (int ii = 0; ii < remain; ii++) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);

    convert_IEEE_float_to_32F_x4(VR_input1);

    fadds(VR_out, VRQ0, VR_input1, VRQ0, VR_input2, VRQ0, 0x10);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x4(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}

static void SubQuantizedInt8ConstI1(const OpData* data_ex, int8_t* output,
                                    const int8_t* input1, const int8_t* input2,
                                    int n) {
  vr128 vr_input1, vr_input2;
  int loopLim = n >> 2;
  //
  // ulsr128 ur_input1, ur_input2;

  vr128 vr_offset1, vr_offset2;
  vr128 vr_multiplier_input1, vr_multiplier_input2;
  vr128 vr_multiplier_output;
  vr128 vr_output_offset, vr_out;
  vr128 vr_shift_input1, vr_shift_input2;
  vr128 vr_raw_sum, vr_output, vr_q7_out;
  int8_t* pOut = output;
  ulsr128 UR_out = align_8x4_store(pOut);
  ulsr128 UR_input2 = align_8x4_load(input2);

  replicate_ar(vr_offset1, 0xf, data_ex->input1_offset_fr32.fr);  // Afloat
  replicate_ar(vr_offset2, 0xf, data_ex->input2_offset_fr32.fr);
  replicate_ar(vr_output_offset, 0xf, data_ex->output_offset_fr32.fr);
  replicate_ar(vr_multiplier_input1, 0xf, data_ex->input1_multiplier_fr32.fr);
  replicate_ar(vr_multiplier_input2, 0xf, data_ex->input2_multiplier_fr32.fr);

  replicate_ar(vr_multiplier_output, 0xf, data_ex->output_multiplier_fr32.fr);

  load8x1_vr_postI(vr_input1, input1, INC1, VRQ0);
  vr_input1 = vreplicate(vr_input1, VRQ0);
  load_8x4_vr_a(vr_input2, UR_input2, input2);

  convert_16I_to_32F_x4(vr_input1, 0);

  // const
  vr_shift_input1 = vexp_adj(vadds(vr_input1, vr_offset1, 0x0),
                             31 - 8 - data_ex->SubOp.left_shift);
  vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);

  if (loopLim > 0) {
    for (int ii = 0; ii < loopLim - 1; ii++) {
      // q7*1<<left
      convert_16I_to_32F_x4(vr_input2, 0);

      vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0x0),
                                 31 - 8 - data_ex->SubOp.left_shift);

      vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

      vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xf0);  // Q24

      vr_output =
          vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

      // convert to 8 bit rndsat-back
      convert_32F_to_16I_x4(vr_output, 0, 0);

      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
      vr_out = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
      store_8x4_vr_a(vr_out, UR_out, pOut);

      load_8x4_vr_a(vr_input2, UR_input2, input2);
    }
    convert_16I_to_32F_x4(vr_input2, 0);
    // add offset each input

    // q7*1<<left
    vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0x0),
                               31 - 8 - data_ex->SubOp.left_shift);

    vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

    vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xf0);  // Q24

    vr_output =
        vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x4(vr_output, 0, 0);
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
    vr_out = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
    store_8x4_vr_a(vr_out, UR_out, pOut);
    flush_8x4(UR_out, pOut);
  }
  // reminder
  if (n & 3) {
    load_8x4_vr_a(vr_input2, UR_input2, input2);
    convert_16I_to_32F_x4(vr_input2, 0);

    vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0xf0),
                               31 - 8 - data_ex->SubOp.left_shift);

    vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

    vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xf0);  // Q24

    vr_output =
        vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x4(vr_output, 0, 0);
    // store 1 byt one
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
    KN_PRINTX_VR128(vr_output);
    for (int ii = 0; ii < (n & 3); ii++) {
      store8x1_vr_postI(vr_output, pOut, INC1, VRQ0);
      vr_output = vpermsi(vr_output, vr_output, 0, SHR_BY_1_ELEM);
    }
  }
}

// input 1 is constant
static void SubFloatConstI1(float* output, const AScalar& input1,
                            const float* input2, const AScalar& act_min,
                            const AScalar& act_max, int size) {
  //  const int size =
  // MatchingElementsSize( tflite::micro::GetTensorShape(input1),
  // tflite::micro::GetTensorShape(input2),
  // tflite::micro::GetTensorShape(output));

  int loopLim = size >> 2;
  int remain = (size & 3);
  vr128 VR_input1, VR_input2;
  vr128 VR_min, VR_max;

  ulsr128 UR_input2;  //, UR_input2;
  vr128 VR_out;
  UR_input2 = align_32x4_load(input2);
  // UR_input2 = align_32x4_load(input2);
  ulsr128 UR_output = align_32x4_store(output);

  replicate_ar(VR_min, 0xf, act_min.fr);
  replicate_ar(VR_max, 0xf, act_max.fr);
  replicate_ar(VR_input1, 0xf, input1.fr);

  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x4_vr_a(VR_input2, UR_input2, input2);
    //  load_32x4_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x4(VR_input2);

      VR_out = vadds(VR_input1, VR_input2, 0xf0);

      load_32x4_vr_a(VR_input2, UR_input2, input2);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x4(VR_out);

      store_32x4_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x4(VR_input2);

    VR_out = vadds(VR_input1, VR_input2, 0xf0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);

    convert_32F_to_IEEE_float_x4(VR_out);

    store_32x4_vr_a(VR_out, UR_output, output);
    flush_32x4(UR_output, output);
  }
  for (int ii = 0; ii < remain; ii++) {
    load32x1_vr_postI(VR_input2, input2, INC1, VRQ0);

    convert_IEEE_float_to_32F_x4(VR_input2);

    fadds(VR_out, VRQ0, VR_input1, VRQ0, VR_input2, VRQ0, 0x10);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x4(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}
static void SubFloat(float* output, const float* input1, const float* input2,
                     const AScalar& act_min, const AScalar& act_max, int size) {
  //  const int size =
  // MatchingElementsSize( tflite::micro::GetTensorShape(input1),
  // tflite::micro::GetTensorShape(input2),
  // tflite::micro::GetTensorShape(output));

  int loopLim = size >> 2;
  int remain = (size & 3);
  vr128 VR_input1, VR_input2;
  vr128 VR_min, VR_max;

  ulsr128 UR_input1, UR_input2;
  vr128 VR_out;
  UR_input1 = align_32x4_load(input1);
  UR_input2 = align_32x4_load(input2);
  ulsr128 UR_output = align_32x4_store(output);

  replicate_ar(VR_min, 0xf, act_min.fr);
  replicate_ar(VR_max, 0xf, act_max.fr);
  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x4_vr_a(VR_input1, UR_input1, input1);
    load_32x4_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x4(VR_input1);
      convert_IEEE_float_to_32F_x4(VR_input2);
      VR_out = vadds(VR_input1, VR_input2, 0xf0);
      load_32x4_vr_a(VR_input1, UR_input1, input1);
      load_32x4_vr_a(VR_input2, UR_input2, input2);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x4(VR_out);

      store_32x4_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x4(VR_input1);
    convert_IEEE_float_to_32F_x4(VR_input2);
    VR_out = vadds(VR_input1, VR_input2, 0xf0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x4(VR_out);

    store_32x4_vr_a(VR_out, UR_output, output);
    flush_32x4(UR_output, output);
  }
  for (int ii = 0; ii < remain; ii++) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);
    load32x1_vr_postI(VR_input2, input2, INC1, VRQ0);
    convert_IEEE_float_to_32F_x4(VR_input1);
    convert_IEEE_float_to_32F_x4(VR_input2);
    fadds(VR_out, VRQ0, VR_input1, VRQ0, VR_input2, VRQ0, 0x10);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x4(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}

static TfLiteStatus SubQuantizedInt8Sat(OpData* data_ex, const int8_t* input1,
                                        const int8_t* input2, int8_t* output,
                                        int n) {
  OpDataSub* data = static_cast<OpDataSub*>(&data_ex->SubOp);
  vr128 vr_input1, vr_input2;
  int loopLim = n >> 2;
  //
  // ulsr128 ur_input1, ur_input2;
  int8_t* pOut = output;
  ulsr128 UR_input1, UR_input2;
  ulsr128 UR_out = align_8x4_store(pOut);
  vr128 vr_offset1, vr_offset2;
  vr128 vr_multiplier_input1, vr_multiplier_input2;
  vr128 vr_multiplier_output;
  vr128 vr_output_offset;
  vr128 vr_shift_input1, vr_shift_input2;
  vr128 vr_raw_sum, vr_output, vr_q7_out;

  replicate_ar(vr_offset1, 0xf, data_ex->input1_offset_fr32.fr);  // Afloat
  replicate_ar(vr_offset2, 0xf, data_ex->input2_offset_fr32.fr);
  replicate_ar(vr_output_offset, 0xf, data_ex->output_offset_fr32.fr);
  replicate_ar(vr_multiplier_input1, 0xf, data_ex->input1_multiplier_fr32.fr);
  replicate_ar(vr_multiplier_input2, 0xf, data_ex->input2_multiplier_fr32.fr);

  replicate_ar(vr_multiplier_output, 0xf, data_ex->output_multiplier_fr32.fr);
  UR_input1 = align_8x4_load(input1);
  UR_input2 = align_8x4_load(input2);
  if (loopLim > 0) {
    load_8x4_vr_a(vr_input1, UR_input1, input1);
    load_8x4_vr_a(vr_input2, UR_input2, input2);

    convert_16I_to_32F_x4(vr_input1, 0);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      // q7*1<<left
      convert_16I_to_32F_x4(vr_input2, 0);
      vr_shift_input1 = vexp_adj(vadds(vr_input1, vr_offset1, 0x0),
                                 31 - 8 - data->left_shift);
      vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0x0),
                                 31 - 8 - data->left_shift);

      vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);
      vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

      vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xf0);  // Q24

      vr_output =
          vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

      // convert to 8 bit rndsat-back
      convert_32F_to_16I_x4(vr_output, 0, 0);

      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
      vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
      store_8x4_vr_a(vr_output, UR_out, pOut);  // , INC1, VRQ0);
      load_8x4_vr_a(vr_input1, UR_input1, input1);
      load_8x4_vr_a(vr_input2, UR_input2, input2);
      convert_16I_to_32F_x4(vr_input1, 0);
    }
    convert_16I_to_32F_x4(vr_input2, 0);
    // add offset each input

    // q7*1<<left
    vr_shift_input1 =
        vexp_adj(vadds(vr_input1, vr_offset1, 0x0), 31 - 8 - data->left_shift);
    vr_shift_input2 =
        vexp_adj(vadds(vr_input2, vr_offset2, 0x0), 31 - 8 - data->left_shift);

    vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);
    vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

    vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xf0);  // Q24

    vr_output =
        vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x4(vr_output, 0, 0);

    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
    store_8x4_vr_a(vr_output, UR_out, pOut);
    flush_8x4(UR_out, pOut);
  }
  // reminder
  if (n & 3) {
    load_8x4_vr_a(vr_input1, UR_input1, input1);
    load_8x4_vr_a(vr_input2, UR_input2, input2);

    convert_16I_to_32F_x4(vr_input1, 0);
    convert_16I_to_32F_x4(vr_input2, 0);
    vr_shift_input1 =
        vexp_adj(vadds(vr_input1, vr_offset1, 0x0), 31 - 8 - data->left_shift);
    vr_shift_input2 =
        vexp_adj(vadds(vr_input2, vr_offset2, 0x0), 31 - 8 - data->left_shift);

    vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);
    vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

    vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xf0);  // Q24

    vr_output =
        vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x4(vr_output, 0, 0);
    // store 1 byt one
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
    KN_PRINTX_VR128(vr_output);
    for (int ii = 0; ii < (n & 3); ii++) {
      store8x1_vr_postI(vr_output, pOut, INC1, VRQ0);
      vr_output = vpermsi(vr_output, vr_output, 0, SHR_BY_1_ELEM);
    }
  }
  return kTfLiteOk;
}

#endif

#ifdef HMD1A_SUB_OPT

static void SubFloatConstI(float* output, const float* input1,
                           const AScalar& input2, const AScalar& act_min,
                           const AScalar& act_max, int size) {
  //  const int size =
  // MatchingElementsSize( tflite::micro::GetTensorShape(input1),
  // tflite::micro::GetTensorShape(input2),
  // tflite::micro::GetTensorShape(output));

  int loopLim = size >> 1;
  int remain = (size & 1);
  vr64 VR_input1, VR_input2;
  vr64 VR_min, VR_max;

  ulsr32 UR_input1;  //, UR_input2;
  vr64 VR_out;
  UR_input1 = align_32x2_load(input1);
  // UR_input2 = align_32x4_load(input2);
  ulsr32 UR_output = align_32x2_store(output);

  replicate_ar(VR_min, 0x3, act_min.fr);
  replicate_ar(VR_max, 0x3, act_max.fr);
  replicate_ar(VR_input2, 0x3, input2.fr);

  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x2_vr_a(VR_input1, UR_input1, input1);
    //  load_32x4_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x2(VR_input1);

      VR_out = vadds(VR_input1, VR_input2, 0xa);

      load_32x2_vr_a(VR_input1, UR_input1, input1);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x2(VR_out);

      store_32x2_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x2(VR_input1);

    VR_out = vadds(VR_input1, VR_input2, 0xa);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);

    convert_32F_to_IEEE_float_x2(VR_out);

    store_32x2_vr_a(VR_out, UR_output, output);
    flush_32x2(UR_output, output);
  }
  if (remain) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);

    convert_IEEE_float_to_32F_x2(VR_input1);

    VR_out = vadds(VR_input1, VR_input2, 0xa);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}

static void SubQuantizedInt8ConstI1(const OpData* data, int8_t* output,
                                    const int8_t* input1, const int8_t* input2,
                                    int n) {
  vr64 vr_input1, vr_input2;
  int loopLim = n >> 1;
  //
  // ulsr128 ur_input1, ur_input2;

  vr64 vr_offset1, vr_offset2;
  vr64 vr_multiplier_input1, vr_multiplier_input2;
  vr64 vr_multiplier_output;
  vr64 vr_output_offset, vr_out;
  vr64 vr_shift_input1, vr_shift_input2;
  vr64 vr_raw_sum, vr_output, vr_q7_out;
  int8_t* pOut = output;
  // ulsr128 UR_out = align_8x4_store(pOut);
  replicate_ar(vr_offset1, 0x3, data->input1_offset_fr32.fr);  // Afloat
  replicate_ar(vr_offset2, 0x3, data->input2_offset_fr32.fr);
  replicate_ar(vr_output_offset, 0x3, data->output_offset_fr32.fr);
  replicate_ar(vr_multiplier_input1, 0x3, data->input1_multiplier_fr32.fr);
  replicate_ar(vr_multiplier_input2, 0x3, data->input2_multiplier_fr32.fr);

  replicate_ar(vr_multiplier_output, 0x3, data->output_multiplier_fr32.fr);

  load8x1_vr_postI(vr_input1, input1, INC1, VRQ0);
  vr_input1 = vreplicate(vr_input1, VRQ0);

  load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);
  load8x1_vr_postI(vr_input2, input2, INC1, VRQ1);

  convert_16I_to_32F_x2(vr_input1, 0);

  // const
  vr_shift_input1 = vexp_adj(vadds(vr_input1, vr_offset1, 0x0),
                             31 - 8 - data->SubOp.left_shift);
  vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);

  if (loopLim > 0) {
    for (int ii = 0; ii < loopLim - 1; ii++) {
      // q7*1<<left
      convert_16I_to_32F_x2(vr_input2, 0);

      vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0x0),
                                 31 - 8 - data->SubOp.left_shift);

      vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

      vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xa);  // Q24

      vr_output =
          vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

      // convert to 8 bit rndsat-back
      convert_32F_to_16I_x2(vr_output, 0, 0);

      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
      vr_out = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
      store8x1_vr_postI(vr_out, pOut, INC1, VRQ0);
      store8x1_vr_postI(vr_out, pOut, INC1, VRQ1);

      load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);
      load8x1_vr_postI(vr_input2, input2, INC1, VRQ1);
    }
    convert_16I_to_32F_x2(vr_input2, 0);
    // add offset each input

    // q7*1<<left
    vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0x0),
                               31 - 8 - data->SubOp.left_shift);

    vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

    vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xa);  // Q24

    vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x2(vr_output, 0, 0);
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
    vr_out = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
    store8x1_vr_postI(vr_out, pOut, INC1, VRQ0);
    store8x1_vr_postI(vr_out, pOut, INC1, VRQ1);
  }
  // reminder
  if (n & 1) {
    load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);
    convert_16I_to_32F_x2(vr_input2, 0);

    vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0x0),
                               31 - 8 - data->SubOp.left_shift);

    vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

    vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xa);  // Q24

    vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x2(vr_output, 0, 0);
    // store 1 byt one
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);

    store8x1_vr_postI(vr_output, pOut, INC1, VRQ0);
  }
}

// input 1 is constant
static void SubFloatConstI1(float* output, const AScalar& input1,
                            const float* input2, const AScalar& act_min,
                            const AScalar& act_max, int size) {
  //  const int size =
  // MatchingElementsSize( tflite::micro::GetTensorShape(input1),
  // tflite::micro::GetTensorShape(input2),
  // tflite::micro::GetTensorShape(output));

  int loopLim = size >> 1;
  int remain = (size & 1);
  vr64 VR_input1, VR_input2;
  vr64 VR_min, VR_max;

  ulsr32 UR_input2;  //, UR_input2;
  vr64 VR_out;
  UR_input2 = align_32x2_load(input2);
  // UR_input2 = align_32x4_load(input2);
  ulsr32 UR_output = align_32x2_store(output);

  replicate_ar(VR_min, 0x3, act_min.fr);
  replicate_ar(VR_max, 0x3, act_max.fr);
  replicate_ar(VR_input1, 0x3, input1.fr);

  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x2_vr_a(VR_input2, UR_input2, input2);
    //  load_32x4_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x2(VR_input2);

      VR_out = vadds(VR_input1, VR_input2, 0xa);

      load_32x2_vr_a(VR_input2, UR_input2, input2);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x2(VR_out);

      store_32x2_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x2(VR_input2);

    VR_out = vadds(VR_input1, VR_input2, 0xa);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);

    convert_32F_to_IEEE_float_x2(VR_out);

    store_32x2_vr_a(VR_out, UR_output, output);
    flush_32x2(UR_output, output);
  }
  if (remain) {
    load32x1_vr_postI(VR_input2, input2, INC1, VRQ0);

    convert_IEEE_float_to_32F_x2(VR_input2);

    VR_out = vadds(VR_input1, VR_input2, 0xa);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}
static void SubFloat(float* output, const float* input1, const float* input2,
                     const AScalar& act_min, const AScalar& act_max, int size) {
  //  const int size =
  // MatchingElementsSize( tflite::micro::GetTensorShape(input1),
  // tflite::micro::GetTensorShape(input2),
  // tflite::micro::GetTensorShape(output));

  int loopLim = size >> 1;
  int remain = (size & 1);
  vr64 VR_input1, VR_input2;
  vr64 VR_min, VR_max;

  ulsr32 UR_input1, UR_input2;
  vr64 VR_out;
  UR_input1 = align_32x2_load(input1);
  UR_input2 = align_32x2_load(input2);
  ulsr32 UR_output = align_32x2_store(output);

  replicate_ar(VR_min, 0x3, act_min.fr);
  replicate_ar(VR_max, 0x3, act_max.fr);
  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x2_vr_a(VR_input1, UR_input1, input1);
    load_32x2_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x2(VR_input1);
      convert_IEEE_float_to_32F_x2(VR_input2);
      VR_out = vadds(VR_input1, VR_input2, 0xa);
      load_32x2_vr_a(VR_input1, UR_input1, input1);
      load_32x2_vr_a(VR_input2, UR_input2, input2);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x2(VR_out);

      store_32x2_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x2(VR_input1);
    convert_IEEE_float_to_32F_x2(VR_input2);
    VR_out = vadds(VR_input1, VR_input2, 0xa);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);

    store_32x2_vr_a(VR_out, UR_output, output);
    flush_32x2(UR_output, output);
  }
  if (remain) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);
    load32x1_vr_postI(VR_input2, input2, INC1, VRQ0);
    convert_IEEE_float_to_32F_x2(VR_input1);
    convert_IEEE_float_to_32F_x2(VR_input2);
    VR_out = vadds(VR_input1, VR_input2, 0xa);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}

static TfLiteStatus SubQuantizedInt8Sat(const OpData* data,
                                        const int8_t* input1,
                                        const int8_t* input2, int8_t* output,
                                        int n) {
  vr64 vr_input1, vr_input2;
  int loopLim = n >> 1;
  //
  // ulsr128 ur_input1, ur_input2;

  vr64 vr_offset1, vr_offset2;
  vr64 vr_multiplier_input1, vr_multiplier_input2;
  vr64 vr_multiplier_output;
  vr64 vr_output_offset;
  vr64 vr_shift_input1, vr_shift_input2;
  vr64 vr_raw_sum, vr_output, vr_q7_out;

  replicate_ar(vr_offset1, 0x3, data->input1_offset_fr32.fr);  // Afloat
  replicate_ar(vr_offset2, 0x3, data->input2_offset_fr32.fr);
  replicate_ar(vr_output_offset, 0x3, data->output_offset_fr32.fr);
  replicate_ar(vr_multiplier_input1, 0x3, data->input1_multiplier_fr32.fr);
  replicate_ar(vr_multiplier_input2, 0x3, data->input2_multiplier_fr32.fr);

  replicate_ar(vr_multiplier_output, 0x3, data->output_multiplier_fr32.fr);

  if (loopLim > 0) {
    load8x2_vr_postI(vr_input1, input1, INC1);
    load8x2_vr_postI(vr_input2, input2, INC1);

    convert_16I_to_32F_x2(vr_input1, 0);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      // q7*1<<left
      convert_16I_to_32F_x2(vr_input2, 0);
      vr_shift_input1 = vexp_adj(vadds(vr_input1, vr_offset1, 0x0),
                                 31 - 8 - data->SubOp.left_shift);
      vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0x0),
                                 31 - 8 - data->SubOp.left_shift);

      vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);
      vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

      vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xa);  // Q24

      vr_output =
          vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

      // convert to 8 bit rndsat-back
      convert_32F_to_16I_x2(vr_output, 0, 0);

      rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
      vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
      store8x1_vr_postI(vr_output, output, INC1, VRQ0);
      store8x1_vr_postI(vr_output, output, INC1, VRQ1);
      load8x2_vr_postI(vr_input1, input1, INC1);
      load8x2_vr_postI(vr_input2, input2, INC1);
      convert_16I_to_32F_x2(vr_input1, 0);
    }
    convert_16I_to_32F_x2(vr_input2, 0);
    // add offset each input

    // q7*1<<left
    vr_shift_input1 = vexp_adj(vadds(vr_input1, vr_offset1, 0x0),
                               31 - 8 - data->SubOp.left_shift);
    vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0x0),
                               31 - 8 - data->SubOp.left_shift);

    vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);
    vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

    vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xa);  // Q24

    vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x2(vr_output, 0, 0);

    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
    store8x1_vr_postI(vr_output, output, INC1, VRQ0);
    store8x1_vr_postI(vr_output, output, INC1, VRQ1);
  }
  // reminder
  if (n & 1) {
    load8x1_vr_postI(vr_input1, input1, INC1, VRQ0);
    load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);

    convert_16I_to_32F_x2(vr_input1, 0);
    convert_16I_to_32F_x2(vr_input2, 0);
    vr_shift_input1 = vexp_adj(vadds(vr_input1, vr_offset1, 0x0),
                               31 - 8 - data->SubOp.left_shift);
    vr_shift_input2 = vexp_adj(vadds(vr_input2, vr_offset2, 0x0),
                               31 - 8 - data->SubOp.left_shift);

    vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);
    vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

    vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0xa);  // Q24

    vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x2(vr_output, 0, 1);
    // store 1 byt one
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);

    store8x1_vr_postI(vr_output, output, INC1, VRQ0);
  }
  return kTfLiteOk;
}

#endif
void* InitSub(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus PrepareSub(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  OpData* data_ex = static_cast<OpData*>(node->user_data);

  OpDataSub* data = static_cast<OpDataSub*>(&data_ex->SubOp);

  auto* params = reinterpret_cast<TfLiteSubParams*>(node->builtin_data);

  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input1 =
      micro_context->AllocateTempInputTensor(node, kSubInputTensor1);
  TF_LITE_ENSURE(context, input1 != nullptr);
  TfLiteTensor* input2 =
      micro_context->AllocateTempInputTensor(node, kSubInputTensor2);
  TF_LITE_ENSURE(context, input2 != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kSubOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);

  TF_LITE_ENSURE_STATUS(
      CalculateOpData(context, params, input1, input2, output, data_ex));

  data_ex->opt_constraint = 0;
  data_ex->opt_constraint_float = 0;
#if (defined(DMX1A_SUB_OPT) || defined(HMD1A_SUB_OPT))
  int input1_count = ElementCount(*input1->dims);
  int input2_count = ElementCount(*input2->dims);
  int output_count = ElementCount(*output->dims);
  KN_PRINTD(input1_count);
  KN_PRINTD(input2_count);
  KN_PRINTD(output_count);
  // data->opt_constraint = 0;
  if ((output->type == kTfLiteInt8) && (data->output_activation_min == -128 &&
                                        data->output_activation_max == 127)) {
    KN_PRINTD(data->requires_broadcast);
    if (0 == data->requires_broadcast) data_ex->opt_constraint = 1;

      // type 2 optimizaition
#if 1
    // determine input 2 is match the latest one
    {
      // int input2_count = tflite::micro::GetTensorShape(input2).FlatSize()
      int input_shape0 =
          input1->dims->data[input1->dims->size - 1];  // Dims(0);
      if (input_shape0 == input2_count && output_count == input1_count &&
          (input_shape0 & 3) == 0)
        data_ex->opt_constraint = 2;  //

      else if (input2_count == output_count &&
               input1_count == 1) {  // type 3: rnnoise GRU input 2 size =
                                     // output size, and input 1 size is const 1
        data_ex->opt_constraint = 3;  //
      }
    }
#endif
  }
  if (data_ex->opt_constraint) {
    tflite::ConvertQ31ToAfloat(data->input1_multiplier,
                               data_ex->input1_multiplier_fr32,
                               data->input1_shift);
    tflite::ConvertQ31ToAfloat(data->input2_multiplier,
                               data_ex->input2_multiplier_fr32,
                               data->input2_shift);
    tflite::ConvertQ31ToAfloat(data->output_multiplier,
                               data_ex->output_multiplier_fr32,
                               31 - 14 + data->output_shift);  //-19

    tflite::ConvertQ31ToAfloat(data->input1_offset, data_ex->input1_offset_fr32,
                               31 - 7);
    tflite::ConvertQ31ToAfloat(data->input2_offset, data_ex->input2_offset_fr32,
                               31 - 7);
    tflite::ConvertQ31ToAfloat(data->output_offset, data_ex->output_offset_fr32,
                               31 - 7);
  }
  // only min = -128 and max=127 acceptable for rnd_sat_pack

  if (output->type == kTfLiteFloat32) {
    // runtime change ?
    // TODO: compare each dims in input1 and output;
    // input2 only 1

    // determine input 2 is match the latest one
    if ((input1_count == input2_count) && (input2_count == output_count)) {
      data_ex->opt_constraint_float = 1;
    } else if (1 == input2_count && output_count == input1_count) {
      data_ex->opt_constraint_float = 2;  // FloatAddWithScalarBroadcast
    } else if (input2_count == output_count && input1_count != 1 &&
               input1_count != input2_count)  // FIXME
    {
      data_ex->opt_constraint_float = 3;
    } else if (input2_count == output_count && input1_count == 1)
      data_ex->opt_constraint_float = 4;
  }
  KN_PRINTD(data->output_activation_min);
  KN_PRINTD(data->output_activation_max);

#endif
  KN_PRINTD(data_ex->opt_constraint);
  KN_PRINTD(data_ex->opt_constraint_float);

  micro_context->DeallocateTempTfLiteTensor(input1);
  micro_context->DeallocateTempTfLiteTensor(input2);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}
void EvalSubFloat(TfLiteContext* context, TfLiteNode* node,
                  TfLiteSubParams* params, OpData* data_ex,
                  const TfLiteEvalTensor* input1,
                  const TfLiteEvalTensor* input2, TfLiteEvalTensor* output) {
  float output_activation_min, output_activation_max;

  const OpDataSub* data = static_cast<OpDataSub*>(&data_ex->SubOp);
  CalculateActivationRange(params->activation, &output_activation_min,
                           &output_activation_max);
  tflite::ArithmeticParams op_params;
  SetActivationParams(output_activation_min, output_activation_max, &op_params);
  if (data->requires_broadcast) {
    tflite::reference_ops::BroadcastSubSlow(
        op_params, tflite::micro::GetTensorShape(input1),
        tflite::micro::GetTensorData<float>(input1),
        tflite::micro::GetTensorShape(input2),
        tflite::micro::GetTensorData<float>(input2),
        tflite::micro::GetTensorShape(output),
        tflite::micro::GetTensorData<float>(output));
  } else {
    tflite::reference_ops::SubWithActivation(
        op_params, tflite::micro::GetTensorShape(input1),
        tflite::micro::GetTensorData<float>(input1),
        tflite::micro::GetTensorShape(input2),
        tflite::micro::GetTensorData<float>(input2),
        tflite::micro::GetTensorShape(output),
        tflite::micro::GetTensorData<float>(output));
  }
}
#ifndef REMOVE_REFOP_SUPPORT
TfLiteStatus EvalSubQuantized(TfLiteContext* context, TfLiteNode* node,
                              TfLiteSubParams* params, OpData* data_ex,
                              const TfLiteEvalTensor* input1,
                              const TfLiteEvalTensor* input2,
                              TfLiteEvalTensor* output) {
#if defined(DMX1A_SUB_OPT) || defined(HMD1A_SUB_OPT)
  if (output->type == kTfLiteInt8 && 0 != data_ex->opt_constraint) {
    if (data_ex->opt_constraint == 1) {
      return SubQuantizedInt8Sat(
          data_ex, tflite::micro::GetTensorData<int8_t>(input1),
          tflite::micro::GetTensorData<int8_t>(input2),
          tflite::micro::GetTensorData<int8_t>(output),
          MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                               tflite::micro::GetTensorShape(input2),
                               tflite::micro::GetTensorShape(output)));
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                       ElementCount(*output->dims));
    } else if (data_ex->opt_constraint == 2) {
      // dim input1 [a,b,c,d], input2 = [d]
      // for loop all a*b*c for each d
      const int8_t* input1_data = tflite::micro::GetTensorData<int8_t>(input1);
      const int8_t* input2_data = tflite::micro::GetTensorData<int8_t>(input2);
      int8_t* output_data = tflite::micro::GetTensorData<int8_t>(output);

      int internal_loop_count =
          tflite::micro::GetTensorShape(input2).FlatSize();
      int external_loop_count =
          tflite::micro::GetTensorShape(input1).FlatSize();
      /*
      tflite::micro::GetTensorData<int8_t>(output),
      MatchingElementsSize(tflite::micro::GetTensorShape(input1),
      tflite::micro::GetTensorShape(input2),
      tflite::micro::GetTensorShape(output));
      */
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input1),
                       ElementCount(*input1->dims));
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input2),
                       ElementCount(*input2->dims));

      for (int ii = 0; ii < external_loop_count;
           ii += internal_loop_count)  // dim 2 , dim3
      {
        SubQuantizedInt8Sat(data_ex, input1_data, input2_data, output_data,
                            internal_loop_count);
        input1_data += internal_loop_count;
        output_data += internal_loop_count;
      }
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                       ElementCount(*output->dims));
    } else if (data_ex->opt_constraint == 3) {
      // dim input1 [a,b,c,d], input2 = [d]
      // for loop all a*b*c for each d
      const int8_t* input1_data = tflite::micro::GetTensorData<int8_t>(input1);
      const int8_t* input2_data = tflite::micro::GetTensorData<int8_t>(input2);
      int8_t* output_data = tflite::micro::GetTensorData<int8_t>(output);

      int loop_count = tflite::micro::GetTensorShape(output).FlatSize();

      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input1),
                       ElementCount(*input1->dims));
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input2),
                       ElementCount(*input2->dims));

      // for (int ii = 0; ii < external_loop_count; ii += internal_loop_count)
      // // dim 2 , dim3
      {
        SubQuantizedInt8ConstI1(data_ex, output_data, input1_data, input2_data,
                                loop_count);
      }
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                       ElementCount(*output->dims));
    }

  } else
#endif
  {
    OpDataSub* data = static_cast<OpDataSub*>(&data_ex->SubOp);
    tflite::ArithmeticParams op_params;
    op_params.left_shift = data->left_shift;
    op_params.input1_offset = data->input1_offset;
    op_params.input1_multiplier = data->input1_multiplier;
    op_params.input1_shift = data->input1_shift;
    op_params.input2_offset = data->input2_offset;
    op_params.input2_multiplier = data->input2_multiplier;
    op_params.input2_shift = data->input2_shift;
    op_params.output_offset = data->output_offset;
    op_params.output_multiplier = data->output_multiplier;
    op_params.output_shift = data->output_shift;
    SetActivationParams(data->output_activation_min,
                        data->output_activation_max, &op_params);
    bool need_broadcast = reference_ops::ProcessBroadcastShapes(
        tflite::micro::GetTensorShape(input1),
        tflite::micro::GetTensorShape(input2), &op_params);

    switch (output->type) {
      case kTfLiteInt8: {
        if (need_broadcast) {
          tflite::reference_ops::BroadcastQuantSubSlow(
              op_params, tflite::micro::GetTensorShape(input1),
              tflite::micro::GetTensorData<int8_t>(input1),
              tflite::micro::GetTensorShape(input2),
              tflite::micro::GetTensorData<int8_t>(input2),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<int8_t>(output));
        } else {
          tflite::reference_ops::Sub(
              op_params, tflite::micro::GetTensorShape(input1),
              tflite::micro::GetTensorData<int8_t>(input1),
              tflite::micro::GetTensorShape(input2),
              tflite::micro::GetTensorData<int8_t>(input2),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<int8_t>(output));
        }
        break;
      }
      case kTfLiteInt16: {
        if (need_broadcast) {
          tflite::reference_ops::BroadcastQuantSubSlow(
              op_params, tflite::micro::GetTensorShape(input1),
              tflite::micro::GetTensorData<int16_t>(input1),
              tflite::micro::GetTensorShape(input2),
              tflite::micro::GetTensorData<int16_t>(input2),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<int16_t>(output));
        } else {
          tflite::reference_ops::Sub(
              op_params, tflite::micro::GetTensorShape(input1),
              tflite::micro::GetTensorData<int16_t>(input1),
              tflite::micro::GetTensorShape(input2),
              tflite::micro::GetTensorData<int16_t>(input2),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<int16_t>(output));
        }
        break;
      }
      default:
        TF_LITE_KERNEL_LOG(context,
                           "Quantized type %s not currently supported.",
                           TfLiteTypeGetName(output->type));
        return kTfLiteError;
    }
  }
  return kTfLiteOk;
}
#endif
TfLiteStatus EvalSubFloat32(TfLiteContext* context, TfLiteNode* node,
                            TfLiteSubParams* params, OpData* data_ex,
                            const TfLiteEvalTensor* input1,
                            const TfLiteEvalTensor* input2,
                            TfLiteEvalTensor* output) {
  float output_activation_min, output_activation_max;

  // const OpDataSub* data = static_cast<OpDataSub*>(&data_ex->SubOp);
  CalculateActivationRange(params->activation, &output_activation_min,
                           &output_activation_max);
  tflite::ArithmeticParams op_params;
  SetActivationParams(output_activation_min, output_activation_max, &op_params);
#if defined(DMX1A_SUB_OPT) || defined(HMD1A_SUB_OPT)
  AScalar act_min, act_max;
  CalculateActivationRangeAflt(params->activation, &act_min, &act_max);

  if (data_ex->opt_constraint_float == 1) {
    const int flat_size =
        MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                             tflite::micro::GetTensorShape(input2),
                             tflite::micro::GetTensorShape(output));
    SubFloat(tflite::micro::GetTensorData<float>(output),
             tflite::micro::GetTensorData<float>(input1),
             tflite::micro::GetTensorData<float>(input2), act_min, act_max,
             flat_size);
    //      KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
    //      flat_size);
  } else if (data_ex->opt_constraint_float == 2) {
    AScalar input2Element;
    const int flat_size =
        MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                             tflite::micro::GetTensorShape(output));

    const float* input2Flt = tflite::micro::GetTensorData<float>(input2);
    KN_PRINTF(input2Flt[0]);
    input2Element = AScalar(input2Flt[0]);
    KN_PRINTAFLT(input2Element);
    SubFloatConstI(tflite::micro::GetTensorData<float>(output),
                   tflite::micro::GetTensorData<float>(input1), input2Element,
                   act_min, act_max, flat_size);
  } else if (data_ex->opt_constraint_float == 3) {
    // AScalar input2Element;
    MatchingElementsSize(tflite::micro::GetTensorShape(input2),
                         tflite::micro::GetTensorShape(output));

    const float* input1Flt = tflite::micro::GetTensorData<float>(input1);
    const float* input2Flt = tflite::micro::GetTensorData<float>(input2);
    float* out = tflite::micro::GetTensorData<float>(output);
    //  KN_PRINTF(input2Flt[0]);
    // input2Element = AScalar(input2Flt[0]);
    // KN_PRINTAFLT(input2Element);
    // A [1,32,1]
    // B [1,32,5]
    // C [1,32,5]
    int outSize = tflite::micro::GetTensorShape(input2).Dims(1);
    int inSize = tflite::micro::GetTensorShape(input2).Dims(2);

    for (int ii = 0; ii < outSize; ii++) {
      AScalar input1Element = AScalar(input1Flt[ii]);
      SubFloatConstI1(out, input1Element, input2Flt, act_min, act_max, inSize);
      out += inSize;
      input2Flt += inSize;
    }
  } else if (data_ex->opt_constraint_float == 4) {
    AScalar input1Element;
    const int flat_size =
        MatchingElementsSize(tflite::micro::GetTensorShape(input2),
                             tflite::micro::GetTensorShape(output));

    const float* input1Flt = tflite::micro::GetTensorData<float>(input1);
    KN_PRINTF(input2Flt[0]);
    input1Element = AScalar(input1Flt[0]);
    KN_PRINTAFLT(input2Element);
    SubFloatConstI1(tflite::micro::GetTensorData<float>(output), input1Element,
                    tflite::micro::GetTensorData<float>(input2), act_min,
                    act_max, flat_size);
  } else
#endif
  {
#ifndef REMOVE_REFOP_SUPPORT

    if (output->type == kTfLiteFloat32) {
      EvalSubFloat(context, node, params, data_ex, input1, input2, output);
    } else if (output->type == kTfLiteInt8 || output->type == kTfLiteInt16) {
      TF_LITE_ENSURE_OK(context,
                        EvalSubQuantized(context, node, params, data_ex, input1,
                                         input2, output));
    } else {
      TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(output->type), output->type);
      return kTfLiteError;
    }
#else
    return kTfLiteError;
#endif
  }

  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                 ElementCount(*output->dims));
  return kTfLiteOk;
}

TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteSubParams*>(node->builtin_data);

  const TfLiteEvalTensor* input1 =
      tflite::micro::GetEvalInput(context, node, kSubInputTensor1);
  const TfLiteEvalTensor* input2 =
      tflite::micro::GetEvalInput(context, node, kSubInputTensor2);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kSubOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  OpData& data = *(static_cast<OpData*>(node->user_data));

  if (output->type == kTfLiteFloat32) {
    EvalSubFloat(context, node, params, &data, input1, input2, output);
  } else if (output->type == kTfLiteInt8 || output->type == kTfLiteInt16) {
#ifndef REMOVE_REFOP_SUPPORT
    TF_LITE_ENSURE_OK(context, EvalSubQuantized(context, node, params, &data,
                                                input1, input2, output));
#else
    return kTfLiteError;
#endif
  } else {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(output->type), output->type);
    return kTfLiteError;
  }

  return kTfLiteOk;
}
TfLiteStatus EvalFloat32(TfLiteContext* context, TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteSubParams*>(node->builtin_data);

  const TfLiteEvalTensor* input1 =
      tflite::micro::GetEvalInput(context, node, kSubInputTensor1);
  const TfLiteEvalTensor* input2 =
      tflite::micro::GetEvalInput(context, node, kSubInputTensor2);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kSubOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  OpData& data = *(static_cast<OpData*>(node->user_data));
  if (output->type != kTfLiteFloat32) {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(output->type), output->type);
    return kTfLiteError;
  }
  EvalSubFloat(context, node, params, &data, input1, input2, output);

  return kTfLiteOk;
}
//}  // namespace sub

TFLMRegistration Register_SUB() {
  return tflite::micro::RegisterOp(InitSub,
                                   /*prepare=*/PrepareSub,
                                   /*invoke=*/Eval);
}
TFLMRegistration Register_SUB_FLOAT32() {
  return tflite::micro::RegisterOp(InitSub,
                                   /*prepare=*/PrepareSub,
                                   /*invoke=*/EvalFloat32);
}
//}  // namespace micro
//}  // namespace ops
}  // namespace tflite
