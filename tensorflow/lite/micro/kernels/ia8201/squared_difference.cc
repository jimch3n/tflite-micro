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
#include "tensorflow/lite/micro/ia8201/config.h"

#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/binary_function.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/add.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_context.h"
#include "tensorflow/lite/micro/micro_log.h"

#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {
    namespace {
   //     namespace micro {
     //       namespace squared_difference {
    constexpr int kInputTensor1 = 0;
    constexpr int kInputTensor2 = 1;
    constexpr int kOutputTensor = 0;
    typedef enum {
        SQDF_OPT_NONE = 0,
        SQDF_OPT_TYPE1 = 1, //,ELEMENT_WISE = 1,
        SQDF_OPT_TYPE2 = 2, //INPUT1_LAST_EQ_INPUT2 size, input1 == output 1
        SQDF_OPT_TYPE3 = 3 // input2 is constat value 1,
    }mul_opt_type;

    struct OpData {
        bool requires_broadcast;
        int opt_constraint_float;
        ArithmeticParams arithmetic_params;
    };

    template <typename T>
    T SquaredDifference(T input1, T input2) {
        const T difference = input1 - input2;
        return difference * difference;
    }

    void* SquaredDifferenceInit(TfLiteContext* context, const char* buffer,
        size_t length) {
        TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
        return context->AllocatePersistentBuffer(context, sizeof(OpData));
    }
    void PrepareQuantized(
        const TfLiteQuantizationParams& input1_quantization_params,
        const TfLiteQuantizationParams& input2_quantization_params,
        const TfLiteQuantizationParams& output_quantization_params,
        const int left_shift,
        const int32_t quantized_activation_min,
        const int32_t quantized_activation_max, OpData* data) {
        data->arithmetic_params.input1_offset =
            -input1_quantization_params.zero_point;
        data->arithmetic_params.input2_offset =
            -input2_quantization_params.zero_point;
        data->arithmetic_params.output_offset =
            output_quantization_params.zero_point;
        data->arithmetic_params.left_shift = left_shift;
        const double twice_max_input_scale =
            2.0 * static_cast<double>(
                    std::max(input1_quantization_params.scale,
                                input2_quantization_params.scale));
        const double real_input1_multiplier =
            static_cast<double>(input1_quantization_params.scale) /
            twice_max_input_scale;
        double real_input2_multiplier =
            static_cast<double>(input2_quantization_params.scale) /
            twice_max_input_scale;
        const double real_output_multiplier =
            (twice_max_input_scale * twice_max_input_scale) /
            static_cast<double>(
                (1 << data->arithmetic_params.left_shift * 2) *
                output_quantization_params.scale);
        QuantizeMultiplierSmallerThanOneExp(
            real_input1_multiplier,
            &data->arithmetic_params.input1_multiplier,
            &data->arithmetic_params.input1_shift);
        QuantizeMultiplierSmallerThanOneExp(
            real_input2_multiplier,
            &data->arithmetic_params.input2_multiplier,
            &data->arithmetic_params.input2_shift);
        QuantizeMultiplier(real_output_multiplier,
                            &data->arithmetic_params.output_multiplier,
                            &data->arithmetic_params.output_shift);
        data->arithmetic_params.quantized_activation_min =
            quantized_activation_min;
        data->arithmetic_params.quantized_activation_max =
            quantized_activation_max;
    }

    TfLiteStatus SquaredDifferencePrepare(TfLiteContext* context,
        TfLiteNode* node) {
        TFLITE_DCHECK(node->user_data != nullptr);
        OpData* data = reinterpret_cast<OpData*>(node->user_data);
        data->requires_broadcast = false;

        TF_LITE_ENSURE_EQ(context, NumInputs(node), 2);
        TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

        MicroContext* micro_context = GetMicroContext(context);

        TfLiteTensor* input1 =
            micro_context->AllocateTempInputTensor(node,
                                                    kInputTensor1);
        TF_LITE_ENSURE(context, input1 != nullptr);
        TfLiteTensor* input2 =
            micro_context->AllocateTempInputTensor(node,
                                                    kInputTensor2);
        TF_LITE_ENSURE(context, input2 != nullptr);
        TfLiteTensor* output =
            micro_context->AllocateTempOutputTensor(node,
                                                    kOutputTensor);
        TF_LITE_ENSURE(context, output != nullptr);

        TF_LITE_ENSURE_TYPES_EQ(context, input1->type, input2->type);
        output->type = input2->type;

        const TfLiteQuantizationParams& input1_quantization_params =
            input1->params;
        const TfLiteQuantizationParams& input2_quantization_params =
            input2->params;
        const TfLiteQuantizationParams& output_quantization_params =
            output->params;
        // Ensure the quantization parameters are equivalent.
        if (input1->type == kTfLiteInt8) {
            const int32_t integer_type_min = std::numeric_limits<int8_t>::min();
            const int32_t integer_type_max = std::numeric_limits<int8_t>::max();
            TF_LITE_ENSURE(context,
                input1_quantization_params.zero_point >= integer_type_min);
            TF_LITE_ENSURE(context,
                input1_quantization_params.zero_point <= integer_type_max);
            TF_LITE_ENSURE(context,
                input2_quantization_params.zero_point >= integer_type_min);
            TF_LITE_ENSURE(context,
                input2_quantization_params.zero_point <= integer_type_max);
            TF_LITE_ENSURE(context,
                output_quantization_params.zero_point >= integer_type_min);
            TF_LITE_ENSURE(context,
                output_quantization_params.zero_point <= integer_type_max);
            PrepareQuantized(
                input1_quantization_params,
                input2_quantization_params,
                output_quantization_params, /*left_shift=*/7,
                /*quantized_activation_min*/ integer_type_min,
                /*quantized_activation_max*/ integer_type_max,
                data);
        } else if (input1->type == kTfLiteInt16) {
            const int32_t integer_type_min =
                std::numeric_limits<int16_t>::min();
            const int32_t integer_type_max =
                std::numeric_limits<int16_t>::max();
            TF_LITE_ENSURE(
                context, input1_quantization_params.zero_point == 0);
            TF_LITE_ENSURE(
                context, input2_quantization_params.zero_point == 0);
            TF_LITE_ENSURE(
                context, output_quantization_params.zero_point == 0);

            // leftshift = 0 as number is already 16-bit. so that
            // maximum shifted result 32767^2 * (1 << (0 * 2 ))
            PrepareQuantized(
                input1_quantization_params,
                input2_quantization_params,
                output_quantization_params, /*left_shift=*/0,
                /*quantized_activation_min*/ integer_type_min,
                /*quantized_activation_max*/ integer_type_max, data);
        }

        data->requires_broadcast = !HaveSameShapes(input1, input2);

        // check input: 1,1,256,
        // input2: 1,1,1
        // 1,1,256
        data->opt_constraint_float = 0;
        int input1_count = ElementCount(*input1->dims);
        int input2_count = ElementCount(*input2->dims);
        int output_count = ElementCount(*output->dims);
#if defined(DMX1A_SQUARED_DIFF_OPT) || defined(HMD1A_SQUARED_DIFF_OPT)
        if (output->type == kTfLiteFloat32)
        {

            //int input_shape0 = input1->dims->data[input1->dims->size - 1];
            /*if (input1_count == input2_count && input2_count == output_count)
            {
                data->opt_constraint_float = SQDF_OPT_TYPE1;
            }
            else if (input_shape0 == input2_count &&
                output_count == input1_count) {
                data->opt_constraint_float = SQDF_OPT_TYPE2;  // 1: 1,1,3,64 , in2: 64, out: 1,3,64
            }
            else */if (1 == input2_count && output_count == input1_count)

            {
                data->opt_constraint_float = SQDF_OPT_TYPE3;  // FloatNulWithScalarBroadcast
            }
        }
#endif
        KN_PRINTD(data->opt_constraint_float);
        micro_context->DeallocateTempTfLiteTensor(input1);
        micro_context->DeallocateTempTfLiteTensor(input2);
        micro_context->DeallocateTempTfLiteTensor(output);
        return kTfLiteOk;
    }

template <typename T>
T SquaredDifference(T x, T y, const ArithmeticParams& params) {
        const int32_t input1_val = params.input1_offset + x;
        const int32_t input2_val = params.input2_offset + y;
        const int32_t shifted_input1_val = input1_val * (1 << params.left_shift);
        const int32_t shifted_input2_val = input2_val * (1 << params.left_shift);
        const int32_t scaled_input1_val =
            MultiplyByQuantizedMultiplierSmallerThanOneExp(
                shifted_input1_val, params.input1_multiplier, params.input1_shift);
        const int32_t scaled_input2_val =
            MultiplyByQuantizedMultiplierSmallerThanOneExp(
                shifted_input2_val, params.input2_multiplier, params.input2_shift);
        const int32_t raw_diff = scaled_input1_val - scaled_input2_val;

        // Max of this is 255^2 * (1 << 14), so won't overflow 32 bits.
        const int32_t squared_raw_diff = raw_diff * raw_diff;
        const int32_t raw_output =
            MultiplyByQuantizedMultiplier(
                squared_raw_diff, params.output_multiplier, params.output_shift) +
            params.output_offset;
        const int32_t clamped_output =
            std::min(params.quantized_activation_max,
                std::max(params.quantized_activation_min, raw_output));
        return static_cast<T>(clamped_output);
    }

    template <typename T>
    void EvalQuantizedSquaredDifference(TfLiteContext* context, TfLiteNode* node,
        const OpData* data,
        const TfLiteEvalTensor* input1,
        const TfLiteEvalTensor* input2,
        TfLiteEvalTensor* output) {
        const auto* op_data = static_cast<const OpData*>(node->user_data);
        if (data->requires_broadcast) {
            reference_integer_ops::BroadcastBinaryFunction4DSlow(
                op_data->arithmetic_params, tflite::micro::GetTensorShape(input1),
                tflite::micro::GetTensorData<T>(input1),
                tflite::micro::GetTensorShape(input2),
                tflite::micro::GetTensorData<T>(input2),
                tflite::micro::GetTensorShape(output),
                tflite::micro::GetTensorData<T>(output),
                reference_integer_ops::CheckArithmeticParams, SquaredDifference);
        }
        else {
            const int flat_size = tflite::micro::GetTensorShape(input1).FlatSize();
            reference_integer_ops::ElementWise(
                flat_size, op_data->arithmetic_params,
                tflite::micro::GetTensorData<T>(input1),
                tflite::micro::GetTensorData<T>(input2),
                tflite::micro::GetTensorData<T>(output),
                reference_integer_ops::CheckArithmeticParams, SquaredDifference);
        }
    }

    template <typename T>
    void EvalSquaredDifference(TfLiteContext* context, TfLiteNode* node,
        const OpData* data, const TfLiteEvalTensor* input1,
        const TfLiteEvalTensor* input2,
        TfLiteEvalTensor* output) {
        if (data->requires_broadcast) {
            reference_ops::BroadcastBinaryFunction4DSlow<T, T, T>(
                tflite::micro::GetTensorShape(input1),
                tflite::micro::GetTensorData<T>(input1),
                tflite::micro::GetTensorShape(input2),
                tflite::micro::GetTensorData<T>(input2),
                tflite::micro::GetTensorShape(output),
                tflite::micro::GetTensorData<T>(output), SquaredDifference<T>);
        }
        else {
            reference_ops::BinaryFunction<T, T, T>(
                tflite::micro::GetTensorShape(input1),
                tflite::micro::GetTensorData<T>(input1),
                tflite::micro::GetTensorShape(input2),
                tflite::micro::GetTensorData<T>(input2),
                tflite::micro::GetTensorShape(output),
                tflite::micro::GetTensorData<T>(output), SquaredDifference<T>);
        }
    }
#ifdef DMX1A_SQUARED_DIFF_OPT
    static void SquaredDiffFloatType3(float* output, const float* input1,
        const AScalar& input2, int size) {
        int loopLim = size >> 2;
        int remain = (size & 3);
        vr128 VR_input1, VR_input2;


        ulsr128 UR_input1;  //, UR_input2;
        vr128 VR_out, VR_tmp;
        UR_input1 = align_32x4_load(input1);
        // UR_input2 = align_32x4_load(input2);
        ulsr128 UR_output = align_32x4_store(output);

        //replicate_ar(VR_min, 0xf, act_min.fr);
        //replicate_ar(VR_max, 0xf, act_max.fr);
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
                VR_tmp = vadds(VR_input1, VR_input2, 0xf0);
                VR_out = vmuls(VR_tmp, VR_tmp, 0);
                load_32x4_vr_a(VR_input1, UR_input1, input1);

                convert_32F_to_IEEE_float_x4(VR_out);

                store_32x4_vr_a(VR_out, UR_output, output);
            }
            convert_IEEE_float_to_32F_x4(VR_input1);

            VR_tmp = vadds(VR_input1, VR_input2, 0xf0);
            VR_out = vmuls(VR_tmp, VR_tmp, 0);
            convert_32F_to_IEEE_float_x4(VR_out);

            store_32x4_vr_a(VR_out, UR_output, output);
            flush_32x4(UR_output, output);
        }
        for (int ii = 0; ii < remain; ii++) {
            load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);

            convert_IEEE_float_to_32F_x4(VR_input1);

            fadds(VR_tmp, VRQ0, VR_input1, VRQ0, VR_input2, VRQ0, 0x10);
            fmuls(VR_out, VRQ0, VR_tmp, VRQ0, VR_tmp, VRQ0, 0x0);
            convert_32F_to_IEEE_float_x4(VR_out);
            store32x1_vr_postI(VR_out, output, INC1, VRQ0);
        }
    }
#endif
#ifdef HMD1A_SQUARED_DIFF_OPT
    static void SquaredDiffFloatType3(float* output, const float* input1,
        const AScalar& input2, int size) {
        int loopLim = size >> 1;
        int remain = (size &1);
        vr64 VR_input1, VR_input2;


        ulsr32 UR_input1;  //, UR_input2;
        vr64 VR_out, VR_tmp;
        UR_input1 = align_32x2_load(input1);
        // UR_input2 = align_32x4_load(input2);
        ulsr32 UR_output = align_32x2_store(output);

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
                VR_tmp = vadds(VR_input1, VR_input2, 0xa);
                VR_out = vmuls(VR_tmp, VR_tmp, 0);
                load_32x2_vr_a(VR_input1, UR_input1, input1);

                convert_32F_to_IEEE_float_x2(VR_out);

                store_32x2_vr_a(VR_out, UR_output, output);
            }
            convert_IEEE_float_to_32F_x2(VR_input1);

            VR_tmp = vadds(VR_input1, VR_input2, 0xa);
            VR_out = vmuls(VR_tmp, VR_tmp, 0);
            convert_32F_to_IEEE_float_x2(VR_out);

            store_32x2_vr_a(VR_out, UR_output, output);
            flush_32x2(UR_output, output);
        }
        if(remain) {
            load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);

            convert_IEEE_float_to_32F_x2(VR_input1);
            fr32 fr_tmp = fadds(get_VRL(VR_input1), get_VRL(VR_input2), 0x2);
            //fadds(VR_tmp, VRQ0, VR_input1, VRQ0, VR_input2, VRQ0, 0x10);
            //fmuls(VR_out, VRQ0, VR_tmp, VRQ0, VR_tmp, VRQ0, 0x0);
            fr32 fr_out = fmuls(fr_tmp, fr_tmp, 0);
            set_VRL(VR_out, fr_out);
            convert_32F_to_IEEE_float_x2(VR_out);
            store32x1_vr_postI(VR_out, output, INC1, VRQ0);
        }
    }
#endif
    TfLiteStatus SquaredDifferenceEvalFloat32(TfLiteContext* context, TfLiteNode* node) {
        OpData* data = reinterpret_cast<OpData*>(node->user_data);

        const TfLiteEvalTensor* input1 =
            tflite::micro::GetEvalInput(context, node, kInputTensor1);
        const TfLiteEvalTensor* input2 =
            tflite::micro::GetEvalInput(context, node, kInputTensor2);
        TfLiteEvalTensor* output =
            tflite::micro::GetEvalOutput(context, node, kOutputTensor);
        if (output->type != kTfLiteFloat32)
        {
            TF_LITE_KERNEL_LOG(context,
                "SquaredDifference only supports FLOAT32, now, got %d.",
                output->type);
            return kTfLiteError;
        }

#if defined(DMX1A_SQUARED_DIFF_OPT) || defined(HMD1A_SQUARED_DIFF_OPT)
        if (data->opt_constraint_float == SQDF_OPT_TYPE3)
        {
            AScalar input2Element;
            const int flat_size =
                MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                    tflite::micro::GetTensorShape(output));

            const float* input2Flt = tflite::micro::GetTensorData<float>(input2);
            KN_PRINTF(input2Flt[0]);
            input2Element = AScalar(input2Flt[0]);
            KN_PRINTAFLT(input2Element);
            //KN_PRINT_AFLOAT(tflite::micro::GetTensorData<float>(output),
            //    ElementCount(*output->dims));
            SquaredDiffFloatType3(tflite::micro::GetTensorData<float>(output),
                tflite::micro::GetTensorData<float>(input1), input2Element,
                flat_size);

        }
        else
#endif
        {
            EvalSquaredDifference<float>(context, node, data, input1, input2, output);
        }
        KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
            ElementCount(*output->dims));
                    
                   
        return kTfLiteOk;
    }
    TfLiteStatus SquaredDifferenceEval(TfLiteContext* context, TfLiteNode* node) {
        OpData* data = reinterpret_cast<OpData*>(node->user_data);

        const TfLiteEvalTensor* input1 =
            tflite::micro::GetEvalInput(context, node, kInputTensor1);
        const TfLiteEvalTensor* input2 =
            tflite::micro::GetEvalInput(context, node, kInputTensor2);
        TfLiteEvalTensor* output =
            tflite::micro::GetEvalOutput(context, node, kOutputTensor);

        if (output->type == kTfLiteFloat32) {
#if defined(DMX1A_SQUARED_DIFF_OPT) || defined(HMD1A_SQUARED_DIFF_OPT)
            if (data->opt_constraint_float == SQDF_OPT_TYPE3)
            {
                AScalar input2Element;
                const int flat_size =
                    MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                        tflite::micro::GetTensorShape(output));

                const float* input2Flt = tflite::micro::GetTensorData<float>(input2);
                KN_PRINTF(input2Flt[0]);
                input2Element = AScalar(input2Flt[0]);
                KN_PRINTAFLT(input2Element);
                KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input1),
                    ElementCount(*output->dims));
                KN_PRINT_SHAPE(tflite::micro::GetTensorShape(input1));
                KN_PRINT_SHAPE(tflite::micro::GetTensorShape(input2));
                KN_PRINT_SHAPE(tflite::micro::GetTensorShape(output));
                //KN_PRINT_AFLOAT(tflite::micro::GetTensorData<float>(output),
                //    ElementCount(*output->dims));
                SquaredDiffFloatType3(tflite::micro::GetTensorData<float>(output),
                    tflite::micro::GetTensorData<float>(input1), input2Element,
                    flat_size);

            }
            else
#endif
            {
                EvalSquaredDifference<float>(context, node, data, input1, input2, output);
            }
            KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                ElementCount(*output->dims));
        }
        else if (output->type == kTfLiteInt32) {
            EvalSquaredDifference<int32_t>(context, node, data, input1, input2, output);
        }
        else if (output->type == kTfLiteInt8) {
            EvalQuantizedSquaredDifference<int8_t>(context, node, data, input1, input2,
                output);
        } else if (output->type == kTfLiteInt16) {
            EvalQuantizedSquaredDifference<int16_t>(
                context, node, data, input1, input2, output);
        } 
        else {
            TF_LITE_KERNEL_LOG(context,
                "SquaredDifference only supports FLOAT32, INT32 and INT8 INT16 now, got %d.",
                output->type);
            return kTfLiteError;
        }

        return kTfLiteOk;
    }
}  // namespace squared_difference

TFLMRegistration Register_SQUARED_DIFFERENCE() {
return tflite::micro::RegisterOp(SquaredDifferenceInit,

/*prepare=*/SquaredDifferencePrepare,
/*invoke=*/SquaredDifferenceEval);
}
TFLMRegistration Register_SQUARED_DIFFERENCE_FLOAT32() {
return tflite::micro::RegisterOp(SquaredDifferenceInit,
/*prepare=*/SquaredDifferencePrepare,
/*invoke=*/SquaredDifferenceEvalFloat32);
}

}  // namespace tflite
