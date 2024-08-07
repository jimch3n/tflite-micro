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
#include "tensorflow/lite/micro/ia700/config.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/tanh.h"

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/tanh.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_utils.h"

#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
namespace tflite {
//namespace ops {
//namespace micro {
//namespace activations {
namespace {
constexpr int kInputTensor = 0;
constexpr int kOutputTensor = 0;

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

void* TanhInit(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus CalculateArithmeticOpData(TfLiteContext* context, TfLiteNode* node,
                                       OpData* data) {
  MicroContext* micro_context = GetMicroContext(context);
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);

  TF_LITE_ENSURE_TYPES_EQ(context, input->type, output->type);

  if (input->type == kTfLiteInt8) {
    static constexpr int kInputIntegerBits = 4;
    const double input_real_multiplier =
        static_cast<double>(input->params.scale) *
        static_cast<double>(1 << (31 - kInputIntegerBits));

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

    // These operators are implemented in fixed-point arithmetic,
    // which intrinsically wants symmetric ranges (zero_point==0)
    // and power-of-two scales (power-of-two is abbreviated below as POT).
    // While more general support would be possible by means of rescaling,
    // that would add some overhead and some loss of accuracy and wouldn't
    // be used at the moment as current quantized LSTM applications are
    // happy with symmetric, power-of-two-scales quantization. So we just
    // implement that narrow case only for now.

    TF_LITE_ENSURE_EQ(context, input->params.zero_point, 0);
    TF_LITE_ENSURE_EQ(context, output->params.zero_point, 0);

    int input_scale_log2_rounded;
    bool param_scale_pot =
        CheckedLog2(input->params.scale, &input_scale_log2_rounded);

    data->input_left_shift =
        (15 - kInputIntegerBits) + input_scale_log2_rounded;
    param_scale_pot &=
        (data->input_left_shift == 0 || data->input_left_shift == 1);

    if (param_scale_pot) {
      data->input_multiplier = 0;
    } else {
      // Calculate multiplier to change input scale to 1/(3*4096)
      // as required by the table lookup.
      // The number 3.0 in the multiplier comes from here,
      // because the interval is [-10.7, 10.7] instead of [-8, 8].
      // So, in this scaling +/-2^17 represents +/-10.7.

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

TfLiteStatus TanhPrepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);

  OpData* data = static_cast<OpData*>(node->user_data);

  MicroContext* micro_context = GetMicroContext(context);
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  data->input_zero_point = input->params.zero_point;
  TF_LITE_ENSURE_OK(context, CalculateArithmeticOpData(context, node, data));
  micro_context->DeallocateTempTfLiteTensor(input);
  return kTfLiteOk;
}

}  // namespace

#ifdef HEMILITE_TANH_OPT
_AI fr32 Tanh1(fr32 x) {
  fr32 fac = seta_fr(kConstTable_Log2_Of_e, 0);
  fr32 one = seta_fr(kConstTable_One, 0);
  fr32 two = seta_fr(kConstTable_Two, 0);
  fr32 denumer, numer, inv1;

  fac = fmuls(two, fac, 0);
  x = fmuls(fac, x, 0);
  x = pow2(x);
  denumer = fadds(one, x, 0);  // exp(2*x) +1
  numer = fadds(one, x, 1);    // exp(2*x) -1
  inv1 = inv(denumer);
  // Newton's method
  two = fmacs(two, inv1, denumer, 1);  // 2 - (x/x)
  inv1 = fmuls(two, inv1, 0);
  x = fmuls(inv1, numer, 0);

  return x;
}
void TanhV(float* y, const float* x, int n) {
  int jammingBit = RUR_JammingBit();
  WUR_JammingBit(1);
  int loopLim = n >> 2;  // Includes loop unrolling count of 2
  int remain = n & 1;
  ulsr32 UR_x = align_32x2_load(x);
  ulsr32 UR_y = align_32x2_store(y);
  vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0);
  vr64 VR_one = vseta_vr(kConstTable_One, 0);
  vr64 VR_two = vseta_vr(kConstTable_Two, 0);
  vr64 VR_x0;
  vr64 VR_x1;
  vr64 VR_y0;
  vr64 VR_y1;
  vr64 VR_z0;
  vr64 VR_z1;
  vr64 VR_n0;
  vr64 VR_n1;

  // VR_fac = 2*log2e
  VR_fac = vmuls(VR_fac, VR_two, 0);
  load_32x2_vr_a(VR_x0, UR_x, x);
  load_32x2_vr_a(VR_x1, UR_x, x);
  convert_IEEE_float_to_32F_x2(VR_x0);
  convert_IEEE_float_to_32F_x2(VR_x1);
  VR_y0 = vmuls(VR_fac, VR_x0, 0);
  VR_y1 = vmuls(VR_fac, VR_x1, 0);
  // Groups of 4
  for (int i = 0; i < loopLim; i++) {
    vr64 VR_t1;

    set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
    set_VRL(VR_z1, pow2(get_VRL(VR_y1)));
    set_VRH(VR_z0, pow2(get_VRH(VR_y0)));
    set_VRH(VR_z1, pow2(get_VRH(VR_y1)));

    VR_n0 = vadds(VR_one, VR_z0, 0x5);  //  exp(2*x) -1
    VR_z0 = vadds(VR_one, VR_z0, 0);    //  exp(2*x) +1

    VR_n1 = vadds(VR_one, VR_z1, 0x5);
    VR_z1 = vadds(VR_one, VR_z1, 0);

    load_32x2_vr_a(VR_x0, UR_x, x);
    load_32x2_vr_a(VR_x1, UR_x, x);

    convert_IEEE_float_to_32F_x2(VR_x0);
    convert_IEEE_float_to_32F_x2(VR_x1);
    set_VRL(VR_y0, inv(get_VRL(VR_z0)));
    set_VRL(VR_y1, inv(get_VRL(VR_z1)));
    set_VRH(VR_y0, inv(get_VRH(VR_z0)));
    set_VRH(VR_y1, inv(get_VRH(VR_z1)));

    // Newton's method
    VR_t1 = vmacs(VR_two, VR_y0, VR_z0, 3, 0);
    VR_y0 = vmuls(VR_t1, VR_y0, 0);

    // Newton's method
    VR_t1 = vmacs(VR_two, VR_y1, VR_z1, 3, 0);
    VR_y1 = vmuls(VR_t1, VR_y1, 0);

    VR_y0 = vmuls(VR_n0, VR_y0, 0);
    VR_y1 = vmuls(VR_n1, VR_y1, 0);
    convert_32F_to_IEEE_float_x2(VR_y0);
    store_32x2_vr_a(VR_y0, UR_y, y);
    VR_y0 = vmuls(VR_fac, VR_x0, 0);
    convert_32F_to_IEEE_float_x2(VR_y1);
    store_32x2_vr_a(VR_y1, UR_y, y);
    VR_y1 = vmuls(VR_fac, VR_x1, 0);
  }
  x -= 4;  // Compensate for loop priming
  if (n & 2) {
    // Group of 2
    set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
    set_VRH(VR_z0, pow2(get_VRH(VR_y0)));

    x += 2;
    VR_n0 = vadds(VR_one, VR_z0, 0x5);
    VR_z0 = vadds(VR_one, VR_z0, 0);

    set_VRL(VR_y0, inv(get_VRL(VR_z0)));
    set_VRH(VR_y0, inv(get_VRH(VR_z0)));
    // Newton's method
    VR_n1 = vmacs(VR_two, VR_y0, VR_z0, 3, 0);
    VR_y0 = vmuls(VR_n1, VR_y0, 0);

    VR_y0 = vmuls(VR_n0, VR_y0, 0);
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

    fr32 fry = Tanh1(get_VRL(VR_x0));
    set_VRL(VR_y0, fry);
    convert_32F_to_IEEE_float_x2(VR_y0);
    store32x1_vr_postI(VR_y0, y, INC1, VRQ0);
    //  store_fr_postI(fry, y, INC1);
  }
  WUR_JammingBit(jammingBit);
}
void TanhQuantizedInt8(
	const OpData* data,  // const AScalar &inputMultipler,
	int8_t* y, const int8_t* x, int depth) {
	int loopLim = depth >> 2;  // Includes loop unrolling count of 2
	int remain = depth & 3;
	//ulsr32 UR_x;

	vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e,  0);
	vr64 VR_x0;
	vr64 VR_y0;
	vr64 VR_z0, VR_n0;
	vr64 VR_one = vseta_vr(kConstTable_One, 0);
	vr64 VR_two = vseta_vr(kConstTable_Two, 0);
	// vr128 VR_two = vseta_vr(kConstTable_Two, 0, 0);
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

	loopLim = depth >> 1;

	// xLocal = (int8_t *)tmpAR; // This line is not required, just a temporary
	// fix for linux build error
	xLocal = (int8_t*)x;

	//UR_x = align_8x4_load(xLocal);
	VR_fac = vmuls(VR_two, VR_fac, 0);
	if (loopLim > 0) {


		for (int i = 0; i < loopLim; i++) {
			//load8x2_vr_postI(VR_x0,  xLocal, INC1);
			load8x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);
			load8x1_vr_postI(VR_x0, xLocal, INC1, VRQ1);

			convert_16I_to_32F_x2(VR_x0, 0);
			// input data[i] - input_zero_point
			VR_x0 = vadds(VR_x0, VR_inputZeroPoint, 0xa);

			// compare range radius
			xt_inOutRangeMin = vle(VR_x0, VR_inputRadiusMin);
			xt_inOutRangeMax = vge(VR_x0, VR_inputRadiusMax);
			// input_data * mulitplier
			VR_x0 = vmuls(VR_x0, VR_inputMulti, 0);
			/// tanh start


			VR_y0 = vmuls(VR_fac, VR_x0, 0);
			set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
			set_VRH(VR_z0, pow2(get_VRH(VR_y0)));


			VR_n0 = vadds(VR_one, VR_z0, 0x5);// 1- exp
			VR_z0 = vadds(VR_one, VR_z0, 0x0);

			set_VRL(VR_y0, inv(get_VRL(VR_z0)));
			set_VRH(VR_y0, inv(get_VRH(VR_z0)));


			// Newton unnecssary for qunzation

			VR_y0 = vmuls(VR_n0, VR_y0, 0);

			//	vr128 VR_tmp  = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
			//	 VR_y0 = vmuls(VR_tmp, VR_y0, 0);

			// convert to uint8_t [ 0~ 1]

			convert_32F_to_16I_x2(VR_y0, 0, 0);  // output_in_q0

			rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, VR_y0, 1);
			//VR_q7_out = vbool(VR_outputZP, VR_q7_out, 0x6);  // XOR 0x80 to subtract
			// -128
			VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
			//VR_out = vexp_adji(VR_y0, 0);
			VR_out = vsel(VR_inputRadiusMinQ7, VR_out, xt_inOutRangeMin);
			VR_out = vsel(VR_inputRadiusMaxQ7, VR_out, xt_inOutRangeMax);

			store8x1_vr_postI(VR_out, yLocal, INC1, VRQ0);
			store8x1_vr_postI(VR_out, yLocal, INC1, VRQ1);
		}

	}
	if (remain) {
		load8x1_vr_postI(VR_x0,  xLocal, INC1, VRQ0);

		convert_16I_to_32F_x2(VR_x0, 0);
		// input data[i] - input_zero_point
		VR_x0 = vadds(VR_x0, VR_inputZeroPoint, 0xa);

		// compare range radius
		xt_inOutRangeMin = vle(VR_x0, VR_inputRadiusMin);
		xt_inOutRangeMax = vge(VR_x0, VR_inputRadiusMax);
		// input_data * mulitplier
		VR_x0 = vmuls(VR_x0, VR_inputMulti, 0);
		/// tanh start

		VR_y0 = vmuls(VR_fac, VR_x0, 0);

		set_VRL(VR_z0, pow2(get_VRL(VR_y0)));

		VR_n0 = vadds(VR_one, VR_z0, 0x5);// 1- exp
		VR_z0 = vadds(VR_one, VR_z0, 0x0);

		set_VRL(VR_y0, inv(get_VRL(VR_z0)));

		VR_y0 = vmuls(VR_n0, VR_y0, 0);

		// VR_tmp  = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
		// VR_y0 = vmuls(VR_tmp, VR_y0, 0);

		// convert to uint8_t [ 0~ 1]

		convert_32F_to_16I_x2(VR_y0, 0, 0);  // output_in_q0
											 //VR_out = vexp_adji(VR_y0, 0);
		rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, VR_y0, 1);
		//VR_q7_out = vbool(VR_outputZP, VR_q7_out, 0x6);  // XOR 0x80 to subtract
		// -128
		VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);

		VR_out = vsel(VR_inputRadiusMinQ7, VR_out, xt_inOutRangeMin);
		VR_out = vsel(VR_inputRadiusMaxQ7, VR_out, xt_inOutRangeMax);


		store8x1_vr_postI(VR_out, yLocal, INC1, VRQ0);

		
	}
}

#endif
void EvalTanhFloat(const TfLiteEvalTensor* input, TfLiteEvalTensor* output) {
  const int flat_size = MatchingFlatSize(tflite::micro::GetTensorShape(input),
                                         tflite::micro::GetTensorShape(output));
  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input), flat_size);
#if defined(HEMILITE_TANH_OPT)

  TanhV((float*)tflite::micro::GetTensorData<float>(output),
        tflite::micro::GetTensorData<float>(input), flat_size);
#else
  {
    reference_ops::Tanh(tflite::micro::GetTensorShape(input),
                        tflite::micro::GetTensorData<float>(input),
                        tflite::micro::GetTensorShape(output),
                        tflite::micro::GetTensorData<float>(output));
  }
#endif
  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output), flat_size);
}
TfLiteStatus TanhEval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData& data = *(static_cast<const OpData*>(node->user_data));

  switch (input->type) {
#ifndef REMOVE_FLOAT_SUPPORT
    case kTfLiteFloat32: {
      EvalTanhFloat(input, output);
      // reference_ops::Tanh(tflite::micro::GetTensorShape(input),
      //                   tflite::micro::GetTensorData<float>(input),
      //                   tflite::micro::GetTensorShape(output),
      //                   tflite::micro::GetTensorData<float>(output));
      return kTfLiteOk;
    } break;
#endif
    case kTfLiteInt16: {
      TanhParams params;
      params.input_left_shift = data.input_left_shift;
      reference_ops::Tanh(params, tflite::micro::GetTensorShape(input),
                          tflite::micro::GetTensorData<int16_t>(input),
                          tflite::micro::GetTensorShape(output),
                          tflite::micro::GetTensorData<int16_t>(output));
      return kTfLiteOk;
    } break;
    case kTfLiteInt8: {
		 KN_PRINT_Q7_SIZE( tflite::micro::GetTensorData<int8_t>(input),
			ElementCount(*input->dims));
#if defined(HEMILITE_TANH_OPT)
		{
			 TanhQuantizedInt8(&data,
				 tflite::micro::GetTensorData<int8_t>(output),
				 tflite::micro::GetTensorData<int8_t>(input),
				 NumElements(input->dims));
			
		}
#else
      reference_integer_ops::Tanh(
          data.input_zero_point, data.input_range_radius, data.input_multiplier,
          data.input_left_shift, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int8_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int8_t>(output));
#endif

		 KN_PRINT_Q7_SIZE( tflite::micro::GetTensorData<int8_t>(output),
			ElementCount(*output->dims));
      return kTfLiteOk;
    } break;
    default:
      TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
                         TfLiteTypeGetName(input->type),
                         TfLiteTypeGetName(output->type));
      return kTfLiteError;
  }
}

//}  // namespace activations

TFLMRegistration Register_TANH() {
  return tflite::micro::RegisterOp(TanhInit,

                                   /*prepare=*/TanhPrepare,
                                   /*invoke=*/TanhEval);
}
//}  // namespace micro
//}  // namespace ops
}  // namespace tflite
