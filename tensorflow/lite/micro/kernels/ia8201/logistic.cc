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
#include "tensorflow/lite/kernels/internal/reference/integer_ops/logistic.h"

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/logistic.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"
#include "tensorflow/lite/micro/ia8201/config.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {
// namespace ops {
// namespace micro {
// namespace activations {
namespace {

const int kLogisticInputTensor = 0;
const int kLogisticOutputTensor = 0;
struct OpData {
  int32_t input_zero_point;
  int32_t input_range_radius;
  int32_t input_multiplier;
  int input_left_shift;
  AScalar inputMultipler;
  AScalar inputRangeRadius;
  AScalar inputZeroPoint;
  int opt_constraint;
};

TfLiteStatus CalculateArithmeticOpData(TfLiteContext* context, TfLiteNode* node,
                                       OpData* data) {
  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kLogisticInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kLogisticOutputTensor);

  TF_LITE_ENSURE_TYPES_EQ(context, input->type, output->type);
  if (input->type == kTfLiteInt8) {
    TF_LITE_ENSURE_EQ(context, output->params.zero_point,
                      std::numeric_limits<int8_t>::min());

    static constexpr int kInputIntegerBits = 4;
    const double input_real_multiplier =
        static_cast<double>(input->params.scale) *
        static_cast<double>(1 << (31 - kInputIntegerBits));

    data->input_zero_point = input->params.zero_point;

    const double q = std::frexp(input_real_multiplier, &data->input_left_shift);
    data->input_multiplier = static_cast<int32_t>(TfLiteRound(q * (1ll << 31)));

    data->input_range_radius =
        CalculateInputRadius(kInputIntegerBits, data->input_left_shift, 31);

    // int32_t kInputIntegerBits = 4;
    // Q7(input) * multipler(31-left_shift) >> conQ4.x
    // 7+(X-left_shift) = 31-4 = 27
    //
    tflite::ConvertQ31ToAfloat(
        data->input_multiplier, data->inputMultipler,
        data->input_left_shift -
            20);  // Q7* Qx() >> 31-shift32- op_data.input_left_shift-5
    tflite::ConvertQ31ToAfloat(data->input_range_radius, data->inputRangeRadius,
                               24);  // Q31 compare to input Q7
    tflite::ConvertQ31ToAfloat(data->input_zero_point, data->inputZeroPoint,
                               24);  //  Q31 compare to input Q7
    KN_PRINTAFLT(data->inputRangeRadius);
    KN_PRINTAFLT(data->inputZeroPoint);

    KN_PRINTAFLT(data->inputMultipler);
  }
  if (input->type == kTfLiteInt16) {
    static constexpr int kInputIntegerBits = 3;
    static constexpr int kOutputFractionalBits = 15;

    // See comments in TanhPrepare about requiring zero_point==0
    // and a power-of-two ("POT") scale.

    TF_LITE_ENSURE_EQ(context, input->params.zero_point, 0);
    TF_LITE_ENSURE_EQ(context, output->params.zero_point, 0);

    int input_scale_log2_rounded;
    bool param_scale_pot =
        CheckedLog2(input->params.scale, &input_scale_log2_rounded);

    data->input_left_shift =
        (15 - kInputIntegerBits) + input_scale_log2_rounded;
    param_scale_pot &= (data->input_left_shift == 0);

    if (param_scale_pot) {
      data->input_multiplier = 0;
    } else {
      // Calculate multiplier to change input scale to 1/(3*4096)
      // as required by the table lookup.
      // In this scaling +/-2^17 represents +/-10.7
      double multiplier =
          static_cast<double>(input->params.scale) * 4096.0 * 3.0;

      data->input_left_shift = 0;

      while (multiplier <= 32767.0 / 2.0 && data->input_left_shift <= 30) {
        data->input_left_shift++;
        multiplier = multiplier * 2.0;
      }

      data->input_multiplier = static_cast<int32_t>(multiplier);
    }

    int output_scale_log2_rounded;
    TF_LITE_ENSURE(
        context, CheckedLog2(output->params.scale, &output_scale_log2_rounded));
    TF_LITE_ENSURE_EQ(context, output_scale_log2_rounded,
                      -kOutputFractionalBits);
  }

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}
}  // namespace

void* LogisticInit(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus IA8201_LogisticPrepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  OpData* data = static_cast<OpData*>(node->user_data);

  TF_LITE_ENSURE_STATUS(CalculateArithmeticOpData(context, node, data));
  data->opt_constraint = 0;
#if defined(DMX1A_LOGISTIC_OPT) || defined(HMD1A_LOGISTIC_OPT)
  data->opt_constraint = 1;  //
#endif

  return kTfLiteOk;
}

#ifdef DMX1A_LOGISTIC_OPT
_AI fr32 Sigmoid1(fr32 x) {
  fr32 fac = seta_fr(kConstTable_Log2_Of_e, 0, 0);
  fr32 one = seta_fr(kConstTable_One, 0, 0);
  x = fpmul(fac, x, 1);
  x = pow2_fr(x);
  x = fpadd(one, x, 0);
  x = inv_fr(x);

  return x;
}

void SigmoidV_Full(float* y, const float* x, int n) {
  int jammingBit = RUR_JammingBit();
  WUR_JammingBit(1);
  int loopLim = n >> 3;  // Includes loop unrolling count of 2
  int remain = n & 3;
  ulsr128 UR_x = align_32x4_load(x);
  ulsr128 UR_y = align_32x4_store(y);
  vr128 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0,
                          0);  // no rounding is consistent with HMD
  vr128 VR_one = vseta_vr(kConstTable_One, 0, 0);
  vr128 VR_x0;
  vr128 VR_x1;
  vr128 VR_y0;
  vr128 VR_y1;
  vr128 VR_z0;
  vr128 VR_z1;

  load_32x4_vr_a(VR_x0, UR_x, x);
  load_32x4_vr_a(VR_x1, UR_x, x);
  convert_IEEE_float_to_32F_x4(VR_x0);
  convert_IEEE_float_to_32F_x4(VR_x1);

  KN_PRINT_VR(VR_x0);
  KN_PRINT_VR(VR_x1);
  VR_y0 = vmuls(VR_fac, VR_x0, 0xF);
  VR_y1 = vmuls(VR_fac, VR_x1, 0xF);
  // Groups of 8
  for (int i = 0; i < loopLim; i++) {
    pow2(VR_z0, VRQ0, VR_y0, VRQ0);
    pow2(VR_z1, VRQ0, VR_y1, VRQ0);
    pow2(VR_z0, VRQ1, VR_y0, VRQ1);
    pow2(VR_z1, VRQ1, VR_y1, VRQ1);
    pow2(VR_z0, VRQ2, VR_y0, VRQ2);
    pow2(VR_z1, VRQ2, VR_y1, VRQ2);
    pow2(VR_z0, VRQ3, VR_y0, VRQ3);
    pow2(VR_z1, VRQ3, VR_y1, VRQ3);

    VR_z0 = vadds(VR_one, VR_z0, 0);
    VR_z1 = vadds(VR_one, VR_z1, 0);

    load_32x4_vr_a(VR_x0, UR_x, x);
    load_32x4_vr_a(VR_x1, UR_x, x);

    convert_IEEE_float_to_32F_x4(VR_x0);
    convert_IEEE_float_to_32F_x4(VR_x1);
    inv(VR_z0, VRQ0, VR_z0, VRQ0);
    inv(VR_z1, VRQ0, VR_z1, VRQ0);
    inv(VR_z0, VRQ1, VR_z0, VRQ1);
    inv(VR_z1, VRQ1, VR_z1, VRQ1);
    inv(VR_z0, VRQ2, VR_z0, VRQ2);
    inv(VR_z1, VRQ2, VR_z1, VRQ2);
    inv(VR_z0, VRQ3, VR_z0, VRQ3);
    inv(VR_z1, VRQ3, VR_z1, VRQ3);

    KN_PRINT_VR(VR_z0);

    convert_32F_to_IEEE_float_x4(VR_z0);
    store_32x4_vr_a(VR_z0, UR_y, y);
    VR_y0 = vmuls(VR_fac, VR_x0, 0xF);
    KN_PRINT_VR(VR_z1);
    convert_32F_to_IEEE_float_x4(VR_z1);
    store_32x4_vr_a(VR_z1, UR_y, y);
    VR_y1 = vmuls(VR_fac, VR_x1, 0xF);
  }
  x -= 8;  // Compensate for loop priming
  if (n & 4) {
    // Group of 4
    pow2(VR_z0, VRQ0, VR_y0, VRQ0);
    pow2(VR_z0, VRQ1, VR_y0, VRQ1);
    pow2(VR_z0, VRQ2, VR_y0, VRQ2);
    pow2(VR_z0, VRQ3, VR_y0, VRQ3);

    x += 4;
    VR_z0 = vadds(VR_one, VR_z0, 0);

    inv(VR_y0, VRQ0, VR_z0, VRQ0);
    inv(VR_y0, VRQ1, VR_z0, VRQ1);
    inv(VR_y0, VRQ2, VR_z0, VRQ2);
    inv(VR_y0, VRQ3, VR_z0, VRQ3);
    KN_PRINT_VR(VR_y0);
    convert_32F_to_IEEE_float_x4(VR_y0);
    store_32x4_vr_a(VR_y0, UR_y, y);
  }
  flush_32x4(UR_y, y);

  // Remaining
  for (int i = 0; i < remain; i++) {
    fr32 frx;
    load_fr_postI(frx, x, INC1);
    unsigned arInput = *(unsigned*)&frx;
    frx = convert_IEEE_float_to_32F(arInput);
    fr32 fry = Sigmoid1(frx);

    unsigned arOutput = convert_32F_to_IEEE_float(fry);
    KN_PRINTF(arOutput);
    store_fr_postI(arOutput, y, INC1);
  }

  WUR_JammingBit(jammingBit);
}

void LogisticQuantizedInt8(
    const OpData* data,  // const AScalar &inputMultipler,
    int8_t* y, const int8_t* x, int depth) {
  int loopLim = depth >> 2;  // Includes loop unrolling count of 2
  int remain = depth & 3;
  ulsr128 UR_x;
  ulsr128 UR_y;
  vr128 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0, 0);
  vr128 VR_x0;
  vr128 VR_y0;
  vr128 VR_z0;
  vr128 VR_one = vseta_vr(kConstTable_One, 0, 0);
  // vr128 VR_two = vseta_vr(kConstTable_Two, 0, 0);
  vr128 VR_inputMulti, VR_outputZP;
  vr128 VR_q7_out, VR_out;
  vr128 VR_inputRadiusMax, VR_inputRadiusMin;
  vr128 VR_inputRadiusMaxQ7, VR_inputRadiusMinQ7;
  vr128 VR_inputZeroPoint;
  // vr128 VR_tmp ;
  int8_t* xLocal;
  int8_t* yLocal = y;
  xtbool4 xt_inOutRangeMax;
  xtbool4 xt_inOutRangeMin;
  const int32_t kOutputZeroPoint =
      0x80808080;  // output zero point, align to logistic.h

  replicate_ar(VR_inputRadiusMaxQ7, 0xf, 0x7f7f7f7f);
  replicate_ar(VR_inputRadiusMinQ7, 0xf, kOutputZeroPoint);

  replicate_ar(VR_outputZP, 0xf, kOutputZeroPoint);
  replicate_ar(VR_inputRadiusMax, 0xf, data->inputRangeRadius.fr);
  VR_inputRadiusMin = s_vnegs(VR_inputRadiusMax, 0xf);

  replicate_ar(VR_inputZeroPoint, 0xf, data->inputZeroPoint.fr);

  replicate_ar(VR_inputMulti, 0xf, data->inputMultipler.fr);

  loopLim = depth >> 2;

  // xLocal = (int8_t *)tmpAR; // This line is not required, just a temporary
  // fix for linux build error
  xLocal = (int8_t*)x;

  UR_x = align_8x4_load(xLocal);
  UR_y = align_8x4_store(yLocal);
  if (loopLim > 0) {
    load_8x4_vr_a(VR_x0, UR_x, xLocal);

    convert_16I_to_32F_x4(VR_x0, 0);

    for (int i = 0; i < loopLim - 1; i++) {
      VR_x0 = vadds(VR_x0, VR_inputZeroPoint, 0xf0);

      // compare range radius
      xt_inOutRangeMin = vle(VR_x0, VR_inputRadiusMin);
      xt_inOutRangeMax = vge(VR_x0, VR_inputRadiusMax);

      VR_z0 = vmuls(VR_x0, VR_inputMulti, 0);

      VR_z0 = vmuls(VR_fac, VR_z0, 0xf);  // 1/ 1- e^x

      pow2(VR_y0, VRQ0, VR_z0, VRQ0);
      pow2(VR_y0, VRQ1, VR_z0, VRQ1);
      pow2(VR_y0, VRQ2, VR_z0, VRQ2);
      pow2(VR_y0, VRQ3, VR_z0, VRQ3);
      VR_z0 = vadds(VR_one, VR_y0, 0);

      inv(VR_y0, VRQ0, VR_z0, VRQ0);
      inv(VR_y0, VRQ1, VR_z0, VRQ1);
      inv(VR_y0, VRQ2, VR_z0, VRQ2);
      inv(VR_y0, VRQ3, VR_z0, VRQ3);
      // Newton unnecssary for qunzation

      // VR_tmp  = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
      // VR_y0 = vmuls(VR_tmp, VR_y0, 0);

      // convert to uint8_t [ 0~ 1]

      convert_32F_to_16I_x4(VR_y0, 0, 0);  // output_in_q0

      rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, 0);
      VR_q7_out = vbool(VR_outputZP, VR_q7_out, 0x6);  // XOR 0x80 to subtract
                                                       // -128
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

      VR_out = vsel(VR_inputRadiusMinQ7, VR_out, xt_inOutRangeMin);
      VR_out = vsel(VR_inputRadiusMaxQ7, VR_out, xt_inOutRangeMax);

      store_8x4_vr_a(VR_out, UR_y, yLocal);
      //   KN_PRINTX_VR128(VR_q7_out);
      // VR_y0 = vsel(VR_y0, VR_zero, xt_inputDiff);

      load_8x4_vr_a(VR_x0, UR_x, xLocal);
      convert_16I_to_32F_x4(VR_x0, 0);
      //				VR_sum = vadds(VR_sum, VR_y0, 0);
    }
    VR_x0 = vadds(VR_x0, VR_inputZeroPoint, 0xf0);

    // compare range radius
    xt_inOutRangeMin = vle(VR_x0, VR_inputRadiusMin);
    xt_inOutRangeMax = vge(VR_x0, VR_inputRadiusMax);
    VR_z0 = vmuls(VR_x0, VR_inputMulti, 0);

    VR_z0 = vmuls(VR_fac, VR_z0, 0xf);  // 1/ 1- e^x

    pow2(VR_y0, VRQ0, VR_z0, VRQ0);
    pow2(VR_y0, VRQ1, VR_z0, VRQ1);
    pow2(VR_y0, VRQ2, VR_z0, VRQ2);
    pow2(VR_y0, VRQ3, VR_z0, VRQ3);
    VR_z0 = vadds(VR_one, VR_y0, 0);
    //  KN_PRINT_VR128(VR_z0);
    inv(VR_y0, VRQ0, VR_z0, VRQ0);
    inv(VR_y0, VRQ1, VR_z0, VRQ1);
    inv(VR_y0, VRQ2, VR_z0, VRQ2);
    inv(VR_y0, VRQ3, VR_z0, VRQ3);
    // Newton unnecssary for qunzation
    // VR_tmp  = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
    // VR_y0 = vmuls(VR_tmp, VR_y0, 0);

    convert_32F_to_16I_x4(VR_y0, 0, 0);  // output_in_q0
    // KN_PRINTX_VR128(VR_y0);
    rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, 0);
    VR_q7_out =
        vbool(VR_outputZP, VR_q7_out, 0x6);  // XOR 0x80 to subtract -128

    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

    VR_out = vsel(VR_inputRadiusMinQ7, VR_out, xt_inOutRangeMin);
    VR_out = vsel(VR_inputRadiusMaxQ7, VR_out, xt_inOutRangeMax);
    store_8x4_vr_a(VR_out, UR_y, yLocal);
    flush_8x4(UR_y, yLocal);
  }
  if (remain) {
    load_8x4_vr_a(VR_x0, UR_x, xLocal);

    convert_16I_to_32F_x4(VR_x0, 0);
    VR_x0 = vadds(VR_x0, VR_inputZeroPoint, 0xf0);

    // compare range radius
    xt_inOutRangeMin = vle(VR_x0, VR_inputRadiusMin);
    xt_inOutRangeMax = vge(VR_x0, VR_inputRadiusMax);

    VR_z0 = vmuls(VR_x0, VR_inputMulti, 0);

    VR_z0 = vmuls(VR_fac, VR_z0, 0xf);  // 1/ 1- e^x
    // at most 3 times

    pow2(VR_y0, VRQ0, VR_z0, VRQ0);
    pow2(VR_y0, VRQ1, VR_z0, VRQ1);
    pow2(VR_y0, VRQ2, VR_z0, VRQ2);

    VR_z0 = vadds(VR_one, VR_y0, 0);
    //  KN_PRINT_VR128(VR_z0);
    inv(VR_y0, VRQ0, VR_z0, VRQ0);
    inv(VR_y0, VRQ1, VR_z0, VRQ1);
    inv(VR_y0, VRQ2, VR_z0, VRQ2);
    // VR_tmp  = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
    // VR_y0 = vmuls(VR_tmp, VR_y0, 0);

    // convert to uint8_t [ 0~ 1]

    convert_32F_to_16I_x4(VR_y0, 0, 0);       // output_in_q0
    rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, 0);  // ronding

    VR_q7_out = vbool(VR_outputZP, VR_q7_out, 0x6);  // XOR 0x80 to subtract
                                                     // -128
    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
    VR_out = vsel(VR_inputRadiusMinQ7, VR_out, xt_inOutRangeMin);
    VR_out = vsel(VR_inputRadiusMaxQ7, VR_out, xt_inOutRangeMax);

    for (int i = 0; i < remain; i++) {
      store8x1_vr_postI(VR_out, yLocal, INC1, VRQ0);
      VR_out = vpermsi(VR_out, VR_out, 0, 0);
    }
  }
}

#endif
#ifdef HMD1A_LOGISTIC_OPT

_AI fr32 Sigmoid1(fr32 x) {
  fr32 fac = seta_fr(kConstTable_Log2_Of_e, 0);
  fr32 one = seta_fr(kConstTable_One, 0);
  x = fmuls(fac, x, 1);
  x = pow2(x);
  x = fadds(one, x, 0);
  x = inv(x);

  return x;
}

void SigmoidV_Full(float* y, const float* x, int n) {
  int jammingBit = RUR_JammingBit();
  WUR_JammingBit(1);
  int loopLim = n >> 2;  // Includes loop unrolling count of 2
  int remain = n & 1;
  ulsr32 UR_x = align_32x2_load(x);
  ulsr32 UR_y = align_32x2_store(y);
  vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0);
  vr64 VR_one = vseta_vr(kConstTable_One, 0);
  vr64 VR_x0;
  vr64 VR_x1;
  vr64 VR_y0;
  vr64 VR_y1;
  vr64 VR_z0;
  vr64 VR_z1;

  load_32x2_vr_a(VR_x0, UR_x, x);
  load_32x2_vr_a(VR_x1, UR_x, x);
  convert_IEEE_float_to_32F_x2(VR_x0);
  convert_IEEE_float_to_32F_x2(VR_x1);
  VR_y0 = vmuls(VR_fac, VR_x0, 3);
  VR_y1 = vmuls(VR_fac, VR_x1, 3);
  // Groups of 4
  for (int i = 0; i < loopLim; i++) {
    set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
    set_VRL(VR_z1, pow2(get_VRL(VR_y1)));
    set_VRH(VR_z0, pow2(get_VRH(VR_y0)));
    set_VRH(VR_z1, pow2(get_VRH(VR_y1)));

    VR_z0 = vadds(VR_one, VR_z0, 0);
    VR_z1 = vadds(VR_one, VR_z1, 0);

    load_32x2_vr_a(VR_x0, UR_x, x);
    load_32x2_vr_a(VR_x1, UR_x, x);

    convert_IEEE_float_to_32F_x2(VR_x0);
    convert_IEEE_float_to_32F_x2(VR_x1);
    set_VRL(VR_z0, inv(get_VRL(VR_z0)));
    set_VRL(VR_z1, inv(get_VRL(VR_z1)));
    set_VRH(VR_z0, inv(get_VRH(VR_z0)));
    set_VRH(VR_z1, inv(get_VRH(VR_z1)));
    convert_32F_to_IEEE_float_x2(VR_z0);
    store_32x2_vr_a(VR_z0, UR_y, y);
    VR_y0 = vmuls(VR_fac, VR_x0, 3);
    convert_32F_to_IEEE_float_x2(VR_z1);
    store_32x2_vr_a(VR_z1, UR_y, y);
    VR_y1 = vmuls(VR_fac, VR_x1, 3);
  }
  x -= 4;  // Compensate for loop priming
  if (n & 2) {
    // Group of 2
    set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
    set_VRH(VR_z0, pow2(get_VRH(VR_y0)));

    x += 2;
    VR_z0 = vadds(VR_one, VR_z0, 0);

    set_VRL(VR_y0, inv(get_VRL(VR_z0)));
    set_VRH(VR_y0, inv(get_VRH(VR_z0)));
    convert_32F_to_IEEE_float_x2(VR_y0);
    store_32x2_vr_a(VR_y0, UR_y, y);
  }
  flush_32x2(UR_y, y);

  // Remaining
  if (remain) {
    fr32 frx;
    load_fr_postI(frx, x, INC1);
    set_VRL(VR_x0, frx);
    convert_IEEE_float_to_32F_x2(VR_x0);
    fr32 fry = Sigmoid1(get_VRL(VR_x0));
    set_VRL(VR_y0, fry);
    convert_32F_to_IEEE_float_x2(VR_y0);
    store32x1_vr_postI(VR_y0, y, INC1, VRQ0);
    // store_fr_postI(fry, y, INC1);
  }
  WUR_JammingBit(jammingBit);
}

void LogisticQuantizedInt8(
    const OpData* data,  // const AScalar &inputMultipler,
    int8_t* y, const int8_t* x, int depth) {
  int loopLim = depth >> 1;  // Includes loop unrolling count of 2
  int remain = depth & 1;
  // ulsr32 UR_x;

  vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0);
  vr64 VR_x0;
  vr64 VR_y0;
  vr64 VR_z0;
  vr64 VR_one = vseta_vr(kConstTable_One, 0);
  // vr128 VR_two = vseta_vr(kConstTable_Two, 0);
  vr64 VR_inputMulti, VR_outputZP;
  vr64 VR_q7_out, VR_out;
  vr64 VR_inputRadiusMax, VR_inputRadiusMin;
  vr64 VR_inputRadiusMaxQ7, VR_inputRadiusMinQ7;
  vr64 VR_inputZeroPoint;
  // vr128 VR_tmp ;
  int8_t* xLocal;
  int8_t* yLocal = y;
  atbool xt_inOutRangeMax;
  atbool xt_inOutRangeMin;

  const int32_t kOutputZeroPoint =
      0x80808080;  // output zero point, align to logistic.h

  replicate_ar(VR_inputRadiusMaxQ7, 0x3, 0x7f7f7f7f);
  replicate_ar(VR_inputRadiusMinQ7, 0x3, kOutputZeroPoint);

  replicate_ar(VR_outputZP, 0x3, kOutputZeroPoint);
  replicate_ar(VR_inputRadiusMax, 0x3, data->inputRangeRadius.fr);
  VR_inputRadiusMin = s_vneg(VR_inputRadiusMax);

  replicate_ar(VR_inputZeroPoint, 0x3, data->inputZeroPoint.fr);

  replicate_ar(VR_inputMulti, 0x3, data->inputMultipler.fr);

  // loopLim = depth>> 1;

  // xLocal = (int8_t *)tmpAR; // This line is not required, just a temporary
  // fix for linux build error

  xLocal = (int8_t*)x;
  // UR_x = align_8x2_load(xLocal);
  if (loopLim > 0) {
    load8x2_vr_postI(VR_x0, xLocal, INC1);

    convert_16I_to_32F_x2(VR_x0, 0);

    for (int i = 0; i < loopLim - 1; i++) {
      VR_x0 = vadds(VR_x0, VR_inputZeroPoint, 0xa);

      // compare range radius
      xt_inOutRangeMin = vle(VR_x0, VR_inputRadiusMin);
      xt_inOutRangeMax = vge(VR_x0, VR_inputRadiusMax);

      VR_z0 = vmuls(VR_x0, VR_inputMulti, 0);

      VR_z0 = vmuls(VR_fac, VR_z0, 0x3);  // 1/ 1- e^x

      // pow2(VR_y0, VRQ0, VR_z0, VRQ0);
      set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
      // pow2(VR_y0, VRQ1, VR_z0, VRQ1);
      set_VRH(VR_y0, pow2(get_VRH(VR_z0)));
      VR_z0 = vadds(VR_one, VR_y0, 0);

      // inv(VR_y0, VRQ0, VR_z0, VRQ0);
      set_VRL(VR_y0, inv(get_VRL(VR_z0)));
      // inv(VR_y0, VRQ1, VR_z0, VRQ1);
      set_VRH(VR_y0, inv(get_VRH(VR_z0)));
      // Newton unnecssary for qunzation

      // VR_tmp  = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
      // VR_y0 = vmuls(VR_tmp, VR_y0, 0);

      // convert to uint8_t [ 0~ 1]

      convert_32F_to_16I_x2(VR_y0, 0, 0);  // output_in_q0

      rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, VR_y0, 0);
      VR_q7_out = vbool(VR_outputZP, VR_q7_out, 0x6);  // XOR 0x80 to subtract
                                                       // -128
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
      VR_out = vsel(VR_inputRadiusMinQ7, VR_out, xt_inOutRangeMin);
      VR_out = vsel(VR_inputRadiusMaxQ7, VR_out, xt_inOutRangeMax);

      store8x1_vr_postI(VR_out, yLocal, INC1, VRQ0);
      store8x1_vr_postI(VR_out, yLocal, INC1, VRQ1);
      //   KN_PRINTX_VR128(VR_q7_out);
      // VR_y0 = vsel(VR_y0, VR_zero, xt_inputDiff);

      load8x2_vr_postI(VR_x0, xLocal, INC1);
      convert_16I_to_32F_x2(VR_x0, 0);
      //				VR_sum = vadds(VR_sum, VR_y0, 0);
    }
    VR_x0 = vadds(VR_x0, VR_inputZeroPoint, 0xa);

    // compare range radius
    xt_inOutRangeMin = vle(VR_x0, VR_inputRadiusMin);
    xt_inOutRangeMax = vge(VR_x0, VR_inputRadiusMax);
    VR_z0 = vmuls(VR_x0, VR_inputMulti, 0);

    VR_z0 = vmuls(VR_fac, VR_z0, 0x3);  // 1/ 1- e^x

    // pow2(VR_y0, VRQ0, VR_z0, VRQ0);
    set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
    // pow2(VR_y0, VRQ1, VR_z0, VRQ1);
    set_VRH(VR_y0, pow2(get_VRH(VR_z0)));
    VR_z0 = vadds(VR_one, VR_y0, 0);

    set_VRL(VR_y0, inv(get_VRL(VR_z0)));

    set_VRH(VR_y0, inv(get_VRH(VR_z0)));

    // convert to uint8_t [ 0~ 1]

    convert_32F_to_16I_x2(VR_y0, 0, 0);  // output_in_q0

    // KN_PRINTX_VR128(VR_y0);
    rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, VR_y0, 0);
    VR_q7_out =
        vbool(VR_outputZP, VR_q7_out, 0x6);  // XOR 0x80 to subtract -128

    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);

    VR_out = vsel(VR_inputRadiusMinQ7, VR_out, xt_inOutRangeMin);

    VR_out = vsel(VR_inputRadiusMaxQ7, VR_out, xt_inOutRangeMax);

    store8x1_vr_postI(VR_out, yLocal, INC1, VRQ0);
    store8x1_vr_postI(VR_out, yLocal, INC1, VRQ1);
  }
  if (remain) {
    load8x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);

    convert_16I_to_32F_x2(VR_x0, 0);
    VR_x0 = vsub(VR_x0, VR_inputZeroPoint);

    // compare range radius
    xt_inOutRangeMin = vle(VR_x0, VR_inputRadiusMin);
    xt_inOutRangeMax = vge(VR_x0, VR_inputRadiusMax);

    VR_z0 = vmuls(VR_x0, VR_inputMulti, 0);

    VR_z0 = vmuls(VR_fac, VR_z0, 0x3);  // 1/ 1- e^x
    // at most 3 times

    // pow2(VR_y0, VRQ0, VR_z0, VRQ0);
    set_VRL(VR_y0, pow2(get_VRL(VR_z0)));

    VR_z0 = vadds(VR_one, VR_y0, 0);
    //  KN_PRINT_VR128(VR_z0);
    // inv(VR_y0, VRQ0, VR_z0, VRQ0);
    set_VRL(VR_y0, inv(get_VRL(VR_z0)));
    // inv(VR_y0, VRQ2, VR_z0, VRQ2);
    // VR_tmp  = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
    // VR_y0 = vmuls(VR_tmp, VR_y0, 0);

    // convert to uint8_t [ 0~ 1]

    convert_32F_to_16I_x2(VR_y0, 0, 0);              // output_in_q0
    rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, VR_y0, 0);  // ronding

    VR_q7_out = vbool(VR_outputZP, VR_q7_out, 0x6);  // XOR 0x80 to subtract
                                                     // -128
    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
    VR_out = vsel(VR_inputRadiusMinQ7, VR_out, xt_inOutRangeMin);
    VR_out = vsel(VR_inputRadiusMaxQ7, VR_out, xt_inOutRangeMax);

    store8x1_vr_postI(VR_out, yLocal, INC1, VRQ0);
  }
}

#endif

void EvalLogisticFloat(const TfLiteEvalTensor* input,
                       TfLiteEvalTensor* output) {
  const int flat_size = MatchingFlatSize(tflite::micro::GetTensorShape(input),
                                         tflite::micro::GetTensorShape(output));
  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input), flat_size);
#if defined(DMX1A_LOGISTIC_OPT) || defined(HMD1A_LOGISTIC_OPT)
  SigmoidV_Full((float*)tflite::micro::GetTensorData<float>(output),
                tflite::micro::GetTensorData<float>(input), flat_size);
#else
  reference_ops::Logistic(tflite::micro::GetTensorShape(input),
                          tflite::micro::GetTensorData<float>(input),
                          tflite::micro::GetTensorShape(output),
                          tflite::micro::GetTensorData<float>(output));
#endif
  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output), flat_size);
}
TfLiteStatus IA8201_LogisticEval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kLogisticInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kLogisticOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  OpData* data = static_cast<OpData*>(node->user_data);

#ifndef REMOVE_FLOAT_SUPPORT
  if (input->type == kTfLiteFloat32) {
    switch (output->type) {
      case kTfLiteFloat32: {
        EvalLogisticFloat(input, output);

        return kTfLiteOk;
      }
      default:
        TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
                           TfLiteTypeGetName(input->type),
                           TfLiteTypeGetName(output->type));
        return kTfLiteError;
    }
  } else if (input->type == kTfLiteInt16) {
    switch (output->type) {
      case kTfLiteInt16: {
        reference_integer_ops::Logistic(
            data->input_multiplier, data->input_left_shift,
            NumElements(input->dims),
            tflite::micro::GetTensorData<int16_t>(input),
            tflite::micro::GetTensorData<int16_t>(output));
        return kTfLiteOk;
      }
      default:
        TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
                           TfLiteTypeGetName(input->type),
                           TfLiteTypeGetName(output->type));
        return kTfLiteError;
    }
  } else
#endif
      if (input->type == kTfLiteInt8) {
    switch (output->type) {
      case kTfLiteInt8: {
#if !(defined(DMX1A_LOGISTIC_OPT) || defined(HMD1A_LOGISTIC_OPT))
        reference_integer_ops::Logistic(
            data->input_zero_point, data->input_range_radius,
            data->input_multiplier, data->input_left_shift,
            NumElements(input->dims),
            tflite::micro::GetTensorData<int8_t>(input),
            tflite::micro::GetTensorData<int8_t>(output));
        // KN_PRINT_Q7_SIZE( tflite::micro::GetTensorData<int8_t>(output),
        // ElementCount(*input->dims) );
#else
        LogisticQuantizedInt8(data,
                              tflite::micro::GetTensorData<int8_t>(output),
                              tflite::micro::GetTensorData<int8_t>(input),
                              NumElements(input->dims));

#endif
        KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                         ElementCount(*input->dims));
        return kTfLiteOk;
      }
      default:
        TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
                           TfLiteTypeGetName(input->type),
                           TfLiteTypeGetName(output->type));
        return kTfLiteError;
    }
  } else {
    // TODO(b/141211002): Also support other data types once we have supported
    // temporary tensors in TFLM.
    TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
                       TfLiteTypeGetName(input->type),
                       TfLiteTypeGetName(output->type));
    return kTfLiteError;
  }
  return kTfLiteOk;
}

//}  // namespace activations

TFLMRegistration Register_LOGISTIC() {
  return tflite::micro::RegisterOp(LogisticInit,
                                   /*prepare=*/IA8201_LogisticPrepare,
                                   /*invoke=*/IA8201_LogisticEval);
}
//}  // namespace micro
//}  // namespace ops
}  // namespace tflite
