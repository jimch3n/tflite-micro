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

#define ENABLE_DILATION_OPT  // enable dialtion optimization

#include "tensorflow/lite/kernels/internal/reference/integer_ops/depthwise_conv.h"

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/micro/ia700/config.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/depthwiseconv_float.h"
#include "tensorflow/lite/kernels/internal/reference/depthwiseconv_uint8.h"
#endif
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/padding.h"
#include "tensorflow/lite/micro/kernels/depthwise_conv.h"
#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount
namespace tflite {
namespace {

constexpr int kDepthwiseConvInputTensor = 0;
constexpr int kDepthwiseConvWeightsTensor = 1;
constexpr int kDepthwiseConvBiasTensor = 2;
constexpr int kDepthwiseConvOutputTensor = 0;

// Depthwise conv is quantized along dimension 3:
// https://www.tensorflow.org/lite/performance/quantization_spec
constexpr int kDepthwiseConvQuantizedDimension = 3;

#ifdef HEMILITE_DW_CONV_OPT
static VAR_ALIGN_16 uint32_t tempVB[4 * 4];
static VAR_ALIGN_16 unsigned int bytearray_hmd[] = {

    0x44444444,
    0x88888888,
    0x11111111,
    0x22222222,

};
#endif
// local Opdata additional member item
typedef enum {
  DS_CONV_OPT_NONE = 0,
  DS_CONV_OPT_TYPE1 = 1,
  DS_CONV_OPT_TYPE2 = 2,  // input channel align 4
  DS_CONV_OPT_TYPE3 = 3,
  DS_CONV_OPT_TYPE4 = 4,

  // hybrid
  DS_CONV_OPT_FLT_X_INT8 = 8,    // kernel float x float(int8->float)
  DS_CONV_OPT_FLT_X_FLT16 = 16,  // kernel MVM8bx8b
} ds_conv_opt_type;

#define DS_CONV_OPT_MASK (DS_CONV_OPT_FLT_X_INT8 - 1)
struct DSConvOpData {
  struct OpDataConv ConvOp;  // reference opdata

  // Index to buffer for optimizations if applicable.
  int buffer_idx;
  int32_t *mapped_filter;  // aligned 4bytes, int8_t data to store pointer for
                           // mapping W
  uint32_t mapped_filter_size;
  // AScalar *outputMultiplerPerCh; // perchannel
  AScalar outputOffset;
  AScalar outputMultipler;  // uint8_t

  uint32_t input_offset_int8;
  uint32_t input_offset_int8_neg;
  int32_t *inputOffsetWithW;

  int opt_constraint;  // FOR each tensor?
  int opt_constraint_float;
  AScalar filter_scale;
  ds_conv2d_layer_t ds_conv2d;

  uint32_t sizeScratchIm2Col;
  uint32_t sizeScratchOutput;
};
template <typename T>
int DepthWiseConvMapFloatCoeffs(
    T *pMapped,
    int32_t mvmMatrix,  // matrix type, big or smaller for mvm_sparse
    int filter_height, int filter_width, const T *filter_data, int depth_multi,
    int input_depth) {
  int nInput = (mvmMatrix == 1) ? filter_height * filter_width * input_depth
                                : filter_height * filter_width;
  int nOutput = input_depth * depth_multi;

#ifdef KN_DEBUG

  printf("nInput: %d nOutput: %d  ", nInput, nOutput);

#endif
  const T *src = filter_data;
  T *dst = pMapped;
  int mappedSize =
      nInput * nOutput;  // nFullRowGroups * nFullColBlocks * BLOCK_SIZE_FLT;
  if (pMapped && filter_data) {
    tflite::block_fill_bytes((char *)pMapped, 0, sizeof(T) * mappedSize);

    for (int dm = 0; dm < depth_multi; dm++) {
      for (int fy = 0; fy < filter_height; fy++) {
        for (int fx = 0; fx < filter_width; fx++) {
          for (int in_ch = 0; in_ch < input_depth; in_ch++) {
            int out_channel = (in_ch * depth_multi) + dm;
            int inputIdx = (fy * filter_width + fx);

            int filter_srcIdx =
                inputIdx * depth_multi * input_depth + out_channel;

            int input_srcIdx =
                (mvmMatrix == 1)
                    ? (fy * filter_width + fx) * input_depth + in_ch
                    : inputIdx;

            // convert to mvm's matrix order
            int group = out_channel / ROWS_PER_GROUP_FLT;
            int j = out_channel % ROWS_PER_GROUP_FLT;
            int block = input_srcIdx;
            int dstIdx;

            dstIdx =  // group * ROWS_PER_GROUP_FLT * nFullBlockColsAligned2 +
                      // block * ROWS_PER_GROUP_FLT + j;
                (mvmMatrix == 1) ? out_channel * nInput + block :

                                 group * ROWS_PER_GROUP_FLT * nInput +
                                     block * ROWS_PER_GROUP_FLT + j;

            dst[dstIdx] = src[filter_srcIdx];
          }
        }
      }
    }
  }
  return mappedSize;
}
void *Init(TfLiteContext *context, const char *buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(DSConvOpData));
}

TfLiteStatus PrepareCommon(TfLiteContext *context, TfLiteNode *node) {
  DSConvOpData *data_ex = static_cast<DSConvOpData *>(node->user_data);

  OpDataConv *data = static_cast<OpDataConv *>(
      &data_ex->ConvOp);  // static_cast<OpDataConv*>(node->user_data);
                          // OpDataConv // auto *params =
  //      reinterpret_cast<TfLiteDepthwiseConvParams *>(node->builtin_data);

  const auto &params =
      *(static_cast<const TfLiteDepthwiseConvParams *>(node->builtin_data));

  MicroContext *micro_context = GetMicroContext(context);

  TfLiteTensor *output =
      micro_context->AllocateTempOutputTensor(node, kDepthwiseConvOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);
  TfLiteTensor *input =
      micro_context->AllocateTempInputTensor(node, kDepthwiseConvInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor *filter =
      micro_context->AllocateTempInputTensor(node, kDepthwiseConvWeightsTensor);
  TF_LITE_ENSURE(context, filter != nullptr);

  const TfLiteType data_type = input->type;
  int width = SizeOfDimension(input, 2);
  int height = SizeOfDimension(input, 1);
  int filter_width = SizeOfDimension(filter, 2);
  int filter_height = SizeOfDimension(filter, 1);

  const int output_width = output->dims->data[2];
  const int output_height = output->dims->data[1];
  // Allocate memory for per-channel quantization parameters
  const int num_channels = filter->dims->data[kDepthwiseConvQuantizedDimension];

  data->per_channel_output_multiplier =
      reinterpret_cast<int32_t *>(context->AllocatePersistentBuffer(
          context, num_channels * sizeof(int32_t)));
  data->per_channel_output_shift =
      reinterpret_cast<int32_t *>(context->AllocatePersistentBuffer(
          context, num_channels * sizeof(int32_t)));

  TF_LITE_ENSURE_STATUS(CalculateOpDataDepthwiseConv(
      context, node, params, width, height, filter_width, filter_height,
      output_width, output_height, data_type, data));

  data->input_zero_point = input->params.zero_point;
  data->filter_zero_point = filter->params.zero_point;
  data->output_zero_point = output->params.zero_point;

  RuntimeShape input_shape = GetTensorShape(input);
  RuntimeShape output_shape = GetTensorShape(output);
  RuntimeShape filter_shape = GetTensorShape(filter);
  ds_conv2d_layer_t &ds_conv2d = data_ex->ds_conv2d;

  // assign ds_conv2d
  ds_conv2d.in_y = input_shape.Dims(1);
  ds_conv2d.in_x = input_shape.Dims(2);
  ds_conv2d.in_ch = input_shape.Dims(3);

  ds_conv2d.ker_y = filter_shape.Dims(1);
  ds_conv2d.ker_x = filter_shape.Dims(2);

  ds_conv2d.out_y = output_shape.Dims(1);
  ds_conv2d.out_x = output_shape.Dims(2);
  ds_conv2d.out_ch = output_shape.Dims(3);

  ds_conv2d.stride_y = params.stride_height;
  ds_conv2d.stride_x = params.stride_width;

  ds_conv2d.dilation_y = params.dilation_height_factor;
  ds_conv2d.dilation_x = params.dilation_width_factor;

  ds_conv2d.padding_y = data->padding.height;
  ds_conv2d.padding_x = data->padding.width;
  ds_conv2d.ch_mult = params.depth_multiplier;
  ds_conv2d.input_offset = -data->input_zero_point;

  KN_PRINTD(ds_conv2d.in_y);
  KN_PRINTD(ds_conv2d.in_x);
  KN_PRINTD(ds_conv2d.in_ch);
  KN_PRINTD(ds_conv2d.ker_y);
  KN_PRINTD(ds_conv2d.ker_x);
  KN_PRINTD(ds_conv2d.padding_y);
  KN_PRINTD(ds_conv2d.padding_x);
  KN_PRINTD(ds_conv2d.stride_y);
  KN_PRINTD(ds_conv2d.stride_x);
  KN_PRINTD(ds_conv2d.dilation_y);
  KN_PRINTD(ds_conv2d.dilation_x);
  KN_PRINTD(ds_conv2d.out_y);
  KN_PRINTD(ds_conv2d.out_x);
  KN_PRINTD(ds_conv2d.out_ch);
  KN_PRINTD(ds_conv2d.ch_mult);
  KN_PRINTD(ds_conv2d.input_offset);

  micro_context->DeallocateTempTfLiteTensor(output);
  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(filter);
  return kTfLiteOk;
}

#if defined(HEMILITE_DW_CONV_OPT)

int DepthWiseConvKernel8xnInputOffset(const int32_t inputOffset,
                                      const int8_t *pAinput,
                                      int32_t *inputOffsetWithW, int m, int n,
                                      int multSigns) {
  // const int8_t *pX = (int8_t *)x;
  // const int8_t *pAct2 = (int8_t*)x +m;

  uint32_t *pTempVBPtr = nullptr;  // = tempVB;
  // int m2 = m >> 2;                 // 32x2 8

  int32_t *pDst = inputOffsetWithW;
  uint32_t *pBitArrays2 = nullptr;  // = (uint32_t *)bytearray_hmd;

  // vr64 VR_yTmp;

  vr64 VR_inputOffset;
  vr64 VR_x;  // , VR_x2;
  vr64 VR_acc, VR_coeff;
  atbool signSpec = atbool(multSigns);
  // ulsr128 UR_x;
  int32_t *pA1 = (int32_t *)pAinput;
  ulsr32 UR_A = align_32x2_load(pA1);

  constexpr int loopCount = 4;
  int n8 = n >> 3;
  //
  VR_acc = vseta_vr(0, 0);
  mov_AccExtend_vr(VR_acc);
  replicate_ar(VR_inputOffset, 0x3, inputOffset);
  for (int jj = 0; jj < n8; jj++) {
    set_BB_vrVB67_zero();
    pTempVBPtr = tempVB;  //

    store32x2_vr_postI(VR_inputOffset, pTempVBPtr, INC1);

    store32x2_vr_postI(VR_inputOffset, pTempVBPtr, INC1);

    store32x2_vr_postI(VR_inputOffset, pTempVBPtr, INC1);

    pTempVBPtr = tempVB;
    load_VB1_postI(pTempVBPtr, INC1);
    load_VB2_postI(pTempVBPtr, INC1);
    load_VB3_postI(pTempVBPtr, INC1);

    VR_x = vexp_adji(VR_inputOffset, 0);
    WUR_MvmAux(0);
    pBitArrays2 = (uint32_t *)bytearray_hmd;
    load_BB0_postI(pBitArrays2, INC1);
    load_BB1_postI(pBitArrays2, INC1);

    load_32x2_vr_a(VR_coeff, UR_A, pA1);
    // 16*3
    for (int i = 0; i < loopCount - 1; i++) {
      mac8bx8b_sparse(VR_acc, VR_coeff, VR_x, signSpec);
      load_32x2_vr_a(VR_coeff, UR_A, pA1);
    }
    mac8bx8b_sparse(VR_acc, VR_coeff, VR_x, signSpec);
  }
  // if(filter_size&1)
  {
    // VR_x = vseta_vr(0, 0);
    replicate_ar(VR_inputOffset, 0x2, 0);
    for (int i = 0; i < (n & 7); i++) {
      WUR_MvmAux(0);
      set_BB_vrVB67_zero();
      // load32x1_vr_postR(VR_x, pX, m2, VRL);  // load column 8
      pBitArrays2 = (uint32_t *)bytearray_hmd;
      load_BB0_postI(pBitArrays2, INC1);
      load_BB1_postI(pBitArrays2, INC1);
      // load_BB2_postI(pBitArrays2, INC1);
      // load_BB3_postI(pBitArrays2, INC1);
      // VR_x = vseta_vr(0, 0, 0); //High part 0, 8 x1 only
      load32x1_vr_postI(VR_coeff, pA1, INC1, VRQ0);
      // load32x1_vr_postI(VR_coeff, pA1, INC1, VRQ1);
      mac8bx8b_sparse(VR_acc, VR_coeff, VR_inputOffset, signSpec);
    }

    store32x2_vr_postI(VR_acc, pDst, INC1);
    store_AccExtend_postI(pDst, INC1);
  }

  return 0;  // (unsigned)pA1 - (unsigned)pAinput; //stride of A
}
#endif
TfLiteStatus PrepareInt8(TfLiteContext *context, TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  DSConvOpData *data_ex = static_cast<DSConvOpData *>(node->user_data);
  OpDataConv *data = static_cast<OpDataConv *>(&data_ex->ConvOp);

  auto *params =
      reinterpret_cast<TfLiteDepthwiseConvParams *>(node->builtin_data);

  MicroContext *micro_context = GetMicroContext(context);

  TfLiteTensor *output =
      micro_context->AllocateTempOutputTensor(node, kDepthwiseConvOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);
  TfLiteTensor *input =
      micro_context->AllocateTempInputTensor(node, kDepthwiseConvInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor *filter =
      micro_context->AllocateTempInputTensor(node, kDepthwiseConvWeightsTensor);
  TF_LITE_ENSURE(context, filter != nullptr);

  // const TfLiteType data_type = input->type;
  // int width = SizeOfDimension(input, 2);
  // int height = SizeOfDimension(input, 1);
  // int filter_width = SizeOfDimension(filter, 2);
  // int filter_height = SizeOfDimension(filter, 1);
  TF_LITE_ENSURE_STATUS(PrepareCommon(context, node));

  RuntimeShape input_shape = GetTensorShape(input);
  RuntimeShape output_shape = GetTensorShape(output);
  RuntimeShape filter_shape = GetTensorShape(filter);
  ds_conv2d_layer_t &ds_conv2d = data_ex->ds_conv2d;

  //     if (input->type == kTfLiteInt8)
  {
    TF_LITE_ENSURE_EQ(context, filter->quantization.type,
                      kTfLiteAffineQuantization);

    // All per-channel quantized tensors need valid zero point and scale arrays.
    const auto *affine_quantization =
        reinterpret_cast<TfLiteAffineQuantization *>(
            filter->quantization.params);
    TF_LITE_ENSURE(context, affine_quantization);
    TF_LITE_ENSURE(context, affine_quantization->scale);
    TF_LITE_ENSURE(context, affine_quantization->zero_point);
    TF_LITE_ENSURE(
        context, affine_quantization->scale->size == 1 ||
                     affine_quantization->scale->size ==
                         filter->dims->data[kDepthwiseConvQuantizedDimension]);
    TF_LITE_ENSURE_EQ(context, affine_quantization->scale->size,
                      affine_quantization->zero_point->size);
  }

  // if (input->type == kTfLiteInt8)
  {
    //  TFLITE_DCHECK_EQ(input_shape.DimensionsCount(), 4);
    //  TFLITE_DCHECK_EQ(filter_shape.DimensionsCount(), 4);
    //  TFLITE_DCHECK_EQ(output_shape.DimensionsCount(), 4);

    const int batch_size = MatchingDim(input_shape, 0, output_shape, 0);

    TFLITE_DCHECK_EQ(batch_size, 1); /* Only batch = 1 is supported */

    int32_t *p_mapped_filter = nullptr;

    const TfLiteEvalTensor *filterEval =
        tflite::micro::GetEvalInput(context, node, kDepthwiseConvWeightsTensor);
    const int8_t *filter_input =
        tflite::micro::GetTensorData<int8_t>(filterEval);

#ifdef ENABLE_DILATION_OPT
    bool dilation_xy1 = true;  // enable DIALTION
#else
    bool dilation_xy1 = (1 == params->dilation_width_factor &&
                         1 == params->dilation_height_factor);
#endif
    data_ex->opt_constraint = dilation_xy1;

#if defined(HEMILITE_DW_CONV_OPT)
    if (data_ex->opt_constraint) {
      // data_ex->opt_constraint =
      //     DEPTHWISE_CONV_OPT_MAC8Bx8B_INPUT_OFFSET;  // input is not 0, or
      //     128

      uint8_t offsetInput = ds_conv2d.input_offset & 0xff;
      data_ex->input_offset_int8 = (offsetInput << 24) | (offsetInput << 16) |
                                   (offsetInput << 8) | offsetInput;
      offsetInput = (data->input_zero_point & 0xff);
      data_ex->input_offset_int8_neg = (offsetInput << 24) |
                                       (offsetInput << 16) |
                                       (offsetInput << 8) | offsetInput;

      //  if (ds_conv2d.input_offset == 128 || ds_conv2d.input_offset == 0)
      {
        // type of only 1
      }

      if (ds_conv2d.ch_mult == 1) {
        {
          data_ex->opt_constraint = DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE;
        }
      } else {
        data_ex->opt_constraint = DEPTHWISE_CONV_OPT_MAC8Bx8B;
      }
    }  // able to use mvm
       // data->mvmConstraint = 0;

    KN_PRINTD(data_ex->opt_constraint);
    KN_PRINTD(tflite::is_coeffs_mapped(context));
    // KN_PRINTD();

    // const int input_depth = ds_conv2d.in_ch;  // input_shape.Dims(3);
    if (data_ex->opt_constraint != 0)  //||data->mvmConstraint == 2 )
    {
      const int32_t buf_size = tflite::DepthWiseConvMap8bitCoeffs(
          NULL, data_ex->opt_constraint, ds_conv2d.ker_y, ds_conv2d.ker_x, NULL,
          params->depth_multiplier, ds_conv2d.in_ch);
      if (!tflite::is_coeffs_mapped(context)) {
        const int8_t *pfilter_val = &filter_input[0];

        p_mapped_filter = (int32_t *)context->AllocatePersistentBuffer(
            context, buf_size * sizeof(int8_t));

        tflite::DepthWiseConvMap8bitCoeffs(
            (int8_t *)p_mapped_filter, data_ex->opt_constraint, ds_conv2d.ker_y,
            ds_conv2d.ker_x, (int8_t *)pfilter_val, params->depth_multiplier,
            ds_conv2d.in_ch);
        data_ex->mapped_filter = p_mapped_filter;
      } else {
        data_ex->mapped_filter = (int32_t *)filter_input;
      }
      // data->mapped_filter = p_mapped_filter;
      data_ex->mapped_filter_size = buf_size;
      KN_PRINT_Q7_SIZE(data_ex->mapped_filter, buf_size);

      int32_t output_matVec = params->depth_multiplier * ds_conv2d.in_ch;
      const TfLiteEvalTensor *biasEval =
          tflite::micro::GetEvalInput(context, node, kDepthwiseConvBiasTensor);
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
      int32_t buf_size_scratch = 0;
      int32_t buf_size_im2col = 0;
      if (data_ex->opt_constraint == DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE) {
        int align8_inch = (((ds_conv2d.in_ch + 7) >> 3) << 3);
        int aling2_filrter_dim =
            (((ds_conv2d.ker_x * ds_conv2d.ker_y + 1) >> 1) << 1);

        buf_size_im2col =
            (align8_inch * aling2_filrter_dim) *
            params
                ->depth_multiplier;  // get scratch buffer size for optimization
      } else if (data_ex->opt_constraint == DEPTHWISE_CONV_OPT_MAC8Bx8B) {
        buf_size_im2col =
            ((((ds_conv2d.in_ch * ds_conv2d.ker_x * ds_conv2d.ker_y) + 15) >> 4)
             << 4) *
            params
                ->depth_multiplier;  // get scratch buffer size for optimization
      }
      // int align8_outch = (((ds_conv2d.out_ch + 7) >> 3) << 3);
      int32_t buf_size_output =
          (((ds_conv2d.out_ch + 7) >> 3) << 3) *
          sizeof(int32_t);  // output store 8 multiple align
      buf_size_scratch = buf_size_im2col + buf_size_output;

      data_ex->sizeScratchIm2Col = buf_size_im2col;
      data_ex->sizeScratchOutput = buf_size_output;
      KN_PRINTD(buf_size_im2col);
      KN_PRINTD(buf_size_output);
      if (buf_size_scratch > 0) {
        TF_LITE_ENSURE_STATUS(context->RequestScratchBufferInArena(
            context, buf_size_scratch, &data_ex->buffer_idx));
      } else {
        data_ex->buffer_idx = -1;
      }
      // prepare ConvInput Offset
      KN_PRINTD(ds_conv2d.input_offset);

      if (ds_conv2d.input_offset != 128 && ds_conv2d.input_offset != 0) {
        if (data_ex->opt_constraint == DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE) {
          int inFCM = ds_conv2d.out_ch * ds_conv2d.ch_mult;
          int inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y;

          int filter_dim_align2 = (((inFCN + 1) >> 1) << 1);

          KN_PRINTD(inFCN);

#if defined(HEMILITE_DW_CONV_OPT)
          const int group = 4;
          const int shift = 2;

#endif
          int inFCM_ALIGN = (((inFCM + group - 1) >> shift) << shift);
          KN_PRINTD(inFCM_ALIGN);
          int32_t *inputOffsetWithW =
              (int32_t *)context->AllocatePersistentBuffer(
                  context, inFCM_ALIGN * sizeof(int32_t));

          data_ex->inputOffsetWithW = inputOffsetWithW;

          for (int g = 0; g < (inFCM_ALIGN >> shift); g++) {
            int32_t *scratchPerGroup = inputOffsetWithW + group * g;
            int8_t *pKernel = (int8_t *)data_ex->mapped_filter +
                              group * filter_dim_align2 * g;

            DepthWiseConvKernel8xnInputOffset(
                data_ex->input_offset_int8,
                pKernel,  // data_ex->mapped_filter,
                scratchPerGroup, inFCM_ALIGN, inFCN, 3);
          }

          KN_PRINT_Q31_SIZE(inputOffsetWithW, inFCM_ALIGN);
        } else if (data_ex->opt_constraint == DEPTHWISE_CONV_OPT_MAC8Bx8B) {
          int inFCM = ds_conv2d.out_ch;
          int inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y * ds_conv2d.in_ch;
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
        }
      } else {
        data_ex->inputOffsetWithW = nullptr;
      }
    }  // constraint

#endif
  }

  micro_context->DeallocateTempTfLiteTensor(output);
  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(filter);
  return kTfLiteOk;
}
TfLiteStatus PrepareFloat(TfLiteContext *context, TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  DSConvOpData *data_ex = static_cast<DSConvOpData *>(node->user_data);
  //   OpDataConv *data = static_cast<OpDataConv *>(&data_ex->ConvOp);

  auto *params =
      reinterpret_cast<TfLiteDepthwiseConvParams *>(node->builtin_data);

  MicroContext *micro_context = GetMicroContext(context);

  TfLiteTensor *output =
      micro_context->AllocateTempOutputTensor(node, kDepthwiseConvOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);
  TfLiteTensor *input =
      micro_context->AllocateTempInputTensor(node, kDepthwiseConvInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor *filter =
      micro_context->AllocateTempInputTensor(node, kDepthwiseConvWeightsTensor);
  TF_LITE_ENSURE(context, filter != nullptr);

  // const TfLiteType data_type = input->type;
  // int width = SizeOfDimension(input, 2);
  // int height = SizeOfDimension(input, 1);
  // int filter_width = SizeOfDimension(filter, 2);
  // int filter_height = SizeOfDimension(filter, 1);
  TF_LITE_ENSURE_STATUS(PrepareCommon(context, node));

  RuntimeShape input_shape = GetTensorShape(input);
  RuntimeShape output_shape = GetTensorShape(output);
  RuntimeShape filter_shape = GetTensorShape(filter);
  ds_conv2d_layer_t &ds_conv2d = data_ex->ds_conv2d;

  data_ex->opt_constraint_float = 0;
#ifdef ENABLE_DILATION_OPT
  bool dilation_xy1 = true;  // enable DIALTION
#else
  bool dilation_xy1 = (1 == params->dilation_width_factor &&
                       1 == params->dilation_height_factor);
#endif
  if (dilation_xy1) {
    data_ex->opt_constraint_float = DS_CONV_OPT_TYPE1;
    if (ds_conv2d.ch_mult == 1 && ((ds_conv2d.out_ch & 3) == 0)) {
      data_ex->opt_constraint_float = DS_CONV_OPT_TYPE2;
    }
  }  // able to use mvm

  KN_PRINTD(data_ex->opt_constraint_float);

  const TfLiteEvalTensor *filterEval =
      tflite::micro::GetEvalInput(context, node, kDepthwiseConvWeightsTensor);

  if (data_ex->opt_constraint_float > 0) {
    switch (filter->type) {
      case kTfLiteFloat32: {
        float *p_mapped_filter = nullptr;
        const float *filter_input =
            tflite::micro::GetTensorData<float>(filterEval);
        const int32_t buf_size = tflite::DepthWiseConvMapFloatCoeffs<float>(
            NULL, data_ex->opt_constraint_float, ds_conv2d.ker_y,
            ds_conv2d.ker_x, NULL, params->depth_multiplier, ds_conv2d.in_ch);
        KN_PRINTD(buf_size);
        KN_PRINTD(tflite::is_coeffs_mapped(context));
        if (!tflite::is_coeffs_mapped(context)) {
          const float *pfilter_val = &filter_input[0];

          p_mapped_filter = (float *)context->AllocatePersistentBuffer(
              context, buf_size * sizeof(float));
          KN_PRINTD(data_ex->opt_constraint_float);
          tflite::DepthWiseConvMapFloatCoeffs<float>(
              (float *)p_mapped_filter, data_ex->opt_constraint_float,
              ds_conv2d.ker_y, ds_conv2d.ker_x, (float *)pfilter_val,
              params->depth_multiplier, ds_conv2d.in_ch);
          data_ex->mapped_filter = (int32_t *)p_mapped_filter;
        } else {
          data_ex->mapped_filter = (int32_t *)filter_input;
        }
        // data->mapped_filter = p_mapped_filter;
        data_ex->mapped_filter_size = buf_size;
        KN_PRINT_FLOAT(data_ex->mapped_filter, buf_size);
      } break;
      case kTfLiteInt8: {  // hybrid mode should converted by
                           // kn_tflite_converter
        // 1. conditioanl only

        data_ex->filter_scale = AScalar(filter->params.scale);

        KN_PRINTAFLT(data_ex->filter_scale);
        // check multiple channels scale
        const auto *affine_quantization =
            reinterpret_cast<TfLiteAffineQuantization *>(
                filter->quantization.params);

        // KN_PRINTD(affine_quantization->scale->data);
        // KN_PRINTD(affine_quantization->zero_point->data);
        if (affine_quantization) {
          const bool is_per_channel = affine_quantization->scale->size > 1;
          const float *filter_scales = affine_quantization->scale->data;
          const int num_channels =
              filter->dims->data[kDepthwiseConvQuantizedDimension];
          if (is_per_channel) {
            for (int i = 0; i < num_channels; ++i) {
              // If per-tensor quantization parameter is specified, broadcast it
              // along the quantization dimension (channels_out).
              const AScalar scale = AScalar(filter_scales[i]);
              data_ex->ConvOp.per_channel_output_multiplier[i] = scale.raw();
            }
            KN_PRINT_AFLOAT(data_ex->ConvOp.per_channel_output_multiplier,
                            num_channels);
          } else {
            data_ex->ConvOp.per_channel_output_multiplier = nullptr;
          }

          // KN_PRINT_FLOAT_INT8_PER_CH(data_ex->mapped_filter,
          //    buf_size,
          //    data_ex->filter_scale);
        } else {
          data_ex->ConvOp.per_channel_output_multiplier = nullptr;
        }
        int8_t *p_mapped_filter = nullptr;
        const int8_t *filter_input =
            tflite::micro::GetTensorData<int8_t>(filterEval);
        const int32_t buf_size = tflite::DepthWiseConvMapFloatCoeffs<int8_t>(
            NULL, data_ex->opt_constraint_float, ds_conv2d.ker_y,
            ds_conv2d.ker_x, NULL, params->depth_multiplier, ds_conv2d.in_ch);
        KN_PRINTD(buf_size);
        KN_PRINTD(tflite::is_coeffs_mapped(context));
        if (!tflite::is_coeffs_mapped(context)) {
          const int8_t *pfilter_val = &filter_input[0];

          p_mapped_filter = (int8_t *)context->AllocatePersistentBuffer(
              context, buf_size * sizeof(int8_t));
          KN_PRINTD(data_ex->opt_constraint_float);
          tflite::DepthWiseConvMapFloatCoeffs<int8_t>(
              p_mapped_filter, data_ex->opt_constraint_float, ds_conv2d.ker_y,
              ds_conv2d.ker_x, pfilter_val, params->depth_multiplier,
              ds_conv2d.in_ch);
          data_ex->mapped_filter = (int32_t *)p_mapped_filter;
        } else {
          data_ex->mapped_filter = (int32_t *)filter_input;
        }
        data_ex->opt_constraint_float |= DS_CONV_OPT_FLT_X_INT8;
        data_ex->mapped_filter_size = buf_size;

        data_ex->filter_scale = AScalar(filter->params.scale);
        // NO PER CH scale
        // KN_PRINT_FLOAT_INT8(data_ex->mapped_filter, buf_size,
        // data_ex->filter_scale);
        KN_PRINT_Q7_SIZE(data_ex->mapped_filter, buf_size);
      } break;
      case kTfLiteFloat16: {
        TfLiteFloat16 *p_mapped_filter = nullptr;
        const TfLiteFloat16 *filter_input =
            tflite::micro::GetTensorData<TfLiteFloat16>(filterEval);
        const int32_t buf_size =
            tflite::DepthWiseConvMapFloatCoeffs<TfLiteFloat16>(
                NULL, data_ex->opt_constraint_float, ds_conv2d.ker_y,
                ds_conv2d.ker_x, NULL, params->depth_multiplier,
                ds_conv2d.in_ch);
        KN_PRINTD(buf_size);
        KN_PRINTD(tflite::is_coeffs_mapped(context));
        if (!tflite::is_coeffs_mapped(context)) {
          const TfLiteFloat16 *pfilter_val = &filter_input[0];

          p_mapped_filter = (TfLiteFloat16 *)context->AllocatePersistentBuffer(
              context, buf_size * sizeof(TfLiteFloat16));
          KN_PRINTD(data_ex->opt_constraint_float);
          tflite::DepthWiseConvMapFloatCoeffs<TfLiteFloat16>(
              p_mapped_filter, data_ex->opt_constraint_float, ds_conv2d.ker_y,
              ds_conv2d.ker_x, pfilter_val, params->depth_multiplier,
              ds_conv2d.in_ch);
          data_ex->mapped_filter = (int32_t *)p_mapped_filter;
        } else {
          data_ex->mapped_filter = (int32_t *)filter_input;
        }
        data_ex->opt_constraint_float |= DS_CONV_OPT_FLT_X_FLT16;
        data_ex->mapped_filter_size = buf_size;
        KN_PRINT_AFLOAT16(data_ex->mapped_filter, buf_size);
      } break;
      default:
        return kTfLiteError;
        break;
    }  // end of switch case filter->type
    KN_PRINTD(data_ex->opt_constraint_float);
  }  // end of data_ex->opt_constraint_float > 0
  int32_t buf_size_scratch = 0;
  int32_t buf_size_im2col =
      ((((ds_conv2d.in_ch * ds_conv2d.ker_x * ds_conv2d.ker_y) + 3) >> 2)
       << 2) *
      params->depth_multiplier *
      sizeof(float);  // get scratch buffer size for optimization

  buf_size_scratch = buf_size_im2col;  // + buf_size_output;

  data_ex->sizeScratchIm2Col = buf_size_im2col;
  data_ex->sizeScratchOutput = 0;  // buf_size_output;
  KN_PRINTD(buf_size_im2col);
  // KN_PRINTD(buf_size_output);
  if (buf_size_scratch > 0) {
    TF_LITE_ENSURE_STATUS(context->RequestScratchBufferInArena(
        context, buf_size_scratch, &data_ex->buffer_idx));
  } else {
    data_ex->buffer_idx = -1;
  }

  micro_context->DeallocateTempTfLiteTensor(output);
  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(filter);
  return kTfLiteOk;
}

TfLiteStatus Prepare(TfLiteContext *context, TfLiteNode *node) {
  MicroContext *micro_context = GetMicroContext(context);
  // const TfLiteTensor *input = GetInput(context, node,
  // kDepthwiseConvInputTensor);
  TfLiteTensor *input =
      micro_context->AllocateTempInputTensor(node, kDepthwiseConvInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  if (input->type == kTfLiteInt8) {  // constraint
    micro_context->DeallocateTempTfLiteTensor(input);
    return PrepareInt8(context, node);
  }

  // data->opt_constraint_float = 0;
  else if (input->type == kTfLiteFloat32) {
    micro_context->DeallocateTempTfLiteTensor(input);
    return PrepareFloat(context, node);
  }

  return kTfLiteError;
}
#ifdef HEMILITE_CONV_OPT
static int DepthWiseConvFloat16Kernel(float *x, const TfLiteFloat16 *A,
                                      const float *bias, float *output, int m,
                                      int n, const AScalar &act_min,
                                      const AScalar &act_max) {
  const TfLiteFloat16 *pA = A;
  const float *pX;
  const float *pBias = bias;
  int loopLimCol = (n >> 1);  // block 16

  int remainCol = n & 1;

  float *pDst = output;

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  vr64 VR_max, VR_min;

  replicate_ar(VR_max, 0x3, act_max.fr);
  replicate_ar(VR_min, 0x3, act_min.fr);

  // filter index:
  //
  for (int i = 0; i < m; i++) {
    VR_y = vseta_vr(0, 0);
    vr64 VR_out, VR_bias;
    pX = x;
    // ulsr32 UR_A = align_16x2_load(pA);
    ulsr32 UR_x = align_32x2_load(pX);
    load16x2_vr_postI(VR_A, pA, INC1);
    load_32x2_vr_a(VR_x, UR_x, pX);

    for (int j = 0; j < loopLimCol - 1; j++) {
      convert_IEEE_float_to_32F_x2(VR_x);
      convert_16F_to_32F_x2(VR_A, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);

      VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);  // linear
                                             //  KN_PRINT_VR(VR_y);
      load16x2_vr_postI(VR_A, pA, INC1);
      load_32x2_vr_a(VR_x, UR_x, pX);
    }

    convert_IEEE_float_to_32F_x2(VR_x);
    convert_16F_to_32F_x2(VR_A, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);

    VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);
    if (remainCol) {
      load16x1_vr_postI(VR_A, pA, INC1, VRQ0);
      load32x1_vr_postI(VR_x, pX, INC1, VRQ0);

      convert_IEEE_float_to_32F_x2(VR_x);
      convert_16F_to_32F_x2(VR_A, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
      // fmacs(VR_y, VRQ0, VR_x, VRQ0, VR_A, VRQ0, 0);
      fr32 fr_y = fmacs(get_VRL(VR_y), get_VRL(VR_x), get_VRL(VR_A), 0);
      set_VRL(VR_y, fr_y);
    }

    load32x1_vr_postI(VR_bias, pBias, INC1, VRQ0);
    convert_IEEE_float_to_32F_x2(VR_bias);
    fr32 fr_yout = fadds(get_VRL(VR_y), get_VRH(VR_y), 0);
    set_VRL(VR_out, fr_yout);

    // fadds(VR_out, VRQ0, VR_out, VRQ0, VR_bias, VRQ0, 0);
    VR_out = vadds(VR_out, VR_bias, 0);
    VR_out = vmax(VR_min, VR_out);
    VR_out = vmin(VR_max, VR_out);

    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, pDst, INC1, VRQ0);
  }

  return 0;
}

static int DepthWiseConvFloatKernel(float *x, const float *A, const float *bias,
                                    float *output, int m, int n,
                                    const AScalar &act_min,
                                    const AScalar &act_max) {
  const float *pA = A;
  const float *pX;
  const float *pBias = bias;
  int loopLimCol = (n >> 1);  // block 16

  int remainCol = n & 1;

  float *pDst = output;

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  vr64 VR_max, VR_min;

  replicate_ar(VR_max, 0x3, act_max.fr);
  replicate_ar(VR_min, 0x3, act_min.fr);

  // filter index:
  //
  for (int i = 0; i < m; i++) {
    VR_y = vseta_vr(0, 0);
    vr64 VR_out, VR_bias;
    pX = x;
    ulsr32 UR_A = align_32x2_load(pA);
    ulsr32 UR_x = align_32x2_load(pX);
    load_32x2_vr_a(VR_A, UR_A, pA);
    load_32x2_vr_a(VR_x, UR_x, pX);

    for (int j = 0; j < loopLimCol - 1; j++) {
      convert_IEEE_float_to_32F_x2(VR_x);
      convert_IEEE_float_to_32F_x2(VR_A);
      // KN_PRINT_VR(VR_A);
      // KN_PRINT_VR(VR_x);

      VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);  // linear
                                             //  KN_PRINT_VR(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);
      load_32x2_vr_a(VR_x, UR_x, pX);
    }

    convert_IEEE_float_to_32F_x2(VR_x);
    convert_IEEE_float_to_32F_x2(VR_A);
    // KN_PRINT_VR(VR_A);
    // KN_PRINT_VR(VR_x);
    VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);
    if (remainCol) {
      load32x1_vr_postI(VR_A, pA, INC1, VRQ0);
      load32x1_vr_postI(VR_x, pX, INC1, VRQ0);

      convert_IEEE_float_to_32F_x2(VR_x);
      convert_IEEE_float_to_32F_x2(VR_A);
      // fmacs(VR_y, VRQ0, VR_x, VRQ0, VR_A, VRQ0, 0);
      fr32 fr_y = fmacs(get_VRL(VR_y), get_VRL(VR_x), get_VRL(VR_A), 0);
      set_VRL(VR_y, fr_y);
    }

    load32x1_vr_postI(VR_bias, pBias, INC1, VRQ0);
    convert_IEEE_float_to_32F_x2(VR_bias);
    // dsums_L(VR_y, VR_y, 0, 0);
    // fadds(VR_out, VRQ0, VR_y, VRQ0, VR_y, VRQ1, 0);

    //    KN_PRINT_VR(VR_out);
    //    KN_PRINT_VR(VR_bias);

    fr32 fr_yout = fadds(get_VRL(VR_y), get_VRH(VR_y), 0);
    set_VRL(VR_y, fr_yout);
    // fadds(VR_out, VRQ0, VR_out, VRQ0, VR_bias, VRQ0, 0);
    VR_out = vadds(VR_y, VR_bias, 0);
    //  KN_PRINT_VR(VR_out);

    VR_out = vmax(VR_min, VR_out);
    VR_out = vmin(VR_max, VR_out);

    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, pDst, INC1, VRQ0);
  }

  return 0;
}

static int DepthWiseConvFloatInt8Kernel(float *x, const int8_t *A,
                                        const AScalar &scale, const float *bias,
                                        float *output, int m, int n,
                                        const AScalar &act_min,
                                        const AScalar &act_max,
                                        AScalar *scale_ptr = nullptr) {
  const int8_t *pA = A;
  const float *pX;
  const float *pBias = bias;
  int loopLimCol = (n >> 1);  // block 16

  int remainCol = n & 1;

  float *pDst = output;

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  vr64 VR_max, VR_min;
  vr64 VR_scale;
  AScalar *pScalePerCh = scale_ptr;

  const int wBlkExp = 7;
  replicate_ar(VR_max, 0x3, act_max.fr);
  replicate_ar(VR_min, 0x3, act_min.fr);
  replicate_ar(VR_scale, 0x3, scale.fr);

  // filter index:
  //
  for (int i = 0; i < m; i++) {
    VR_y = vseta_vr(0, 0);
    vr64 VR_out, VR_bias;
    pX = x;
    // ulsr128 UR_A = align_8x4_load(pA);
    ulsr32 UR_x = align_32x2_load(pX);
    load8x2_vr_postI(VR_A, pA, INC1);
    load_32x2_vr_a(VR_x, UR_x, pX);

    for (int j = 0; j < loopLimCol - 1; j++) {
      convert_IEEE_float_to_32F_x2(VR_x);
      convert_16I_to_32F_x2(VR_A, wBlkExp);

      VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);  // linear
                                             //  KN_PRINT_VR(VR_y);
      load8x2_vr_postI(VR_A, pA, INC1);
      load_32x2_vr_a(VR_x, UR_x, pX);
    }

    convert_IEEE_float_to_32F_x2(VR_x);
    convert_16I_to_32F_x2(VR_A, wBlkExp);

    VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);
    if (remainCol) {
      load8x1_vr_postI(VR_A, pA, INC1, VRQ0);
      load32x1_vr_postI(VR_x, pX, INC1, VRQ0);

      convert_IEEE_float_to_32F_x2(VR_x);
      convert_16I_to_32F_x2(VR_A, wBlkExp);
      // fmacs(VR_y, VRQ0, VR_x, VRQ0, VR_A, VRQ0, 0);
      fr32 fr_y = fmacs(get_VRL(VR_y), get_VRL(VR_x), get_VRL(VR_A), 0);
      set_VRL(VR_y, fr_y);
    }

    load32x1_vr_postI(VR_bias, pBias, INC1, VRQ0);
    convert_IEEE_float_to_32F_x2(VR_bias);

    fr32 fr_yout = fadds(get_VRL(VR_y), get_VRH(VR_y), 0);
    set_VRL(VR_y, fr_yout);
    if (scale_ptr) {
      load32x1_vr_postI(VR_scale, pScalePerCh, INC1, VRQ0);
    }
    VR_out = vmuls(VR_y, VR_scale, 0);
    VR_out = vadds(VR_out, VR_bias, 0);

    VR_out = vmax(VR_min, VR_out);
    VR_out = vmin(VR_max, VR_out);

    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, pDst, INC1, VRQ0);
  }

  return 0;
}
static int DepthWiseConvFloatInt8KernelVIP(float *x, const int8_t *A,
                                           const AScalar &scale,
                                           const float *bias, float *output,
                                           int m, int n, const AScalar &act_min,
                                           const AScalar &act_max,
                                           AScalar *scale_ptr = nullptr) {
  const float *pBias = bias;
  int loopLimRow = (m >> 1);

  float *pDst = output;
  const int wBlkExp = 7;
  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  vr64 VR_max, VR_min;
  vr64 VR_scale;
  int nextIn = m >> 1;
  TF_LITE_ASSERT((m & 1) == 0);

  ulsr32 UR_b = align_32x2_load(pBias);
  ulsr32 UR_out = align_32x2_store(pDst);
  AScalar *pScalePerCh = scale_ptr;
  replicate_ar(VR_max, 0x3, act_max.fr);
  replicate_ar(VR_min, 0x3, act_min.fr);
  replicate_ar(VR_scale, 0x3, scale.fr);
  {
    for (int i = 0; i < loopLimRow; i++) {
      const float *pX = x + i * 2;
      const int8_t *pA = (int8_t *)A + i * 2 * n;

      // ulsr32 UR_A = align_8x4_load(pA);
      VR_y = vseta_vr(0, 0);
      vr64 VR_out, VR_bias;

      load8x2_vr_postI(VR_A, pA, INC1);

      load32x2_vr_postR(VR_x, pX, nextIn);

      for (int j = 0; j < n - 1; j++) {
        convert_IEEE_float_to_32F_x2(VR_x);
        convert_16I_to_32F_x2(VR_A, wBlkExp);
        VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);
        // KN_PRINT_VR64(VR_y);
        load8x2_vr_postI(VR_A, pA, INC1);
        load32x2_vr_postR(VR_x, pX, nextIn);
      }

      convert_IEEE_float_to_32F_x2(VR_x);
      convert_16I_to_32F_x2(VR_A, wBlkExp);

      VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);

      // KN_PRINT_VR64(VR_y);
      load_32x2_vr_a(VR_bias, UR_b, pBias);

      // KN_PRINT_VR64(VR_bias);
      convert_IEEE_float_to_32F_x2(VR_bias);

      if (scale_ptr) {
        load32x2_vr_postI(VR_scale, pScalePerCh, INC1);
      }
      // KN_PRINT_VR64(VR_scale);
      VR_y = vmuls(VR_scale, VR_y, 0);  // scale up
      VR_out = vadds(VR_y, VR_bias, 0);
      // KN_PRINT_VR64(VR_out);
      VR_out = vmax(VR_min, VR_out);
      VR_out = vmin(VR_max, VR_out);
      // KN_PRINT_VR64(VR_out);
      convert_32F_to_IEEE_float_x2(VR_out);
      store_32x2_vr_a(VR_out, UR_out, pDst);
    }
  }
  flush_32x2(UR_out, pDst);
  return 0;
}

static int DepthWiseConvFloat16KernelVIP(float *x, const TfLiteFloat16 *A,
                                         const float *bias, float *output,
                                         int m, int n, const AScalar &act_min,
                                         const AScalar &act_max) {
  const float *pBias = bias;
  int loopLimRow = (m >> 1);

  float *pDst = output;
  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  vr64 VR_max, VR_min;
  int nextIn = m >> 1;
  TF_LITE_ASSERT((m & 1) == 0);

  ulsr32 UR_b = align_32x2_load(pBias);
  ulsr32 UR_out = align_32x2_store(pDst);

  replicate_ar(VR_max, 0x3, act_max.fr);
  replicate_ar(VR_min, 0x3, act_min.fr);
  {
    for (int i = 0; i < loopLimRow; i++) {
      const float *pX = x + i * 2;
      const TfLiteFloat16 *pA = (TfLiteFloat16 *)A + i * 2 * n;

      // ulsr128 UR_A = align_16x4_load(pA);
      VR_y = vseta_vr(0, 0);
      vr64 VR_out, VR_bias;

      load16x2_vr_postI(VR_A, pA, INC1);

      load32x2_vr_postR(VR_x, pX, nextIn);

      for (int j = 0; j < n - 1; j++) {
        convert_IEEE_float_to_32F_x2(VR_x);
        convert_16F_to_32F_x2(VR_A, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
        VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);
        load16x2_vr_postI(VR_A, pA, INC1);
        load32x2_vr_postR(VR_x, pX, nextIn);
      }

      convert_IEEE_float_to_32F_x2(VR_x);
      convert_16F_to_32F_x2(VR_A, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);

      VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);

      load_32x2_vr_a(VR_bias, UR_b, pBias);
      convert_IEEE_float_to_32F_x2(VR_bias);

      VR_out = vadds(VR_y, VR_bias, 0);

      VR_out = vmax(VR_min, VR_out);
      VR_out = vmin(VR_max, VR_out);

      convert_32F_to_IEEE_float_x2(VR_out);
      store_32x2_vr_a(VR_out, UR_out, pDst);
    }
  }
  flush_32x2(UR_out, pDst);
  return 0;
}
static int DepthWiseConvFloatKernelVIP(float *x, const float *A,
                                       const float *bias, float *output, int m,
                                       int n, const AScalar &act_min,
                                       const AScalar &act_max) {
  //  const float *pA = A;
  //  const float *pX;
  const float *pBias = bias;
  //  int loopLimCol = (n >> 2);    // block 16
  int loopLimRow = (m >> 1);
  //  int remainRow= m & 3;

  float *pDst = output;

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  vr64 VR_max, VR_min;
  int nextIn = m >> 1;
  TF_LITE_ASSERT((m & 1) == 0);

  ulsr32 UR_b = align_32x2_load(pBias);
  ulsr32 UR_out = align_32x2_store(pDst);

  replicate_ar(VR_max, 0x3, act_max.fr);
  replicate_ar(VR_min, 0x3, act_min.fr);

  // KN_PRINTD(nextIn);
  // filter index:
  //
  //  for(int g = 0; g < loopLimRow; g++)
  {
    //  ulsr128 UR_out = align_32x4_store(pDst);
    for (int i = 0; i < loopLimRow; i++) {
      const float *pX = x + i * 2;
      const float *pA = A + i * 2 * n;

      ulsr32 UR_A = align_32x2_load(pA);
      VR_y = vseta_vr(0, 0);
      vr64 VR_out, VR_bias;
      load_32x2_vr_a(VR_A, UR_A, pA);
      load32x2_vr_postR(VR_x, pX, nextIn);

      for (int j = 0; j < n - 1; j++) {
        convert_IEEE_float_to_32F_x2(VR_x);
        convert_IEEE_float_to_32F_x2(VR_A);
        VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);
        load_32x2_vr_a(VR_A, UR_A, pA);  //, nextIn);
        load32x2_vr_postR(VR_x, pX, nextIn);
      }

      convert_IEEE_float_to_32F_x2(VR_x);
      convert_IEEE_float_to_32F_x2(VR_A);
      VR_y = vmacs(VR_y, VR_x, VR_A, 0, 0);

      load_32x2_vr_a(VR_bias, UR_b, pBias);  //, INC1);
      convert_IEEE_float_to_32F_x2(VR_bias);
      VR_out = vadds(VR_y, VR_bias, 0);

      VR_out = vmax(VR_min, VR_out);
      VR_out = vmin(VR_max, VR_out);
      //  KN_PRINT_VR(VR_out);
      convert_32F_to_IEEE_float_x2(VR_out);
      store_32x2_vr_a(VR_out, UR_out, pDst);  //, INC1, VRQ0);
    }
  }
  flush_32x2(UR_out, pDst);
  return 0;
}

int DepthWiseConvKernel8xn(const int32_t *x, const int32_t *pAinput,
                           int32_t *pScratchSrc, int32_t *inputOffsetWithW,
                           int m, int n, int multSigns) {
#ifdef KN_DEBUG
  if ((m & 3) != 0) return NULL;

  CHECK_ALIGN_4(x);
  CHECK_ALIGN_4(pAinput);
  CHECK_ALIGN_16(pScratchSrc);
#endif
  const int8_t *pX = (int8_t *)x;
  // const int8_t *pAct2 = (int8_t*)x +m;

  uint32_t *pTempVBPtr = nullptr;  // = tempVB;
  int m2 = m >> 2;                 // 32x2 8

  int32_t *pDst = pScratchSrc;
  uint32_t *pBitArrays2 = nullptr;  // = (uint32_t *)bytearray_hmd;

  vr64 VR_yTmp;
  vr64 VR_x0;  // , VR_x2;
  vr64 VR_acc, VR_x, VR_coeff;
  atbool signSpec = atbool(multSigns);
  // ulsr128 UR_x;
  int32_t *pA1 = (int32_t *)pAinput;
  ulsr32 UR_A = align_32x2_load(pA1);

  // int loopCount = 4;
  int n8 = n >> 3;
  int32_t *inputOffsetW = inputOffsetWithW;
  if (inputOffsetWithW == nullptr) {
    VR_acc = vseta_vr(0, 0);
    mov_AccExtend_vr(VR_acc);
  } else {
    load32x2_vr_postI(VR_acc, inputOffsetW, INC1);
    load32x2_vr_postI(VR_x0, inputOffsetW, INC1);
    mov_AccExtend_vr(VR_x0);
  }
  for (int jj = 0; jj < n8; jj++) {
    set_BB_vrVB67_zero();
    pTempVBPtr = tempVB;  //
    load32x1_vr_postR(VR_yTmp, pX, m2,
                      VRL);  // load Y Temp, move in the loop boday
    load32x1_vr_postR(VR_yTmp, pX, m2, VRH);  // VR16

    // split into 32x2, 32x2..
    load32x1_vr_postR(VR_x0, pX, m2, VRL);
    load32x1_vr_postR(VR_x0, pX, m2, VRH);
    store32x2_vr_postI(VR_x0, pTempVBPtr, INC1);

    load32x1_vr_postR(VR_x0, pX, m2, VRL);
    load32x1_vr_postR(VR_x0, pX, m2, VRH);
    store32x2_vr_postI(VR_x0, pTempVBPtr, INC1);

    load32x1_vr_postR(VR_x0, pX, m2, VRL);
    load32x1_vr_postR(VR_x0, pX, m2, VRH);
    store32x2_vr_postI(VR_x0, pTempVBPtr, INC1);

    pTempVBPtr = tempVB;
    load_VB1_postI(pTempVBPtr, INC1);
    load_VB2_postI(pTempVBPtr, INC1);
    load_VB3_postI(pTempVBPtr, INC1);

    VR_x = vexp_adji(VR_yTmp, 0);
    WUR_MvmAux(0);
    pBitArrays2 = (uint32_t *)bytearray_hmd;
    load_BB0_postI(pBitArrays2, INC1);
    load_BB1_postI(pBitArrays2, INC1);

    load_32x2_vr_a(VR_coeff, UR_A, pA1);
    // 16*3
    // for (int i = 0; i < loopCount - 1; i++) {
    mac8bx8b_sparse(VR_acc, VR_coeff, VR_x, signSpec);
    load_32x2_vr_a(VR_coeff, UR_A, pA1);

    mac8bx8b_sparse(VR_acc, VR_coeff, VR_x, signSpec);
    load_32x2_vr_a(VR_coeff, UR_A, pA1);

    mac8bx8b_sparse(VR_acc, VR_coeff, VR_x, signSpec);
    load_32x2_vr_a(VR_coeff, UR_A, pA1);
    //}
    mac8bx8b_sparse(VR_acc, VR_coeff, VR_x, signSpec);
  }
  // if(filter_size&1)
  {
    VR_x = vseta_vr(0, 0);
    for (int i = 0; i < (n & 7); i++) {
      WUR_MvmAux(0);
      set_BB_vrVB67_zero();
      load32x1_vr_postR(VR_x, pX, m2, VRL);  // load column 8
      pBitArrays2 = (uint32_t *)bytearray_hmd;
      load_BB0_postI(pBitArrays2, INC1);
      load_BB1_postI(pBitArrays2, INC1);
      // load_BB2_postI(pBitArrays2, INC1);
      // load_BB3_postI(pBitArrays2, INC1);
      // VR_x = vseta_vr(0, 0, 0); //High part 0, 8 x1 only
      load32x1_vr_postI(VR_coeff, pA1, INC1, VRQ0);
      // load32x1_vr_postI(VR_coeff, pA1, INC1, VRQ1);
      mac8bx8b_sparse(VR_acc, VR_coeff, VR_x, signSpec);
    }

    store32x2_vr_postI(VR_acc, pDst, INC1);
    store_AccExtend_postI(pDst, INC1);
  }

  return 0;  // (unsigned)pA1 - (unsigned)pAinput; //stride of A
}
int DepthWiseConvApplyOffsetPerCh(
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
  vr64 VR_q7_out;

  vr64 VR_out;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);

  vr64 VR_outOffset;

  replicate_ar(VR_outOffset, 0x3, outOffsetFr32.fr);
  ulsr32 UR_outMultPerCh = align_32x2_load(pOutMultiplerFr32);

  uint32_t groupOfChannel = (uint32_t)output_depth >> 1;
  if (groupOfChannel > 0) {
    load_32x2_vr_a(VR_outMultPerCh, UR_outMultPerCh, pOutMultiplerFr32);
    load_32x2_vr_a(VR_b0, UR_b, pB);
    load_32x2_vr_a(VR_y, UR_Dst, pDst);
    convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
    convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
    for (uint32_t group = 0; group < groupOfChannel - 1; group++) {
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
    // VR_out = vexp_adji(VR_out, 8);

    convert_32F_to_16I_x2(VR_out, (unsigned int)1 - 8, 1);
    rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
    // accExt

    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
    store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
    store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
  }

  if (output_depth & 1) {
    // load_32x4_vr_a(VR_y, UR_Dst, pDst);
    load32x1_vr_postI(VR_y, pDst, INC1, VRQ0);
    load32x1_vr_postI(VR_b0, pB, INC1, VRQ0);
    load32x1_vr_postI(VR_outMultPerCh, pOutMultiplerFr32, INC1, VRQ0);
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
int DepthWiseConvSparseInt8PerCh(
    int32_t *x, const int32_t *A, const AScalar *bias, int8_t *output,
    int channel, int filter_dim, int32_t *inputOffsetW,
    const AScalar &outOffsetFr32,
    const AScalar *pOutMultiplerFr32,  // array output channel
    int32_t *pScratch, int signs) {
  int m = (((channel + 3) >> 2) << 2);
  // int n = channel * 2;
  // uint32_t *scratch = pingPong;
  const int32_t *AInput = (const int32_t *)A;

  int filter_dim_align2 = (((filter_dim + 1) >> 1)
                           << 1);  // to align next block input A is 16 bytes,
                                   // unaligned load can ignore alignment
  for (int g = 0; g<m> > 2; g++) {
    // output 8 of n input
    int32_t *scratchPerGroup = pScratch + 4 * g;
    int8_t *pBuffer = (int8_t *)x + (g)*4;  // +f*nPerFilter*channel;
    int8_t *pKernel = (int8_t *)AInput + 4 * filter_dim_align2 * g;
    int32_t *inputOffsetGroup =
        (inputOffsetW == nullptr) ? 0 : inputOffsetW + g * 4;
    DepthWiseConvKernel8xn((int32_t *)pBuffer, (const int32_t *)pKernel,
                           (int32_t *)scratchPerGroup, inputOffsetGroup, m,
                           filter_dim, signs);
  }
  //  KN_PRINT_Q31_SIZE(pScratch, channel);

  DepthWiseConvApplyOffsetPerCh(output, pScratch, bias, channel, outOffsetFr32,
                                pOutMultiplerFr32, signs);
  return 0;
}
// DepthWiseConvQuantizedInt8PerCh HMD
int DepthWiseConvQuantizedInt8PerChInputOffset(
    int32_t *x, const int32_t *A, const AScalar *bias, int8_t *output, int m,
    int n, const AScalar &outOffsetFr32,
    // uint32_t input_offset,             // minus - zero_point
    int32_t *inputOffsetWithW,
    const AScalar *pOutMultiplerFr32,  // array output channel
    int32_t *pScratch, int signs) {
  const int32_t *pA = A;
  const int32_t *pX;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
  int32_t *pDst = pScratch;

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  atbool signSpec = atbool(signs);
  // atbool signSpecInput = atbool(3);
  int32_t *inputOffsetW = inputOffsetWithW;
  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x4_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0) {
    return -1;
  }

  for (int i = 0; i < loopLimRow; i++) {
    // VR_y = vseta_vr(0, 0);
    // mov_AccExtend_vr(VR_y);
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
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    store32x2_vr_postI(VR_y, pDst, INC1);
    store_AccExtend_postI(pDst, INC1);

    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 8/4 = 2;
  }

  DepthWiseConvApplyOffsetPerCh(output, pScratch, bias, m, outOffsetFr32,
                                pOutMultiplerFr32, signs);
  return 0;
}

#endif

#if defined(HEMILITE_DW_CONV_OPT)

void DepthwiseConvFloatInt8VIP(TfLiteDepthwiseConvParams *params,
                               const DSConvOpData *data,
                               const float *input_data,
                               const int8_t *filter_data,
                               const float *bias_data, float *output_data,
                               int w_mapped_type = 0)

{
  const ds_conv2d_layer_t &ds_conv2d = data->ds_conv2d;

  int inFCM = 0;
  int inFCN = 0;

  float *pBuffer = (float *)ds_conv2d.pIm2Col;
  //  float *pOutput = (float *)ds_conv2d.pOutput;
  float *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = ds_conv2d.ker_x;
  int32_t dim_im_in_x = ds_conv2d.in_x;
  int32_t ch_im_in = ds_conv2d.in_ch;
  AScalar act_min, act_max;
  // const int dbg_idx = -10;//309/inFCM;
  uint16_t dilation_y = ds_conv2d.dilation_y;
  uint16_t dilation_x = ds_conv2d.dilation_x;
  // float output_activation_min, output_activation_max;
  CalculateActivationRangeAflt(params->activation, &act_min, &act_max);

  AScalar filter_scale = data->filter_scale;

  KN_PRINTAFLT(act_max);
  KN_PRINTAFLT(act_min);
  KN_PRINTD(w_mapped_type);
  {
    int BlkSize = ds_conv2d.ker_x * ds_conv2d.ker_y *
                  ds_conv2d.in_ch;           // im2col buffer sizel
    if (w_mapped_type == DS_CONV_OPT_TYPE2)  // VIP
    {
      inFCM = ds_conv2d.in_ch;  //
      inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y;

    } else  // if(w_mapped_type == DS_CONV_OPT_TYPE1)
    {
      inFCM = ds_conv2d.in_ch * ds_conv2d.ch_mult;
      inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y * ds_conv2d.in_ch;
    }
    KN_PRINTD(inFCM);
    KN_PRINTD(inFCN);
    AScalar *scale_per_channel =
        (AScalar *)data->ConvOp.per_channel_output_multiplier;
    if (scale_per_channel) {
      KN_PRINT_AFLOAT(scale_per_channel, inFCM);
    }
    for (int i_out_y = 0; i_out_y < ds_conv2d.out_y; ++i_out_y) {
      for (int i_out_x = 0; i_out_x < ds_conv2d.out_x; ++i_out_x) {
        int offset_im_src, offset_im_dst;
        int len_cpy_x, len_cpy_y;

        im2col_idx im2col_tab_2;
        int padding =
            tflite::ConvIm2ColIndex(ds_conv2d, i_out_x, i_out_y, &im2col_tab_2);
        len_cpy_y = im2col_tab_2.cpy_len_y;
        len_cpy_x = im2col_tab_2.cpy_len_x;
        offset_im_dst = im2col_tab_2.im_dst_offset;
        offset_im_src = im2col_tab_2.im_src_offset;

        if (!padding) {
          tflite::block_fill_words((int32_t *)pBuffer, 0, BlkSize);
        }

        tflite::im2col_padding_align4<float>(
            pBuffer + offset_im_dst, (const float *)input_data + offset_im_src,
            dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in,
            dilation_y, dilation_x);
        if (w_mapped_type == DS_CONV_OPT_TYPE2)  // VIP
        {
          KN_PRINT_FLOAT(pBuffer, inFCN);
          DepthWiseConvFloatInt8KernelVIP(
              (float *)pBuffer, (const int8_t *)filter_data, filter_scale,
              (const float *)bias_data, (float *)&outBuf[outBufIdx * inFCM],
              inFCM, inFCN, act_min, act_max, scale_per_channel);
          KN_PRINT_FLOAT(&outBuf[outBufIdx * inFCM], inFCM);
        } else {
          DepthWiseConvFloatInt8Kernel(
              (float *)pBuffer, (const int8_t *)filter_data, filter_scale,
              (const float *)bias_data, (float *)&outBuf[outBufIdx * inFCM],
              inFCM, inFCN, act_min, act_max, scale_per_channel);
        }
        outBufIdx += 1;
      }
    }
  }
}

void DepthwiseConvFloat16VIP(TfLiteDepthwiseConvParams *params,
                             const DSConvOpData *data, const float *input_data,
                             const TfLiteFloat16 *filter_data,
                             const float *bias_data, float *output_data,
                             int w_mapped_type = 0)

{
  const ds_conv2d_layer_t &ds_conv2d = data->ds_conv2d;

  int inFCM = 0;
  int inFCN = 0;

  float *pBuffer = (float *)ds_conv2d.pIm2Col;
  //  float *pOutput = (float *)ds_conv2d.pOutput;
  float *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = ds_conv2d.ker_x;
  int32_t dim_im_in_x = ds_conv2d.in_x;
  int32_t ch_im_in = ds_conv2d.in_ch;
  AScalar act_min, act_max;
  // const int dbg_idx = -10;//309/inFCM;
  uint16_t dilation_y = ds_conv2d.dilation_y;
  uint16_t dilation_x = ds_conv2d.dilation_x;
  // float output_activation_min, output_activation_max;
  CalculateActivationRangeAflt(params->activation, &act_min, &act_max);

  AScalar filter_scale = data->filter_scale;

  {
    int BlkSize = ds_conv2d.ker_x * ds_conv2d.ker_y *
                  ds_conv2d.in_ch;           // im2col buffer sizel
    if (w_mapped_type == DS_CONV_OPT_TYPE2)  // VIP
    {
      inFCM = ds_conv2d.in_ch;  //
      inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y;

    } else  // if(w_mapped_type == DS_CONV_OPT_TYPE1)
    {
      inFCM = ds_conv2d.in_ch * ds_conv2d.ch_mult;
      inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y * ds_conv2d.in_ch;
    }
    for (int i_out_y = 0; i_out_y < ds_conv2d.out_y; ++i_out_y) {
      for (int i_out_x = 0; i_out_x < ds_conv2d.out_x; ++i_out_x) {
        int offset_im_src, offset_im_dst;
        int len_cpy_x, len_cpy_y;

        im2col_idx im2col_tab_2;
        int padding =
            tflite::ConvIm2ColIndex(ds_conv2d, i_out_x, i_out_y, &im2col_tab_2);
        len_cpy_y = im2col_tab_2.cpy_len_y;
        len_cpy_x = im2col_tab_2.cpy_len_x;
        offset_im_dst = im2col_tab_2.im_dst_offset;
        offset_im_src = im2col_tab_2.im_src_offset;

        if (!padding) {
          tflite::block_fill_words((int32_t *)pBuffer, 0, BlkSize);
        }

        tflite::im2col_padding_align4<float>(
            pBuffer + offset_im_dst, (const float *)input_data + offset_im_src,
            dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in,
            dilation_y, dilation_x);

        if (w_mapped_type == DS_CONV_OPT_TYPE2) {
          DepthWiseConvFloat16KernelVIP(
              (float *)pBuffer, (const TfLiteFloat16 *)filter_data,
              (const float *)bias_data, (float *)&outBuf[outBufIdx * inFCM],
              inFCM, inFCN, act_min, act_max);
        } else {
          DepthWiseConvFloat16Kernel(
              (float *)pBuffer, (const TfLiteFloat16 *)filter_data,
              (const float *)bias_data, (float *)&outBuf[outBufIdx * inFCM],
              inFCM, inFCN, act_min, act_max);
        }
        outBufIdx += 1;
      }
    }
  }
}
void DepthwiseConvFloatVIP(TfLiteDepthwiseConvParams *params,
                           const DSConvOpData *data, const float *input_data,
                           const float *filter_data, const float *bias_data,
                           float *output_data, int w_mapped_type = 0)

{
  const ds_conv2d_layer_t &ds_conv2d = data->ds_conv2d;

  //  const AScalar *outputMultiplerPerCh =
  //    (const AScalar *)
  //       data->per_channel_output_multiplier;  // data->outputMultiplerPerCh;
  // const AScalar &outputOffset = data->outputOffset;
  int inFCM = 0;
  int inFCN = 0;
  //  int inFCN16Size = 0;

  float *pBuffer = (float *)ds_conv2d.pIm2Col;
  //  float *pOutput = (float *)ds_conv2d.pOutput;
  float *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = ds_conv2d.ker_x;
  int32_t dim_im_in_x = ds_conv2d.in_x;
  int32_t ch_im_in = ds_conv2d.in_ch;
  AScalar act_min, act_max;
  // const int dbg_idx = -10;//309/inFCM;
  uint16_t dilation_y = ds_conv2d.dilation_y;
  uint16_t dilation_x = ds_conv2d.dilation_x;
  // float output_activation_min, output_activation_max;
  CalculateActivationRangeAflt(params->activation, &act_min, &act_max);

  {
    int BlkSize = ds_conv2d.ker_x * ds_conv2d.ker_y *
                  ds_conv2d.in_ch;           // im2col buffer sizel
    if (w_mapped_type == DS_CONV_OPT_TYPE2)  // VIP
    {
      inFCM = ds_conv2d.in_ch;  //
      inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y;

    } else  // if(w_mapped_type == DS_CONV_OPT_TYPE1)
    {
      inFCM = ds_conv2d.in_ch * ds_conv2d.ch_mult;
      inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y * ds_conv2d.in_ch;
    }

    for (int i_out_y = 0; i_out_y < ds_conv2d.out_y; ++i_out_y) {
      for (int i_out_x = 0; i_out_x < ds_conv2d.out_x; ++i_out_x) {
        int offset_im_src, offset_im_dst;
        int len_cpy_x, len_cpy_y;

        im2col_idx im2col_tab_2;
        int padding =
            tflite::ConvIm2ColIndex(ds_conv2d, i_out_x, i_out_y, &im2col_tab_2);
        len_cpy_y = im2col_tab_2.cpy_len_y;
        len_cpy_x = im2col_tab_2.cpy_len_x;
        offset_im_dst = im2col_tab_2.im_dst_offset;
        offset_im_src = im2col_tab_2.im_src_offset;

        if (!padding) {
          tflite::block_fill_words((int32_t *)pBuffer, 0, BlkSize);
        }

        tflite::im2col_padding_align4<float>(
            pBuffer + offset_im_dst, (const float *)input_data + offset_im_src,
            dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in,
            dilation_y, dilation_x);
        if (w_mapped_type == DS_CONV_OPT_TYPE2) {
          DepthWiseConvFloatKernelVIP(
              (float *)pBuffer, (const float *)filter_data,
              (const float *)bias_data, (float *)&outBuf[outBufIdx * inFCM],
              inFCM, inFCN, act_min, act_max);
        } else {
          DepthWiseConvFloatKernel((float *)pBuffer, (const float *)filter_data,
                                   (const float *)bias_data,
                                   (float *)&outBuf[outBufIdx * inFCM], inFCM,
                                   inFCN, act_min, act_max);
        }
        outBufIdx += 1;
      }
    }
  }
}

#if 0
static void DepthwiseConvFloat(TfLiteDepthwiseConvParams *params,
                               const DSConvOpData *data, const float *input_data,
                               const float *filter_data, const float *bias_data,
                               float *output_data)

{
  const ds_conv2d_layer_t &ds_conv2d = data->ds_conv2d;

  //  const AScalar *outputMultiplerPerCh =
  //    (const AScalar *)
  //       data->per_channel_output_multiplier;  // data->outputMultiplerPerCh;
  // const AScalar &outputOffset = data->outputOffset;
  int inFCM = 0;
  int inFCN = 0;
  //  int inFCN16Size = 0;

  float *pBuffer = (float *)ds_conv2d.pIm2Col;
  //  float *pOutput = (float *)ds_conv2d.pOutput;
  float *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = ds_conv2d.ker_x;
  int32_t dim_im_in_x = ds_conv2d.in_x;
  int32_t ch_im_in = ds_conv2d.in_ch;
  AScalar act_min, act_max;
  uint16_t dilation_y = ds_conv2d.dilation_y;
  uint16_t dilation_x = ds_conv2d.dilation_x;

  // float output_activation_min, output_activation_max;
  CalculateActivationRangeAflt(params->activation, &act_min, &act_max);
  KN_PRINTAFLT(act_min);
  KN_PRINTAFLT(act_max);
  //  uint32_t input_offset = (ds_conv2d.input_offset == 128) ? 0x80808080 :
  //  0x0;
  // if (data->opt_constraint_float == 1)
  {
    inFCM = ds_conv2d.in_ch * ds_conv2d.ch_mult;
    inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y * ds_conv2d.in_ch;
    //  int inFCNA4 = (((inFCN + 3) >> 2) << 2);
    // inFCN16Size = ((inFCNA4) + 15) / 16;

    KN_PRINTD(inFCM);
    KN_PRINTD(inFCN);
    for (int i_out_y = 0; i_out_y < ds_conv2d.out_y; ++i_out_y) {
      for (int i_out_x = 0; i_out_x < ds_conv2d.out_x; ++i_out_x) {
        int offset_im_src, offset_im_dst;
        int len_cpy_x, len_cpy_y;

        im2col_idx im2col_tab_2;
        int padding =
            tflite::ConvIm2ColIndex(ds_conv2d, i_out_x, i_out_y, &im2col_tab_2);
        len_cpy_y = im2col_tab_2.cpy_len_y;
        len_cpy_x = im2col_tab_2.cpy_len_x;
        offset_im_dst = im2col_tab_2.im_dst_offset;
        offset_im_src = im2col_tab_2.im_src_offset;
        if (!padding) {
          tflite::block_fill_words((int32_t *)pBuffer, 0, inFCN);
        }

        tflite::im2col_padding_align4<float>(
            pBuffer + offset_im_dst, (const float *)input_data + offset_im_src,
            dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in, dilation_y, dilation_x);

        //KN_PRINT_FLOAT(pBuffer, inFCN);
        DepthWiseConvFloatKernel((float *)pBuffer, (const float *)filter_data,
                                 (const float *)bias_data,
                                 (float *)&outBuf[outBufIdx * inFCM], inFCM,
                                 inFCN, act_min, act_max);

        //KN_PRINT_FLOAT(&outBuf[outBufIdx * inFCM], inFCM);
        outBufIdx += 1;
      }
    }
  }
}
#endif
static void DepthwiseConvPerChannelPadding(DSConvOpData *data_ex,
                                           const int8_t *input_data,
                                           const int8_t *filter_data,
                                           const int32_t *bias_data,
                                           int8_t *output_data, int sign)

{
  // DSConvOpData *data_ex = static_cast<DSConvOpData *>(node->user_data);
  OpDataConv *data = static_cast<OpDataConv *>(&data_ex->ConvOp);

  constexpr int group = 4;
  constexpr int shift = 2;

  const ds_conv2d_layer_t &ds_conv2d = data_ex->ds_conv2d;

  const AScalar *outputMultiplerPerCh =
      (const AScalar *)
          data->per_channel_output_multiplier;  // data->outputMultiplerPerCh;
  const AScalar &outputOffset = data_ex->outputOffset;
  int inFCM = 0;
  int inFCN = 0;
  int inFCN16Size = 0;

  int8_t *pBuffer = (int8_t *)ds_conv2d.pIm2Col;
  int32_t *pOutput = (int32_t *)ds_conv2d.pOutput;
  int8_t *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = ds_conv2d.ker_x;
  int32_t dim_im_in_x = ds_conv2d.in_x;
  int32_t ch_im_in = ds_conv2d.in_ch;
  uint16_t dilation_y = ds_conv2d.dilation_y;
  uint16_t dilation_x = ds_conv2d.dilation_x;
  // input_offset;
  if (data_ex->opt_constraint == DEPTHWISE_CONV_OPT_MAC8Bx8B) {
    // int ch_align = (((ds_conv2d.out_ch + group - 1) >> shift) << shift);
    inFCM = ds_conv2d.in_ch * ds_conv2d.ch_mult;
    // int in_ch_align = (ds_conv2d.in_ch & (group - 1)) == 0;
    // inFCM = ch_align;                           //
    inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y * ds_conv2d.in_ch;
    int inFCNA4 = (((inFCN + 3) >> 2) << 2);
    inFCN16Size = ((inFCNA4) + 15) / 16;

    uint32_t input_offset_neg;
    uint32_t input_offset;
    int32_t *inputOffsetWithW = data_ex->inputOffsetWithW;
    if (inputOffsetWithW == nullptr) {
      input_offset = (ds_conv2d.input_offset == 128) ? 0x80808080 : 0x0;
      input_offset_neg = 0;
    } else {
      input_offset = 0;
      input_offset_neg = (data_ex->input_offset_int8_neg);
    }

    for (int i_out_y = 0; i_out_y < ds_conv2d.out_y; ++i_out_y) {
      for (int i_out_x = 0; i_out_x < ds_conv2d.out_x; ++i_out_x) {
        int offset_im_src, offset_im_dst;
        int len_cpy_x, len_cpy_y;

        im2col_idx im2col_tab_2;
        int padding =
            tflite::ConvIm2ColIndex(ds_conv2d, i_out_x, i_out_y, &im2col_tab_2);
        len_cpy_y = im2col_tab_2.cpy_len_y;
        len_cpy_x = im2col_tab_2.cpy_len_x;
        offset_im_dst = im2col_tab_2.im_dst_offset;
        offset_im_src = im2col_tab_2.im_src_offset;
        if (!padding) {
          tflite::block_fill_words((int32_t *)pBuffer, input_offset_neg,
                                   inFCN16Size * 4);
        }

        tflite::im2col_padding_offset(
            pBuffer + offset_im_dst, (const int8_t *)input_data + offset_im_src,
            dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in,
            input_offset, dilation_y, dilation_x);

        int status = DepthWiseConvQuantizedInt8PerChInputOffset(
            (int32_t *)pBuffer, (const int32_t *)filter_data,
            (const AScalar *)bias_data, &outBuf[outBufIdx * inFCM], inFCM,
            inFCN, outputOffset, inputOffsetWithW, outputMultiplerPerCh,
            pOutput, sign);
        TFLITE_DCHECK(status == 0);
        outBufIdx += 1;
      }
    }
  } else if (data_ex->opt_constraint == DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE) {
    int ch_align = (((ds_conv2d.out_ch + group - 1) >> shift) << shift);

    int in_ch_align = (ds_conv2d.in_ch & (group - 1)) == 0;
    inFCM = ch_align;                           //
    inFCN = ds_conv2d.ker_x * ds_conv2d.ker_y;  // filter_dim without ch
    int inFCNA4 = (((inFCN * inFCM + 3) >> 2) << 2);
    inFCN16Size = ((inFCNA4) + 15) / 16;

    uint32_t input_offset_neg;
    uint32_t input_offset;
    if (data_ex->inputOffsetWithW == nullptr) {
      input_offset = (ds_conv2d.input_offset == 128) ? 0x80808080 : 0x0;
      input_offset_neg = 0;
    } else {
      input_offset = 0;
      input_offset_neg = (data_ex->input_offset_int8_neg);
    }
    for (int i_out_y = 0; i_out_y < ds_conv2d.out_y; ++i_out_y) {
      for (int i_out_x = 0; i_out_x < ds_conv2d.out_x; ++i_out_x) {
        int offset_im_src, offset_im_dst;
        int len_cpy_x, len_cpy_y;

        im2col_ex_idx im2col_tab_2;
        int padding =
            tflite::ConvIm2ColIndex(ds_conv2d, i_out_x, i_out_y, &im2col_tab_2);
        len_cpy_y = im2col_tab_2.cpy_len_y;
        len_cpy_x = im2col_tab_2.len_wo_ch;
        offset_im_dst = im2col_tab_2.dst_offset_wo_ch;
        offset_im_src = im2col_tab_2.src_offset_wo_ch;
        if (!padding) {
          tflite::block_fill_words((int32_t *)pBuffer, input_offset_neg,
                                   inFCN16Size * 4);
        }

#ifdef KN_DEBUG
        // CHECK_ALIGN_4(pBuffer+offset_im_dst);
        // CHECK_ALIGN_4((const int8_t *)input_data +offset_im_src);
        CHECK_ALIGN_4(filter_data);
#endif
        if (in_ch_align) {
          tflite::im2colex_padding_offset_align4(
              pBuffer, offset_im_dst, (const int8_t *)input_data, offset_im_src,
              dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in,
              input_offset, dilation_y, dilation_x);
        } else {
          // not align 8 copy
          // destination offset is multplie of 4
          // KN_ASSERT(input_offset == 0 );
          tflite::im2col_padding_unalign(
              pBuffer, offset_im_dst, (const int8_t *)input_data, offset_im_src,
              dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in,
              ch_align, input_offset, dilation_y, dilation_x);
        }
        {
          DepthWiseConvSparseInt8PerCh(
              (int32_t *)pBuffer, (const int32_t *)filter_data,
              (const AScalar *)bias_data, &outBuf[outBufIdx * ds_conv2d.in_ch],
              ds_conv2d.in_ch, inFCN, data_ex->inputOffsetWithW, outputOffset,
              outputMultiplerPerCh, pOutput, sign);

          outBufIdx += 1;
        }
        // i_out_x_prev = i_out_x;
      }
      // i_out_y_prev = i_out_y;
    }
  }
}

TfLiteStatus DepthwiseConvPerChOpt(TfLiteContext *context, TfLiteNode *node,
                                   TfLiteDepthwiseConvParams *params,
                                   DSConvOpData *data_ex,
                                   const TfLiteEvalTensor *input,
                                   const TfLiteEvalTensor *filter,
                                   const TfLiteEvalTensor *bias,
                                   TfLiteEvalTensor *output) {
  int32_t input_offset = -(data_ex->ConvOp.input_zero_point);

  // get scratch buffer
  int32_t *p_aligned_scratch = nullptr;
  if (0 == data_ex->opt_constraint) {
    return kTfLiteError;
  }
  if (data_ex->buffer_idx > -1) {
    p_aligned_scratch =
        (int32_t *)context->GetScratchBuffer(context, data_ex->buffer_idx);

    if (((uint32_t)p_aligned_scratch & 0xf) != 0)
      p_aligned_scratch =
          (int32_t *)((((uint32_t)p_aligned_scratch + 0xf) >> 4) << 4);
  }
  data_ex->ds_conv2d.pIm2Col = p_aligned_scratch;
  data_ex->ds_conv2d.pOutput =
      (int32_t *)((int8_t *)p_aligned_scratch + data_ex->sizeScratchIm2Col);
  int sign = (input_offset == 128) ? 1 : 3;

  DepthwiseConvPerChannelPadding(
      data_ex, tflite::micro::GetTensorData<int8_t>(input),
      (const int8_t *)data_ex->mapped_filter,
      tflite::micro::GetTensorData<int32_t>(bias),
      tflite::micro::GetTensorData<int8_t>(output), sign);

  // KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
  // ElementCount(*output->dims));
  return kTfLiteOk;
}
#endif
static TfLiteStatus EvalDepthWiseConvQuantizedPerChannel(
    TfLiteContext *context, TfLiteNode *node, TfLiteDepthwiseConvParams *params,
    DSConvOpData *data_ex, const TfLiteEvalTensor *input,
    const TfLiteEvalTensor *filter, const TfLiteEvalTensor *bias,
    TfLiteEvalTensor *output) {
  // Call to reference implementation can be removed when dilation is supported
  // in the optimized implementations.
  TfLiteStatus status = kTfLiteOk;
  OpDataConv *data = static_cast<OpDataConv *>(&data_ex->ConvOp);
  DepthwiseParams op_params;
  op_params.padding_type = PaddingType::kSame;
  op_params.padding_values.width = data->padding.width;
  op_params.padding_values.height = data->padding.height;
  op_params.stride_width = params->stride_width;
  op_params.stride_height = params->stride_height;
  op_params.dilation_width_factor = params->dilation_width_factor;
  op_params.dilation_height_factor = params->dilation_height_factor;
  op_params.depth_multiplier = params->depth_multiplier;
  op_params.input_offset = -data->input_zero_point;
  op_params.weights_offset = 0;
  op_params.output_offset = data->output_zero_point;
  // TODO(b/130439627): Use calculated value for clamping.
  op_params.quantized_activation_min = std::numeric_limits<int8_t>::min();
  op_params.quantized_activation_max = std::numeric_limits<int8_t>::max();

  RuntimeShape filter_shape = tflite::micro::GetTensorShape(filter);
  RuntimeShape input_shape = tflite::micro::GetTensorShape(input);
  RuntimeShape output_shape = tflite::micro::GetTensorShape(output);
  RuntimeShape bias_shape = tflite::micro::GetTensorShape(bias);

  //    const int batch_size = MatchingDim(input_shape, 0, output_shape, 0);
  const int output_depth = MatchingDim(filter_shape, 3, output_shape, 3);
  TFLITE_DCHECK_EQ(bias_shape.FlatSize(), output_depth);

#if defined(HEMILITE_DW_CONV_OPT)
  if (data_ex->opt_constraint) {
    status = DepthwiseConvPerChOpt(context, node, params, data_ex, input,
                                   filter, bias, output);

  } else
#endif
  {
#ifndef REMOVE_REFOP_SUPPORT
    reference_integer_ops::DepthwiseConvPerChannel(
        op_params, data->per_channel_output_multiplier,
        data->per_channel_output_shift, tflite::micro::GetTensorShape(input),
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
  KN_PRINTD(data_ex->opt_constraint);
  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                   ElementCount(*output->dims));
  return status;
}
#ifndef REMOVE_REFOP_SUPPORT
void EvalQuantized(TfLiteContext *context, TfLiteNode *node,
                   TfLiteDepthwiseConvParams *params, const OpDataConv *data,
                   const TfLiteEvalTensor *input,
                   const TfLiteEvalTensor *filter, const TfLiteEvalTensor *bias,
                   TfLiteEvalTensor *output) {
  const int32_t input_offset = -data->input_zero_point;
  const int32_t filter_offset = -data->filter_zero_point;
  const int32_t output_offset = data->output_zero_point;

  tflite::DepthwiseParams op_params;
  // Padding type is ignored, but still set.
  op_params.padding_type = PaddingType::kSame;
  op_params.padding_values.width = data->padding.width;
  op_params.padding_values.height = data->padding.height;
  op_params.stride_width = params->stride_width;
  op_params.stride_height = params->stride_height;
  op_params.dilation_width_factor = params->dilation_width_factor;
  op_params.dilation_height_factor = params->dilation_height_factor;
  op_params.depth_multiplier = params->depth_multiplier;
  op_params.quantized_activation_min = data->output_activation_min;
  op_params.quantized_activation_max = data->output_activation_max;
  op_params.input_offset = input_offset;
  op_params.weights_offset = filter_offset;
  op_params.output_offset = output_offset;
  op_params.output_multiplier = data->output_multiplier;
  // Legacy ops used mixed left and right shifts. Now all are +ve-means-left.
  op_params.output_shift = -data->output_shift;
  // TODO:: support uint8_t

  tflite::reference_ops::DepthwiseConv(
      op_params, tflite::micro::GetTensorShape(input),
      tflite::micro::GetTensorData<uint8_t>(input),
      tflite::micro::GetTensorShape(filter),
      tflite::micro::GetTensorData<uint8_t>(filter),
      tflite::micro::GetTensorShape(bias),
      tflite::micro::GetTensorData<int32_t>(bias),
      tflite::micro::GetTensorShape(output),
      tflite::micro::GetTensorData<uint8_t>(output));
}
#endif

static void EvalFloat(TfLiteContext *context, TfLiteNode *node,
                      TfLiteDepthwiseConvParams *params, DSConvOpData *data_ex,
                      const TfLiteEvalTensor *input,
                      const TfLiteEvalTensor *filter,
                      const TfLiteEvalTensor *bias, TfLiteEvalTensor *output) {
  float output_activation_min, output_activation_max;
  CalculateActivationRange(params->activation, &output_activation_min,
                           &output_activation_max);

#if defined(HEMILITE_DW_CONV_OPT)

  if (data_ex->opt_constraint_float > 0) {
    // get scratch buffer
    int32_t *p_aligned_scratch = nullptr;

    if (data_ex->buffer_idx > -1) {
      p_aligned_scratch =
          (int32_t *)context->GetScratchBuffer(context, data_ex->buffer_idx);

      // p force align up 16 bytes
      if (((uint32_t)p_aligned_scratch & 0xf) != 0)
        p_aligned_scratch =
            (int32_t *)((((uint32_t)p_aligned_scratch + 0xf) >> 4) << 4);
    }
    data_ex->ds_conv2d.pIm2Col = p_aligned_scratch;
    data_ex->ds_conv2d.pOutput = nullptr;

    // KN_PRINTX(data_ex->ds_conv2d.pIm2Col);
  }

  KN_PRINTX(data_ex->opt_constraint_float);
  KN_PRINTD(filter->type);
  if (data_ex->opt_constraint_float > 0) {
    switch (filter->type) {
      case kTfLiteFloat32:
        /*if (data_ex->opt_constraint_float == DS_CONV_OPT_TYPE1) {
            DepthwiseConvFloat(params, data_ex,
                tflite::micro::GetTensorData<float>(input),
                // tflite::micro::GetTensorData<float>(filter),
                (const float*)data_ex->mapped_filter,
                tflite::micro::GetTensorData<float>(bias),
                tflite::micro::GetTensorData<float>(output));
        }
        else if (data_ex->opt_constraint_float == DS_CONV_OPT_TYPE2)
        */
        {
          DepthwiseConvFloatVIP(
              params, data_ex, tflite::micro::GetTensorData<float>(input),
              // tflite::micro::GetTensorData<float>(filter),
              (const float *)data_ex->mapped_filter,
              tflite::micro::GetTensorData<float>(bias),
              tflite::micro::GetTensorData<float>(output),
              data_ex->opt_constraint_float & DS_CONV_OPT_MASK);
        }
        break;

      case kTfLiteInt8:

        if (0 != (data_ex->opt_constraint_float & DS_CONV_OPT_FLT_X_INT8)) {
          KN_PRINT_Q7_SIZE(data_ex->mapped_filter, ElementCount(*output->dims));

          DepthwiseConvFloatInt8VIP(
              params, data_ex, tflite::micro::GetTensorData<float>(input),
              // tflite::micro::GetTensorData<float>(filter),
              (const int8_t *)data_ex->mapped_filter,
              tflite::micro::GetTensorData<float>(bias),
              tflite::micro::GetTensorData<float>(output),
              data_ex->opt_constraint_float & DS_CONV_OPT_MASK);
        }
        break;
      case kTfLiteFloat16:
        if (0 != (data_ex->opt_constraint_float & DS_CONV_OPT_FLT_X_FLT16)) {
          // TBD

          DepthwiseConvFloat16VIP(
              params, data_ex, tflite::micro::GetTensorData<float>(input),
              (const TfLiteFloat16 *)data_ex->mapped_filter,
              tflite::micro::GetTensorData<float>(bias),
              tflite::micro::GetTensorData<float>(output),
              data_ex->opt_constraint_float & DS_CONV_OPT_MASK);
        }
        break;
      default:
        TFLITE_DCHECK(filter->type == kTfLiteFloat32 ||
                      filter->type == kTfLiteInt8 ||
                      filter->type == kTfLiteFloat16);
    }
  } else
#endif
  {
#ifndef REMOVE_REFOP_SUPPORT
    OpDataConv *data = static_cast<OpDataConv *>(&data_ex->ConvOp);
    tflite::DepthwiseParams op_params;
    // Padding type is ignored, but still set.
    op_params.padding_type = PaddingType::kSame;
    op_params.padding_values.width = data->padding.width;
    op_params.padding_values.height = data->padding.height;
    op_params.stride_width = params->stride_width;
    op_params.stride_height = params->stride_height;
    op_params.dilation_width_factor = params->dilation_width_factor;
    op_params.dilation_height_factor = params->dilation_height_factor;
    op_params.depth_multiplier = params->depth_multiplier;
    op_params.float_activation_min = output_activation_min;
    op_params.float_activation_max = output_activation_max;

    tflite::reference_ops::DepthwiseConv(
        op_params, tflite::micro::GetTensorShape(input),
        tflite::micro::GetTensorData<float>(input),
        tflite::micro::GetTensorShape(filter),
        tflite::micro::GetTensorData<float>(filter),
        tflite::micro::GetTensorShape(bias),
        tflite::micro::GetTensorData<float>(bias),
        tflite::micro::GetTensorShape(output),
        tflite::micro::GetTensorData<float>(output));
    //    #else
    //    return kTfLiteError;
#endif
  }

  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                 ElementCount(*output->dims));
}

TfLiteStatus EvalDepthWiseConvFloatInt8(TfLiteContext *context,
                                        TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  auto *params =
      reinterpret_cast<TfLiteDepthwiseConvParams *>(node->builtin_data);
  DSConvOpData &data_ex = *(static_cast<DSConvOpData *>(node->user_data));

  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kDepthwiseConvOutputTensor);
  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kDepthwiseConvInputTensor);
  const TfLiteEvalTensor *filter =
      tflite::micro::GetEvalInput(context, node, kDepthwiseConvWeightsTensor);
  const TfLiteEvalTensor *bias =
      (NumInputs(node) == 3)
          ? tflite::micro::GetEvalInput(context, node, kDepthwiseConvBiasTensor)
          : nullptr;
  TfLiteStatus status = kTfLiteOk;
  float output_activation_min, output_activation_max;
  CalculateActivationRange(params->activation, &output_activation_min,
                           &output_activation_max);
  KN_PRINTD(data_ex.opt_constraint_float);

#if defined(HEMILITE_DW_CONV_OPT)

  if (data_ex.opt_constraint_float > 0) {
    // get scratch buffer
    // KN_PRINTD(data_ex->opt_constraint_float);
    int32_t *p_aligned_scratch = nullptr;

    if (data_ex.buffer_idx > -1) {
      p_aligned_scratch =
          (int32_t *)context->GetScratchBuffer(context, data_ex.buffer_idx);
    }
    data_ex.ds_conv2d.pIm2Col = p_aligned_scratch;
    data_ex.ds_conv2d.pOutput = nullptr;

    // KN_PRINTX(data_ex->ds_conv2d.pIm2Col);
  }
  if (data_ex.opt_constraint_float > 0) {
    switch (filter->type) {
      case kTfLiteInt8:
        if (0 != (data_ex.opt_constraint_float & DS_CONV_OPT_FLT_X_INT8)) {
          DepthwiseConvFloatInt8VIP(
              params, &data_ex, tflite::micro::GetTensorData<float>(input),
              // tflite::micro::GetTensorData<float>(filter),
              (const int8_t *)data_ex.mapped_filter,
              tflite::micro::GetTensorData<float>(bias),
              tflite::micro::GetTensorData<float>(output),
              data_ex.opt_constraint_float & DS_CONV_OPT_MASK);
        }
        break;

      default:
        TFLITE_DCHECK(filter->type == kTfLiteInt8);
    }
  }
#endif
  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                 ElementCount(*output->dims));
  return status;
}

TfLiteStatus EvalDepthWiseConvFloat16(TfLiteContext *context,
                                      TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  auto *params =
      reinterpret_cast<TfLiteDepthwiseConvParams *>(node->builtin_data);
  DSConvOpData &data_ex = *(static_cast<DSConvOpData *>(node->user_data));

  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kDepthwiseConvOutputTensor);
  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kDepthwiseConvInputTensor);
  const TfLiteEvalTensor *filter =
      tflite::micro::GetEvalInput(context, node, kDepthwiseConvWeightsTensor);
  const TfLiteEvalTensor *bias =
      (NumInputs(node) == 3)
          ? tflite::micro::GetEvalInput(context, node, kDepthwiseConvBiasTensor)
          : nullptr;
  TfLiteStatus status = kTfLiteOk;
  float output_activation_min, output_activation_max;
  CalculateActivationRange(params->activation, &output_activation_min,
                           &output_activation_max);
  KN_PRINTD(data_ex.opt_constraint_float);
#if defined(HEMILITE_DW_CONV_OPT)

  if (data_ex.opt_constraint_float > 0) {
    // get scratch buffer
    // KN_PRINTD(data_ex->opt_constraint_float);
    int32_t *p_aligned_scratch = nullptr;

    if (data_ex.buffer_idx > -1) {
      p_aligned_scratch =
          (int32_t *)context->GetScratchBuffer(context, data_ex.buffer_idx);

      if (((uint32_t)p_aligned_scratch & 0xf) != 0)
        p_aligned_scratch =
            (int32_t *)((((uint32_t)p_aligned_scratch + 0xf) >> 4) << 4);
    }
    data_ex.ds_conv2d.pIm2Col = p_aligned_scratch;
    data_ex.ds_conv2d.pOutput = nullptr;

    // KN_PRINTX(data_ex->ds_conv2d.pIm2Col);
  }
  if (data_ex.opt_constraint_float > 0) {
    switch (filter->type) {
      case kTfLiteFloat16:
        if (0 != (data_ex.opt_constraint_float & DS_CONV_OPT_FLT_X_FLT16)) {
          // TBD

          DepthwiseConvFloat16VIP(
              params, &data_ex, tflite::micro::GetTensorData<float>(input),
              (const TfLiteFloat16 *)data_ex.mapped_filter,
              tflite::micro::GetTensorData<float>(bias),
              tflite::micro::GetTensorData<float>(output),
              data_ex.opt_constraint_float & DS_CONV_OPT_MASK);
        }
        break;
      default:
        TFLITE_DCHECK(filter->type == kTfLiteFloat16);
    }
  }

#endif

  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                 ElementCount(*output->dims));

  return status;
}
TfLiteStatus EvalDepthWiseConv(TfLiteContext *context, TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  auto *params =
      reinterpret_cast<TfLiteDepthwiseConvParams *>(node->builtin_data);
  DSConvOpData &data_ex = *(static_cast<DSConvOpData *>(node->user_data));

  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kDepthwiseConvOutputTensor);
  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kDepthwiseConvInputTensor);
  const TfLiteEvalTensor *filter =
      tflite::micro::GetEvalInput(context, node, kDepthwiseConvWeightsTensor);
  const TfLiteEvalTensor *bias =
      (NumInputs(node) == 3)
          ? tflite::micro::GetEvalInput(context, node, kDepthwiseConvBiasTensor)
          : nullptr;
  TfLiteStatus status = kTfLiteOk;
  // TODO(aselle): Consider whether float conv and quantized conv should be
  // separate ops to avoid dispatch overhead here.
  switch (input->type) {  // Already know in/out types are same.

    case kTfLiteFloat32:
      EvalFloat(context, node, params, &data_ex, input, filter, bias, output);
      break;

    case kTfLiteInt8:
      status = EvalDepthWiseConvQuantizedPerChannel(
          context, node, params, &data_ex, input, filter, bias, output);
      break;
#ifndef REMOVE_REFOP_SUPPORT
    case kTfLiteUInt8: {
      OpDataConv &data = data_ex.ConvOp;
      EvalQuantized(context, node, params, &data, input, filter, bias, output);
      break;
    }
#endif
    default:
      TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(input->type), input->type);
      return kTfLiteError;
  }
  return status;
}
TfLiteStatus EvalDepthWiseConvInt8Opt(TfLiteContext *context,
                                      TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  auto *params =
      reinterpret_cast<TfLiteDepthwiseConvParams *>(node->builtin_data);
  DSConvOpData &data_ex = *(static_cast<DSConvOpData *>(node->user_data));

  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kDepthwiseConvOutputTensor);
  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kDepthwiseConvInputTensor);
  const TfLiteEvalTensor *filter =
      tflite::micro::GetEvalInput(context, node, kDepthwiseConvWeightsTensor);
  const TfLiteEvalTensor *bias =
      (NumInputs(node) == 3)
          ? tflite::micro::GetEvalInput(context, node, kDepthwiseConvBiasTensor)
          : nullptr;
  TfLiteStatus status = kTfLiteOk;
  // TODO(aselle): Consider whether float conv and quantized conv should be
  // separate ops to avoid dispatch overhead here.
  if (kTfLiteInt8 != input->type) {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(input->type), input->type);
  }
  status = EvalDepthWiseConvQuantizedPerChannel(context, node, params, &data_ex,
                                                input, filter, bias, output);
  // DepthwiseConvPerChOpt(context, node, params, &data_ex, input, filter, bias,
  // output);
  return status;
}
}  // namespace

TFLMRegistration Register_DEPTHWISE_CONV_2D() {
  return tflite::micro::RegisterOp(Init,
                                   /*prepare=*/Prepare,
                                   /*invoke=*/EvalDepthWiseConv);
}

TFLMRegistration Register_DEPTHWISE_CONV_2D_INT8() {
  return tflite::micro::RegisterOp(Init,
                                   /*prepare=*/PrepareInt8,
                                   /*invoke=*/EvalDepthWiseConvInt8Opt);
}
TFLMRegistration Register_DEPTHWISE_CONV_2D_FLOAT16() {
  return tflite::micro::RegisterOp(Init,

                                   /*prepare=*/Prepare,
                                   /*invoke=*/EvalDepthWiseConvFloat16);
}

TFLMRegistration Register_DEPTHWISE_CONV_2D_FLOATINT8() {
  return tflite::micro::RegisterOp(Init,

                                   /*prepare=*/Prepare,
                                   /*invoke=*/EvalDepthWiseConvFloatInt8);
}
}  // namespace tflite
