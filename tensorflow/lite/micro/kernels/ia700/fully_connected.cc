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
//#define KN_DEBUG
#include "tensorflow/lite/micro/ia700/config.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/fully_connected.h"
#endif
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/integer_ops/fully_connected.h"
#endif
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/fully_connected.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount

#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
namespace tflite {
namespace {
    typedef enum {
        FC_OPT_NONE = 0,
        FC_OPT_TYPE1 = 1,
        FC_OPT_TYPE2 = 2, // input channel align 4
        FC_OPT_TYPE3 = 3,
        FC_OPT_TYPE4 = 4,

        // hybrid using MVM MAP
        FC_OPT_FLT_X_INT8_MVM = 8,
    } fc_opt_type;
struct OpData {
  // The scaling factor from input to output (aka the 'real multiplier') can
  // be represented as a fixed point multiplier plus a left shift.

  OpDataFullyConnected FcOp;

  int buffer_idx;
  int32_t *mapped_filter;  // aligned 4bytes, int8_t data to store pointer for
                           // mapping W
  AScalar outputMultipler;
  AScalar outputOffset;
  uint32_t input_offset_int8;
  int32_t *inputOffsetWithW;
  //int32_t filter_int8_exp;
  AScalar filter_scale; // for quantized int8 weight
  int opt_constraint;  //
  int opt_constraint_float;
};


TfLiteStatus CalculateOpData(TfLiteContext *context,
                             TfLiteFusedActivation activation,
                             TfLiteType data_type, const TfLiteTensor *input,
                             const TfLiteTensor *filter,
                             const TfLiteTensor *bias, TfLiteTensor *output,
                             OpData *data_ex) {
  TfLiteStatus status = kTfLiteOk;
  OpDataFullyConnected* data = &data_ex->FcOp;
  // Set buffer index to a reset value
  data_ex->buffer_idx = -1;
  if (data_type != kTfLiteFloat32) {
    double real_multiplier = 0.0;
    TF_LITE_ENSURE_STATUS(GetQuantizedConvolutionMultipler(
        context, input, filter, bias, output, &real_multiplier));
    int exponent;
    data_ex->outputMultipler = AScalar(real_multiplier);  // convert to afloat
    QuantizeMultiplier(real_multiplier, &data->output_multiplier, &exponent);

    // Work around for Int16 use reference ops
    data->output_shift = exponent;  //-exponent;
    TF_LITE_ENSURE_STATUS(CalculateActivationRangeQuantized(
        context, activation, output, &data->output_activation_min,
        &data->output_activation_max));

    data->input_zero_point = input->params.zero_point;
    data->filter_zero_point = filter->params.zero_point;
    data->output_zero_point = output->params.zero_point;

    return CalculateActivationRangeQuantized(context, activation, output,
                                             &data->output_activation_min,
                                             &data->output_activation_max);
      //#endif
  }
  return status;
}
//#endif
void *Init(TfLiteContext *context, const char *buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

#ifdef HEMILITE_FC_OPT


int FullyConnectedFloatInt8(float* y, const float* x, const int8_t* A,
    const float* bias, int m, int n, const AScalar& act_min,
    const AScalar& act_max, const AScalar& scale) {
    int loopGroupLim = (m >> 1);
    int loopBlockLim2 = (n >> 1);
    //  int jammingBit = RUR_JammingBit();
    const int8_t* pW = A;
    //  int maxExp;
    int ii, jj;

    float* pActOut;
    const float* pBiasLocal;
    //   WUR_JammingBit(1);
    int8_t* pWa0;
    int8_t* pWa1;

    vr64 VR_w0;
    vr64 VR_act_max, VR_act_min;
    vr64 VR_bias;
    vr64 VR_scale;
    ulsr32 UR_blk;
    ulsr32 UR_actOut, UR_bias;
    // unsigned Maxidx;
    const int wBlkExp = 7;
    replicate_ar(VR_act_max, 0x3, act_max.fr);
    replicate_ar(VR_act_min, 0x3, act_min.fr);
    replicate_ar(VR_scale, 0x3, scale.fr);
    pActOut = y;

    pBiasLocal = bias;
    UR_actOut = align_32x2_store(pActOut);
    if (pBiasLocal) {
        UR_bias = align_32x2_load(pBiasLocal);
    }
    VR_bias = vseta_vr(0, 0);
    if (loopGroupLim > 0) {
        for (jj = 0; jj < loopGroupLim; jj++)  // group
        {
            vr64 VR_blk = vseta_vr(0, 0);
            vr64 VR_out0 = VR_blk;
            vr64 VR_out1 = VR_blk;

            vr64 VR_actOut = VR_blk;

            pWa1 = pWa0 = (int8_t*)pW;
            load8x1_vr_postR(VR_out1, pWa1, n, VRQ0);  // dummy load

            VR_out0 = vadds(VR_out0, VR_out0, 0xa);
            VR_out1 = vadds(VR_out1, VR_out1, 0xa);
            float* pIn0 = (float*)x;
            if (loopBlockLim2 > 0) {
                // register vr128 VR_act;
                //UR_w0 = align_16x2_load(pWa0);
                //UR_w1 = align_16x2_load(pWa1);
                UR_blk = align_32x2_load(pIn0);
                load_32x2_vr_a(VR_blk, UR_blk, pIn0);
                load8x2_vr_postI_unalign(VR_w0, pWa0, INC1);
                convert_16I_to_32F_x2(VR_w0, wBlkExp); 
                // convert IEEE to afloat
                convert_IEEE_float_to_32F_x2(VR_blk);
                //convert_IEEE_float_to_32F_x2(VR_w0);
                for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
                {
                    // KN_PRINT_VR128(VR_blk);  KN_PRINT_VR128(VR_w0);
                    VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
                    //    KN_PRINT_VR128(VR_out0);
                    load8x2_vr_postI_unalign(VR_w0, pWa1, INC1);  convert_16I_to_32F_x2(VR_w0, wBlkExp); 
                   
                    //convert_IEEE_float_to_32F_x2(VR_w0);
                    VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);

                    load8x2_vr_postI_unalign(VR_w0, pWa0, INC1);  convert_16I_to_32F_x2(VR_w0, wBlkExp);
                  
                    load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
                   // convert_IEEE_float_to_32F_x2(VR_w0);
                    convert_IEEE_float_to_32F_x2(VR_blk);
                }

                VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);

                load8x2_vr_postI_unalign(VR_w0, pWa1, INC1); 
                convert_16I_to_32F_x2(VR_w0, wBlkExp); 
               

                //convert_IEEE_float_to_32F_x2(VR_w0);
                VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);
            }
            fr32 fr_out0, fr_out1;

            if (n & 1) {
                load8x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
                convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0); 
         
                load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
                convert_IEEE_float_to_32F_x2(VR_blk);
                fr_out0 = fmacs(get_VRL(VR_out0), get_VRL(VR_w0), get_VRL(VR_blk), 0);
                load8x1_vr_postI(VR_w0, pWa1, INC1, VRQ0);
                convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0); 

                fr_out1 = fmacs(get_VRL(VR_out1), get_VRL(VR_w0), get_VRL(VR_blk), 0);

                set_VRL(VR_out0, fr_out0);
                set_VRL(VR_out1, fr_out1);
            }

            fr_out0 = fadds(get_VRL(VR_out0), get_VRH(VR_out0), 0);
            fr_out1 = fadds(get_VRL(VR_out1), get_VRH(VR_out1), 0);

            set_VRL(VR_actOut, fr_out0);
            set_VRH(VR_actOut, fr_out1);
            VR_actOut = vmuls(VR_actOut, VR_scale, 0);
            if (pBiasLocal) {
                load_32x2_vr_a(VR_bias, UR_bias, pBiasLocal);

            }
            //      KN_PRINT_VR128(VR_bias);
            VR_actOut = vadds(VR_actOut, VR_bias, 0);

            //         KN_PRINT_VR128(VR_actOut);

            VR_actOut = vmax(VR_actOut, VR_act_min);
            VR_actOut = vmin(VR_actOut, VR_act_max);
            //    KN_PRINT_VR128(VR_actOut);
            convert_32F_to_IEEE_float_x2(VR_actOut);

            //                      KN_PRINT_VR128(VR_actOut);
            store_32x2_vr_a(VR_actOut, UR_actOut, pActOut);
            pW += 2 * n;  // add to next block
        }
        flush_32x2(UR_actOut, pActOut);
    }

    if (m & 1)  // for (jj = loopGroupLim << 2; jj < m; jj++)  // group
    {
        vr64 VR_actOut = vseta_vr(0, 0);
        vr64 VR_blk;
        vr64 VR_out0;

        pWa0 = (int8_t*)pW;  // 1st group

        VR_out0 = vexp_adji(VR_actOut, 0x0);

        float* pIn0 = (float*)x;
        if (loopBlockLim2 > 0) {
            //UR_w0 = align_32x2_load(pWa0);

            UR_blk = align_32x2_load(pIn0);
            load_32x2_vr_a(VR_blk, UR_blk, pIn0);
            load8x2_vr_postI_unalign(VR_w0, pWa0, INC1);
            convert_16I_to_32F_x2(VR_w0, wBlkExp); 
     
            convert_IEEE_float_to_32F_x2(VR_blk);
            // convert_IEEE_float_to_32F_x2(VR_w0);

            for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
            {
                VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
                load8x2_vr_postI_unalign(VR_w0, pWa0, INC1); 
                convert_16I_to_32F_x2(VR_w0, wBlkExp);
         
                load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
                convert_IEEE_float_to_32F_x2(VR_blk);
                //   convert_IEEE_float_to_32F_x2(VR_w0);
            }

            VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
        }
        fr32 fr_out0;
        if (n & 1) {
            load8x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
            convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0); 

            load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);

            convert_IEEE_float_to_32F_x2(VR_blk);
            // convert_IEEE_float_to_32F_x2(VR_w0);

            fr_out0 = fmacs(get_VRL(VR_out0), get_VRL(VR_w0), get_VRL(VR_blk), 0);
            set_VRL(VR_out0, fr_out0);
        }
        // dsums_L(VR_out0, VR_out0, 0, 0);
        // fadds(VR_actOut, VRQ0, VR_out0, VRQ1, VR_out0, VRQ0, 0);
        fr_out0 = fadds(get_VRL(VR_out0), get_VRH(VR_out0), 0);

        set_VRL(VR_actOut, fr_out0);
        VR_actOut = vmuls(VR_actOut, VR_scale, 0);
        // VR_exp = afloat_exp_extract(VR_actOut);
        // fmax(VR_maxExp, VRQ0, VR_maxExp, VRQ0, VR_exp, VRQ0);
        // if (pBiasLocal) {
        //    fr32 fr_bias;
        if (pBiasLocal) {
            load32x1_vr_postI(VR_bias, pBiasLocal, INC1, VRQ0);

            //   convert_IEEE_float_to_32F_x2(VR_bias);
        }
        VR_actOut = vadds(VR_actOut, VR_bias, 0);
        VR_actOut = vmax(VR_actOut, VR_act_min);
        VR_actOut = vmin(VR_actOut, VR_act_max);

        convert_32F_to_IEEE_float_x2(VR_actOut);
        store32x1_vr_postI(VR_actOut, pActOut, INC1, VRQ0);

        // pW += n;  // add to next group
    }

    return 0;  //(maxExp-31);
}
int FullyConnectedFloat16(float* y, const float* x, const TfLiteFloat16* A,
    const float* bias, int m, int n, const AScalar& act_min,
    const AScalar& act_max) {
    int loopGroupLim = (m >> 1);
    int loopBlockLim2 = (n >> 1);
    //  int jammingBit = RUR_JammingBit();
    const TfLiteFloat16* pW = A;
    //  int maxExp;
    int ii, jj;

    float* pActOut;
    const float* pBiasLocal;
    //   WUR_JammingBit(1);
    TfLiteFloat16* pWa0;
    TfLiteFloat16* pWa1;

    vr64 VR_w0;
    vr64 VR_act_max, VR_act_min;
    vr64 VR_bias;
    // vr128 VR_maxExp = vseta_vr(0, 0, 0);
    // mir30 mirIdx;
    // vr128 VR_exp;
   // ulsr32 UR_w0, UR_w1;  //, UR_w2, UR_w3;
    ulsr32 UR_blk;
    ulsr32 UR_actOut, UR_bias;
    // unsigned Maxidx;
   
    replicate_ar(VR_act_max, 0x3, act_max.fr);
    replicate_ar(VR_act_min, 0x3, act_min.fr);
    pActOut = y;

    pBiasLocal = bias;
    UR_actOut = align_32x2_store(pActOut);
    if (pBiasLocal) {
        UR_bias = align_32x2_load(pBiasLocal);
    }
    VR_bias = vseta_vr(0, 0);
    if (loopGroupLim > 0) {
        for (jj = 0; jj < loopGroupLim; jj++)  // group
        {
            vr64 VR_blk = vseta_vr(0, 0);
            vr64 VR_out0 = VR_blk;
            vr64 VR_out1 = VR_blk;

            vr64 VR_actOut = VR_blk;

            pWa1 = pWa0 = (TfLiteFloat16*)pW;
            load16x1_vr_postR(VR_out1, pWa1, n, VRQ0);  // dummy load

            VR_out0 = vadds(VR_out0, VR_out0, 0xa);
            VR_out1 = vadds(VR_out1, VR_out1, 0xa);
            float* pIn0 = (float*)x;
            if (loopBlockLim2 > 0) {
                // register vr128 VR_act;
                //UR_w0 = align_16x2_load(pWa0);
                //UR_w1 = align_16x2_load(pWa1);
                UR_blk = align_32x2_load(pIn0);
                load_32x2_vr_a(VR_blk, UR_blk, pIn0);
                load16x2_vr_postI_unalign(VR_w0, pWa0, INC1); 
                convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                // convert IEEE to afloat
                convert_IEEE_float_to_32F_x2(VR_blk);
                //convert_IEEE_float_to_32F_x2(VR_w0);
                for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
                {
                    // KN_PRINT_VR128(VR_blk);  KN_PRINT_VR128(VR_w0);
                    VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
                    //    KN_PRINT_VR128(VR_out0);
                    load16x2_vr_postI_unalign(VR_w0, pWa1, INC1); convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                    //convert_IEEE_float_to_32F_x2(VR_w0);
                    VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);

                    load16x2_vr_postI_unalign(VR_w0, pWa0, INC1); convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                    load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
                   // convert_IEEE_float_to_32F_x2(VR_w0);
                    convert_IEEE_float_to_32F_x2(VR_blk);
                }

                VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);

                load16x2_vr_postI_unalign(VR_w0, pWa1, INC1); convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);

                //convert_IEEE_float_to_32F_x2(VR_w0);
                VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);
            }
            fr32 fr_out0, fr_out1;

            if (n & 1) {
                load16x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS, VRQ0);
                load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
                // convert_IEEE_float_to_32F_x2(VR_w0);
                convert_IEEE_float_to_32F_x2(VR_blk);
                // for (ii = loopBlockLim2 << 2; ii < n; ii++)
                //   if(n&1){
                //          fmacs(VR_out0, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);
                fr_out0 = fmacs(get_VRL(VR_out0), get_VRL(VR_w0), get_VRL(VR_blk), 0);
                load16x1_vr_postI(VR_w0, pWa1, INC1, VRQ0);convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS, VRQ0);
                // convert_IEEE_float_to_32F_x2(VR_w0);
                 //          fmacs(VR_out1, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);
                fr_out1 = fmacs(get_VRL(VR_out1), get_VRL(VR_w0), get_VRL(VR_blk), 0);

                set_VRL(VR_out0, fr_out0);
                set_VRL(VR_out1, fr_out1);
            }

            fr_out0 = fadds(get_VRL(VR_out0), get_VRH(VR_out0), 0);
            fr_out1 = fadds(get_VRL(VR_out1), get_VRH(VR_out1), 0);

            set_VRL(VR_actOut, fr_out0);
            set_VRH(VR_actOut, fr_out1);

            //   KN_PRINT_VR128(VR_actOut);
            if (pBiasLocal) {
                load_32x2_vr_a(VR_bias, UR_bias, pBiasLocal);
                //  convert_IEEE_float_to_32F_x2(VR_bias);
            }
            //      KN_PRINT_VR128(VR_bias);
            VR_actOut = vadds(VR_actOut, VR_bias, 0);

            //         KN_PRINT_VR128(VR_actOut);

            VR_actOut = vmax(VR_actOut, VR_act_min);
            VR_actOut = vmin(VR_actOut, VR_act_max);
            //    KN_PRINT_VR128(VR_actOut);
            convert_32F_to_IEEE_float_x2(VR_actOut);

            //                      KN_PRINT_VR128(VR_actOut);
            store_32x2_vr_a(VR_actOut, UR_actOut, pActOut);
            pW += 2 * n;  // add to next block
        }
        flush_32x2(UR_actOut, pActOut);
    }

    if (m & 1)  // for (jj = loopGroupLim << 2; jj < m; jj++)  // group
    {
        vr64 VR_actOut = vseta_vr(0, 0);
        vr64 VR_blk;
        vr64 VR_out0;

        pWa0 = (TfLiteFloat16*)pW;  // 1st group

        VR_out0 = vexp_adji(VR_actOut, 0x0);

        float* pIn0 = (float*)x;
        if (loopBlockLim2 > 0) {
            //UR_w0 = align_32x2_load(pWa0);

            UR_blk = align_32x2_load(pIn0);
            load_32x2_vr_a(VR_blk, UR_blk, pIn0);
            load16x2_vr_postI_unalign(VR_w0, pWa0, INC1);
            convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
            convert_IEEE_float_to_32F_x2(VR_blk);
            // convert_IEEE_float_to_32F_x2(VR_w0);

            for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
            {
                VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
                load16x2_vr_postI_unalign(VR_w0,  pWa0, INC1); convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
                convert_IEEE_float_to_32F_x2(VR_blk);
                //   convert_IEEE_float_to_32F_x2(VR_w0);
            }

            VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
        }
        fr32 fr_out0;
        if (n & 1) {
            load16x1_vr_postI(VR_w0, pWa0, INC1, VRQ0); 
            convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS, VRQ0);

            load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);

            convert_IEEE_float_to_32F_x2(VR_blk);
            // convert_IEEE_float_to_32F_x2(VR_w0);

            fr_out0 = fmacs(get_VRL(VR_out0), get_VRL(VR_w0), get_VRL(VR_blk), 0);
            set_VRL(VR_out0, fr_out0);
        }
        // dsums_L(VR_out0, VR_out0, 0, 0);
        // fadds(VR_actOut, VRQ0, VR_out0, VRQ1, VR_out0, VRQ0, 0);
        fr_out0 = fadds(get_VRL(VR_out0), get_VRH(VR_out0), 0);

        set_VRL(VR_actOut, fr_out0);
        // VR_exp = afloat_exp_extract(VR_actOut);
        // fmax(VR_maxExp, VRQ0, VR_maxExp, VRQ0, VR_exp, VRQ0);
        // if (pBiasLocal) {
        //    fr32 fr_bias;
        if (pBiasLocal) {
            load32x1_vr_postI(VR_bias, pBiasLocal, INC1, VRQ0);

            //   convert_IEEE_float_to_32F_x2(VR_bias);
        }
        VR_actOut = vadds(VR_actOut, VR_bias, 0);
        VR_actOut = vmax(VR_actOut, VR_act_min);
        VR_actOut = vmin(VR_actOut, VR_act_max);

        convert_32F_to_IEEE_float_x2(VR_actOut);
        store32x1_vr_postI(VR_actOut, pActOut, INC1, VRQ0);

        // pW += n;  // add to next group
    }

    return 0;  //(maxExp-31);
}

int FullyConnectedFloat(float *y, const float *x, const float *A,
                        const float *bias, int m, int n, const AScalar &act_min,
                        const AScalar &act_max) {
  int loopGroupLim = (m >> 1);
  int loopBlockLim2 = (n >> 1);
  //  int jammingBit = RUR_JammingBit();
  const float *pW = A;
  //  int maxExp;
  int ii, jj;

  float *pActOut;
  const float *pBiasLocal;
  //   WUR_JammingBit(1);
  float *pWa0;
  float *pWa1;

  vr64 VR_w0;
  vr64 VR_act_max, VR_act_min;
  vr64 VR_bias;
  // vr128 VR_maxExp = vseta_vr(0, 0, 0);
  // mir30 mirIdx;
  // vr128 VR_exp;
  ulsr32 UR_w0, UR_w1;  //, UR_w2, UR_w3;
  ulsr32 UR_blk;
  ulsr32 UR_actOut, UR_bias;
  // unsigned Maxidx;

  replicate_ar(VR_act_max, 0x3, act_max.fr);
  replicate_ar(VR_act_min, 0x3, act_min.fr);
  pActOut = y;

  pBiasLocal = bias;
  UR_actOut = align_32x2_store(pActOut);
  if (pBiasLocal) {
    UR_bias = align_32x2_load(pBiasLocal);
  }
  VR_bias = vseta_vr(0, 0);
  if (loopGroupLim > 0) {
    for (jj = 0; jj < loopGroupLim; jj++)  // group
    {
      vr64 VR_blk = vseta_vr(0, 0);
      vr64 VR_out0 = VR_blk;
      vr64 VR_out1 = VR_blk;

      vr64 VR_actOut = VR_blk;

      pWa1 = pWa0 = (float *)pW;
      load32x1_vr_postR(VR_out1, pWa1, n, VRQ0);  // dummy load

      VR_out0 = vadds(VR_out0, VR_out0, 0xa);
      VR_out1 = vadds(VR_out1, VR_out1, 0xa);
      float *pIn0 = (float *)x;
      if (loopBlockLim2 > 0) {
        // register vr128 VR_act;
        UR_w0 = align_32x2_load(pWa0);
        UR_w1 = align_32x2_load(pWa1);
        UR_blk = align_32x2_load(pIn0);
        load_32x2_vr_a(VR_blk, UR_blk, pIn0);
        load_32x2_vr_a(VR_w0, UR_w0, pWa0);
        // convert IEEE to afloat
        convert_IEEE_float_to_32F_x2(VR_blk);
        //convert_IEEE_float_to_32F_x2(VR_w0);
        for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
        {
          // KN_PRINT_VR128(VR_blk);  KN_PRINT_VR128(VR_w0);
          VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
          //    KN_PRINT_VR128(VR_out0);
          load_32x2_vr_a(VR_w0, UR_w1, pWa1);
          //convert_IEEE_float_to_32F_x2(VR_w0);
          VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);

          load_32x2_vr_a(VR_w0, UR_w0, pWa0);
          load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
         // convert_IEEE_float_to_32F_x2(VR_w0);
          convert_IEEE_float_to_32F_x2(VR_blk);
        }

        VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);

        load_32x2_vr_a(VR_w0, UR_w1, pWa1);
        //convert_IEEE_float_to_32F_x2(VR_w0);
        VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);
      }
      fr32 fr_out0, fr_out1;

      if (n & 1) {
        load32x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
        load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
       // convert_IEEE_float_to_32F_x2(VR_w0);
        convert_IEEE_float_to_32F_x2(VR_blk);
        // for (ii = loopBlockLim2 << 2; ii < n; ii++)
        //   if(n&1){
        //          fmacs(VR_out0, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);
        fr_out0 = fmacs(get_VRL(VR_out0), get_VRL(VR_w0), get_VRL(VR_blk), 0);
        load32x1_vr_postI(VR_w0, pWa1, INC1, VRQ0);
       // convert_IEEE_float_to_32F_x2(VR_w0);
        //          fmacs(VR_out1, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);
        fr_out1 = fmacs(get_VRL(VR_out1), get_VRL(VR_w0), get_VRL(VR_blk), 0);

        set_VRL(VR_out0, fr_out0);
        set_VRL(VR_out1, fr_out1);
      }

      fr_out0 = fadds(get_VRL(VR_out0), get_VRH(VR_out0), 0);
      fr_out1 = fadds(get_VRL(VR_out1), get_VRH(VR_out1), 0);

      set_VRL(VR_actOut, fr_out0);
      set_VRH(VR_actOut, fr_out1);

      //   KN_PRINT_VR128(VR_actOut);
      if (pBiasLocal) {
        load_32x2_vr_a(VR_bias, UR_bias, pBiasLocal);
      //  convert_IEEE_float_to_32F_x2(VR_bias);
      }
      //      KN_PRINT_VR128(VR_bias);
      VR_actOut = vadds(VR_actOut, VR_bias, 0);

      //         KN_PRINT_VR128(VR_actOut);

      VR_actOut = vmax(VR_actOut, VR_act_min);
      VR_actOut = vmin(VR_actOut, VR_act_max);
      //    KN_PRINT_VR128(VR_actOut);
      convert_32F_to_IEEE_float_x2(VR_actOut);

      //                      KN_PRINT_VR128(VR_actOut);
      store_32x2_vr_a(VR_actOut, UR_actOut, pActOut);
      pW += 2 * n;  // add to next block
    }
    flush_32x2(UR_actOut, pActOut);
  }

  if (m & 1)  // for (jj = loopGroupLim << 2; jj < m; jj++)  // group
  {
    vr64 VR_actOut = vseta_vr(0, 0);
    vr64 VR_blk;
    vr64 VR_out0;

    pWa0 = (float *)pW;  // 1st group

    VR_out0 = vexp_adji(VR_actOut, 0x0);

    float *pIn0 = (float *)x;
    if (loopBlockLim2 > 0) {
      UR_w0 = align_32x2_load(pWa0);

      UR_blk = align_32x2_load(pIn0);
      load_32x2_vr_a(VR_blk, UR_blk, pIn0);
      load_32x2_vr_a(VR_w0, UR_w0, pWa0);
      convert_IEEE_float_to_32F_x2(VR_blk);
     // convert_IEEE_float_to_32F_x2(VR_w0);

      for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
      {
        VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
        load_32x2_vr_a(VR_w0, UR_w0, pWa0);
        load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
        convert_IEEE_float_to_32F_x2(VR_blk);
     //   convert_IEEE_float_to_32F_x2(VR_w0);
      }

      VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
    }
    fr32 fr_out0;
    if (n & 1) {
      load32x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);

      load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);

      convert_IEEE_float_to_32F_x2(VR_blk);
     // convert_IEEE_float_to_32F_x2(VR_w0);

      fr_out0 = fmacs(get_VRL(VR_out0), get_VRL(VR_w0), get_VRL(VR_blk), 0);
      set_VRL(VR_out0, fr_out0);
    }
    // dsums_L(VR_out0, VR_out0, 0, 0);
    // fadds(VR_actOut, VRQ0, VR_out0, VRQ1, VR_out0, VRQ0, 0);
    fr_out0 = fadds(get_VRL(VR_out0), get_VRH(VR_out0), 0);

    set_VRL(VR_actOut, fr_out0);
    // VR_exp = afloat_exp_extract(VR_actOut);
    // fmax(VR_maxExp, VRQ0, VR_maxExp, VRQ0, VR_exp, VRQ0);
    // if (pBiasLocal) {
    //    fr32 fr_bias;
    if (pBiasLocal) {
      load32x1_vr_postI(VR_bias, pBiasLocal, INC1, VRQ0);

   //   convert_IEEE_float_to_32F_x2(VR_bias);
    }
    VR_actOut = vadds(VR_actOut, VR_bias, 0);
    VR_actOut = vmax(VR_actOut, VR_act_min);
    VR_actOut = vmin(VR_actOut, VR_act_max);

    convert_32F_to_IEEE_float_x2(VR_actOut);
    store32x1_vr_postI(VR_actOut, pActOut, INC1, VRQ0);

    // pW += n;  // add to next group
  }

  return 0;  //(maxExp-31);
}
int FullyConnectedKernel(int32_t *x, const int32_t *A, const AScalar *bias,
                         int8_t *output, int m, int n,
                         const AScalar &outOffsetFr32,
                         const uint32_t input_offset_int8x4,  // xor 128
                         const AScalar &outMultiplerFr32, int signs) {
  int8_t *pY = output;

  const int32_t *pA = A;
  const int32_t *pX;
  const int32_t *pB = (const int32_t *)bias;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2), 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
  int processLastLoop = ((m & 3) != 0);

  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x2_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration 
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0)
  {
      loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0)
  {
      return -1;
  }

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  vr64 VR_inputOffset;
  atbool signSpec = atbool(signs);

  vr64 VR_outMult;
  vr64 VR_outOffset;
  vr64 VR_b0 = vseta_vr(kConstTable_Zero, 0);
  replicate_ar(VR_outMult, 0x3, outMultiplerFr32.fr);
  replicate_ar(VR_outOffset, 0x3, outOffsetFr32.fr);
  replicate_ar(VR_inputOffset, 0x3, input_offset_int8x4);
  for (int i = 0; i < loopLimRow; i++) {
    VR_y = vseta_vr(0, 0);
    mov_AccExtend_vr(VR_y);
    pX = x;
    ulsr32 UR_A = align_32x2_load(pA);
    ulsr32 UR_x = align_32x2_load(pX);
    ulsr32 UR_b;
    load_32x2_vr_a(VR_A, UR_A, pA);

    if (pB) {
      UR_b = align_32x2_load(pB);
      load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
    }

    for (int j = 0; j < loopLimCol; j++) {
      load_32x2_vr_a(VR_x, UR_x, pX);
      VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(0);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 2); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_q7_out;

      vr64 VR_out;

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1 - 8, 0);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      // accExt
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ0);

      if (pB) {
        load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }
      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_out2 = vadds(VR_y, VR_b0, 0x0);
      VR_out2 = vmuls(VR_out2, VR_outMult, 0);
      VR_out2 = vadds(VR_out2, VR_outOffset, 0);
      // VR_out2 = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out2, (unsigned int)1 - 8, 0);

      rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out2, 1);
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
      VR_out2 = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRH);

      store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ1);

      store8x1_vr_postI(VR_out2, pY, INC1, VRQ0);
      store8x1_vr_postI(VR_out2, pY, INC1, VRQ1);
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ1);
    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_q7_out;

      vr64 VR_out;

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1 - 8, 0);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

      VR_y = mov_vr_AccExtend();

      if (pB) {
        load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_out2 = vadds(VR_y, VR_b0, 0x0);
      VR_out2 = vmuls(VR_out2, VR_outMult, 0);
      VR_out2 = vadds(VR_out2, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out2, (unsigned int)1 - 8, 0);
      rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out2, 1);
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
      VR_out2 = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRH);
      switch (m & 0x3) {
        case 3:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
          store8x1_vr_postI(VR_out2, pY, INC1, VRQ0);
          break;
        case 2:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
          break;
        case 1:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          break;
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}
int FullyConnectedKernelInputOffset(int32_t *x, const int32_t *A,
                                    const AScalar *bias, int8_t *output, int m,
                                    int n, const AScalar &outOffsetFr32,
                                    const int32_t *inputOffsetWithW,  // xor 128
                                    const AScalar &outMultiplerFr32,
                                    int signs) {
  int8_t *pY = output;

  const int32_t *pA = A;
  const int32_t *pX;
  const int32_t *pB = (const int32_t *)bias;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2), 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
  int processLastLoop = ((m & 3) != 0);


  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x2_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration 
  if(((unsigned int)x&3) != 0 && loopLimCol != 0)
  {
      loopLimCol = 0;
  }
  
  if(((unsigned int )x&1)!=0)
  {
    return -1;
  }
  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  // vr64 VR_inputOffset;
  atbool signSpec = atbool(signs);

  vr64 VR_outMult;
  vr64 VR_outOffset;
  vr64 VR_b0 = vseta_vr(kConstTable_Zero, 0);
  const int32_t *inputOffsetW = inputOffsetWithW;
  replicate_ar(VR_outMult, 0x3, outMultiplerFr32.fr);
  replicate_ar(VR_outOffset, 0x3, outOffsetFr32.fr);
  // replicate_ar(VR_inputOffset, 0x3, input_offset_int8x4);
  for (int i = 0; i < loopLimRow; i++) {
    if (inputOffsetW) {
      load32x2_vr_postI(VR_y, inputOffsetW, INC1);
      load32x2_vr_postI(VR_x, inputOffsetW, INC1);
      mov_AccExtend_vr(VR_x);
    } else {
      VR_y = vseta_vr(0, 0);
      mov_AccExtend_vr(VR_y);
    }
    pX = x;
    ulsr32 UR_A = align_32x2_load(pA);
    ulsr32 UR_x = align_32x2_load(pX);
    ulsr32 UR_b;
    load_32x2_vr_a(VR_A, UR_A, pA);

    if (pB) {
      UR_b = align_32x2_load(pB);
      load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
    }
    for (int j = 0; j < loopLimCol; j++) {
      load_32x2_vr_a(VR_x, UR_x, pX);
      WUR_MvmAux(0);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x2_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x2_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x2_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 2); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_q7_out;

      vr64 VR_out;

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1 - 8, 0);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      // accExt
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ0);
      if (pB) {
        load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_out2 = vadds(VR_y, VR_b0, 0x0);
      VR_out2 = vmuls(VR_out2, VR_outMult, 0);
      VR_out2 = vadds(VR_out2, VR_outOffset, 0);
      // VR_out2 = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out2, (unsigned int)1 - 8, 0);

      rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out2, 1);
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
      VR_out2 = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRH);

      store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ1);

      store8x1_vr_postI(VR_out2, pY, INC1, VRQ0);
      store8x1_vr_postI(VR_out2, pY, INC1, VRQ1);
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ1);
    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_q7_out;

      vr64 VR_out;

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1 - 8, 0);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

      VR_y = mov_vr_AccExtend();
      if (pB) {
        load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_out2 = vadds(VR_y, VR_b0, 0x0);
      VR_out2 = vmuls(VR_out2, VR_outMult, 0);
      VR_out2 = vadds(VR_out2, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out2, (unsigned int)1 - 8, 0);
      rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out2, 1);
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
      VR_out2 = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRH);
      switch (m & 0x3) {
        case 3:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
          store8x1_vr_postI(VR_out2, pY, INC1, VRQ0);
          break;
        case 2:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
          break;
        case 1:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          break;
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}

static void FullyConnectedQuantizedInt8(
    TfLiteContext *context, tflite::FullyConnectedParams &op_params,
    const OpData &data, const int8_t *inputLocal, const int8_t *filterMVM,
    const int32_t *baisMVM, const int8_t *outputLocal, const int batches,
    const int accum_depth, const int output_depth, TfLiteType type) {
  int8_t *p_fc_mapped_filter = (int8_t *)data.mapped_filter;
  // int8_t *p_dmx1a_fc_aligned_input  = nullptr;

  // if (data.buffer_idx > -1) {
  //	p_dmx1a_fc_aligned_input = (int8_t *)context->GetScratchBuffer(context,
  // data.buffer_idx);
  //}

  int sign = 3;
  //			int input_aligned4 = data.is_input_align_4;
  sign = (128 == op_params.input_offset)
             ? 1
             : sign;  // assumption: 128 + sign 8bit = unsigned

  int batch = batches;
  KN_PRINTD(batch);
  KN_PRINTD(op_params.input_offset);
  KN_PRINTX(data.input_offset_int8);
  int status = 0;
  while (batch) {
    if (data.opt_constraint == 2) {
      status = FullyConnectedKernel(
          (int32_t *)inputLocal, (int32_t *)p_fc_mapped_filter,
          (AScalar *)baisMVM, (int8_t *)outputLocal, output_depth, accum_depth,
          data.outputOffset, data.input_offset_int8,
          // op_params.output_offset,
          data.outputMultipler, sign);
    } else {
      status = FullyConnectedKernelInputOffset(
          (int32_t *)inputLocal, (int32_t *)p_fc_mapped_filter,
          (AScalar *)baisMVM, (int8_t *)outputLocal, output_depth, accum_depth,
          data.outputOffset, data.inputOffsetWithW, data.outputMultipler, sign);
    }
    if (status != 0)
    {
        TFLITE_DCHECK(status == 0);
        break;
    }
    // KN_PRINT_Q7_SIZE(outputLocal, output_depth);
    inputLocal += accum_depth;
    outputLocal += output_depth;
    batch--;
  }
}
#endif

TfLiteStatus Prepare(TfLiteContext *context, TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  OpData *data_ex = static_cast<OpData *>(node->user_data);

  OpDataFullyConnected* data =
      static_cast<OpDataFullyConnected*>(&data_ex->FcOp);
  const auto params =
      static_cast<const TfLiteFullyConnectedParams *>(node->builtin_data);
  // new memory allocation
  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input = micro_context->AllocateTempInputTensor(
      node, kFullyConnectedInputTensor);  // GetInput(context, node, kInputTensor);
  TfLiteTensor* filter = micro_context->AllocateTempInputTensor(
      node, kFullyConnectedWeightsTensor);  // GetInput(context, node,
                                            // kWeightsTensor);
  TfLiteTensor* bias = micro_context->AllocateTempInputTensor(
      node, kFullyConnectedBiasTensor);   // GetOptionalInputTensor(context,
                                         // node, kBiasTensor);
  TfLiteTensor* output = micro_context->AllocateTempOutputTensor(
      node,
      kFullyConnectedOutputTensor);  // GetOutput(context, node, kOutputTensor);
  TF_LITE_ENSURE_TYPES_EQ(context, input->type, output->type);
  //TF_LITE_ENSURE_MSG(context,  input->type == filter->type,
  //                   "kernel Int8 Hybrid models are not supported on TFLite Micro.");
  TF_LITE_ENSURE_STATUS(CalculateOpData(context, params->activation,
                                        input->type, input, filter, bias,
                                        output, data_ex));
  RuntimeShape filter_shape = GetTensorShape(filter);
  RuntimeShape output_shape = GetTensorShape(output);

  TFLITE_DCHECK_GE(output_shape.DimensionsCount(), 1);


  data_ex->opt_constraint = 0;
  data_ex->opt_constraint_float = false;
#if defined(HEMILITE_FC_OPT)
  const int filter_dim_count = filter_shape.DimensionsCount();
  const int output_dim_count = output_shape.DimensionsCount();
  const int output_depth = output_shape.Dims(output_dim_count-1);
  const int accum_depth = filter_shape.Dims(filter_dim_count - 1);
  // KN_PRINTD( data->filter_zero_point);
  data_ex->opt_constraint =
      //(output_dim_count == 2) &&
      input->type ==   kTfLiteInt8 &&  // nullptr != GetTensorData<int32_t>(bias) &&
      (data->filter_zero_point == 0 && data->output_activation_min == -128 &&
       data->output_activation_max == 127);

  data_ex->opt_constraint_float =  //(output_dim_count == 2) &&
      (filter->type == kTfLiteFloat32 || filter->type == kTfLiteFloat16 || filter->type == kTfLiteInt8) 
      && (input->type == kTfLiteFloat32) && (output->type == kTfLiteFloat32);
  // disable for testing kernel script
#if 0
  if (filter->type == kTfLiteFloat16)
  {
          TF_LITE_ENSURE_MSG(context, tflite::is_coeffs_mapped(context) == true,
          "float16 must converted from kn model script");
  }

#endif
  KN_PRINTD(filter->type);
  KN_PRINTD(input->type);
 // KN_PRINTX(GetTensorData<float>(bias));
  KN_PRINTD(data_ex->opt_constraint);
  KN_PRINTD(data->filter_zero_point);
  KN_PRINTD(data->output_activation_min);
  KN_PRINTD(data->output_activation_max);
  if (data_ex->opt_constraint) {
    // remove scratch
    data_ex->buffer_idx = -1;

    int32_t *p_fc_mapped_filter = nullptr;

    const TfLiteEvalTensor *filterEval = tflite::micro::GetEvalInput(
        context, node, kFullyConnectedWeightsTensor);
    const int8_t *filter_input =
        tflite::micro::GetTensorData<int8_t>(filterEval);
    const int32_t map_coeff_size = tflite::FullyConnectedMap8bitCoeffs(
        NULL, NULL, output_depth, accum_depth);

    // if(params->weights_format == kTfLiteFullyConnectedWeightsFormatDefault)
    KN_PRINTD(output_depth);
    KN_PRINTD(accum_depth);
    // KN_PRINT_Q7_SIZE(filter_input, output_depth * accum_depth);
    if (!tflite::is_coeffs_mapped(context)) {
      KN_PRINTD(map_coeff_size);
      KN_PRINT_Q7_SIZE( filter_input, (output_depth
       *accum_depth));

      p_fc_mapped_filter =
          (int32_t *)context->AllocatePersistentBuffer(context, map_coeff_size);
      if (p_fc_mapped_filter) {
        tflite::FullyConnectedMap8bitCoeffs((int8_t *)p_fc_mapped_filter,
                                            (int8_t *)filter_input,
                                            output_depth, accum_depth);
      }
       KN_PRINT_Q7_SIZE(p_fc_mapped_filter, map_coeff_size);
    } else {
      p_fc_mapped_filter = (int32_t *)filter_input;  // remapping
    }
    // KN_PRINT_Q7_SIZE(p_dmx1a_fc_mapped_filter, map_coeff_size);
    uint8_t offsetInput = (-data->input_zero_point) & 0xff;
    // uint32_t offsetVR=offsetInput;
    data_ex->input_offset_int8 = (offsetInput << 24) | (offsetInput << 16) |
                              (offsetInput << 8) | offsetInput;

    data_ex->mapped_filter = (int32_t*)p_fc_mapped_filter;
    if (data_ex->input_offset_int8 == 0x80808080 ||
        data_ex->input_offset_int8 == 0x0) {
      data_ex->opt_constraint = 2;  // faster without input offset
      data_ex->inputOffsetWithW = nullptr;
    } else {
      int inFCMA8 = (((output_depth + 7) >> 3) << 3);
      int32_t *inputOffsetWithW = (int32_t *)context->AllocatePersistentBuffer(
          context, inFCMA8 * sizeof(int32_t));
      data_ex->inputOffsetWithW = inputOffsetWithW;

      MVMInputOffsetPrepare(data_ex->mapped_filter, inputOffsetWithW,
                            output_depth, accum_depth,
                            data_ex->input_offset_int8);
      KN_PRINT_Q31_SIZE(data_ex->inputOffsetWithW, inFCMA8);
    }

    if (bias) {
      const TfLiteEvalTensor *biasEval =
          tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
      const int32_t *bias_input =
          tflite::micro::GetTensorData<int32_t>(biasEval);
      tflite::ConvertQ31ToAfloat(bias_input, (AScalar *)bias_input,
                                 output_depth, 17);
    }
    tflite::ConvertQ31ToAfloat(data->output_zero_point,
                               data_ex->outputOffset,
                               17);
  }

  if (data_ex->opt_constraint_float)
  {
      const TfLiteEvalTensor* weightEval = tflite::micro::GetEvalInput(
        context, node, kFullyConnectedWeightsTensor);
      const float* weight =
          tflite::micro::GetTensorData<float>(weightEval);
      
      if (filter->type == kTfLiteFloat32)
      {
          if (weight)
          {
              tflite::ConvertIEEEFloatToAfloat(weight, (AScalar*)weight, ElementCount(*weightEval->dims));
          }
          //KN_PRINT_AFLOAT
         // KN_PRINT_AFLOAT(weight, ElementCount(*weightEval->dims));
      }
      else if (filter->type == kTfLiteFloat16)
      {
          //KN_PRINT_AFLOAT16(weight, ElementCount(*weightEval->dims));
      }
      else if (filter->type == kTfLiteInt8)
      {
          //KN_PRINT_Q7_SIZE(weight, ElementCount(*weightEval->dims));
        data_ex->filter_scale =
            AScalar(filter->params.scale);  // take zero point as block exp
          KN_PRINTAFLT(data_ex->filter_scale);
          // SHOULd HAVE NO PER OUTPUT SCALE
          if (tflite::is_coeffs_mapped(context))
          {
            data_ex->opt_constraint_float = FC_OPT_FLT_X_INT8_MVM;

              // for 32bit alignment
              TF_LITE_ENSURE_STATUS(// for convert MVM input temp store
                  context->RequestScratchBufferInArena(
                    context, sizeof(int8_t) * accum_depth,
                    &data_ex->buffer_idx));
              //data->inputOffsetWithW = p_fc_in_temp; // TEMP
          }
      }
      if (bias)
      {
          const TfLiteEvalTensor* biasEval =
              tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
          const float* bias_data =
              tflite::micro::GetTensorData<float>(biasEval);

          if (bias_data)
          {
              tflite::ConvertIEEEFloatToAfloat(bias_data, (AScalar*)bias_data, ElementCount(*biasEval->dims));

              KN_PRINT_AFLOAT(bias_data, ElementCount(*biasEval->dims));
          }
      }
  }
#endif

  
  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(filter);
  if(bias) micro_context->DeallocateTempTfLiteTensor(bias);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

TfLiteStatus EvalFullyConnectedQuantizedInt8(
    TfLiteContext *context, TfLiteNode *node,const  OpData &data_ex,
    const TfLiteEvalTensor *input, const TfLiteEvalTensor *filter,
    const TfLiteEvalTensor *bias, TfLiteEvalTensor *output) {
  // The 'if' condition can be removed when null handling of bias is added to

  const OpDataFullyConnected &data = static_cast<OpDataFullyConnected >(data_ex.FcOp);
  tflite::FullyConnectedParams op_params;
  op_params.input_offset = -data.input_zero_point;
  op_params.weights_offset = -data.filter_zero_point;
  op_params.output_offset = data.output_zero_point;
  op_params.output_multiplier = data.output_multiplier;
  // TODO(b/138810107): Figure out whether output shift should be inverted
  op_params.output_shift = data.output_shift;
  op_params.quantized_activation_min = data.output_activation_min;
  op_params.quantized_activation_max = data.output_activation_max;

  const RuntimeShape output_shape = tflite::micro::GetTensorShape(output);
 // TFLITE_DCHECK_EQ(output_shape.DimensionsCount(), 2);

  const RuntimeShape input_shape = tflite::micro::GetTensorShape(input);
  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input),
                   ElementCount(*input->dims));
  KN_PRINT_SHAPE(input_shape);
  KN_PRINT_SHAPE(tflite::micro::GetTensorShape(filter));
  KN_PRINT_SHAPE(output_shape);
#if defined(HEMILITE_FC_OPT)
  if (data_ex.opt_constraint) {
    const int8_t *inputLocal = tflite::micro::GetTensorData<int8_t>(input);
    const int8_t *outputLocal = tflite::micro::GetTensorData<int8_t>(output);
    const int8_t *filterMVM = tflite::micro::GetTensorData<int8_t>(filter);
    const int32_t *baisMVM = (bias) ? tflite::micro::GetTensorData<int32_t>(bias): nullptr;
    const int output_dim_count = output_shape.DimensionsCount();
    const int output_depth = output_shape.Dims(output_dim_count-1);
    const RuntimeShape filter_shape = tflite::micro::GetTensorShape(filter);
    const int filter_dim_count = filter_shape.DimensionsCount();
    int accum_depth = filter_shape.Dims(filter_dim_count - 1);
    int32_t inputCount = ElementCount(*input->dims);

    accum_depth =
        XT_MIN(accum_depth,
               inputCount);  // real input dim  and aligned input filter shape
    const int batches = FlatSizeSkipDim(output_shape, output_dim_count - 1);

    FullyConnectedQuantizedInt8(context, op_params, data_ex, inputLocal, filterMVM,
                                baisMVM, outputLocal, batches, accum_depth,
                                output_depth, kTfLiteInt8);

  } else
#endif
  {
#ifndef REMOVE_REFOP_SUPPORT

    const int32_t* bias_data =
        nullptr != bias ? tflite::micro::GetTensorData<int32_t>(bias)
        : nullptr;

    reference_integer_ops::FullyConnected(
        op_params, tflite::micro::GetTensorShape(input),
        tflite::micro::GetTensorData<int8_t>(input),
        tflite::micro::GetTensorShape(filter),
        tflite::micro::GetTensorData<int8_t>(filter),
        tflite::micro::GetTensorShape(bias),
        bias_data,
        tflite::micro::GetTensorShape(output),
        tflite::micro::GetTensorData<int8_t>(output));
#else
    return kTfLiteError;
#endif
    //   KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
    //   ElementCount(*output->dims));
  }
  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                   ElementCount(*output->dims));
  return kTfLiteOk;
}
#ifndef REMOVE_REFOP_SUPPORT
TfLiteStatus EvalQuantized(TfLiteContext *context, TfLiteNode *node,
                           const OpData &data_ex, const TfLiteEvalTensor *input,
                           const TfLiteEvalTensor *filter,
                           const TfLiteEvalTensor *bias,
                           TfLiteEvalTensor *output) {
  const OpDataFullyConnected &data =
      static_cast<OpDataFullyConnected>((data_ex.FcOp));

  const int32_t input_offset = -data.input_zero_point;
  const int32_t filter_offset = -data.filter_zero_point;
  const int32_t output_offset = data.output_zero_point;

  tflite::FullyConnectedParams op_params;
  op_params.input_offset = input_offset;
  op_params.weights_offset = filter_offset;
  op_params.output_offset = output_offset;
  op_params.output_multiplier = data.output_multiplier;
  // Legacy ops used mixed left and right shifts. Now all are +ve-means-left.
  op_params.output_shift = data.output_shift;
  op_params.quantized_activation_min = data.output_activation_min;
  op_params.quantized_activation_max = data.output_activation_max;

  const RuntimeShape output_shape = tflite::micro::GetTensorShape(output);
  TFLITE_DCHECK_EQ(output_shape.DimensionsCount(), 2);
  //    const int batches = output_shape.Dims(0);
  // const int output_depth = output_shape.Dims(1);
  const RuntimeShape filter_shape = tflite::micro::GetTensorShape(filter);
  // const int filter_dim_count = filter_shape.DimensionsCount();
  // const int accum_depth = filter_shape.Dims(filter_dim_count - 1);
  const RuntimeShape input_shape = tflite::micro::GetTensorShape(input);

#define TF_LITE_FULLY_CONNECTED(output_data_type)      \
  reference_ops::FullyConnected(                       \
      op_params, tflite::micro::GetTensorShape(input), \
      tflite::micro::GetTensorData<uint8_t>(input),    \
      tflite::micro::GetTensorShape(filter),           \
      tflite::micro::GetTensorData<uint8_t>(filter),   \
      tflite::micro::GetTensorShape(bias),             \
      tflite::micro::GetTensorData<int32_t>(bias),     \
      tflite::micro::GetTensorShape(output),           \
      tflite::micro::GetTensorData<output_data_type>(output))
  switch (output->type) {
    case kTfLiteUInt8:
      TF_LITE_FULLY_CONNECTED(uint8_t);
      break;
    case kTfLiteInt16:
      TF_LITE_FULLY_CONNECTED(int16_t);
      break;
    default:
      TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(output->type), output->type);
      return kTfLiteError;
  }

  return kTfLiteOk;
}
#endif

TfLiteStatus EvalFloatInt8(TfLiteContext* context, TfLiteNode* node,
    const OpData& data, TfLiteFusedActivation activation,
    const TfLiteEvalTensor* input,
    const TfLiteEvalTensor* filter,
    const TfLiteEvalTensor* bias, TfLiteEvalTensor* output) {
    float output_activation_min, output_activation_max;
    CalculateActivationRange(activation, &output_activation_min,
        &output_activation_max);
    tflite::FullyConnectedParams op_params;
    op_params.float_activation_min = output_activation_min;
    op_params.float_activation_max = output_activation_max;
#if defined(HEMILITE_FC_OPT)
    KN_PRINTD(data.opt_constraint_float);
    if (data.opt_constraint_float) {

        const RuntimeShape output_shape = tflite::micro::GetTensorShape(output);
        const int output_dim_count = output_shape.DimensionsCount();

        const int batches = FlatSizeSkipDim(output_shape, output_dim_count - 1);
        float* inputLocal = (float*)tflite::micro::GetTensorData<float>(input);
        float* outputLocal = tflite::micro::GetTensorData<float>(output);
        const int8_t* filterLocal = tflite::micro::GetTensorData<int8_t>(filter);
        const float* biasLocal = bias ? tflite::micro::GetTensorData<float>(bias) : nullptr;
        const int output_depth = output_shape.Dims(output_dim_count - 1);
        const RuntimeShape filter_shape = tflite::micro::GetTensorShape(filter);
        const int filter_dim_count = filter_shape.DimensionsCount();
        int accum_depth = filter_shape.Dims(filter_dim_count - 1);
        int32_t inputCount = ElementCount(*input->dims);
        AScalar scale = data.filter_scale;
        AScalar act_min, act_max;
        CalculateActivationRangeAflt(activation, &act_min, &act_max);
        TF_LITE_ENSURE_MSG(context, ((unsigned int)filterLocal & 0x3) == 0, "filter pointer must 4 byte align");
        accum_depth =
            XT_MIN(accum_depth,
                inputCount);  // real input dim  and aligned input filter shape
        int batch = batches;
        while (batch) {

            if (data.opt_constraint_float == FC_OPT_FLT_X_INT8_MVM)
            {
                int32_t* p_x_tmp = nullptr;
                if (data.buffer_idx > -1) {
                    p_x_tmp =
                        (int32_t*)context->GetScratchBuffer(context, data.buffer_idx);
                }

                MVMFloatInt8Kernel(outputLocal, inputLocal,(const int32_t *) filterLocal, biasLocal,
                    output_depth, accum_depth, p_x_tmp, act_min, act_max, scale);
            }
            else {
                FullyConnectedFloatInt8(outputLocal, inputLocal, filterLocal, biasLocal,
                    output_depth, accum_depth, act_min, act_max, scale);
            }

            inputLocal += accum_depth;
            outputLocal += output_depth;
            batch--;
        }
    }
    else
#endif
    {

        return kTfLiteError;

    }

    KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
        ElementCount(*output->dims));

    return kTfLiteOk;
}

TfLiteStatus EvalFloat16(TfLiteContext* context, TfLiteNode* node,
    const OpData& data, TfLiteFusedActivation activation,
    const TfLiteEvalTensor* input,
    const TfLiteEvalTensor* filter,
    const TfLiteEvalTensor* bias, TfLiteEvalTensor* output) {
    float output_activation_min, output_activation_max;
    CalculateActivationRange(activation, &output_activation_min,
        &output_activation_max);
    tflite::FullyConnectedParams op_params;
    op_params.float_activation_min = output_activation_min;
    op_params.float_activation_max = output_activation_max;
#if defined(HEMILITE_FC_OPT)
    KN_PRINTD(data.opt_constraint_float);
    if (data.opt_constraint_float) {

        const RuntimeShape output_shape = tflite::micro::GetTensorShape(output);
        const int output_dim_count = output_shape.DimensionsCount();

        const int batches = FlatSizeSkipDim(output_shape, output_dim_count - 1);
        float* inputLocal = (float*)tflite::micro::GetTensorData<float>(input);
        float* outputLocal = tflite::micro::GetTensorData<float>(output);
        const TfLiteFloat16* filterLocal = tflite::micro::GetTensorData<TfLiteFloat16>(filter);
        const float* biasLocal = bias ? tflite::micro::GetTensorData<float>(bias) : nullptr;
        const int output_depth = output_shape.Dims(output_dim_count - 1);
        const RuntimeShape filter_shape = tflite::micro::GetTensorShape(filter);
        const int filter_dim_count = filter_shape.DimensionsCount();
        int accum_depth = filter_shape.Dims(filter_dim_count - 1);
        int32_t inputCount = ElementCount(*input->dims);

        AScalar act_min, act_max;
        CalculateActivationRangeAflt(activation, &act_min, &act_max);
        TF_LITE_ENSURE_MSG(context, ((unsigned int)filterLocal & 0x3) == 0, "filter pointer must 4 byte align");
        accum_depth =
            XT_MIN(accum_depth,
                inputCount);  // real input dim  and aligned input filter shape
        int batch = batches;
        while (batch) {
            FullyConnectedFloat16(outputLocal, inputLocal, filterLocal, biasLocal,
                output_depth, accum_depth, act_min, act_max);
     

            inputLocal += accum_depth;
            outputLocal += output_depth;
            batch--;
        }
    }
    else
#endif
    {

        return kTfLiteError;

    }

    KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
        ElementCount(*output->dims));

    return kTfLiteOk;
}
TfLiteStatus EvalFloat32(TfLiteContext *context, TfLiteNode *node,
                       const OpData &data, TfLiteFusedActivation activation,
                       const TfLiteEvalTensor *input,
                       const TfLiteEvalTensor *filter,
                       const TfLiteEvalTensor *bias, TfLiteEvalTensor *output) {
  float output_activation_min, output_activation_max;
  CalculateActivationRange(activation, &output_activation_min,
                           &output_activation_max);
  tflite::FullyConnectedParams op_params;
  op_params.float_activation_min = output_activation_min;
  op_params.float_activation_max = output_activation_max;
#if defined(HEMILITE_FC_OPT)
  KN_PRINTD(data.opt_constraint_float);
  if (data.opt_constraint_float) {
    // data->in
    // const float output_activation_min = op_params.float_activation_min;
    //  const float output_activation_max = op_params.float_activation_max;
    // TODO(b/62193649): This really should be:
    //     const int batches = ArraySize(output_dims, 1);
    // but the current --variable_batch hack consists in overwriting the 3rd
    // dimension with the runtime batch size, as we don't keep track for each
    // array of which dimension is the batch dimension in it.

    const RuntimeShape output_shape = tflite::micro::GetTensorShape(output);
    const int output_dim_count = output_shape.DimensionsCount();

    const int batches = FlatSizeSkipDim(output_shape, output_dim_count - 1);
    float *inputLocal = (float *)tflite::micro::GetTensorData<float>(input);
    float *outputLocal = tflite::micro::GetTensorData<float>(output);
    const float *filterLocal = tflite::micro::GetTensorData<float>(filter);
    const float *biasLocal = bias ? tflite::micro::GetTensorData<float>(bias): nullptr;
    const int output_depth = output_shape.Dims(output_dim_count-1);
    const RuntimeShape filter_shape = tflite::micro::GetTensorShape(filter);
    const int filter_dim_count = filter_shape.DimensionsCount();
    int accum_depth = filter_shape.Dims(filter_dim_count - 1);
    int32_t inputCount = ElementCount(*input->dims);

    AScalar act_min, act_max;
    CalculateActivationRangeAflt(activation, &act_min, &act_max);

    accum_depth =
        XT_MIN(accum_depth,
               inputCount);  // real input dim  and aligned input filter shape
    int batch = batches;
    while (batch) {
      FullyConnectedFloat(outputLocal, inputLocal, filterLocal, biasLocal,
                          output_depth, accum_depth, act_min, act_max);
      // if(baisLocal) {
      //   FullyConnecteAddBias();
      //  }
     
      inputLocal += accum_depth;
      outputLocal += output_depth;
      batch--;
    }
  } else
#endif
  {
#ifndef REMOVE_REFOP_SUPPORT
    const float* bias_data = bias ? tflite::micro::GetTensorData<float>(bias) : nullptr;
    KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input),
                   ElementCount(*input->dims));
    tflite::reference_ops::FullyConnected(
        op_params, tflite::micro::GetTensorShape(input),
        tflite::micro::GetTensorData<float>(input),
        tflite::micro::GetTensorShape(filter),
        tflite::micro::GetTensorData<float>(filter),
        tflite::micro::GetTensorShape(bias),
        bias_data,
        tflite::micro::GetTensorShape(output),
        tflite::micro::GetTensorData<float>(output));
  #else
return kTfLiteError;
  #endif
  }

    KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                 ElementCount(*output->dims));

  return kTfLiteOk;
}

TfLiteStatus Eval(TfLiteContext *context, TfLiteNode *node) {
  TFLITE_DCHECK(node->builtin_data != nullptr);
#ifndef REMOVE_FLOAT_SUPPORT
  const auto *params =
      static_cast<const TfLiteFullyConnectedParams *>(node->builtin_data);
#endif
  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedInputTensor);
  const TfLiteEvalTensor *filter =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedWeightsTensor);

  const TfLiteEvalTensor* bias =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);

  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kFullyConnectedOutputTensor);

  //const TfLiteEvalTensor* bias = biasTmp ? tflite::micro::GetEvalInput(context, node, kBiasTensor) : nullptr;
  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData& data = *(static_cast<const OpData*>(node->user_data));

  // Checks in Prepare ensure input, output and filter types are all the same.
  switch (input->type) {
    case kTfLiteFloat32:
        switch (filter->type)
        {
        case kTfLiteFloat32:
            return EvalFloat32(context, node, data, params->activation, input, filter,
                bias, output);
        case kTfLiteFloat16:
            return EvalFloat16(context, node, data, params->activation, input, filter,
                bias, output);
        case kTfLiteInt8:
            EvalFloatInt8(context, node, data, params->activation, input, filter,
                bias, output);
            break;
        default:
            TF_LITE_KERNEL_LOG(context, "filter Type %s (%d) not supported. for input float32",
                TfLiteTypeGetName(filter->type), filter->type);
            return kTfLiteError;
        }
        break;
    case kTfLiteInt8:
      return EvalFullyConnectedQuantizedInt8(context, node, data, input, filter,
                                             bias, output);
#ifndef REMOVE_REFOP_SUPPORT
    case kTfLiteUInt8:
      return EvalQuantized(context, node, data, input, filter, bias, output);

    case kTfLiteInt16: {
      switch (filter->type) {
        case kTfLiteInt8: {
          KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(filter),
                            ElementCount(*filter->dims));

          KN_PRINT_Q15_SIZE(tflite::micro::GetTensorData<int16_t>(input),
                            ElementCount(*input->dims));

          tflite::reference_integer_ops::FullyConnected(
              FullyConnectedParamsQuantized(data.FcOp),
              tflite::micro::GetTensorShape(input),
              tflite::micro::GetTensorData<int16_t>(input),
              tflite::micro::GetTensorShape(filter),
              tflite::micro::GetTensorData<int8_t>(filter),
              tflite::micro::GetTensorShape(bias),
              tflite::micro::GetOptionalTensorData<int64_t>(bias),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<int16_t>(output));

          KN_PRINT_Q15_SIZE(tflite::micro::GetTensorData<int16_t>(output),
                            ElementCount(*output->dims));

          break;
        }
        default: {
          TF_LITE_KERNEL_LOG(context, "Filter type %s (%d) not supported.",
                             TfLiteTypeGetName(filter->type), input->type);
          return kTfLiteError;
        }
      }
    }
        break;
#endif
    default:
      TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(input->type), input->type);
      return kTfLiteError;
  }
  return kTfLiteOk;
}

TfLiteStatus EvalFullyConnectedInt8(TfLiteContext *context, TfLiteNode *node) {
  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedInputTensor);
  const TfLiteEvalTensor *filter =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedWeightsTensor);
 // const TfLiteEvalTensor *bias =
 //     tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
 // const TfLiteTensor* biasTmp =
 //     GetOptionalInputTensor(context, node, kFullyConnectedBiasTensor); //FIXME
 
  
  const TfLiteEvalTensor* bias =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kFullyConnectedOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData &data = *(static_cast<const OpData *>(node->user_data));

  // Checks in Prepare ensure input, output and filter types are all the same.
  if (input->type != kTfLiteInt8) {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(input->type), input->type);
    return kTfLiteError;
  }

  EvalFullyConnectedQuantizedInt8(context, node, data, input, filter, bias,
                                  output);

  return kTfLiteOk;
}

TfLiteStatus EvalFullyConnectedFloatInt8(TfLiteContext* context, TfLiteNode* node) {
    const TfLiteEvalTensor* input =
        tflite::micro::GetEvalInput(context, node, kFullyConnectedInputTensor);
    const TfLiteEvalTensor* filter =
        tflite::micro::GetEvalInput(context, node, kFullyConnectedWeightsTensor);
    // const TfLiteEvalTensor *bias =
    //     tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
    //const TfLiteTensor* biasTmp =
    //    GetOptionalInputTensor(context, node, kFullyConnectedBiasTensor); //FIXME
    const TfLiteEvalTensor* bias =
        tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
    TfLiteEvalTensor* output =
        tflite::micro::GetEvalOutput(context, node, kFullyConnectedOutputTensor);

    TFLITE_DCHECK(node->user_data != nullptr);
    const OpData& data = *(static_cast<const OpData*>(node->user_data));
#ifndef REMOVE_FLOAT_SUPPORT
    const auto* params =
        static_cast<const TfLiteFullyConnectedParams*>(node->builtin_data);
#endif
    if (input->type != kTfLiteFloat32 && filter->type != kTfLiteInt8) {
        TF_LITE_KERNEL_LOG(context, "Input Type %s (%d) Filter Type %s (%d) not supported.",
            TfLiteTypeGetName(input->type), input->type,
            TfLiteTypeGetName(filter->type), filter->type);
        return kTfLiteError;
    }

    EvalFloatInt8(context, node, data, params->activation, input, filter,
        bias, output);
  
    return kTfLiteOk;
}

TfLiteStatus EvalFullyConnectedFloat16(TfLiteContext* context, TfLiteNode* node) {
    const TfLiteEvalTensor* input =
        tflite::micro::GetEvalInput(context, node, kFullyConnectedInputTensor);
    const TfLiteEvalTensor* filter =
        tflite::micro::GetEvalInput(context, node, kFullyConnectedWeightsTensor);
    // const TfLiteEvalTensor *bias =
    //     tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
    //const TfLiteTensor* biasTmp =
    //    GetOptionalInputTensor(context, node, kFullyConnectedBiasTensor); //FIXME
    const TfLiteEvalTensor* bias =
        tflite::micro::GetEvalInput(context, node,
                                              kFullyConnectedBiasTensor);
    TfLiteEvalTensor* output =
        tflite::micro::GetEvalOutput(context, node, kFullyConnectedOutputTensor);

    TFLITE_DCHECK(node->user_data != nullptr);
    const OpData& data = *(static_cast<const OpData*>(node->user_data));
#ifndef REMOVE_FLOAT_SUPPORT
    const auto* params =
        static_cast<const TfLiteFullyConnectedParams*>(node->builtin_data);
#endif
    if (input->type != kTfLiteFloat32 && filter->type != kTfLiteFloat16) {
        TF_LITE_KERNEL_LOG(context, "IN Type %s (%d) FILTER %s (%d) not supported.",
            TfLiteTypeGetName(input->type), input->type, 
            TfLiteTypeGetName(filter->type), filter->type);
        return kTfLiteError;
    }

    EvalFloat16(context, node, data, params->activation, input, filter,
        bias, output);

    return kTfLiteOk;
}
TfLiteStatus EvalFullyConnectedFloat32(TfLiteContext* context, TfLiteNode* node) {
    const TfLiteEvalTensor* input =
        tflite::micro::GetEvalInput(context, node, kFullyConnectedInputTensor);
    const TfLiteEvalTensor* filter =
        tflite::micro::GetEvalInput(context, node, kFullyConnectedWeightsTensor);
    // const TfLiteEvalTensor *bias =
    //     tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
    //const TfLiteTensor* biasTmp =
    //    GetOptionalInputTensor(context, node, kFullyConnectedBiasTensor); //FIXME
    const TfLiteEvalTensor* bias =
        tflite::micro::GetEvalInput(context, node,
                                       kFullyConnectedBiasTensor);
   
    TfLiteEvalTensor* output =
        tflite::micro::GetEvalOutput(context, node, kFullyConnectedOutputTensor);

    TFLITE_DCHECK(node->user_data != nullptr);
    const OpData& data = *(static_cast<const OpData*>(node->user_data));
#ifndef REMOVE_FLOAT_SUPPORT
    const auto* params =
        static_cast<const TfLiteFullyConnectedParams*>(node->builtin_data);
#endif
    if (input->type != kTfLiteFloat32) {
        TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
            TfLiteTypeGetName(input->type), input->type);
        return kTfLiteError;
    }
    //EvalFloat32(context, node, data, params->activation, input, filter,
  //      bias, output);
    switch (filter->type)
    {
    case kTfLiteFloat32:
        return EvalFloat32(context, node, data, params->activation, input, filter,
            bias, output);
    case kTfLiteFloat16:
        return EvalFloat16(context, node, data, params->activation, input, filter,
            bias, output);
    case kTfLiteInt8:
        return EvalFloatInt8(context, node, data, params->activation, input, filter,
            bias, output);
    default:
        TF_LITE_KERNEL_LOG(context, "filter Type %s (%d) not supported. for input float32",
            TfLiteTypeGetName(filter->type), filter->type);
        return kTfLiteError;
    }
    return kTfLiteOk;
}
}  // namespace

TFLMRegistration Register_FULLY_CONNECTED() {
  return tflite::micro::RegisterOp(Init, Prepare, Eval);
}

TFLMRegistration Register_FULLY_CONNECTED_INT8() {
  return tflite::micro::RegisterOp(Init, Prepare, EvalFullyConnectedInt8);
}
TFLMRegistration Register_FULLY_CONNECTED_FLOAT32() {
  return tflite::micro::RegisterOp(Init, Prepare, EvalFullyConnectedFloat32);
}

TFLMRegistration Register_FULLY_CONNECTED_FLOAT16() {
  return tflite::micro::RegisterOp(Init, Prepare, EvalFullyConnectedFloat16);
}
TFLMRegistration Register_FULLY_CONNECTED_FLOATINT8() {
  return tflite::micro::RegisterOp(Init, Prepare, EvalFullyConnectedFloatInt8);
}
}  // namespace tflite
