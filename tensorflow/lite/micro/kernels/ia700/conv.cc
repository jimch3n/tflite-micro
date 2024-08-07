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
#define ENABLE_DILATION_OPT // enable dialtion optimization 
#include "tensorflow/lite/micro/ia700/config.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/conv.h"
#endif
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/integer_ops/conv.h"
#endif
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/padding.h"
#include "tensorflow/lite/micro/kernels/conv.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"

#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount
#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
namespace tflite {
namespace {

// Conv is quantized along dimension 0:
// https://www.tensorflow.org/lite/performance/quantization_spec
constexpr int kConvQuantizedDimension = 0;
// local Opdata additional member item
typedef enum {
    CONV_OPT_NONE=0,
    CONV_OPT_TYPE1 = 1,
    CONV_OPT_TYPE2 = 2, // input channel align 4
    CONV_OPT_TYPE3 = 3,
    CONV_OPT_TYPE4 = 4,

    // hybrid
    CONV_OPT_FLT_X_INT8_PW=8,
} conv_opt_type;
struct OpData {
  struct OpDataConv ConvOp;
  // Index to buffer for optimizations if applicable.
  int buffer_idx;
  // uint32_t im2col_scratch_bytes;  // scratch bytes for im2col
  // uint16_t input_scratch_bytes;
  int32_t *mapped_filter;  // aligned 4bytes, int8_t data to store pointer for
                           // mapping W
  // AScalar *outputMultiplerPerCh; // perchannel
  AScalar outputOffset;
  AScalar outputMultipler;  // uint8_t
  uint32_t input_offset_int8;
  uint32_t input_offset_int8_neg;
  int32_t *inputOffsetWithW;  // pre-compute (inputOffset)* w
  AScalar filter_scale;
  int opt_constraint;         // 0: 1:input offset 0 or 128,  2: align4 copy,

  int opt_constraint_float;
  ds_conv2d_layer_t conv2d;

  uint32_t sizeScratchIm2Col;
  uint32_t sizeScratchOutput;
};

TfLiteStatus ConvPrepareOpt(TfLiteContext *context, TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  // OpDataConv* data = static_cast<OpDataConv*>(node->user_data);

  OpData *data_ex = static_cast<OpData *>(node->user_data);
  OpDataConv *data = static_cast<OpDataConv *>(&data_ex->ConvOp);

  const auto &params =
      *(static_cast<const TfLiteConvParams *>(node->builtin_data));

  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kConvOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kConvInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor* filter =
      micro_context->AllocateTempInputTensor(node, kConvWeightsTensor);
  TF_LITE_ENSURE(context, filter != nullptr);


  const int input_width = input->dims->data[2];
  const int input_height = input->dims->data[1];
  const int filter_width = filter->dims->data[2];
  const int filter_height = filter->dims->data[1];
  const int output_width = output->dims->data[2];
  const int output_height = output->dims->data[1];

  // Dynamically allocate per-channel quantization parameters.
  const int num_channels = filter->dims->data[kConvQuantizedDimension];
  data->per_channel_output_multiplier =
      static_cast<int32_t *>(context->AllocatePersistentBuffer(
          context, num_channels * sizeof(int32_t)));
  data->per_channel_output_shift =
      static_cast<int32_t *>(context->AllocatePersistentBuffer(
          context, num_channels * sizeof(int32_t)));

  // All per-channel quantized tensors need valid zero point and scale arrays.
  if (input->type == kTfLiteInt8 || input->type == kTfLiteInt16) {
    TF_LITE_ENSURE_EQ(context, filter->quantization.type,
                      kTfLiteAffineQuantization);

    const auto *affine_quantization =
        static_cast<TfLiteAffineQuantization *>(filter->quantization.params);
    TFLITE_DCHECK(affine_quantization != nullptr);
    TFLITE_DCHECK(affine_quantization->scale != nullptr);
    TFLITE_DCHECK(affine_quantization->zero_point != nullptr);

    TF_LITE_ENSURE(context,
                   affine_quantization->scale->size == 1 ||
                       affine_quantization->scale->size ==
                           filter->dims->data[kConvQuantizedDimension]);
    TF_LITE_ENSURE_EQ(context, affine_quantization->scale->size,
                      affine_quantization->zero_point->size);
  }

  TF_LITE_ENSURE_STATUS(CalculateOpDataConv(
      context, node, params, input_width, input_height, filter_width,
      filter_height, output_width, output_height, input->type, data));
  ds_conv2d_layer_t &conv2d = data_ex->conv2d;

  // assign conv2d

  RuntimeShape input_shape = GetTensorShape(input);
  RuntimeShape output_shape = GetTensorShape(output);
  RuntimeShape filter_shape = GetTensorShape(filter);

  conv2d.in_y = input_shape.Dims(1);
  conv2d.in_x = input_shape.Dims(2);
  conv2d.in_ch = input_shape.Dims(3);

  conv2d.ker_y = filter_shape.Dims(1);
  conv2d.ker_x = filter_shape.Dims(2);

  conv2d.out_y = output_shape.Dims(1);
  conv2d.out_x = output_shape.Dims(2);
  conv2d.out_ch = output_shape.Dims(3);

  conv2d.dilation_y = params.dilation_height_factor;
  conv2d.dilation_x = params.dilation_width_factor;

  conv2d.stride_y = params.stride_height;
  conv2d.stride_x = params.stride_width;
  conv2d.padding_y = data->padding.height;
  conv2d.padding_x = data->padding.width;
  conv2d.input_offset = -data->input_zero_point;
  //    conv2d.filter_offset = -data->filter_zero_point;
  KN_PRINTD(conv2d.dilation_y); KN_PRINTD(conv2d.dilation_x);
  if (input->type == kTfLiteInt8) {
    // Initialize cmsis-nn convolution parameters
    data_ex->opt_constraint = CONV_OPT_NONE;
#if defined(HEMILITE_CONV_OPT)
    int32_t *p_mapped_filter = nullptr;

    const TfLiteEvalTensor *filterEval =
        tflite::micro::GetEvalInput(context, node, kConvWeightsTensor);
    const int8_t *filter_input =
        tflite::micro::GetTensorData<int8_t>(filterEval);

    uint8_t offsetInput = conv2d.input_offset & 0xff;
    // uint32_t offsetVR=offsetInput;
    data_ex->input_offset_int8 = (offsetInput << 24) | (offsetInput << 16) |
                                 (offsetInput << 8) | offsetInput;
    offsetInput = (data->input_zero_point & 0xff);
    data_ex->input_offset_int8_neg = (offsetInput << 24) | (offsetInput << 16) |
                                     (offsetInput << 8) | offsetInput;
#ifdef ENABLE_DILATION_OPT
    bool dilation_xy1 = true; //enable DIALTION
#else
    bool dilation_xy1 = (1 == params.dilation_width_factor &&     1 == params.dilation_height_factor);
#endif
    KN_PRINTD(dilation_xy1);
    KN_PRINTD(conv2d.input_offset);

    if ((conv2d.input_offset >= -128 &&
         conv2d.input_offset <= 128) && dilation_xy1)
    {
      data_ex->opt_constraint = CONV_OPT_TYPE1;
      if ((conv2d.in_ch & 3) == 0) {
        // aliged 4 byte copy
        data_ex->opt_constraint = CONV_OPT_TYPE2;  // TODO
      }
    }
    if (0 != data_ex->opt_constraint) {
      const int input_depth = conv2d.in_ch;  // input_shape.Dims(3);
      const int output_depth = conv2d.out_ch;
      int32_t output_matVec = output_depth;
      const int8_t *pfilter_val = &filter_input[0];
      const int32_t map_coeff_size = tflite::ConvMap8bitCoeffs(
          NULL, conv2d.ker_y, conv2d.ker_x, NULL, output_depth, input_depth);

      if (!tflite::is_coeffs_mapped(context)) {
        // const int32_t map_coeff_size = tflite::dmx1a::ConvMap8bitCoeffs(NULL,
        // conv2d.ker_y, conv2d.ker_x, NULL,  output_depth ,input_depth );
        p_mapped_filter = (int32_t *)context->AllocatePersistentBuffer(
            context, map_coeff_size * sizeof(int8_t));
        if (p_mapped_filter) {
          tflite::ConvMap8bitCoeffs((int8_t *)p_mapped_filter, conv2d.ker_y,
                                    conv2d.ker_x, (int8_t *)pfilter_val,
                                    output_depth, input_depth);
        }
      } else {
        p_mapped_filter = (int32_t *)pfilter_val;
      }

      data_ex->mapped_filter = p_mapped_filter;
      const TfLiteEvalTensor *biasEval =
          tflite::micro::GetEvalInput(context, node, kConvBiasTensor);
      const int32_t *bias_input =
          tflite::micro::GetTensorData<int32_t>(biasEval);
      tflite::ConvertQ31ToAfloat(bias_input, (AScalar *)bias_input,
                                 output_matVec, 17);
      tflite::ConvertQ31ToAfloat(data->output_zero_point, data_ex->outputOffset,
                                 17);

      // data->outputMultiplerPerCh = (AScalar
      // *)context->AllocatePersistentBuffer(context,
      // output_matVec*sizeof(AScalar));
      tflite::ConvertQ31ToAfloat(data->per_channel_output_multiplier,
                                 (AScalar *)data->per_channel_output_multiplier,
                                 output_matVec, data->per_channel_output_shift,
                                 0);

      int buf_size_im2col =
          ((((conv2d.in_ch * conv2d.ker_x * conv2d.ker_y) + 15) >> 4)
           << 4);  // get scratch buffer size for optimization

      int32_t buf_size_output =
          (((conv2d.out_ch + 7) >> 3) << 3) *
          sizeof(int32_t);  // output store 8 multiple align

      int buf_size_scratch = buf_size_im2col + buf_size_output;
      data_ex->sizeScratchIm2Col = buf_size_im2col;
      data_ex->sizeScratchOutput = buf_size_output;

      if (buf_size_scratch > 0) {
        TF_LITE_ENSURE_STATUS(context->RequestScratchBufferInArena(
            context, buf_size_scratch, &data_ex->buffer_idx));

      } else {
        data_ex->buffer_idx = -1;
      }
      // prepare ConvInput Offset
      KN_PRINTD(conv2d.input_offset);
      if (conv2d.input_offset != 128 &&
          conv2d.input_offset != 0)
      {
        int inFCM = conv2d.out_ch;
        int inFCN = conv2d.ker_x * conv2d.ker_y * conv2d.in_ch;
        int inFCMA8 = (((inFCM + 7) >> 3) << 3);
        KN_PRINTD(inFCM);
        KN_PRINTD(inFCN);
        int32_t *inputOffsetWithW =
            (int32_t *)context->AllocatePersistentBuffer(
                context, inFCMA8 * sizeof(int32_t));
        data_ex->inputOffsetWithW = inputOffsetWithW;

        MVMInputOffsetPrepare(data_ex->mapped_filter, inputOffsetWithW, inFCM,
                              inFCN, data_ex->input_offset_int8);

        KN_PRINT_Q31_SIZE(data_ex->inputOffsetWithW, inFCMA8);
      } else {
        data_ex->inputOffsetWithW = nullptr;
      }
    }  // constraint

#endif
  }
// float allocation

  if (input->type == kTfLiteFloat32) {
    // Initialize cmsis-nn convolution parameters
    data_ex->opt_constraint_float = false;
#if defined(HEMILITE_CONV_OPT)
    //    int32_t *p_mapped_filter = nullptr;

#ifdef ENABLE_DILATION_OPT
    bool dilation_xy1 = true; //enable DIALTION
#else
    bool dilation_xy1 =     (1 == params.dilation_width_factor &&
            1 == params.dilation_height_factor); //enable DIALTION
#endif
    data_ex->opt_constraint_float = (
        (filter->type == kTfLiteFloat32 || filter->type == kTfLiteFloat16 || filter->type == kTfLiteInt8) &&\
        dilation_xy1);  // FIXME: any constraint
      // disable for testing kernel script
#if 0
    if (filter->type == kTfLiteFloat16)
    {
        TF_LITE_ENSURE_MSG(context, tflite::is_coeffs_mapped(context) == true,
            "float16 must converted from kn model script");
    }

#endif

    if (0 != data_ex->opt_constraint_float) {
      //  const int input_depth = conv2d.in_ch;  // input_shape.Dims(3);
      //   const int output_depth = conv2d.out_ch;
      //    int32_t output_matVec = output_depth;
      //      const int8_t *pfilter_val = &filter_input[0];
        if (filter->type == kTfLiteInt8)
        {
            data_ex->filter_scale = AScalar(filter->params.scale);
            // check multiple channels scale
            const auto* affine_quantization =
                reinterpret_cast<TfLiteAffineQuantization*>(filter->quantization.params);
            if (affine_quantization)
            {
                const bool is_per_channel = affine_quantization->scale->size > 1;
                const float* filter_scales = affine_quantization->scale->data;

                if (is_per_channel) {

                    for (int i = 0; i < num_channels; ++i) {
                        // If per-tensor quantization parameter is specified, broadcast it along the
                        // quantization dimension (channels_out).
                        const AScalar scale = AScalar(filter_scales[i]);
                        data->per_channel_output_multiplier[i] = scale.raw();
                    }

                }
                else {
                    data->per_channel_output_multiplier = nullptr;
                }
            }
            else {
                data->per_channel_output_multiplier = nullptr;
            }
            // check hybrid INT8 is PW convwith mapped ? 
            if((conv2d.padding_x == 0) && (conv2d.padding_y == 0) && (conv2d.stride_x == 1) &&
                (conv2d.stride_y == 1) && (conv2d.ker_x == 1) && (conv2d.ker_y == 1) &&
                (conv2d.dilation_x == 1 && conv2d.dilation_y == 1))
                {
                if (tflite::is_coeffs_mapped(context))
                {
                    data_ex->opt_constraint_float = CONV_OPT_FLT_X_INT8_PW;
                }
                }
        }
        KN_PRINTD(data_ex->opt_constraint_float);
      data_ex->sizeScratchIm2Col =
          sizeof(float) *
          ((((conv2d.in_ch * conv2d.ker_x * conv2d.ker_y) + 15) >> 4)
           << 4);  // get scratch buffer size for optimization
      int buf_size_scratch = data_ex->sizeScratchIm2Col;
      KN_PRINTD(data_ex->sizeScratchIm2Col);
      if (buf_size_scratch > 0) {
        TF_LITE_ENSURE_STATUS(context->RequestScratchBufferInArena(
            context, buf_size_scratch, &data_ex->buffer_idx));

      } else {
        data_ex->buffer_idx = -1;
      }
      // inplace overwritten weight/bias in afloat, and 
      const TfLiteEvalTensor* weightEval =
          tflite::micro::GetEvalInput(context, node, kConvWeightsTensor);
      const float* weight =
          tflite::micro::GetTensorData<float>(weightEval);
      if (weight)
      {
          if (filter->type == kTfLiteFloat32)
              tflite::ConvertIEEEFloatToAfloat(weight, (AScalar*)weight, ElementCount(*weightEval->dims));
          else if (filter->type == kTfLiteAfloat32)
          {
              // skip the tensor from dequantized cannot replacement
          }
      }
      const TfLiteEvalTensor* biasEval =
          tflite::micro::GetEvalInput(context, node, kConvBiasTensor);
      const float* bias =
          tflite::micro::GetTensorData<float>(biasEval);
      if (bias)
      {
          tflite::ConvertIEEEFloatToAfloat(bias, (AScalar*)bias, ElementCount(*biasEval->dims));

      }
    }  // constraint
#endif
  }

  micro_context->DeallocateTempTfLiteTensor(filter);
  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}  // namespace
void *InitConv(TfLiteContext *context, const char *buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}
#if defined(HEMILITE_CONV_OPT)

int ConvFloatKernel(float *y, const float *x, const float *A, const float *bias,
                    int m, int n, const AScalar &act_min,
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

  UR_bias = align_32x2_load(pBiasLocal);

  if (loopGroupLim > 0) {
    for (jj = 0; jj < loopGroupLim; jj++)  // group
    {
      vr64 VR_blk = vseta_vr(0, 0);
      vr64 VR_out0 = VR_blk;
      vr64 VR_out1 = VR_blk;
      vr64 VR_bias;
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
          //convert_IEEE_float_to_32F_x2(VR_w0);
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

      load_32x2_vr_a(VR_bias, UR_bias, pBiasLocal);

     // convert_IEEE_float_to_32F_x2(VR_bias);
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
    vr64 VR_out0, VR_bias;

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
      //  convert_IEEE_float_to_32F_x2(VR_w0);
      }

      VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
    }
    fr32 fr_out0;
    if (n & 1) {
      load32x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);

      load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);

      convert_IEEE_float_to_32F_x2(VR_blk);
    //  convert_IEEE_float_to_32F_x2(VR_w0);

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
    load32x1_vr_postI(VR_bias, pBiasLocal, INC1, VRQ0);
    //} else {
    // VR_bias = vseta_vr(kConstTable_Zero, 0, 0);
    //}
   // convert_IEEE_float_to_32F_x2(VR_bias);
    VR_actOut = vadds(VR_actOut, VR_bias, 0);
    VR_actOut = vmax(VR_actOut, VR_act_min);
    VR_actOut = vmin(VR_actOut, VR_act_max);

    convert_32F_to_IEEE_float_x2(VR_actOut);
    store32x1_vr_postI(VR_actOut, pActOut, INC1, VRQ0);

    // pW += n;  // add to next group
  }
  return 0;  //(maxExp-31);
}

// input offset is carried, and sign, split two mac
// (input+input_offset)*filter
// = input*filter+ input_offset*filter
//


int ConvApplyOffsetPerCh(
    int8_t *outputQ7, int32_t *pDst, const AScalar *bias, int output_depth,
    const AScalar &outOffsetFr32,
    const AScalar *pOutMultiplerFr32,  // array output channel
    int signs) {
  vr64 VR_y;
  vr64 VR_b0;
  vr64 VR_outMultPerCh;
  int8_t *pY = outputQ7;
  const int32_t *pB = (const int32_t *)bias;
  ulsr32 UR_Dst = align_32x2_load(pDst);
  ulsr32 UR_b = align_32x2_load(pB);

  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);

  vr64 VR_outOffset;
  vr64 VR_q7_out;

  vr64 VR_out;
  replicate_ar(VR_outOffset, 0x3, outOffsetFr32.fr);
  ulsr32 UR_outMultPerCh = align_32x2_load(pOutMultiplerFr32);

  uint32_t groupOfChannel = (uint32_t)output_depth >> 1;
  if (groupOfChannel > 0)
  {
	  load_32x2_vr_a(VR_outMultPerCh, UR_outMultPerCh, pOutMultiplerFr32);
	  load_32x2_vr_a(VR_b0, UR_b, pB);
	  load_32x2_vr_a(VR_y, UR_Dst, pDst);
	  convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
	  convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
	  for (uint32_t group = 0; group < groupOfChannel - 1; group++) {

		  // convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
		  // convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);


		  VR_out = vadds(VR_y, VR_b0, 0x0);
		  VR_out = vmuls(VR_out, VR_outMultPerCh, 0);
		  VR_out = vadds(VR_out, VR_outOffset, 0);
		  // VR_out = vexp_adji(VR_out, 8);

		  load_32x2_vr_a(VR_b0, UR_b, pB);
		  load_32x2_vr_a(VR_y, UR_Dst, pDst);

		  convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
		  convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
		  load_32x2_vr_a(VR_outMultPerCh, UR_outMultPerCh, pOutMultiplerFr32);
		  convert_32F_to_16I_x2(VR_out, (unsigned int)1 - 8, 1);
		  rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
		  // accExt
		  VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
		  store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
		  store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
	  }
	  VR_out = vadds(VR_y, VR_b0, 0x0);
	  VR_out = vmuls(VR_out, VR_outMultPerCh, 0);
	  VR_out = vadds(VR_out, VR_outOffset, 0);

	  convert_32F_to_16I_x2(VR_out, (unsigned int)1 - 8, 1);
	  rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
	  // accExt
	  VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
	  store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
	  store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
  }

  if (output_depth & 1) {
    load32x1_vr_postI(VR_y, pDst, INC1, VRQ0);
	load32x1_vr_postI(VR_b0, pB, INC1, VRQ0);
	load32x1_vr_postI(VR_outMultPerCh,  pOutMultiplerFr32, INC1, VRQ0);
    convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);

    VR_out = vadds(VR_y, VR_b0, 0x0);
    VR_out = vmuls(VR_out, VR_outMultPerCh, 0);
    VR_out = vadds(VR_out, VR_outOffset, 0);
    // VR_out = vexp_adji(VR_out, 8);
    convert_32F_to_16I_x2(VR_out, (unsigned int)1 - 8, 1);
    rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);

    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
    store8x1_vr_postI(VR_out, pY, INC1, VRQ0);

  }
  return 0;
}
int ConvQuantizedInt8PerChInputOffset(
    int32_t *x, const int32_t *A, const AScalar *bias, int8_t *output, int m,
    int n, const AScalar &outOffsetFr32, int32_t *inputOffsetWithW,
    const AScalar *pOutMultiplerFr32,  // array output channel
    int32_t *pScratch, int signs) {

  int32_t *pDst = pScratch;
  const int32_t *pA = A;
  const int32_t *pX;


  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment


  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  atbool signSpec = atbool(signs);

  int32_t *inputOffsetW = inputOffsetWithW;
#ifdef KN_DEBUG
  // align_output
  // CHECK_ALIGN_4(pY);
  // CHECK_ALIGN_4(pA);
  // CHECK_ALIGN_4(x);
  // CHECK_ALIGN_4(pB);
  // KN_PRINT_AFLOAT(pOutMultiplerFr32, m);
#endif
    // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
// prevent using load_32x4_vr_a unalign,
// nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration 
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0)
  {
      loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0)
  {
      return -1;
  }
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
    // const int32_t *pA1 = pA;
    ulsr32 UR_A = align_32x2_load(pA);
    ulsr32 UR_x = align_32x2_load(pX);
    load_32x2_vr_a(VR_A, UR_A, pA);

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
      WUR_MvmAux(1);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x2_vr_a(VR_A, UR_A, pA);
    }
    store32x2_vr_postI(VR_y, pDst, INC1);
    store_AccExtend_postI(pDst, INC1);

    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 8/4 = 2;
  }

  ConvApplyOffsetPerCh(output, pScratch, bias, m, outOffsetFr32,
                       pOutMultiplerFr32, signs);
  return 0;
}

#endif

#if defined(HEMILITE_CONV_OPT)

void ConvFloat(const OpData &data_ex, const float *input_data,
               const float *filter_data, const float *bias_data,
               float *output_data, const AScalar &act_min,
               const AScalar &act_max)

{
  ds_conv2d_layer_t conv2d = data_ex.conv2d;
  // AScalar act_min = AScalar(convParam.float_activation_max);
  //  AScalar act_max = AScalar (convParam.float_activation_max);
  //  const AScalar *per_channel_output_multiplier =
  //    (const AScalar *)(data_ex.ConvOp.per_channel_output_multiplier);
  int inFCM = conv2d.out_ch;
  int inFCN = conv2d.ker_x * conv2d.ker_y * conv2d.in_ch;

  // int inFCNA4 = (((inFCN + 3) >> 2) << 2);
  // int inFCN16Size = ((inFCNA4) + 15) / 16;

  float *pBuffer = (float *)conv2d.pIm2Col;

  float *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = conv2d.ker_x;
  int32_t dim_im_in_x = conv2d.in_x;
  int32_t ch_im_in = conv2d.in_ch;
  uint16_t dilation_y = conv2d.dilation_y;
  uint16_t dilation_x = conv2d.dilation_x;
  // KN_PRINTD(inFCM);
  // KN_PRINTD(inFCN);
  //         KN_PRINTF(convParam.float_activation_max);
  //      KN_PRINTF(convParam.float_activation_min);

  // KN_PRINTAFLT(act_min);
  // KN_PRINTAFLT(act_max);
  //  uint32_t input_offset = (conv2d.input_offset == 128) ? 0x80808080 : 0;  //
  for (int i_out_y = 0; i_out_y < conv2d.out_y; ++i_out_y) {
    for (int i_out_x = 0; i_out_x < conv2d.out_x; ++i_out_x) {
      // HACK padding with input negative offset, and inputhe mac8bx8b will
      // compensate to zero
      int offset_im_src, offset_im_dst;
      int len_cpy_x, len_cpy_y;
      im2col_idx im2col_tab_2;
      int padding =
          tflite::ConvIm2ColIndex(conv2d, i_out_x, i_out_y, &im2col_tab_2);
      len_cpy_y = im2col_tab_2.cpy_len_y;
      len_cpy_x = im2col_tab_2.cpy_len_x;
      offset_im_dst = im2col_tab_2.im_dst_offset;
      offset_im_src = im2col_tab_2.im_src_offset;

      // KN_PRINTD(len_cpy_y);
      // KN_PRINTD(len_cpy_x);
      // KN_PRINTD(offset_im_dst);
      // KN_PRINTD(offset_im_src);
      // KN_PRINT_FLOAT(filter_data, inFCM * inFCN);
      // KN_PRINT_FLOAT(bias_data, inFCM);
      if (!padding) {
        tflite::block_fill_words((int32_t *)pBuffer, 0, inFCN);
      }

      tflite::im2col_padding_align4<float>(
          pBuffer + offset_im_dst, (const float *)input_data + offset_im_src,
          dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in, dilation_y, dilation_x);

      // TODO:unrollx4
#if 1
      // KN_PRINT_FLOAT(pBuffer, inFCN);
      {
        ConvFloatKernel(&outBuf[outBufIdx * inFCM], (float *)pBuffer,
                        (const float *)filter_data, (const float *)bias_data,
                        inFCM, inFCN, act_min, act_max);
        // KN_PRINT_FLOAT(&outBuf[outBufIdx * inFCM], inFCM);
        outBufIdx += 1;
      }
#endif
      // i_out_x_prev = i_out_x;
    }
    // i_out_y_prev = i_out_y;
  }
}

void ConvPerChannelPaddingInputOffset(const OpData &data_ex,
                                      const int8_t *input_data,
                                      const int8_t *filter_data,
                                      const int32_t *bias_data,
                                      int8_t *output_data,
                                      int32_t *inputOffsetWithW,  //_int8,
                                      uint32_t inputOffset_int8_neg, int sign)

{
  ds_conv2d_layer_t conv2d = data_ex.conv2d;
  const AScalar *per_channel_output_multiplier =
      (const AScalar *)(data_ex.ConvOp.per_channel_output_multiplier);

  // AScalar outputMultiplerPerCh = data.outputMultiplerPerCh;
  // AScalar outputOffset = data.outputOffset;
  int inFCM = conv2d.out_ch;
  int inFCN = conv2d.ker_x * conv2d.ker_y * conv2d.in_ch;

  int inFCNA4 = (((inFCN + 3) >> 2) << 2);
  int inFCN16Size = ((inFCNA4) + 15) / 16;

  int8_t *pBuffer = (int8_t *)conv2d.pIm2Col;
  int32_t *pOutput = (int32_t *)conv2d.pOutput;
  int8_t *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = conv2d.ker_x;
  int32_t dim_im_in_x = conv2d.in_x;
  int32_t ch_im_in = conv2d.in_ch;
  uint16_t dilation_y = conv2d.dilation_y;
  uint16_t dilation_x = conv2d.dilation_x;
  int status = 0;
  for (int i_out_y = 0; i_out_y < conv2d.out_y; ++i_out_y) {
    for (int i_out_x = 0; i_out_x < conv2d.out_x; ++i_out_x) {
      // HACK padding with input negative offset, and inputhe mac8bx8b will
      // compensate to zero
      int offset_im_src, offset_im_dst;
      int len_cpy_x, len_cpy_y;
      im2col_idx im2col_tab_2;
      int padding =
          tflite::ConvIm2ColIndex(conv2d, i_out_x, i_out_y, &im2col_tab_2);
      len_cpy_y = im2col_tab_2.cpy_len_y;
      len_cpy_x = im2col_tab_2.cpy_len_x;
      offset_im_dst = im2col_tab_2.im_dst_offset;
      offset_im_src = im2col_tab_2.im_src_offset;
      if (!padding) {
        tflite::block_fill_words((int32_t *)pBuffer, inputOffset_int8_neg,
                                 inFCN16Size * 4);
      }

      if (data_ex.opt_constraint == CONV_OPT_TYPE1) {
        tflite::im2col_padding(
            pBuffer + offset_im_dst, (const int8_t *)input_data + offset_im_src,
            dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in, dilation_y, dilation_x);
      } else if (data_ex.opt_constraint == CONV_OPT_TYPE2) {
        tflite::im2col_padding_align4<int8_t>(
            pBuffer + offset_im_dst, (const int8_t *)input_data + offset_im_src,
            dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in, dilation_y, dilation_x);
      }
      // TODO:unrollx4
      // KN_PRINT_Q7_SIZE(pBuffer, inFCN);
      /*

      */
      {
        status = ConvQuantizedInt8PerChInputOffset(
            (int32_t *)pBuffer, (const int32_t *)filter_data,
            (const AScalar *)bias_data, (int8_t *)&outBuf[outBufIdx * inFCM],
            inFCM, inFCN, data_ex.outputOffset, inputOffsetWithW,
            (const AScalar *)per_channel_output_multiplier, pOutput, sign);
        TFLITE_DCHECK(status == 0);
        outBufIdx += 1;
      }
      // i_out_x_prev = i_out_x;
    }
    // i_out_y_prev = i_out_y;
  }
}
void ConvPerChannelPadding(
    const OpData &data_ex, const int8_t *input_data, const int8_t *filter_data,
    const int32_t *bias_data,
    int8_t *output_data,  // uint32_t inputOffset_int8,uint32_t
                          // inputOffset_int8_neg,
    int sign)

{
  ds_conv2d_layer_t conv2d = data_ex.conv2d;
  const AScalar *per_channel_output_multiplier =
      (const AScalar *)(data_ex.ConvOp.per_channel_output_multiplier);
  int inFCM = conv2d.out_ch;
  int inFCN = conv2d.ker_x * conv2d.ker_y * conv2d.in_ch;

  int inFCNA4 = (((inFCN + 3) >> 2) << 2);
  int inFCN16Size = ((inFCNA4) + 15) / 16;

  int8_t *pBuffer = (int8_t *)conv2d.pIm2Col;
  int32_t *pOutput = (int32_t *)conv2d.pOutput;
  int8_t *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = conv2d.ker_x;
  int32_t dim_im_in_x = conv2d.in_x;
  int32_t ch_im_in = conv2d.in_ch;
  uint32_t input_offset = (conv2d.input_offset == 128) ? 0x80808080 : 0;  //
  for (int i_out_y = 0; i_out_y < conv2d.out_y; ++i_out_y) {
    for (int i_out_x = 0; i_out_x < conv2d.out_x; ++i_out_x) {
      // HACK padding with input negative offset, and inputhe mac8bx8b will
      // compensate to zero
      int offset_im_src, offset_im_dst;
      int len_cpy_x, len_cpy_y;
      int dilation_y, dilation_x;
      dilation_y = conv2d.dilation_y;
      dilation_x = conv2d.dilation_x;
      im2col_idx im2col_tab_2;
      int padding =
          tflite::ConvIm2ColIndex(conv2d, i_out_x, i_out_y, &im2col_tab_2);
      len_cpy_y = im2col_tab_2.cpy_len_y;
      len_cpy_x = im2col_tab_2.cpy_len_x;
      offset_im_dst = im2col_tab_2.im_dst_offset;
      offset_im_src = im2col_tab_2.im_src_offset;
      if (!padding) {
        tflite::block_fill_words((int32_t *)pBuffer, 0, inFCN16Size * 4);
      }

      if (data_ex.opt_constraint == CONV_OPT_TYPE1) {
        tflite::im2col_padding_offset(
            pBuffer + offset_im_dst, (const int8_t *)input_data + offset_im_src,
            dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in,
            input_offset, dilation_y, dilation_x);
      } else if (data_ex.opt_constraint == CONV_OPT_TYPE2) {
        tflite::im2col_padding_offset_align4(
            pBuffer + offset_im_dst, (const int8_t *)input_data + offset_im_src,
            dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in,
            input_offset, dilation_y, dilation_x);
      }
      // TODO:unrollx4

      {
        ConvQuantizedInt8PerChInputOffset(
            (int32_t *)pBuffer, (const int32_t *)filter_data,
            (const AScalar *)bias_data, (int8_t *)&outBuf[outBufIdx * inFCM],
            inFCM, inFCN, data_ex.outputOffset, NULL,
            (const AScalar *)per_channel_output_multiplier, pOutput, sign);

        outBufIdx += 1;
      }
      // i_out_x_prev = i_out_x;
    }
    // i_out_y_prev = i_out_y;
  }
}
#endif



TfLiteStatus EvalConvFloat(TfLiteContext *context, TfLiteNode *node,
                           const TfLiteConvParams &params,
                           const OpData &data_ex,

                           const TfLiteEvalTensor *input,
                           const TfLiteEvalTensor *filter,
                           const TfLiteEvalTensor *bias,
                           TfLiteEvalTensor *output, TfLiteEvalTensor *im2col) {

    KN_PRINTD(data_ex.opt_constraint_float);
#if defined(HEMILITE_CONV_OPT)
  if (data_ex.opt_constraint_float) {
    AScalar afloat_activation_min, afloat_activation_max;
    CalculateActivationRangeAflt(params.activation, &afloat_activation_min,
                                 &afloat_activation_max);

    //     int32_t input_offset = -data.input_zero_point;
    const int batches = MatchingDim(tflite::micro::GetTensorShape(input), 0,
                                    tflite::micro::GetTensorShape(output), 0);
    int8_t *p_aligned_scratch = nullptr;

    if (data_ex.buffer_idx > -1) {
      p_aligned_scratch =
          (int8_t *)context->GetScratchBuffer(context, data_ex.buffer_idx);
    }
    ds_conv2d_layer_t *conv2d = (ds_conv2d_layer_t *)&data_ex.conv2d;
    conv2d->pIm2Col = (int32_t *)p_aligned_scratch;
    conv2d->pOutput = nullptr;
    //	(int32_t *)((int8_t *)p_aligned_scratch + data_ex.sizeScratchIm2Col);
    // int sign_in_offset = (input_offset == 128) ? 1 : 3;

    // KN_PRINTD(batches);
    int batch = batches;
    const float *pInputLocal =
        (const float *)tflite::micro::GetTensorData<float>(input);
    float *pOutputLocal = tflite::micro::GetTensorData<float>(output);
    const float *pFilter = tflite::micro::GetTensorData<float>(filter);

    // ConvParams convParam =    ConvParamsAFloat(params, data);

    int input_conv_depth = conv2d->in_ch * conv2d->in_x * conv2d->in_y;
    int output_conv_depth = conv2d->out_ch * conv2d->out_x * conv2d->out_y;

    //  KN_PRINTD(input_conv_depth);
    // KN_PRINTD(output_conv_depth);

    while (batch) {
      ConvFloat(data_ex, (const float *)pInputLocal,
                //  (const float *)data_ex.mapped_filter,
                pFilter, tflite::micro::GetTensorData<float>(bias),
                pOutputLocal, afloat_activation_min, afloat_activation_max);

      // KN_PRINTD(batch);

      pInputLocal += input_conv_depth;
      pOutputLocal += output_conv_depth;
      batch--;
    }
  }

  else
#endif

  {
  #ifndef REMOVE_REFOP_SUPPORT
    const OpDataConv &data = data_ex.ConvOp;
    ConvParams convParam = ConvParamsFloat(params, data);
    tflite::reference_ops::Conv(convParam, tflite::micro::GetTensorShape(input),
                                tflite::micro::GetTensorData<float>(input),
                                tflite::micro::GetTensorShape(filter),
                                tflite::micro::GetTensorData<float>(filter),
                                tflite::micro::GetTensorShape(bias),
                                tflite::micro::GetTensorData<float>(bias),
                                tflite::micro::GetTensorShape(output),
                                tflite::micro::GetTensorData<float>(output),
                                tflite::micro::GetTensorShape(nullptr),
                                nullptr);
    #else
    return kTfLiteError;
    #endif
  }
  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                 ElementCount(*output->dims));

  return kTfLiteOk;
}
TfLiteStatus EvalConvQuantizedPerChannel(
    TfLiteContext *context, TfLiteNode *node, const TfLiteConvParams &params,
    const OpData &data_ex,

    const TfLiteEvalTensor *input, const TfLiteEvalTensor *filter,
    const TfLiteEvalTensor *bias, TfLiteEvalTensor *output,
    TfLiteEvalTensor *im2col) {
  const OpDataConv &data = data_ex.ConvOp;
  ConvParams op_params;
  op_params.input_offset = -data.input_zero_point;
  op_params.output_offset = data.output_zero_point;
  op_params.stride_height = params.stride_height;
  op_params.stride_width = params.stride_width;
  op_params.dilation_height_factor = params.dilation_height_factor;
  op_params.dilation_width_factor = params.dilation_width_factor;
  op_params.padding_values.height = data.padding.height;
  op_params.padding_values.width = data.padding.width;
  op_params.quantized_activation_min = data.output_activation_min;
  op_params.quantized_activation_max = data.output_activation_max;
  KN_PRINTD(data_ex.opt_constraint);
#if defined(HEMILITE_CONV_OPT)
  if (data_ex.opt_constraint) {
    int32_t input_offset = -data.input_zero_point;
    const int batches = MatchingDim(tflite::micro::GetTensorShape(input), 0,
                                    tflite::micro::GetTensorShape(output), 0);
    int8_t *p_aligned_scratch = nullptr;

    if (data_ex.buffer_idx > -1) {
      p_aligned_scratch =
          (int8_t *)context->GetScratchBuffer(context, data_ex.buffer_idx);
    }
    ds_conv2d_layer_t *conv2d = (ds_conv2d_layer_t *)&data_ex.conv2d;
    conv2d->pIm2Col = (int32_t *)p_aligned_scratch;
    conv2d->pOutput =
        (int32_t *)((int8_t *)p_aligned_scratch + data_ex.sizeScratchIm2Col);

    int sign_in_offset = (input_offset == 128) ? 1 : 3;

    int batch = batches;
    const int8_t *pInputLocal =
        (const int8_t *)tflite::micro::GetTensorData<int8_t>(input);
    int8_t *pOutputLocal = tflite::micro::GetTensorData<int8_t>(output);
    int input_conv_depth = conv2d->in_ch * conv2d->in_x * conv2d->in_y;
    int output_conv_depth = conv2d->out_ch * conv2d->out_x * conv2d->out_y;

    while (batch) {

        
      if (nullptr == data_ex.inputOffsetWithW) {
        // tflite::AddConstQuantizedInt8Fast128(  (  int32_t *)pInputLocal,
        // (uint32_t *)pInputLocal, input_conv_depth);
        // KN_PRINT_Q7_SIZE(p_aligned_input,input_conv_depth );
        ConvPerChannelPadding(data_ex, (const int8_t *)pInputLocal,
                              (const int8_t *)data_ex.mapped_filter,
                              tflite::micro::GetTensorData<int32_t>(bias),
                              pOutputLocal, sign_in_offset);
      } else 
      
      {
        // memcpy(p_aligned_input, pInputLocal,
        // input_conv_depth*sizeof(int8_t));

        ConvPerChannelPaddingInputOffset(
            data_ex, (const int8_t *)pInputLocal,
            (const int8_t *)data_ex.mapped_filter,
            tflite::micro::GetTensorData<int32_t>(bias), pOutputLocal,
            data_ex.inputOffsetWithW, data_ex.input_offset_int8_neg,
            sign_in_offset);
      }

      pInputLocal += input_conv_depth;
      pOutputLocal += output_conv_depth;
      batch--;
    }

  } else
#endif
  {
    // TODO(b/154032858): Investigate removing extra copies.

#ifndef REMOVE_REFOP_SUPPORT
    reference_integer_ops::ConvPerChannel(
        op_params, data.per_channel_output_multiplier,
        data.per_channel_output_shift, tflite::micro::GetTensorShape(input),
        tflite::micro::GetTensorData<int8_t>(input),
        tflite::micro::GetTensorShape(filter),
        tflite::micro::GetTensorData<int8_t>(filter),
        tflite::micro::GetTensorShape(bias),
        tflite::micro::GetTensorData<int32_t>(bias),
        tflite::micro::GetTensorShape(output),
        tflite::micro::GetTensorData<int8_t>(output));
#else
    return kTfLiteError;
#endif
  }
  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                   ElementCount(*output->dims));
  return kTfLiteOk;
}


#if defined(HEMILITE_CONV_OPT)
int ConvFloatInt8Kernel(float* y, const float* x, const int8_t* A, const float* bias,
    int m, int n, const AScalar& act_min,
    const AScalar& act_max, const AScalar& scale, AScalar* scale_ptr = nullptr) {
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
    const int wBlkExp = 7;
    vr64 VR_w0;
    vr64 VR_act_max, VR_act_min;
    vr64 VR_scale;
    // vr128 VR_maxExp = vseta_vr(0, 0, 0);
    // mir30 mirIdx;
    // vr128 VR_exp;
    //ulsr32 UR_w0, UR_w1;  //, UR_w2, UR_w3;
    ulsr32 UR_blk;
    ulsr32 UR_actOut, UR_bias;
    AScalar* pScalePerCh = scale_ptr;

    replicate_ar(VR_act_max, 0x3, act_max.fr);
    replicate_ar(VR_act_min, 0x3, act_min.fr);
    replicate_ar(VR_scale, 0x3, scale.fr);
    pActOut = y;

    pBiasLocal = bias;
    UR_actOut = align_32x2_store(pActOut);

    UR_bias = align_32x2_load(pBiasLocal);

    if (loopGroupLim > 0) {
        for (jj = 0; jj < loopGroupLim; jj++)  // group
        {
            vr64 VR_blk = vseta_vr(0, 0);
            vr64 VR_out0 = VR_blk;
            vr64 VR_out1 = VR_blk;
            vr64 VR_bias;
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
                for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
                {

                    convert_16I_to_32F_x2(VR_w0, wBlkExp);

                    convert_IEEE_float_to_32F_x2(VR_blk);
                    VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
                    load8x2_vr_postI_unalign(VR_w0, pWa1, INC1); 
                    convert_16I_to_32F_x2(VR_w0, wBlkExp);
           
                    VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);
                    load8x2_vr_postI_unalign(VR_w0, pWa0, INC1);  
                    load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
                    
                }
                convert_16I_to_32F_x2(VR_w0, wBlkExp);
                convert_IEEE_float_to_32F_x2(VR_blk);
                VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);

                load8x2_vr_postI_unalign(VR_w0, pWa1, INC1); 
                convert_16I_to_32F_x2(VR_w0, wBlkExp);
 
                //convert_IEEE_float_to_32F_x2(VR_w0);
                VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);
            }
            fr32 fr_out0, fr_out1;

            if (n & 1) {
                load8x1_vr_postI(VR_w0, pWa0, INC1, VRQ0); convert_16I_to_32F_x2(VR_w0, wBlkExp);

                load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
                // convert_IEEE_float_to_32F_x2(VR_w0);
                convert_IEEE_float_to_32F_x2(VR_blk);
                // for (ii = loopBlockLim2 << 2; ii < n; ii++)
                //   if(n&1){
                //          fmacs(VR_out0, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);
                fr_out0 = fmacs(get_VRL(VR_out0), get_VRL(VR_w0), get_VRL(VR_blk), 0);
                load8x1_vr_postI(VR_w0, pWa1, INC1, VRQ0); convert_16I_to_32F_x2(VR_w0, wBlkExp);
   
                 //          fmacs(VR_out1, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);
                fr_out1 = fmacs(get_VRL(VR_out1), get_VRL(VR_w0), get_VRL(VR_blk), 0);

                set_VRL(VR_out0, fr_out0);
                set_VRL(VR_out1, fr_out1);
            }

            fr_out0 = fadds(get_VRL(VR_out0), get_VRH(VR_out0), 0);
            fr_out1 = fadds(get_VRL(VR_out1), get_VRH(VR_out1), 0);

            set_VRL(VR_actOut, fr_out0);
            set_VRH(VR_actOut, fr_out1);
            if (scale_ptr)
            {
                load32x2_vr_postI(VR_scale, pScalePerCh, INC1);
            }
            VR_actOut = vmuls(VR_actOut, VR_scale, 0);


            load_32x2_vr_a(VR_bias, UR_bias, pBiasLocal);

            VR_actOut = vadds(VR_actOut, VR_bias, 0);

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
        vr64 VR_out0, VR_bias;

        pWa0 = (int8_t*)pW;  // 1st group

        VR_out0 = vexp_adji(VR_actOut, 0x0);

        float* pIn0 = (float*)x;
        if (loopBlockLim2 > 0) {
            // UR_w0 = align_32x2_load(pWa0);

             //UR_blk = align_32x2_load(pIn0);
            load_32x2_vr_a(VR_blk, UR_blk, pIn0);
            load8x2_vr_postI_unalign(VR_w0, pWa0, INC1); convert_16I_to_32F_x2(VR_w0, wBlkExp);

            convert_IEEE_float_to_32F_x2(VR_blk);
            // convert_IEEE_float_to_32F_x2(VR_w0);

            for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
            {
                VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
                load8x2_vr_postI_unalign(VR_w0, pWa0, INC1);  convert_16I_to_32F_x2(VR_w0, wBlkExp);

                load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
                convert_IEEE_float_to_32F_x2(VR_blk);
                //  convert_IEEE_float_to_32F_x2(VR_w0);
            }

            VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
        }
        fr32 fr_out0;
        if (n & 1) {
            load8x1_vr_postI(VR_w0, pWa0, INC1, VRQ0); convert_16I_to_32F_x2(VR_w0, wBlkExp);

            load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);

            convert_IEEE_float_to_32F_x2(VR_blk);
            //  convert_IEEE_float_to_32F_x2(VR_w0);

            fr_out0 = fmacs(get_VRL(VR_out0), get_VRL(VR_w0), get_VRL(VR_blk), 0);
            set_VRL(VR_out0, fr_out0);
        }
        // dsums_L(VR_out0, VR_out0, 0, 0);
        // fadds(VR_actOut, VRQ0, VR_out0, VRQ1, VR_out0, VRQ0, 0);
        fr_out0 = fadds(get_VRL(VR_out0), get_VRH(VR_out0), 0);

        set_VRL(VR_actOut, fr_out0);
        if (scale_ptr)
            load32x1_vr_postI(VR_scale, pScalePerCh, INC1, VRQ0);

        VR_actOut = vmuls(VR_actOut, VR_scale, 0);
        // VR_exp = afloat_exp_extract(VR_actOut);
        // fmax(VR_maxExp, VRQ0, VR_maxExp, VRQ0, VR_exp, VRQ0);
        // if (pBiasLocal) {
        //    fr32 fr_bias;
        load32x1_vr_postI(VR_bias, pBiasLocal, INC1, VRQ0);
        //} else {
        // VR_bias = vseta_vr(kConstTable_Zero, 0, 0);
        //}
       // convert_IEEE_float_to_32F_x2(VR_bias);
        VR_actOut = vadds(VR_actOut, VR_bias, 0);
        VR_actOut = vmax(VR_actOut, VR_act_min);
        VR_actOut = vmin(VR_actOut, VR_act_max);

        convert_32F_to_IEEE_float_x2(VR_actOut);
        store32x1_vr_postI(VR_actOut, pActOut, INC1, VRQ0);

        // pW += n;  // add to next group
    }
    return 0;  //(maxExp-31);
}


//Kernel Float16
int ConvFloatKernel16(float* y, const float* x, const TfLiteFloat16* A, const float* bias,
    int m, int n, const AScalar& act_min,
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

    // vr128 VR_maxExp = vseta_vr(0, 0, 0);
    // mir30 mirIdx;
    // vr128 VR_exp;
    //ulsr32 UR_w0, UR_w1;  //, UR_w2, UR_w3;
    ulsr32 UR_blk;
    ulsr32 UR_actOut, UR_bias;
    // unsigned Maxidx;

    replicate_ar(VR_act_max, 0x3, act_max.fr);
    replicate_ar(VR_act_min, 0x3, act_min.fr);
    pActOut = y;

    pBiasLocal = bias;
    UR_actOut = align_32x2_store(pActOut);

    UR_bias = align_32x2_load(pBiasLocal);

    if (loopGroupLim > 0) {
        for (jj = 0; jj < loopGroupLim; jj++)  // group
        {
            vr64 VR_blk = vseta_vr(0, 0);
            vr64 VR_out0 = VR_blk;
            vr64 VR_out1 = VR_blk;
            vr64 VR_bias;
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
                load16x2_vr_postI_unalign(VR_w0, pWa0, INC1); convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                // convert IEEE to afloat
                convert_IEEE_float_to_32F_x2(VR_blk);
                //convert_IEEE_float_to_32F_x2(VR_w0);
                for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
                {
                    // KN_PRINT_VR128(VR_blk);  KN_PRINT_VR128(VR_w0);
                    VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
                    //    KN_PRINT_VR128(VR_out0);
                    load16x2_vr_postI_unalign(VR_w0,  pWa1, INC1);convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                    //convert_IEEE_float_to_32F_x2(VR_w0);
                    VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);

                    load16x2_vr_postI_unalign(VR_w0, pWa0, INC1); convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                    load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
                    //convert_IEEE_float_to_32F_x2(VR_w0);
                    convert_IEEE_float_to_32F_x2(VR_blk);
                }

                VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);

                load16x2_vr_postI_unalign(VR_w0, pWa1, INC1);convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                //convert_IEEE_float_to_32F_x2(VR_w0);
                VR_out1 = vmacs(VR_out1, VR_w0, VR_blk, 0, 0);
            }
            fr32 fr_out0, fr_out1;

            if (n & 1) {
                load16x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
                // convert_IEEE_float_to_32F_x2(VR_w0);
                convert_IEEE_float_to_32F_x2(VR_blk);
                // for (ii = loopBlockLim2 << 2; ii < n; ii++)
                //   if(n&1){
                //          fmacs(VR_out0, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);
                fr_out0 = fmacs(get_VRL(VR_out0), get_VRL(VR_w0), get_VRL(VR_blk), 0);
                load16x1_vr_postI(VR_w0, pWa1, INC1, VRQ0);convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
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

            load_32x2_vr_a(VR_bias, UR_bias, pBiasLocal);

            // convert_IEEE_float_to_32F_x2(VR_bias);
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
        vr64 VR_out0, VR_bias;

        pWa0 = (TfLiteFloat16*)pW;  // 1st group

        VR_out0 = vexp_adji(VR_actOut, 0x0);

        float* pIn0 = (float*)x;
        if (loopBlockLim2 > 0) {
           // UR_w0 = align_32x2_load(pWa0);

            //UR_blk = align_32x2_load(pIn0);
            load_32x2_vr_a(VR_blk, UR_blk, pIn0);
            load16x2_vr_postI_unalign(VR_w0, pWa0, INC1);convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
            convert_IEEE_float_to_32F_x2(VR_blk);
            // convert_IEEE_float_to_32F_x2(VR_w0);

            for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
            {
                VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
                load16x2_vr_postI_unalign(VR_w0, pWa0, INC1); convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
                load_32x2_vr_a(VR_blk, UR_blk, pIn0);  // next for block
                convert_IEEE_float_to_32F_x2(VR_blk);
                //  convert_IEEE_float_to_32F_x2(VR_w0);
            }

            VR_out0 = vmacs(VR_out0, VR_w0, VR_blk, 0, 0);
        }
        fr32 fr_out0;
        if (n & 1) {
            load16x1_vr_postI(VR_w0, pWa0, INC1, VRQ0); convert_16F_to_32F_x2(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);

            load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);

            convert_IEEE_float_to_32F_x2(VR_blk);
            //  convert_IEEE_float_to_32F_x2(VR_w0);

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
        load32x1_vr_postI(VR_bias, pBiasLocal, INC1, VRQ0);
        //} else {
        // VR_bias = vseta_vr(kConstTable_Zero, 0, 0);
        //}
       // convert_IEEE_float_to_32F_x2(VR_bias);
        VR_actOut = vadds(VR_actOut, VR_bias, 0);
        VR_actOut = vmax(VR_actOut, VR_act_min);
        VR_actOut = vmin(VR_actOut, VR_act_max);

        convert_32F_to_IEEE_float_x2(VR_actOut);
        store32x1_vr_postI(VR_actOut, pActOut, INC1, VRQ0);

        // pW += n;  // add to next group
    }
    return 0;  //(maxExp-31);
}



#endif


#if defined(HEMILITE_CONV_OPT)

void ConvFloatInt8(const OpData& data_ex, const float* input_data,
    const int8_t* filter_data, const float* bias_data,
    float* output_data, const AScalar& act_min,
    const AScalar& act_max)

{
    ds_conv2d_layer_t conv2d = data_ex.conv2d;
    // AScalar act_min = AScalar(convParam.float_activation_max);
    //  AScalar act_max = AScalar (convParam.float_activation_max);
    //  const AScalar *per_channel_output_multiplier =
    //    (const AScalar *)(data_ex.ConvOp.per_channel_output_multiplier);
    int inFCM = conv2d.out_ch;
    int inFCN = conv2d.ker_x * conv2d.ker_y * conv2d.in_ch;

    // int inFCNA4 = (((inFCN + 3) >> 2) << 2);
    // int inFCN16Size = ((inFCNA4) + 15) / 16;

    float* pBuffer = (float*)conv2d.pIm2Col;

    float* outBuf = output_data;
    int status = 0;
    int32_t outBufIdx = 0;
    int32_t dim_kernel_x = conv2d.ker_x;
    int32_t dim_im_in_x = conv2d.in_x;
    int32_t ch_im_in = conv2d.in_ch;
    uint16_t dilation_y = conv2d.dilation_y;
    uint16_t dilation_x = conv2d.dilation_x;
    const AScalar scale = data_ex.filter_scale;
    AScalar* scale_per_channel = (AScalar *)data_ex.ConvOp.per_channel_output_multiplier;
    // KN_PRINTD(inFCM);
    // KN_PRINTD(inFCN);
    //         KN_PRINTF(convParam.float_activation_max);
    //      KN_PRINTF(convParam.float_activation_min);

    // KN_PRINTAFLT(act_min);
    // KN_PRINTAFLT(act_max);
    //  uint32_t input_offset = (conv2d.input_offset == 128) ? 0x80808080 : 0;  //
    for (int i_out_y = 0; i_out_y < conv2d.out_y; ++i_out_y) {
        for (int i_out_x = 0; i_out_x < conv2d.out_x; ++i_out_x) {
            // HACK padding with input negative offset, and inputhe mac8bx8b will
            // compensate to zero
            if (data_ex.opt_constraint_float == CONV_OPT_FLT_X_INT8_PW)
            {
                // point wise conv without copy and check align in/out 4  or 2

                //KN_PRINT_Q7_SIZE(pBuffer);
                pBuffer = (float *)input_data;
                //KN_PRINT_FLOAT(pBuffer, inFCN);
                status = tflite::MVMFloatInt8Kernel(&outBuf[outBufIdx * inFCM], (float*)pBuffer,
                    (const int32_t*)filter_data, (const float*)bias_data,
                    inFCM, inFCN , conv2d.pIm2Col, act_min, act_max, scale, scale_per_channel);
                TFLITE_DCHECK(status == 0);
                outBufIdx += 1;
            }
            else {
                int offset_im_src, offset_im_dst;
                int len_cpy_x, len_cpy_y;
                im2col_idx im2col_tab_2;
                int padding =
                    tflite::ConvIm2ColIndex(conv2d, i_out_x, i_out_y, &im2col_tab_2);
                len_cpy_y = im2col_tab_2.cpy_len_y;
                len_cpy_x = im2col_tab_2.cpy_len_x;
                offset_im_dst = im2col_tab_2.im_dst_offset;
                offset_im_src = im2col_tab_2.im_src_offset;

                if (!padding) {
                    tflite::block_fill_words((int32_t*)pBuffer, 0, inFCN);
                }

                tflite::im2col_padding_align4<float>(
                    pBuffer + offset_im_dst, (const float*)input_data + offset_im_src,
                    dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in, dilation_y, dilation_x);

                // TODO:unrollx4
#if 1
                  //KN_PRINT_FLOAT(pBuffer, inFCN);
                {
                    ConvFloatInt8Kernel(&outBuf[outBufIdx * inFCM], (float*)pBuffer,
                        (const int8_t*)filter_data, (const float*)bias_data,
                        inFCM, inFCN, act_min, act_max, scale, scale_per_channel);
                    // KN_PRINT_FLOAT(&outBuf[outBufIdx * inFCM], inFCM);
                    outBufIdx += 1;
                }
#endif
            }
            // i_out_x_prev = i_out_x;
        }
        // i_out_y_prev = i_out_y;
    }
}

void ConvFloat16(const OpData& data_ex, const float* input_data,
    const TfLiteFloat16* filter_data, const float* bias_data,
    float* output_data, const AScalar& act_min,
    const AScalar& act_max)

{
    ds_conv2d_layer_t conv2d = data_ex.conv2d;
    // AScalar act_min = AScalar(convParam.float_activation_max);
    //  AScalar act_max = AScalar (convParam.float_activation_max);
    //  const AScalar *per_channel_output_multiplier =
    //    (const AScalar *)(data_ex.ConvOp.per_channel_output_multiplier);
    int inFCM = conv2d.out_ch;
    int inFCN = conv2d.ker_x * conv2d.ker_y * conv2d.in_ch;

    // int inFCNA4 = (((inFCN + 3) >> 2) << 2);
    // int inFCN16Size = ((inFCNA4) + 15) / 16;

    float* pBuffer = (float*)conv2d.pIm2Col;

    float* outBuf = output_data;
    int32_t outBufIdx = 0;
    int32_t dim_kernel_x = conv2d.ker_x;
    int32_t dim_im_in_x = conv2d.in_x;
    int32_t ch_im_in = conv2d.in_ch;
    uint16_t dilation_y = conv2d.dilation_y;
    uint16_t dilation_x = conv2d.dilation_x;
    // KN_PRINTD(inFCM);
    // KN_PRINTD(inFCN);
    //         KN_PRINTF(convParam.float_activation_max);
    //      KN_PRINTF(convParam.float_activation_min);

    // KN_PRINTAFLT(act_min);
    // KN_PRINTAFLT(act_max);
    //  uint32_t input_offset = (conv2d.input_offset == 128) ? 0x80808080 : 0;  //
    for (int i_out_y = 0; i_out_y < conv2d.out_y; ++i_out_y) {
        for (int i_out_x = 0; i_out_x < conv2d.out_x; ++i_out_x) {
            // HACK padding with input negative offset, and inputhe mac8bx8b will
            // compensate to zero

            int offset_im_src, offset_im_dst;
            int len_cpy_x, len_cpy_y;
            im2col_idx im2col_tab_2;
            int padding =
                tflite::ConvIm2ColIndex(conv2d, i_out_x, i_out_y, &im2col_tab_2);
            len_cpy_y = im2col_tab_2.cpy_len_y;
            len_cpy_x = im2col_tab_2.cpy_len_x;
            offset_im_dst = im2col_tab_2.im_dst_offset;
            offset_im_src = im2col_tab_2.im_src_offset;

            // KN_PRINTD(len_cpy_y);
            // KN_PRINTD(len_cpy_x);
            // KN_PRINTD(offset_im_dst);
            // KN_PRINTD(offset_im_src);
            // KN_PRINT_FLOAT(filter_data, inFCM * inFCN);
            // KN_PRINT_FLOAT(bias_data, inFCM);
            if (!padding) {
                tflite::block_fill_words((int32_t*)pBuffer, 0, inFCN);
            }

            tflite::im2col_padding_align4<float>(
                pBuffer + offset_im_dst, (const float*)input_data + offset_im_src,
                dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in, dilation_y, dilation_x);

            // TODO:unrollx4
#if 1
      // KN_PRINT_FLOAT(pBuffer, inFCN);
            {
                ConvFloatKernel16(&outBuf[outBufIdx * inFCM], (float*)pBuffer,
                    (const TfLiteFloat16*)filter_data, (const float*)bias_data,
                    inFCM, inFCN, act_min, act_max);
                // KN_PRINT_FLOAT(&outBuf[outBufIdx * inFCM], inFCM);
                outBufIdx += 1;
            }
#endif
            // i_out_x_prev = i_out_x;
        }
        // i_out_y_prev = i_out_y;
    }
}

#endif
TfLiteStatus EvalConvFloatInt8(TfLiteContext* context, TfLiteNode* node,
    const TfLiteConvParams& params,
    const OpData& data_ex,
    const TfLiteEvalTensor* input,
    const TfLiteEvalTensor* filter,
    const TfLiteEvalTensor* bias,
    TfLiteEvalTensor* output, TfLiteEvalTensor* im2col) {

    KN_PRINTD(data_ex.opt_constraint_float);
#if defined(HEMILITE_CONV_OPT)
    if (data_ex.opt_constraint_float) {
        AScalar afloat_activation_min, afloat_activation_max;
        CalculateActivationRangeAflt(params.activation, &afloat_activation_min,
            &afloat_activation_max);

        //     int32_t input_offset = -data.input_zero_point;
        const int batches = MatchingDim(tflite::micro::GetTensorShape(input), 0,
            tflite::micro::GetTensorShape(output), 0);
        int8_t* p_aligned_scratch = nullptr;

        if (data_ex.buffer_idx > -1) {
            p_aligned_scratch =
                (int8_t*)context->GetScratchBuffer(context, data_ex.buffer_idx);
        }
        ds_conv2d_layer_t* conv2d = (ds_conv2d_layer_t*)&data_ex.conv2d;
        conv2d->pIm2Col = (int32_t*)p_aligned_scratch;
        conv2d->pOutput = nullptr;
        int batch = batches;
        const float* pInputLocal =
            (const float*)tflite::micro::GetTensorData<float>(input);
        float* pOutputLocal = tflite::micro::GetTensorData<float>(output);
        const int8_t* pFilter = tflite::micro::GetTensorData<int8_t>(filter);

       
        int input_conv_depth = conv2d->in_ch * conv2d->in_x * conv2d->in_y;
        int output_conv_depth = conv2d->out_ch * conv2d->out_x * conv2d->out_y;

        //  KN_PRINTD(input_conv_depth);
        // KN_PRINTD(output_conv_depth);

        while (batch) {
            ConvFloatInt8(data_ex, (const float*)pInputLocal,
                //  (const float *)data_ex.mapped_filter,
                pFilter, tflite::micro::GetTensorData<float>(bias),
                pOutputLocal, afloat_activation_min, afloat_activation_max);

            // KN_PRINTD(batch);

            pInputLocal += input_conv_depth;
            pOutputLocal += output_conv_depth;
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




TfLiteStatus EvalConvFloat16Internal(TfLiteContext* context, TfLiteNode* node,
    const TfLiteConvParams& params,
    const OpData& data_ex,

    const TfLiteEvalTensor* input,
    const TfLiteEvalTensor* filter,
    const TfLiteEvalTensor* bias,
    TfLiteEvalTensor* output, TfLiteEvalTensor* im2col) {

    KN_PRINTD(data_ex.opt_constraint_float);
#if defined(HEMILITE_CONV_OPT)
    if (data_ex.opt_constraint_float) {
        AScalar afloat_activation_min, afloat_activation_max;
        CalculateActivationRangeAflt(params.activation, &afloat_activation_min,
            &afloat_activation_max);

        //     int32_t input_offset = -data.input_zero_point;
        const int batches = MatchingDim(tflite::micro::GetTensorShape(input), 0,
            tflite::micro::GetTensorShape(output), 0);
        int8_t* p_aligned_scratch = nullptr;

        if (data_ex.buffer_idx > -1) {
            p_aligned_scratch =
                (int8_t*)context->GetScratchBuffer(context, data_ex.buffer_idx);
        }
        ds_conv2d_layer_t* conv2d = (ds_conv2d_layer_t*)&data_ex.conv2d;
        conv2d->pIm2Col = (int32_t*)p_aligned_scratch;
        conv2d->pOutput = nullptr;
        //	(int32_t *)((int8_t *)p_aligned_scratch + data_ex.sizeScratchIm2Col);
        // int sign_in_offset = (input_offset == 128) ? 1 : 3;

        // KN_PRINTD(batches);
        int batch = batches;
        const float* pInputLocal =
            (const float*)tflite::micro::GetTensorData<float>(input);
        float* pOutputLocal = tflite::micro::GetTensorData<float>(output);
        const TfLiteFloat16* pFilter = tflite::micro::GetTensorData<TfLiteFloat16>(filter);

        // ConvParams convParam =    ConvParamsAFloat(params, data);

        int input_conv_depth = conv2d->in_ch * conv2d->in_x * conv2d->in_y;
        int output_conv_depth = conv2d->out_ch * conv2d->out_x * conv2d->out_y;

        //  KN_PRINTD(input_conv_depth);
        // KN_PRINTD(output_conv_depth);

        while (batch) {
            ConvFloat16(data_ex, (const float*)pInputLocal,
                //  (const float *)data_ex.mapped_filter,
                pFilter, tflite::micro::GetTensorData<float>(bias),
                pOutputLocal, afloat_activation_min, afloat_activation_max);

            // KN_PRINTD(batch);

            pInputLocal += input_conv_depth;
            pOutputLocal += output_conv_depth;
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



TfLiteStatus EvalConv(TfLiteContext *context, TfLiteNode *node) {
  const auto &params =
      *(reinterpret_cast<TfLiteConvParams *>(node->builtin_data));
    TfLiteStatus status = kTfLiteOk;
  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kConvInputTensor);
  const TfLiteEvalTensor *filter =
      tflite::micro::GetEvalInput(context, node, kConvWeightsTensor);
  const TfLiteEvalTensor *bias =
      (NumInputs(node) == 3)
          ? tflite::micro::GetEvalInput(context, node, kConvBiasTensor)
          : nullptr;
  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kConvOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  // const OpData& data = *(static_cast<const OpData*>(node->user_data));
  const auto &data_ex = *(static_cast<const OpData *>(node->user_data));

  // TFLITE_DCHECK(node->user_data != nullptr);
  TF_LITE_ENSURE_EQ(context, input->type, output->type);
  // enable 16x8
  //TF_LITE_ENSURE_MSG(context, input->type == filter->type,
  //                   "Hybrid models are not supported on TFLite Micro.");

  switch (input->type) {  // Already know in/out types are same.

    case kTfLiteFloat32: 
    {
        switch (filter->type)
        {
        case kTfLiteFloat32:
            status = EvalConvFloat(context, node, params, data_ex, input, filter,
                bias, output, nullptr);
            break;
        case kTfLiteFloat16:
            status = EvalConvFloat16Internal(context, node, params, data_ex, input, filter,
                bias, output, nullptr);
            break;
        case kTfLiteInt8:
            status = EvalConvFloatInt8(context, node, params, data_ex, input, filter,
                bias, output, nullptr);
            break;
        default:
            TF_LITE_KERNEL_LOG(context, "filter Type %s (%d) for input float32 not supported.",
                TfLiteTypeGetName(filter->type), filter->type);
            return kTfLiteError;
        }
    }
    break;

    case kTfLiteInt8:
      status = EvalConvQuantizedPerChannel(
          context, node, params, data_ex, input, filter, bias, output, nullptr);
      break;
#ifndef REMOVE_REFOP_SUPPORT
    case kTfLiteInt16: {
      switch (bias->type) {
        case kTfLiteInt32: {
          const OpDataConv& data = data_ex.ConvOp;
          reference_integer_ops::ConvPerChannel(
              ConvParamsQuantized(params, data),
              data.per_channel_output_multiplier, data.per_channel_output_shift,
              tflite::micro::GetTensorShape(input),
              tflite::micro::GetTensorData<int16_t>(input),
              tflite::micro::GetTensorShape(filter),
              tflite::micro::GetTensorData<int8_t>(filter),
              tflite::micro::GetTensorShape(bias),
              tflite::micro::GetTensorData<std::int32_t>(bias),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<int16_t>(output));
          break;
        }
        case kTfLiteInt64: {
          const OpDataConv& data = data_ex.ConvOp;
          reference_integer_ops::ConvPerChannel(
              ConvParamsQuantized(params, data),
              data.per_channel_output_multiplier, data.per_channel_output_shift,
              tflite::micro::GetTensorShape(input),
              tflite::micro::GetTensorData<int16_t>(input),
              tflite::micro::GetTensorShape(filter),
              tflite::micro::GetTensorData<int8_t>(filter),
              tflite::micro::GetTensorShape(bias),
              tflite::micro::GetTensorData<std::int64_t>(bias),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<int16_t>(output));
          break;
        }
        default:

          TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                             TfLiteTypeGetName(input->type), input->type);
          return kTfLiteError;
      }
    } break;
#endif
    default:
      TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(input->type), input->type);
      return kTfLiteError;
  }
  return status;
}
TfLiteStatus EvalConvInt8(TfLiteContext *context, TfLiteNode *node) {
  const auto &params =
      *(reinterpret_cast<TfLiteConvParams *>(node->builtin_data));

  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kConvInputTensor);
  const TfLiteEvalTensor *filter =
      tflite::micro::GetEvalInput(context, node, kConvWeightsTensor);
  const TfLiteEvalTensor *bias =
      (NumInputs(node) == 3)
          ? tflite::micro::GetEvalInput(context, node, kConvBiasTensor)
          : nullptr;
  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kConvOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  // const OpData& data = *(static_cast<const OpData*>(node->user_data));
  const auto &data_ex = *(static_cast<const OpData *>(node->user_data));
  //  const OpDataConv &data = data_ex.ConvOp;
  // TFLITE_DCHECK(node->user_data != nullptr);
  TF_LITE_ENSURE_EQ(context, input->type, output->type);
  // enable 16x8
  TF_LITE_ENSURE_MSG(
      context,
      input->type == filter->type ||
          (input->type == kTfLiteInt16 && filter->type == kTfLiteInt8),
      "Hybrid models are not supported on TFLite Micro.");

  EvalConvQuantizedPerChannel(context, node, params, data_ex, input, filter,
                              bias, output, nullptr);

  return kTfLiteOk;
}

TfLiteStatus EvalConvFloat32(TfLiteContext* context, TfLiteNode* node) {
    const auto& params =
        *(reinterpret_cast<TfLiteConvParams*>(node->builtin_data));

    const TfLiteEvalTensor* input =
        tflite::micro::GetEvalInput(context, node, kConvInputTensor);
    const TfLiteEvalTensor* filter =
        tflite::micro::GetEvalInput(context, node, kConvWeightsTensor);
    const TfLiteEvalTensor* bias =
        (NumInputs(node) == 3)
        ? tflite::micro::GetEvalInput(context, node, kConvBiasTensor)
        : nullptr;
    TfLiteEvalTensor* output =
        tflite::micro::GetEvalOutput(context, node, kConvOutputTensor);
    TfLiteStatus status = kTfLiteOk;
    TFLITE_DCHECK(node->user_data != nullptr);
    // const OpData& data = *(static_cast<const OpData*>(node->user_data));
    const auto& data_ex = *(static_cast<const OpData*>(node->user_data));
    //  const OpDataConv &data = data_ex.ConvOp;
    // TFLITE_DCHECK(node->user_data != nullptr);
    TF_LITE_ENSURE_EQ(context, input->type, output->type);

    TF_LITE_ENSURE_MSG(context, (filter->type == kTfLiteFloat32 
        || filter->type == kTfLiteFloat16 || filter->type == kTfLiteInt8)
        ,
        "filter data type only for float32 or float16 or int8 (scale).");

    switch (filter->type)
    {
    case kTfLiteFloat32:
        status = EvalConvFloat(context, node, params, data_ex, input, filter,
            bias, output, nullptr);
        break;
    case kTfLiteFloat16:
        status = EvalConvFloat16Internal(context, node, params, data_ex, input, filter,
            bias, output, nullptr);
        break;
    case kTfLiteInt8:
        status = EvalConvFloatInt8(context, node, params, data_ex, input, filter,
            bias, output, nullptr);
        break;
    default:
        TF_LITE_KERNEL_LOG(context, "filter Type %s (%d) for float32/float16/int8 not supported.",
            TfLiteTypeGetName(filter->type), filter->type);
        return kTfLiteError;
    }

    return status;
}

TfLiteStatus EvalConvFloat16(TfLiteContext* context, TfLiteNode* node) {
    const auto& params =
        *(reinterpret_cast<TfLiteConvParams*>(node->builtin_data));

    const TfLiteEvalTensor* input =
        tflite::micro::GetEvalInput(context, node, kConvInputTensor);
    const TfLiteEvalTensor* filter =
        tflite::micro::GetEvalInput(context, node, kConvWeightsTensor);
    const TfLiteEvalTensor* bias =
        (NumInputs(node) == 3)
        ? tflite::micro::GetEvalInput(context, node, kConvBiasTensor)
        : nullptr;
    TfLiteEvalTensor* output =
        tflite::micro::GetEvalOutput(context, node, kConvOutputTensor);

    TFLITE_DCHECK(node->user_data != nullptr);
    // const OpData& data = *(static_cast<const OpData*>(node->user_data));
    const auto& data_ex = *(static_cast<const OpData*>(node->user_data));
    //  const OpDataConv &data = data_ex.ConvOp;
    // TFLITE_DCHECK(node->user_data != nullptr);
    TF_LITE_ENSURE_EQ(context, input->type, output->type);

    TF_LITE_ENSURE_MSG(context, kTfLiteFloat16 == filter->type,
        "Conv Float16 Eval filter type MUST kTfLiteFloat16.");

    EvalConvFloat16Internal(context, node, params, data_ex, input, filter,
        bias, output, nullptr);

    return kTfLiteOk;
}

TfLiteStatus EvalConvFloatInt8(TfLiteContext* context, TfLiteNode* node) {
    const auto& params =
        *(reinterpret_cast<TfLiteConvParams*>(node->builtin_data));

    const TfLiteEvalTensor* input =
        tflite::micro::GetEvalInput(context, node, kConvInputTensor);
    const TfLiteEvalTensor* filter =
        tflite::micro::GetEvalInput(context, node, kConvWeightsTensor);
    const TfLiteEvalTensor* bias =
        (NumInputs(node) == 3)
        ? tflite::micro::GetEvalInput(context, node, kConvBiasTensor)
        : nullptr;
    TfLiteEvalTensor* output =
        tflite::micro::GetEvalOutput(context, node, kConvOutputTensor);

    TFLITE_DCHECK(node->user_data != nullptr);
    // const OpData& data = *(static_cast<const OpData*>(node->user_data));
    const auto& data_ex = *(static_cast<const OpData*>(node->user_data));
    //  const OpDataConv &data = data_ex.ConvOp;
    // TFLITE_DCHECK(node->user_data != nullptr);
    TF_LITE_ENSURE_EQ(context, input->type, output->type);

    TF_LITE_ENSURE_MSG(context, kTfLiteInt8 == filter->type,
        "EvalConvFloatInt8  filter type MUST kTfLiteInt8.");

    EvalConvFloatInt8(context, node, params, data_ex, input, filter,
        bias, output, nullptr);

    return kTfLiteOk;
}
}  // namespace

TFLMRegistration Register_CONV_2D() {
  return tflite::micro::RegisterOp(InitConv,
  
          /*prepare=*/ConvPrepareOpt,
          /*invoke=*/EvalConv);
}

TFLMRegistration Register_CONV_2D_INT8REF() {
  return tflite::micro::RegisterOp(InitConv,
          /*prepare=*/ConvPrepareOpt,
          /*invoke=*/EvalConvInt8);
}

TFLMRegistration Register_CONV_2D_FLOAT32() {
  return tflite::micro::RegisterOp(InitConv,
        /*prepare=*/ConvPrepareOpt,
        /*invoke=*/EvalConvFloat32);
}

TFLMRegistration Register_CONV_2D_FLOAT16() {
    return tflite::micro::RegisterOp(InitConv,
        /*prepare=*/ConvPrepareOpt,
        /*invoke=*/EvalConvFloat16);
}

TFLMRegistration Register_CONV_2D_FLOATINT8() {
  return tflite::micro::RegisterOp(InitConv,
  
        /*prepare=*/ConvPrepareOpt,
        /*invoke=*/EvalConvFloatInt8);
}
}  // namespace tflite
