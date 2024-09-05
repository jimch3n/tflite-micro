/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

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
#include "tensorflow/lite/micro/kernels/ia8201/lstm_eval.h"

#include <limits>

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/portable_tensor_utils.h"
#include "tensorflow/lite/kernels/internal/reference/fully_connected.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/fully_connected.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/logistic.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/mul.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/tanh.h"
#include "tensorflow/lite/kernels/internal/reference/logistic.h"
#include "tensorflow/lite/kernels/internal/reference/mul.h"
#include "tensorflow/lite/kernels/internal/reference/portable_tensor_utils_impl.h"
#include "tensorflow/lite/kernels/internal/reference/tanh.h"
#include "tensorflow/lite/micro/ia8201/debug_helper.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {

LstmTensors::LstmTensors(TfLiteContext* context, TfLiteNode* node) {
  micro_context_ = GetMicroContext(context);
  // 24 internal tensors. see lstm_shared.h for tensor names
  for (size_t i = 0; i < 24; i++) {
    internal_tensors_[i] = micro_context_->AllocateTempInputTensor(node, i);
  }
  output_tensor_ =
      micro_context_->AllocateTempOutputTensor(node, kLstmOutputTensor);
}

LstmTensors::~LstmTensors() {
  for (size_t i = 0; i < 24; i++) {
    if (internal_tensors_[i] != nullptr) {
      micro_context_->DeallocateTempTfLiteTensor(internal_tensors_[i]);
    }
  }
  micro_context_->DeallocateTempTfLiteTensor(output_tensor_);
}

// Verify the LSTM internal tensor properties (e.g., type checks)
// Input/output/states/fc weights tensors are required for kernel evaulation.
// The state tensors should be variables. Variants of the standard LSTM
// are not supported here, therefore their corresponding tensors should be
// invalid
TfLiteStatus LstmTensors::ValidateTensorStatus(TfLiteContext* context) const {
  // Verify certain tensor properties
  // input tensor
  TF_LITE_ENSURE(context, internal_tensors_[kLstmInputTensor] != nullptr);
  // hidden state
  TF_LITE_ENSURE(context, internal_tensors_[kLstmOutputStateTensor] != nullptr);
  TF_LITE_ENSURE(context,
                 internal_tensors_[kLstmOutputStateTensor]->is_variable);
  // hidden state becomes input so they must have the same type
  TF_LITE_ENSURE_EQ(context, internal_tensors_[kLstmOutputStateTensor]->type,
                    internal_tensors_[kLstmInputTensor]->type);
  // cell state
  TF_LITE_ENSURE(context, internal_tensors_[kLstmCellStateTensor] != nullptr);
  TF_LITE_ENSURE(context, internal_tensors_[kLstmCellStateTensor]->is_variable);
  // output
  TF_LITE_ENSURE(context, output_tensor_ != nullptr);
  // output type is the same as the input type (activations)
  TF_LITE_ENSURE_EQ(context, output_tensor_->type,
                    internal_tensors_[kLstmInputTensor]->type);

  // weight tensors (1-9, see lstm_shared for index definition)
  const auto weight_type =
      internal_tensors_[kLstmInputToForgetWeightsTensor]->type;
  for (size_t i = 1; i < 9; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] != nullptr);
    TF_LITE_ENSURE_EQ(context, internal_tensors_[i]->type, weight_type);
  }

  // bias tensors (12-15, see lstm_shared for index definition)
  const auto bias_type = internal_tensors_[kLstmForgetGateBiasTensor]->type;
  for (size_t i = 12; i < 16; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] != nullptr);
    TF_LITE_ENSURE_EQ(context, internal_tensors_[i]->type, bias_type);
  }
  // Tensors from LSTM variants are invalid
  // No peephole
  for (size_t i = 9; i < 12; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] == nullptr);
  }
  // No projection
  for (size_t i = 16; i < 18; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] == nullptr);
  }
  // No internal layer norm
  for (size_t i = 20; i < 24; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] == nullptr);
  }
  return kTfLiteOk;
}
namespace lstm_internal {
#if !defined(DMX1A_LSTM_OPT) && !defined(HMD1A_LSTM_OPT)
const int32_t kInt16Max = std::numeric_limits<int16_t>::max();
const int32_t kInt16Min = std::numeric_limits<int16_t>::min();
void AddElementWise(const int16_t* input_1, const int16_t* input_2, int n_batch,
                    int n_input, int16_t* output) {

  for (int batch = 0; batch < n_batch; ++batch) {
    for (int i = 0; i < n_input; ++i) {
      const int index = batch * n_input + i;
      int32_t sum = input_1[index] + input_2[index];
      const int32_t sum_clamped = std::min(kInt16Max, std::max(kInt16Min, sum));
      output[index] = static_cast<int16_t>(sum_clamped);
    }
  }
}


#endif
void AddElementWise(const float* input_1, const float* input_2, int n_batch,
                    int n_input, float* output) {
  KN_PRINT_FLOAT(input_1, n_input * n_batch);
  KN_PRINT_FLOAT(input_2, n_input * n_batch);
  for (int batch = 0; batch < n_batch; ++batch) {
    for (int i = 0; i < n_input; ++i) {
      const int index = batch * n_input + i;
      output[index] = input_1[index] + input_2[index];
    }
  }
  KN_PRINT_FLOAT(output, n_input * n_batch);
}
#if defined(DMX1A_LSTM_OPT)

void AddElementWise(const int16_t* input_1, const int16_t* input_2, int n_batch,
                    int n_input, int16_t* output) {

  //  xa_nn_elm_add_16x16_16(output, input_1, input_2, n_batch * n_input);
  // KN_PRINTS("TODO 16+16");
  // for(int ii =0; ii < )
  for (int batch = 0; batch < n_batch; ++batch) {
    const int16_t *in1, *in2;
    int16_t* out;
    const int index = batch * n_input;
    in1 = &input_1[index];
    in2 = &input_2[index];
    out = &output[index];
    int nloop = n_input >> 2;
    int remain = n_input & 3;
    vr128 VR_in1, VR_in2;
    vr128 VR_sum;

    ulsr128 UR_in1 = align_16x4_load(in1);
    ulsr128 UR_in2 = align_16x4_load(in2);
    if (nloop > 0) {
      ulsr128 UR_out = align_16x4_store(out);

      load_16x4_vr_a(VR_in1, UR_in1, in1);
      load_16x4_vr_a(VR_in2, UR_in2, in2);

      for (int i = 0; i < nloop - 1; ++i) {
        convert_16I_to_32F_x4(VR_in1, 0);
        convert_16I_to_32F_x4(VR_in2, 0);
        VR_sum = vadds(VR_in1, VR_in2, 0);
        convert_32F_to_16I_x4(VR_sum, 0, 0);
        store_16x4_vr_a(VR_sum, UR_out, out);

        load_16x4_vr_a(VR_in1, UR_in1, in1);
        load_16x4_vr_a(VR_in2, UR_in2, in2);
      }
      convert_16I_to_32F_x4(VR_in1, 0);
      convert_16I_to_32F_x4(VR_in2, 0);
      VR_sum = vadds(VR_in1, VR_in2, 0);
      convert_32F_to_16I_x4(VR_sum, 0, 0);
      store_16x4_vr_a(VR_sum, UR_out, out);
      flush_16x4(UR_out, out);
    }

    if (remain) {
      load_16x4_vr_a(VR_in1, UR_in1, in1);
      load_16x4_vr_a(VR_in2, UR_in2, in2);

      convert_16I_to_32F_x4(VR_in1, 0);
      convert_16I_to_32F_x4(VR_in2, 0);
      VR_sum = vadds(VR_in1, VR_in2, 0);
      convert_32F_to_16I_x4(VR_sum, 0, 0);
      for (int ii = 0; ii < remain; ii++) {
        store16x1_vr_postI(VR_sum, out, INC1, VRQ0);
        VR_sum = vpermsi(VR_sum, VR_sum, 0, SHR_BY_1_ELEM);
      }
    }
  }


  KN_PRINT_Q15_SIZE(output, n_batch * n_input);
}
#define SIGMOD_EXP (3)
_AI fr32 Sigmoid1(fr32 x) {
  fr32 fac = seta_fr(kConstTable_Log2_Of_e, 0, 0);
  fr32 one = seta_fr(kConstTable_One, 0, 0);
  x = fpmul(fac, x, 1);
  x = pow2_fr(x);
  x = fpadd(one, x, 0);
  x = inv_fr(x);

  return x;
}

void Sigmoid(int16_t* data, int32_t data_size) {
  // ConvertQ15ToAfloat();
  int loopLim = data_size >> 2;  // Includes loop unrolling count of 2
  int remain = data_size & 3;

  int16_t* x = data;
  int16_t* y = data;

  vr128 VR_x0, VR_y0, VR_z0;
  ulsr128 UR_x = align_16x4_load(x);
  ulsr128 UR_y = align_16x4_store(y);
  vr128 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0,
                          0);  // no rounding is consistent with HMD
  vr128 VR_one = vseta_vr(kConstTable_One, 0, 0);

  if (loopLim > 0) {
    load_16x4_vr_a(VR_x0, UR_x, x);
    convert_16I_to_32F_x4(VR_x0, SIGMOD_EXP);

    VR_y0 = vmuls(VR_fac, VR_x0, 0xF);
    for (int i = 0; i < loopLim - 1; i++) {
      pow2(VR_z0, VRQ0, VR_y0, VRQ0);
      pow2(VR_z0, VRQ1, VR_y0, VRQ1);
      pow2(VR_z0, VRQ2, VR_y0, VRQ2);
      pow2(VR_z0, VRQ3, VR_y0, VRQ3);
      VR_z0 = vadds(VR_one, VR_z0, 0);
      load_16x4_vr_a(VR_x0, UR_x, x);
      inv(VR_z0, VRQ0, VR_z0, VRQ0);
      inv(VR_z0, VRQ1, VR_z0, VRQ1);
      inv(VR_z0, VRQ2, VR_z0, VRQ2);
      inv(VR_z0, VRQ3, VR_z0, VRQ3);
      convert_16I_to_32F_x4(VR_x0, SIGMOD_EXP);
      convert_32F_to_16I_x4(VR_z0, 0, 1);  // Q 11
      store_16x4_vr_a(VR_z0, UR_y, y);
      VR_y0 = vmuls(VR_fac, VR_x0, 0xF);
    }
    pow2(VR_z0, VRQ0, VR_y0, VRQ0);
    pow2(VR_z0, VRQ1, VR_y0, VRQ1);
    pow2(VR_z0, VRQ2, VR_y0, VRQ2);
    pow2(VR_z0, VRQ3, VR_y0, VRQ3);
    VR_z0 = vadds(VR_one, VR_z0, 0);

    inv(VR_z0, VRQ0, VR_z0, VRQ0);
    inv(VR_z0, VRQ1, VR_z0, VRQ1);
    inv(VR_z0, VRQ2, VR_z0, VRQ2);
    inv(VR_z0, VRQ3, VR_z0, VRQ3);
    convert_32F_to_16I_x4(VR_z0, 0, 1);
    store_16x4_vr_a(VR_z0, UR_y, y);

    flush_16x4(UR_y, y);
  }

  // Remaining
  for (int i = 0; i < remain; i++) {
    fr32 frx;
    vr128 VR_x;
    load16x1_vr_postI(VR_x, x, INC1, VRQ0);
    convert_16I_to_32F_x4(VR_x, SIGMOD_EXP);
    frx = move32_fr_vr_idx(VR_x, VRQ0);

    fr32 fry = Sigmoid1(frx);
    set_VRQ0(VR_x, fry);
    convert_32F_to_16I_x1(VR_x, 0, 1, VRQ0);
    store16x1_vr_postI(VR_x, y, INC1, VRQ0);
  }

  // xa_nn_vec_sigmoid_sym16s_sym16s(data, data, 0, 0, data_size);
}
static void SigmoidV_Full(float* y, const float* x, int n) {
  int loopLim = n >> 2;  // Includes loop unrolling count of 2
  int remain = n & 3;
  ulsr128 UR_x = align_32x4_load(x);
  ulsr128 UR_y = align_32x4_store(y);
  vr128 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0,
                          0);  // no rounding is consistent with HMD
  vr128 VR_one = vseta_vr(kConstTable_One, 0, 0);
  vr128 VR_x0;

  vr128 VR_y0;

  vr128 VR_z0;

  if (loopLim > 0) {
    load_32x4_vr_a(VR_x0, UR_x, x);

    convert_IEEE_float_to_32F_x4(VR_x0);

    KN_PRINT_VR(VR_x0);

    VR_y0 = vmuls(VR_fac, VR_x0, 0xF);
    // Groups of 8
    for (int i = 0; i < loopLim - 1; i++) {
      pow2(VR_z0, VRQ0, VR_y0, VRQ0);
      pow2(VR_z0, VRQ1, VR_y0, VRQ1);
      pow2(VR_z0, VRQ2, VR_y0, VRQ2);
      pow2(VR_z0, VRQ3, VR_y0, VRQ3);

      VR_z0 = vadds(VR_one, VR_z0, 0);

      load_32x4_vr_a(VR_x0, UR_x, x);

      convert_IEEE_float_to_32F_x4(VR_x0);
      inv(VR_z0, VRQ0, VR_z0, VRQ0);
      inv(VR_z0, VRQ1, VR_z0, VRQ1);
      inv(VR_z0, VRQ2, VR_z0, VRQ2);

      inv(VR_z0, VRQ3, VR_z0, VRQ3);

      KN_PRINT_VR(VR_z0);

      convert_32F_to_IEEE_float_x4(VR_z0);
      store_32x4_vr_a(VR_z0, UR_y, y);
      VR_y0 = vmuls(VR_fac, VR_x0, 0xF);
    }
    pow2(VR_z0, VRQ0, VR_y0, VRQ0);
    pow2(VR_z0, VRQ1, VR_y0, VRQ1);
    pow2(VR_z0, VRQ2, VR_y0, VRQ2);
    pow2(VR_z0, VRQ3, VR_y0, VRQ3);

    VR_z0 = vadds(VR_one, VR_z0, 0);

    inv(VR_z0, VRQ0, VR_z0, VRQ0);
    inv(VR_z0, VRQ1, VR_z0, VRQ1);
    inv(VR_z0, VRQ2, VR_z0, VRQ2);
    inv(VR_z0, VRQ3, VR_z0, VRQ3);

    KN_PRINT_VR(VR_z0);
    convert_32F_to_IEEE_float_x4(VR_z0);
    store_32x4_vr_a(VR_z0, UR_y, y);

    flush_32x4(UR_y, y);
  }
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
}

void Sigmoid(float* data, int32_t data_size) {
  int data_dims[2] = {1, data_size};
  RuntimeShape data_shape(2, reinterpret_cast<const int32_t*>(data_dims));
  SigmoidV_Full(data, data, data_shape.FlatSize());
  // reference_ops::Logistic(data_shape, data, data_shape, data);
  KN_PRINT_FLOAT(data, data_shape.FlatSize());
}

void Sigmoid(const RuntimeShape& data_shape, int16_t* data) {
  //  KN_PRINT_Q15_SIZE(data, data_shape.FlatSize());

  Sigmoid(data, data_shape.FlatSize());
  KN_PRINT_Q15_SIZE(data, data_shape.FlatSize());
}

void Sigmoid(const RuntimeShape& data_shape, float* data) {
  // reference_ops::Logistic(data_shape, data, data_shape, data);

  SigmoidV_Full(data, data, data_shape.FlatSize());
}

_AI fr32 Tanh1(fr32 x) {
  fr32 fac = seta_fr(kConstTable_Log2_Of_e, 0, 0);
  fr32 one = seta_fr(kConstTable_One, 0, 0);
  fr32 two = seta_fr(kConstTable_Two, 0, 0);
  fr32 denumer, numer, inv1;

  fac = fpmul(two, fac, 0);
  x = fpmul(fac, x, 0);
  x = pow2_fr(x);
  denumer = fpadd(one, x, 0);  // exp(2*x) + 1
  numer = fpadd(one, x, 1);    // exp(2*x) -1
  inv1 = inv_fr(denumer);
  // Newton's method
  fpmac(two, inv1, denumer, 1);  // 2 - (x/x)
  inv1 = fpmul(two, inv1, 0);
  x = fpmul(inv1, numer, 0);

  return x;
}
void Tanh(int32_t cell_state_scale_power, int16_t* input_data,
          int16_t* output_data, int32_t data_size) {
  int32_t tanh_input_left_shift = (15 + cell_state_scale_power) - 3;
  // int32_t input_multiplier = 0;
  if (tanh_input_left_shift < 0) /* handling negative shift value */
  {
    tanh_input_left_shift = -tanh_input_left_shift;
  }

  int16_t* x = input_data;
  int16_t* y = output_data;
  int loopLim = data_size >> 2;  // Includes loop unrolling count of 2
  int remain = data_size & 3;
  ulsr128 UR_x = align_16x4_load(x);
  ulsr128 UR_y = align_16x4_store(y);
  vr128 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0, 0);
  vr128 VR_one = vseta_vr(kConstTable_One, 0, 0);
  vr128 VR_two = vseta_vr(kConstTable_Two, 0, 0);

  vr128 VR_x0;
  vr128 VR_y0;
  vr128 VR_z0;
  vr128 VR_n0;
  VR_fac = vmuls(VR_fac, VR_two, 0);

  // Groups of 4
  if (loopLim > 0) {
    vr128 VR_t1;
    load_16x4_vr_a(VR_x0, UR_x, x);
    convert_16I_to_32F_x4(VR_x0, SIGMOD_EXP + tanh_input_left_shift);

    VR_y0 = vmuls(VR_fac, VR_x0, 0);
    for (int i = 0; i < loopLim - 1; i++) {
      pow2(VR_z0, VRQ0, VR_y0, VRQ0);
      pow2(VR_z0, VRQ1, VR_y0, VRQ1);
      pow2(VR_z0, VRQ2, VR_y0, VRQ2);
      pow2(VR_z0, VRQ3, VR_y0, VRQ3);

      VR_n0 = vadds(VR_one, VR_z0, 0xf);  // 1- exp(2*x)
      VR_z0 = vadds(VR_one, VR_z0, 0);    // 1+ exp(2*x)

      load_16x4_vr_a(VR_x0, UR_x, x);

      convert_16I_to_32F_x4(VR_x0, SIGMOD_EXP + tanh_input_left_shift);
      inv(VR_y0, VRQ0, VR_z0, VRQ0);
      inv(VR_y0, VRQ1, VR_z0, VRQ1);
      inv(VR_y0, VRQ2, VR_z0, VRQ2);
      inv(VR_y0, VRQ3, VR_z0, VRQ3);

      // Newton's method
      VR_t1 = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
      VR_y0 = vmuls(VR_t1, VR_y0, 0);

      VR_y0 = vmuls(VR_n0, VR_y0, 0);
      convert_32F_to_16I_x4(VR_y0, 0, 1);
      store_16x4_vr_a(VR_y0, UR_y, y);
      VR_y0 = vmuls(VR_fac, VR_x0, 0);
    }

    pow2(VR_z0, VRQ0, VR_y0, VRQ0);
    pow2(VR_z0, VRQ1, VR_y0, VRQ1);
    pow2(VR_z0, VRQ2, VR_y0, VRQ2);
    pow2(VR_z0, VRQ3, VR_y0, VRQ3);

    VR_n0 = vadds(VR_one, VR_z0, 0xf);  // 1- exp(2*x)
    VR_z0 = vadds(VR_one, VR_z0, 0);    // 1+ exp(2*x)

    inv(VR_y0, VRQ0, VR_z0, VRQ0);

    inv(VR_y0, VRQ1, VR_z0, VRQ1);

    inv(VR_y0, VRQ2, VR_z0, VRQ2);

    inv(VR_y0, VRQ3, VR_z0, VRQ3);

    // Newton's method
    VR_t1 = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
    VR_y0 = vmuls(VR_t1, VR_y0, 0);

    VR_y0 = vmuls(VR_n0, VR_y0, 0);
    convert_32F_to_16I_x4(VR_y0, 0, 1);
    store_16x4_vr_a(VR_y0, UR_y, y);
    flush_16x4(UR_y, y);
  }

  // Remaining
  for (int i = 0; i < remain; i++) {
    // fr32 frx;
    vr128 VR_x0, VR_y0;
    load16x1_vr_postI(VR_x0, x, INC1, VRQ0);

    convert_16I_to_32F_x4(VR_x0, SIGMOD_EXP + tanh_input_left_shift);
    fr32 fry = Tanh1(get_VRQ0(VR_x0));

    set_VRQ0(VR_y0, fry);
    convert_32F_to_16I_x4(VR_y0, 0, 1);
    store16x1_vr_postI(VR_y0, y, INC1, VRQ0);
  }

  // xa_nn_vec_tanh_sym16s_sym16s(output_data, input_data, input_multiplier,
  //                             tanh_input_left_shift, data_size);
}
static void TanhV(float* y, const float* x, int n) {
  int loopLim = n >> 2;  // Includes loop unrolling count of 2
  int remain = n & 3;
  ulsr128 UR_x = align_32x4_load(x);
  ulsr128 UR_y = align_32x4_store(y);
  vr128 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0, 0);
  vr128 VR_one = vseta_vr(kConstTable_One, 0, 0);
  vr128 VR_two = vseta_vr(kConstTable_Two, 0, 0);
  vr128 VR_x0;
  vr128 VR_y0;
  vr128 VR_z0;
  vr128 VR_n0;

  // VR_fac = 2*log2e
  VR_fac = vmuls(VR_fac, VR_two, 0);

  // Groups of 4
  if (loopLim > 0) {
    vr128 VR_t1;
    load_32x4_vr_a(VR_x0, UR_x, x);

    convert_IEEE_float_to_32F_x4(VR_x0);
    VR_y0 = vmuls(VR_fac, VR_x0, 0);
    for (int i = 0; i < loopLim - 1; i++) {
      pow2(VR_z0, VRQ0, VR_y0, VRQ0);
      pow2(VR_z0, VRQ1, VR_y0, VRQ1);
      pow2(VR_z0, VRQ2, VR_y0, VRQ2);
      pow2(VR_z0, VRQ3, VR_y0, VRQ3);

      VR_n0 = vadds(VR_one, VR_z0, 0xf);  // 1- exp(2*x)
      VR_z0 = vadds(VR_one, VR_z0, 0);    // 1+ exp(2*x)

      load_32x4_vr_a(VR_x0, UR_x, x);

      convert_IEEE_float_to_32F_x4(VR_x0);
      inv(VR_y0, VRQ0, VR_z0, VRQ0);
      inv(VR_y0, VRQ1, VR_z0, VRQ1);
      inv(VR_y0, VRQ2, VR_z0, VRQ2);
      inv(VR_y0, VRQ3, VR_z0, VRQ3);

      // Newton's method
      VR_t1 = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
      VR_y0 = vmuls(VR_t1, VR_y0, 0);

      // Newton's method

      VR_y0 = vmuls(VR_n0, VR_y0, 0);

      convert_32F_to_IEEE_float_x4(VR_y0);

      store_32x4_vr_a(VR_y0, UR_y, y);
      VR_y0 = vmuls(VR_fac, VR_x0, 0);
    }

    pow2(VR_z0, VRQ0, VR_y0, VRQ0);
    pow2(VR_z0, VRQ1, VR_y0, VRQ1);
    pow2(VR_z0, VRQ2, VR_y0, VRQ2);
    pow2(VR_z0, VRQ3, VR_y0, VRQ3);

    VR_n0 = vadds(VR_one, VR_z0, 0xf);  // 1- exp(2*x)
    VR_z0 = vadds(VR_one, VR_z0, 0);    // 1+ exp(2*x)

    convert_IEEE_float_to_32F_x4(VR_x0);
    inv(VR_y0, VRQ0, VR_z0, VRQ0);
    inv(VR_y0, VRQ1, VR_z0, VRQ1);
    inv(VR_y0, VRQ2, VR_z0, VRQ2);
    inv(VR_y0, VRQ3, VR_z0, VRQ3);

    // Newton's method
    VR_t1 = vmacs_adj(VR_two, VR_y0, VR_z0, 0xf, 0);
    VR_y0 = vmuls(VR_t1, VR_y0, 0);

    VR_y0 = vmuls(VR_n0, VR_y0, 0);
    convert_32F_to_IEEE_float_x4(VR_y0);
    store_32x4_vr_a(VR_y0, UR_y, y);
    flush_32x4(UR_y, y);
  }

  // Remaining
  for (int i = 0; i < remain; i++) {
    fr32 frx;
    load_fr_postI(frx, x, INC1);
    unsigned arInput = *(unsigned*)&frx;
    frx = convert_IEEE_float_to_32F(arInput);
    //   convert_IEEE_float_to_32F_x4(VR_x1);
    fr32 fry = Tanh1(frx);
    unsigned out = convert_32F_to_IEEE_float(fry);

    store_fr_postI(out, y, INC1);
  }
}

void Tanh(int32_t cell_state_scale_power, float* input_data, float* output_data,
          int32_t data_size) {
  int data_dims[2] = {1, data_size};
  RuntimeShape data_shape(2, reinterpret_cast<const int32_t*>(data_dims));
  TanhV(output_data, input_data, data_size);

  KN_PRINT_FLOAT(output_data, data_size);
}

void Tanh(int32_t cell_state_scale_power, const RuntimeShape& input_data_shape,
          int16_t* input_data, const RuntimeShape& output_data_shape,
          int16_t* output_data) {
  KN_PRINT_Q15_SIZE(input_data, input_data_shape.FlatSize());

  Tanh(cell_state_scale_power, input_data, output_data,
       input_data_shape.FlatSize());
  // input_data_shape, input_data, output_data_shape,
  // output_data);
  KN_PRINT_Q15_SIZE(output_data, output_data_shape.FlatSize());
}

void Tanh(int32_t cell_state_scale_power, const RuntimeShape& input_data_shape,
          float* input_data, const RuntimeShape& output_data_shape,
          float* output_data) {
  TanhV(input_data, output_data, input_data_shape.FlatSize());
}

// Input and output have the same shape in LSTM
void Mul(const ArithmeticParams& params, const int16_t* input1_data,
         const int16_t* input2_data, int8_t* output_data, int32_t data_size) {
  // xa_nn_elm_mul_sym16sxsym16s_asym8s(
  //    output_data, params.output_offset, params.output_shift,
  //    params.output_multiplier, params.quantized_activation_min,
  //   params.quantized_activation_max, input1_data, input2_data, data_size);
  const int16_t* pin1 = input1_data;
  const int16_t* pin2 = input2_data;
  int8_t* pOut = output_data;
  int loop = data_size >> 2;
  int remain = data_size & 3;
  AScalar outMultipler, outputOffset;
  KN_PRINTX(params.output_multiplier);
  ConvertQ31ToAfloat(params.output_multiplier, outMultipler,
                     31 - 14 + params.output_shift);
  // int out_shift =
  ConvertQ31ToAfloat(params.output_offset, outputOffset, 17 + 1);

  KN_PRINTAFLT(outMultipler);
  KN_PRINTAFLT(outputOffset);
  vr128 VR_out, VR_q7_out;
  vr128 VR_outMultipler;
  vr128 VR_ouputOffset;
  vr128 VR_in1, VR_in2;
  replicate_ar(VR_outMultipler, 0xf, outMultipler.fr);

  replicate_ar(VR_ouputOffset, 0xf, outputOffset.fr);

  ulsr128 UR_in1 = align_16x4_load(pin1);
  ulsr128 UR_in2 = align_16x4_load(pin2);
  ulsr128 UR_out = align_8x4_store(pOut);

  if (loop > 0) {
    load_16x4_vr_a(VR_in1, UR_in1, pin1);
    load_16x4_vr_a(VR_in2, UR_in2, pin2);

    convert_16I_to_32F_x4(VR_in1, 0);
    convert_16I_to_32F_x4(VR_in2, 0);
    for (int ii = 0; ii < loop - 1; ii++) {
      VR_out = vmuls(VR_in1, VR_in2, 0);
      VR_out = vmacs_adj(VR_ouputOffset, VR_outMultipler, VR_out, 0, 0);

      convert_32F_to_16I_x4(VR_out, -8 + 2, 1);

      rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      store_8x4_vr_a(VR_out, UR_out, pOut);

      load_16x4_vr_a(VR_in1, UR_in1, pin1);
      load_16x4_vr_a(VR_in2, UR_in2, pin2);

      convert_16I_to_32F_x4(VR_in1, 0);
      convert_16I_to_32F_x4(VR_in2, 0);
    }
    VR_out = vmuls(VR_in1, VR_in2, 0);
    // VR_out = vmuls(VR_outMultipler, VR_out, 0);
    VR_out = vmacs_adj(VR_ouputOffset, VR_outMultipler, VR_out, 0, 0);
    convert_32F_to_16I_x4(VR_out, -8 + 2, 1);
    rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
    // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
    store_8x4_vr_a(VR_out, UR_out, pOut);
    flush_8x4(UR_out, pOut);
  }

  if (remain) {
    load_16x4_vr_a(VR_in1, UR_in1, pin1);
    load_16x4_vr_a(VR_in2, UR_in2, pin2);

    convert_16I_to_32F_x4(VR_in1, 0);
    convert_16I_to_32F_x4(VR_in2, 0);
    VR_out = vmuls(VR_in1, VR_in2, 0);
    VR_out = vmacs_adj(VR_ouputOffset, VR_outMultipler, VR_out, 0, 0);
    convert_32F_to_16I_x4(VR_out, -8 + 2, 1);
    rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

    for (int ii = 0; ii < remain; ii++) {
      store8x1_vr_postI(VR_out, pOut, INC1, VRQ0);
      VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
    }
  }
}

// Input and output have the same shape in LSTM
void Mul(const ArithmeticParams& params, const int16_t* input1_data,
         const int16_t* input2_data, int16_t* output_data, int32_t data_size) {
  // int dims_4D[4] = {1, 1, 1, data_size};
  // xa_nn_elm_mul_broadcast_4D_sym16sxsym16s_sym16s(
  //     output_data, dims_4D, params.output_shift, params.output_multiplier,
  //     params.quantized_activation_min, params.quantized_activation_max,
  //     input1_data, dims_4D, input2_data, dims_4D);
  KN_PRINTS("todo mul 16x16 = 16\n");
  return;
}

// Input and output have the same shape in LSTM
void Mul(const ArithmeticParams& params, const float* input1_data,
         const float* input2_data, float* output_data, int32_t data_size) {
  int dims_2D[2] = {1, data_size};
  RuntimeShape data_shape(2, reinterpret_cast<const int32_t*>(dims_2D));
  return reference_ops::Mul(params, data_shape, input1_data, data_shape,
                            input2_data, data_shape, output_data);
}
// API for external test
//

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const int16_t* input1_data, const int16_t* input2_data,
         int8_t* output_data) {
  KN_PRINT_Q15_SIZE(input1_data, shape.FlatSize());
  KN_PRINT_Q15_SIZE(input2_data, shape.FlatSize());
  KN_PRINTX(params.output_multiplier);
  KN_PRINTX(params.output_shift);
  KN_PRINTD(params.output_offset);
  reference_integer_ops::MulElementwise(shape.FlatSize(), params, input1_data,
                                        input2_data, output_data);

  KN_PRINT_Q7_SIZE(output_data, shape.FlatSize());
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const int16_t* input1_data, const int16_t* input2_data,
         int16_t* output_data) {
  KN_PRINT_Q15_SIZE(input1_data, shape.FlatSize());
  KN_PRINT_Q15_SIZE(input2_data, shape.FlatSize());
  /*
      const int32_t input1_val = params.input1_offset + input1_data[i];
    const int32_t input2_val = params.input2_offset + input2_data[i];
    const int32_t unclamped_result =
        params.output_offset +
        MultiplyByQuantizedMultiplier(input1_val * input2_val,
                                      params.output_multiplier,
                                      params.output_shift);
  */
  KN_PRINTD(params.input1_offset);
  KN_PRINTD(params.output_multiplier);
  KN_PRINTD(params.output_shift);
  KN_PRINTD(params.input2_offset);
  reference_integer_ops::MulElementwise(shape.FlatSize(), params, input1_data,
                                        input2_data, output_data);

  KN_PRINT_Q15_SIZE(output_data, shape.FlatSize());
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const float* input1_data, const float* input2_data,
         float* output_data) {
  return reference_ops::Mul(params, shape, input1_data, shape, input2_data,
                            shape, output_data);
}

// input MVM8bx8b with bias, output offset,mutlipler,shift
int FullyConnectedKernelLSTM(int32_t* x, const int32_t* A, const AScalar* bias,
                             int16_t* output, int m, int n,
                             const AScalar& outOffsetFr32,
                             const uint32_t input_offset_int8x4,  // xor 128
                             const AScalar& outMultiplerFr32, int signs) {
  int16_t* pY = output;

  const int32_t* pA = A;
  const int32_t* pX;
  const int32_t* pB = (const int32_t*)bias;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2), 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 3);  // block 16
  int loopLimRow = ((m + 7) >> 3);         // group 8 alignment
  int processLastLoop = ((m & 7) != 0);

  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x4_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0) {
    return -1;
  }
  vr128 VR_A;
  vr128 VR_x;
  vr128 VR_y;
  vr128 VR_inputOffset;
  xtbool2 signSpec = int_to_xt_bool2(signs);

  vr128 VR_outMult;
  vr128 VR_outOffset;
  vr128 VR_b0 = vseta_vr(kConstTable_Zero, 0, 0);
  ulsr128 UR_out = align_16x4_store(pY);
  replicate_ar(VR_outMult, 0xf, outMultiplerFr32.fr);
  replicate_ar(VR_outOffset, 0xf, outOffsetFr32.fr);
  replicate_ar(VR_inputOffset, 0xf, input_offset_int8x4);
  KN_PRINTAFLT(outMultiplerFr32);
  KN_PRINTAFLT(outOffsetFr32);
  KN_PRINTX(input_offset_int8x4);
  for (int i = 0; i < loopLimRow; i++) {
    VR_y = vseta_vr(0, 0, 0);
    mov_AccExtend_vr(VR_y);
    pX = x;
    ulsr128 UR_A = align_32x4_load(pA);
    ulsr128 UR_x = align_32x4_load(pX);
    ulsr128 UR_b;
    load_32x4_vr_a(VR_A, UR_A, pA);

    if (pB) {
      UR_b = align_32x4_load(pB);
      load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
    }

    for (int j = 0; j < loopLimCol; j++) {
      load_32x4_vr_a(VR_x, UR_x, pX);
      VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(0);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 3); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
    }
    KN_PRINTX_VR(VR_y);
    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      // vr128 VR_q7_out;

      vr128 VR_out;
      // KN_PRINT_VR(VR_y);
      // KN_PRINT_VR(VR_b0);
      VR_out = vadds(VR_y, VR_b0, 0x0);
      // KN_PRINT_VR(VR_out);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      // KN_PRINT_VR(VR_out);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);
      // KN_PRINTX_VR(VR_out);
      // convert_32F_to_16I_x4(VR_out, (unsigned int)1 - 8, 0);
      store_16x4_vr_a(VR_out, UR_out, pY);

      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      // accExt
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ0);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      // store_8x4_vr_a(VR_out, UR_out, pY);

      if (pB) {
        load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      // KN_PRINT_VR(VR_out);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);

      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      store_16x4_vr_a(VR_out, UR_out, pY);
      // store_8x4_vr_a(VR_out, UR_out, pY);
      flush_16x4(UR_out, pY);
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ1);
    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      // vr128 VR_q7_out;
      KN_PRINT_VR(VR_y);
      vr128 VR_out;
      KN_PRINT_VR(VR_b0);
      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      KN_PRINTX_VR(VR_out);
      for (int32_t j = 0; j < (m & 0x7) && j < 4; j++) {
        store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
        VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
      }

      if ((m & 7) <= 4) {
        break;
      }
      VR_y = mov_vr_AccExtend();

      if (pB) {
        load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

      for (int32_t j = 4; j < (m & 0x7) && j < 8; j++) {
        store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
        VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 4;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}

int FullyConnectedKernelInputOffsetLSTM(
    int32_t* x, const int32_t* A, const AScalar* bias, int16_t* output, int m,
    int n, const AScalar& outOffsetFr32,
    const int32_t* inputOffsetWithW,  // xor 128
    const AScalar& outMultiplerFr32, int signs) {
  int16_t* pY = output;

  const int32_t* pA = A;
  const int32_t* pX;
  const int32_t* pB = (const int32_t*)bias;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2), 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 3);  // block 16
  int loopLimRow = ((m + 7) >> 3);         // group 8 alignment
  int processLastLoop = ((m & 7) != 0);

  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x4_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0) {
    return -1;
  }

  vr128 VR_A;
  vr128 VR_x;
  vr128 VR_y;
  //  vr128 VR_inputOffset;
  xtbool2 signSpec = int_to_xt_bool2(signs);
  //  xtbool2 signSpecInput = int_to_xt_bool2(3);
  const int32_t* inputOffsetW = inputOffsetWithW;

  vr128 VR_outMult;
  vr128 VR_outOffset;
  vr128 VR_b0 = vseta_vr(kConstTable_Zero, 0, 0);
  ulsr128 UR_out = align_8x4_load(pY);
  replicate_ar(VR_outMult, 0xf, outMultiplerFr32.fr);
  replicate_ar(VR_outOffset, 0xf, outOffsetFr32.fr);
  // replicate_ar(VR_inputOffset, 0xf, input_offset_int8x4);
  for (int i = 0; i < loopLimRow; i++) {
    if (inputOffsetWithW) {
      load32x4_vr_postI(VR_y, inputOffsetW, INC1);
      load32x4_vr_postI(VR_x, inputOffsetW, INC1);
      mov_AccExtend_vr(VR_x);
    } else {
      VR_y = vseta_vr(0, 0, 0);
      mov_AccExtend_vr(VR_y);
    }
    pX = x;
    ulsr128 UR_A = align_32x4_load(pA);
    ulsr128 UR_x = align_32x4_load(pX);
    ulsr128 UR_b;
    load_32x4_vr_a(VR_A, UR_A, pA);

    if (pB) {
      UR_b = align_32x4_load(pB);
      load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
    }
    for (int j = 0; j < loopLimCol; j++) {
      load_32x4_vr_a(VR_x, UR_x, pX);
      WUR_MvmAux(0);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x4_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 3); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      //   KN_PRINTX_VR128(VR_A); KN_PRINTX_VR128(VR_x);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
    }
    KN_PRINTX_VR(VR_y);
    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      // vr128 VR_q7_out;

      vr128 VR_out;

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      // accExt
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      store_16x4_vr_a(VR_out, UR_out, pY);

      if (pB) {
        load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);

      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      store_16x4_vr_a(VR_out, UR_out, pY);
      flush_16x4(UR_out, pY);
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ1);
    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      // vr128 VR_q7_out;

      vr128 VR_out;

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      KN_PRINT_VR(VR_out);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      KN_PRINTX_VR(VR_out);
      for (int32_t j = 0; j < (m & 0x7) && j < 4; j++) {
        store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
        VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
      }

      if ((m & 7) <= 4) {
        break;
      }
      VR_y = mov_vr_AccExtend();

      if (pB) {
        load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

      for (int32_t j = 4; j < (m & 0x7) && j < 8; j++) {
        store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
        VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 4;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}

void FullyConnected(const FullyConnectedParams& params,
                    const int8_t* input_data, const int8_t* filter_data,
                    const int32_t* bias_data, int16_t* output_data,
                    const int num_batches, const int output_depth,
                    const int accum_depth) {
#pragma loop_count min = 1

  KN_PRINTD(params.input_offset);
  //			int input_aligned4 = data.is_input_align_4;
  int sign = (128 == params.input_offset)
                 ? 1
                 : 3;  // assumption: 128 + sign 8bit = unsigned

  KN_PRINT_Q7_SIZE(input_data, accum_depth);
  // ignore filter_data get from mapped_filter pointer;
  int32_t* map_filter_data = (params.mapped_filter);

  KN_PRINT_Q7_SIZE_ATMOST(map_filter_data,
                          ALIGN_COEFF_SIZE(accum_depth, output_depth), 64);

  KN_PRINTX(bias_data);
  KN_PRINTD(params.opt_constraint);
  const int8_t* inputLocal = input_data;
  int16_t* outputLocal = output_data;

  AScalar AoutputMultiplier = AScalar::Raw(params.outputMultipler);
  AScalar AoutputOffset = AScalar::Raw(params.outputOffset);

  for (int b = 0; b < num_batches; b++) {
    // xa_nn_matXvec_out_stride_sym8sxasym8s_16(
    //     output_data + b * output_depth, filter_data,
    //      input_data + b * accum_depth, bias_data, output_depth, accum_depth,
    //      accum_depth, 1, params.input_offset, params.output_multiplier,
    //      params.output_shift);
    if (params.opt_constraint == 2) {
      FullyConnectedKernelLSTM((int32_t*)inputLocal, (int32_t*)map_filter_data,
                               (AScalar*)params.bias_aflt,
                               (int16_t*)outputLocal, output_depth, accum_depth,
                               AoutputOffset, params.input_offset_int8,
                               AoutputMultiplier, sign);
      // input offset 80808080 or 0 xor input
    } else {
      FullyConnectedKernelInputOffsetLSTM(
          (int32_t*)inputLocal, (int32_t*)map_filter_data,
          (AScalar*)params.bias_aflt, (int16_t*)outputLocal, output_depth,
          accum_depth, AoutputOffset,

          params.inputOffsetWithW, AoutputMultiplier, sign);
    }

    inputLocal += accum_depth;
    outputLocal += output_depth;

    KN_PRINT_Q15_SIZE(output_data, output_depth);
  }

  return;
}

void FullyConnected(const FullyConnectedParams& params,
                    const int16_t* input_data, const int8_t* filter_data,
                    const int64_t* bias_data, int16_t* output_data,
                    const int num_batches, const int output_depth,
                    const int accum_depth) {
  // xa_nn_matmul_sym8sxsym16s_sym16s(
  //    output_data, filter_data, input_data, bias_data, output_depth,
  //    accum_depth, accum_depth, num_batches, accum_depth, output_depth, 1,
  //    params.input_offset, params.output_multiplier, params.output_shift,
  //    params.output_offset);
  KN_PRINTS("TODO: 16x8");
  // 16x8
  // TODO FIXME
  return;
}

void FullyConnected(const FullyConnectedParams& params, const float* input_data,
                    const float* filter_data, const float* bias_data,
                    float* output_data, const int num_batches,
                    const int output_depth, const int accum_depth) {
  int input_dims[2] = {num_batches, output_depth};
  RuntimeShape input_shape(2, reinterpret_cast<const int32_t*>(input_dims));
  RuntimeShape bias_shape(1, bias_data == NULL ? 0 : output_depth);
  int filter_dims[2] = {output_depth, accum_depth};
  RuntimeShape filter_shape(2, reinterpret_cast<const int32_t*>(filter_dims));
  int output_dims[2] = {num_batches, output_depth};
  RuntimeShape output_shape(2, reinterpret_cast<const int32_t*>(output_dims));

  KN_PRINT_FLOAT(input_data, input_shape.FlatSize());
  KN_PRINT_FLOAT(filter_data, filter_shape.FlatSize());
  KN_PRINT_FLOAT(bias_data, bias_shape.FlatSize());

  tflite::reference_ops::FullyConnected(params, input_shape, input_data,
                                        filter_shape, filter_data, bias_shape,
                                        bias_data, output_shape, output_data);
  KN_PRINT_FLOAT(output_data, output_shape.FlatSize());
}
#endif

#if defined(HMD1A_LSTM_OPT)

void AddElementWise(const int16_t* input_1, const int16_t* input_2, int n_batch,
                    int n_input, int16_t* output) {

  //  xa_nn_elm_add_16x16_16(output, input_1, input_2, n_batch * n_input);
  // KN_PRINTS("TODO 16+16");
  // for(int ii =0; ii < )
  for (int batch = 0; batch < n_batch; ++batch) {
    const int16_t *in1, *in2;
    int16_t* out;
    const int index = batch * n_input;
    in1 = &input_1[index];
    in2 = &input_2[index];
    out = &output[index];
    int nloop = n_input >> 1;
    int remain = n_input & 1;
    vr64 VR_in1, VR_in2;
    vr64 VR_sum;
    
    //ulsr32 UR_in1 = align_16x2_load(in1);
    //ulsr32 UR_in2 = align_16x2_load(in2);
    if (nloop > 0) {
      //ulsr128 UR_out = align_16x4_store(out);

      load16x2_vr_postI(VR_in1, in1, INC1);
      load16x2_vr_postI(VR_in2, in2, INC1);

      for (int i = 0; i < nloop - 1; ++i) {
        convert_16I_to_32F_x2(VR_in1, 0);
        convert_16I_to_32F_x2(VR_in2, 0);
        VR_sum = vadds(VR_in1, VR_in2, 0);
        convert_32F_to_16I_x2(VR_sum, 0, 0);
        store16x2_vr_postI(VR_sum, out, INC1);

        load16x2_vr_postI(VR_in1, in1, INC1);
        load16x2_vr_postI(VR_in2, in2, INC1);
      }
      convert_16I_to_32F_x2(VR_in1, 0);
      convert_16I_to_32F_x2(VR_in2, 0);
      VR_sum = vadds(VR_in1, VR_in2, 0);
      convert_32F_to_16I_x2(VR_sum, 0, 0);
      store16x2_vr_postI(VR_sum, out, INC1);
      //flush_16x4(UR_out, out);
    }

    if (remain) {
      load16x1_vr_postI(VR_in1, in1, INC1, VRQ0);
      load16x1_vr_postI(VR_in2, in2, INC1, VRQ0);

      convert_16I_to_32F_x2(VR_in1, 0);
      convert_16I_to_32F_x2(VR_in2, 0);
      VR_sum = vadds(VR_in1, VR_in2, 0);
      convert_32F_to_16I_x2(VR_sum, 0, 0);
      //for (int ii = 0; ii < remain; ii++) {
        store16x1_vr_postI(VR_sum, out, INC1, VRQ0);
        //VR_sum = vpermsi(VR_sum, VR_sum, 0, SHR_BY_1_ELEM);
      //}
    }
  }


  KN_PRINT_Q15_SIZE(output, n_batch * n_input);
}
#define SIGMOD_EXP (3)
_AI fr32 Sigmoid1(fr32 x) {
  fr32 fac = seta_fr(kConstTable_Log2_Of_e, 0);
  fr32 one = seta_fr(kConstTable_One, 0);
  x = fmuls(fac, x, 1);
  x = pow2(x);
  x = fadds(one, x, 0);
  x = inv(x);

  return x;
}

void Sigmoid(int16_t* data, int32_t data_size) {

  int loopLim = data_size >> 1;  // Includes loop unrolling count of 2
  int remain = data_size & 1;

  int16_t* x = data;
  int16_t* y = data;

  vr64 VR_x0, VR_y0, VR_z0;
  vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0);  // no rounding is consistent with HMD
  vr64 VR_one = vseta_vr(kConstTable_One, 0);

  if (loopLim > 0) {
    load16x2_vr_postI(VR_x0, x, INC1);
    convert_16I_to_32F_x2(VR_x0, SIGMOD_EXP);

    VR_y0 = vmuls(VR_fac, VR_x0, 0x3);
    for (int i = 0; i < loopLim - 1; i++) {
      set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
      set_VRH(VR_z0, pow2(get_VRH(VR_y0)));

      VR_z0 = vadds(VR_one, VR_z0, 0);
      load16x2_vr_postI(VR_x0, x, INC1);

      set_VRL(VR_z0, inv(get_VRL(VR_z0)));
      set_VRH(VR_z0, inv(get_VRH(VR_z0)));

      convert_16I_to_32F_x2(VR_x0, SIGMOD_EXP);
      convert_32F_to_16I_x2(VR_z0, 0, 1);  // Q 11
      store16x2_vr_postI(VR_z0, y, INC1);
      VR_y0 = vmuls(VR_fac, VR_x0, 0x3);
    }
    set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
    set_VRH(VR_z0, pow2(get_VRH(VR_y0)));
    VR_z0 = vadds(VR_one, VR_z0, 0);

    set_VRL(VR_z0, inv(get_VRL(VR_z0)));
    set_VRH(VR_z0, inv(get_VRH(VR_z0)));

    convert_32F_to_16I_x2(VR_z0, 0, 1);
    store16x2_vr_postI(VR_z0, y, INC1);
  }

  // Remaining
  if(remain) {
    fr32 frx;
    vr64 VR_x;
    load16x1_vr_postI(VR_x, x, INC1, VRQ0);
    convert_16I_to_32F_x2(VR_x, SIGMOD_EXP);
    frx = move32_fr_vr_idx(VR_x, VRQ0);

    fr32 fry = Sigmoid1(frx);
    set_VRL(VR_x, fry);
    convert_32F_to_16I_x1(VR_x, 0, 1, VRQ0);
    store16x1_vr_postI(VR_x, y, INC1, VRQ0);
  }
}
static void SigmoidV_Full(float* y, const float* x, int n) {
  int loopLim = n >> 1;  // Includes loop unrolling count of 2
  int remain = n & 1;
  ulsr32 UR_x = align_32x2_load(x);
  ulsr32 UR_y = align_32x2_store(y);
  vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 
                          0);  // no rounding is consistent with HMD
  vr64 VR_one = vseta_vr(kConstTable_One,  0);
  vr64 VR_x0;
  vr64 VR_y0;
  vr64 VR_z0;

  if (loopLim > 0) {
    load_32x2_vr_a(VR_x0, UR_x, x);
    convert_IEEE_float_to_32F_x2(VR_x0);

    VR_y0 = vmuls(VR_fac, VR_x0, 0x3);
    // Groups of 8
    for (int i = 0; i < loopLim - 1; i++) {
      set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
      set_VRH(VR_z0, pow2(get_VRH(VR_y0)));


      VR_z0 = vadds(VR_one, VR_z0, 0);

      load_32x2_vr_a(VR_x0, UR_x, x);

      convert_IEEE_float_to_32F_x2(VR_x0);
      set_VRL(VR_z0, inv(get_VRL(VR_z0)));
      set_VRH(VR_z0, inv(get_VRH(VR_z0)));


      convert_32F_to_IEEE_float_x2(VR_z0);
      store_32x2_vr_a(VR_z0, UR_y, y);
      VR_y0 = vmuls(VR_fac, VR_x0, 0x3);
    }
    set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
    set_VRH(VR_z0, pow2(get_VRH(VR_y0)));


    VR_z0 = vadds(VR_one, VR_z0, 0);
    set_VRL(VR_z0, inv(get_VRL(VR_z0)));
    set_VRH(VR_z0, inv(get_VRH(VR_z0)));

    convert_32F_to_IEEE_float_x2(VR_z0);
    store_32x2_vr_a(VR_z0, UR_y, y);

    flush_32x2(UR_y, y);
  }
  // Remaining
  if( remain) {
    //vr64 frx;
    load32x1_vr_postI(VR_x0, x, INC1, VRQ0);
    //unsigned arInput = *(unsigned*)&frx;
    convert_IEEE_float_to_32F_x2(VR_x0);
    fr32 fry = Sigmoid1( get_VRL(VR_x0));
    set_VRL(VR_y0, fry);
    convert_32F_to_IEEE_float_x2(VR_y0);
    store32x1_vr_postI(VR_y0, y, INC1, VRQ0);
  }
}

void Sigmoid(float* data, int32_t data_size) {
  int data_dims[2] = {1, data_size};
  RuntimeShape data_shape(2, reinterpret_cast<const int32_t*>(data_dims));
  SigmoidV_Full(data, data, data_shape.FlatSize());
  // reference_ops::Logistic(data_shape, data, data_shape, data);
  KN_PRINT_FLOAT(data, data_shape.FlatSize());
}

void Sigmoid(const RuntimeShape& data_shape, int16_t* data) {
  //  KN_PRINT_Q15_SIZE(data, data_shape.FlatSize());

  Sigmoid(data, data_shape.FlatSize());
  KN_PRINT_Q15_SIZE(data, data_shape.FlatSize());
}

void Sigmoid(const RuntimeShape& data_shape, float* data) {
  // reference_ops::Logistic(data_shape, data, data_shape, data);

  SigmoidV_Full(data, data, data_shape.FlatSize());
}

_AI fr32 Tanh1(fr32 x) {
  fr32 fac = seta_fr(kConstTable_Log2_Of_e,  0);
  fr32 one = seta_fr(kConstTable_One,  0);
  fr32 two = seta_fr(kConstTable_Two,  0);
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
void Tanh(int32_t cell_state_scale_power, int16_t* input_data,
          int16_t* output_data, int32_t data_size) {
  int32_t tanh_input_left_shift = (15 + cell_state_scale_power) - 3;
  // int32_t input_multiplier = 0;
  if (tanh_input_left_shift < 0) /* handling negative shift value */
  {
    tanh_input_left_shift = -tanh_input_left_shift;
  }

  int16_t* x = input_data;
  int16_t* y = output_data;
  int loopLim = data_size >> 1;  // Includes loop unrolling count of 2
  int remain = data_size & 1;
 
  vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e,  0);
  vr64 VR_one = vseta_vr(kConstTable_One,  0);
  vr64 VR_two = vseta_vr(kConstTable_Two,  0);

  vr64 VR_x0;
  vr64 VR_y0;
  vr64 VR_z0;
  vr64 VR_n0;
  VR_fac = vmuls(VR_fac, VR_two, 0);

  // Groups of 2
  if (loopLim > 0) {
    vr64 VR_t1;
    load16x2_vr_postI(VR_x0, x, INC1);
    convert_16I_to_32F_x2(VR_x0, SIGMOD_EXP + tanh_input_left_shift);

    VR_y0 = vmuls(VR_fac, VR_x0, 0);
    for (int i = 0; i < loopLim - 1; i++) {
      set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
      set_VRH(VR_z0, pow2(get_VRH(VR_y0)));


      VR_n0 = vadds(VR_one, VR_z0, 0x5);  // 1- exp(2*x)
      VR_z0 = vadds(VR_one, VR_z0, 0);    // 1+ exp(2*x)

      load16x2_vr_postI(VR_x0, x, INC1);

      convert_16I_to_32F_x2(VR_x0, SIGMOD_EXP + tanh_input_left_shift);
      set_VRL(VR_y0, inv(get_VRL(VR_z0)));
      set_VRH(VR_y0, inv(get_VRH(VR_z0)));


      // Newton's method
      VR_t1 = vmacs(VR_two, VR_y0, VR_z0, 3, 0);
      VR_y0 = vmuls(VR_t1, VR_y0, 0);

      VR_y0 = vmuls(VR_n0, VR_y0, 0);
      convert_32F_to_16I_x2(VR_y0, 0, 1);
      store16x2_vr_postI(VR_y0, y, INC1);
      VR_y0 = vmuls(VR_fac, VR_x0, 0);
    }

    set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
    set_VRH(VR_z0, pow2(get_VRH(VR_y0)));

    VR_n0 = vadds(VR_one, VR_z0, 0x5);  // 1- exp(2*x)
    VR_z0 = vadds(VR_one, VR_z0, 0);    // 1+ exp(2*x)

    set_VRL(VR_y0, inv(get_VRL(VR_z0)));
    set_VRH(VR_y0, inv(get_VRH(VR_z0)));

    // Newton's method
    VR_t1 = vmacs(VR_two, VR_y0, VR_z0, 3, 0);
    VR_y0 = vmuls(VR_t1, VR_y0, 0);

    VR_y0 = vmuls(VR_n0, VR_y0, 0);
    convert_32F_to_16I_x2(VR_y0, 0, 1);
    store16x2_vr_postI(VR_y0,  y, INC1);
  }

  // Remaining
  if(remain) {
    // fr32 frx;
    vr64 VR_x0, VR_y0;
    load16x1_vr_postI(VR_x0, x, INC1, VRQ0);

    convert_16I_to_32F_x2(VR_x0, SIGMOD_EXP + tanh_input_left_shift);
    fr32 fry = Tanh1(get_VRL(VR_x0));

    set_VRL(VR_y0, fry);
    convert_32F_to_16I_x2(VR_y0, 0, 1);
    store16x1_vr_postI(VR_y0, y, INC1, VRQ0);
  }
}
static void TanhV(float* y, const float* x, int n) {
  int loopLim = n >> 1;  // Includes loop unrolling count of 2
  int remain = n & 1;

  ulsr32 UR_x = align_32x2_load(x);
  ulsr32 UR_y = align_32x2_store(y);
  vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e,  0);
  vr64 VR_one = vseta_vr(kConstTable_One, 0);
  vr64 VR_two = vseta_vr(kConstTable_Two, 0);
  vr64 VR_x0;
  vr64 VR_y0;
  vr64 VR_z0;
  vr64 VR_n0;

  // VR_fac = 2*log2e
  VR_fac = vmuls(VR_fac, VR_two, 0);

  // Groups of 4
  if (loopLim > 0) {
    vr64 VR_t1;
    load_32x2_vr_a(VR_x0, UR_x, x);

    convert_IEEE_float_to_32F_x2(VR_x0);
    VR_y0 = vmuls(VR_fac, VR_x0, 0);
    for (int i = 0; i < loopLim - 1; i++) {
      set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
      set_VRH(VR_z0, pow2(get_VRH(VR_y0)));

      VR_n0 = vadds(VR_one, VR_z0, 0xf);  // 1- exp(2*x)
      VR_z0 = vadds(VR_one, VR_z0, 0);    // 1+ exp(2*x)

      load_32x2_vr_a(VR_x0, UR_x, x);

      convert_IEEE_float_to_32F_x2(VR_x0);
      set_VRL(VR_y0, inv(get_VRL(VR_z0)));
      set_VRH(VR_y0, inv(get_VRH(VR_z0)));


      // Newton's method
      VR_t1 = vmacs(VR_two, VR_y0, VR_z0, 3, 0);
      VR_y0 = vmuls(VR_t1, VR_y0, 0);

      VR_y0 = vmuls(VR_n0, VR_y0, 0);

      convert_32F_to_IEEE_float_x2(VR_y0);

      store_32x2_vr_a(VR_y0, UR_y, y);
      VR_y0 = vmuls(VR_fac, VR_x0, 0);
    }
    set_VRL(VR_z0, pow2(get_VRL(VR_y0)));
    set_VRH(VR_z0, pow2(get_VRH(VR_y0)));

    VR_n0 = vadds(VR_one, VR_z0, 0xf);  // 1- exp(2*x)
    VR_z0 = vadds(VR_one, VR_z0, 0);    // 1+ exp(2*x)

    set_VRL(VR_y0, inv(get_VRL(VR_z0)));
    set_VRH(VR_y0, inv(get_VRH(VR_z0)));

    // Newton's method
    VR_t1 = vmacs(VR_two, VR_y0, VR_z0, 3, 0);
    VR_y0 = vmuls(VR_t1, VR_y0, 0);

    VR_y0 = vmuls(VR_n0, VR_y0, 0);

    convert_32F_to_IEEE_float_x2(VR_y0);

    store_32x2_vr_a(VR_y0, UR_y, y);
    flush_32x2(UR_y, y);
  }

  // Remaining
  if(remain) {
    
    load32x1_vr_postI(VR_x0, x, INC1, VRQ0);
    convert_IEEE_float_to_32F_x2(VR_x0);
    fr32 fry = Tanh1(get_VRL(VR_x0));
    set_VRL(VR_y0, fry);
    convert_32F_to_IEEE_float_x2(VR_y0);
    store32x1_vr_postI(VR_y0, y, INC1, VRQ0);
  }
}

void Tanh(int32_t cell_state_scale_power, float* input_data, float* output_data,
          int32_t data_size) {
  int data_dims[2] = {1, data_size};
  RuntimeShape data_shape(2, reinterpret_cast<const int32_t*>(data_dims));
  TanhV(output_data, input_data, data_size);

  KN_PRINT_FLOAT(output_data, data_size);
}

void Tanh(int32_t cell_state_scale_power, const RuntimeShape& input_data_shape,
          int16_t* input_data, const RuntimeShape& output_data_shape,
          int16_t* output_data) {
  KN_PRINT_Q15_SIZE(input_data, input_data_shape.FlatSize());

  Tanh(cell_state_scale_power, input_data, output_data,
       input_data_shape.FlatSize());
  // input_data_shape, input_data, output_data_shape,
  // output_data);
  KN_PRINT_Q15_SIZE(output_data, output_data_shape.FlatSize());
}

void Tanh(int32_t cell_state_scale_power, const RuntimeShape& input_data_shape,
          float* input_data, const RuntimeShape& output_data_shape,
          float* output_data) {
  TanhV(input_data, output_data, input_data_shape.FlatSize());
}

// Input and output have the same shape in LSTM
void Mul(const ArithmeticParams& params, const int16_t* input1_data,
         const int16_t* input2_data, int8_t* output_data, int32_t data_size) {
  // xa_nn_elm_mul_sym16sxsym16s_asym8s(
  //    output_data, params.output_offset, params.output_shift,
  //    params.output_multiplier, params.quantized_activation_min,
  //   params.quantized_activation_max, input1_data, input2_data, data_size);
  const int16_t* pin1 = input1_data;
  const int16_t* pin2 = input2_data;
  int8_t* pOut = output_data;
  int loop = data_size >> 1;
  int remain = data_size & 1;
  AScalar outMultipler, outputOffset;
  KN_PRINTX(params.output_multiplier);
  ConvertQ31ToAfloat(params.output_multiplier, outMultipler,
                     31 - 14 + params.output_shift);
  // int out_shift =
  ConvertQ31ToAfloat(params.output_offset, outputOffset, 17 + 1);

  KN_PRINTAFLT(outMultipler);
  KN_PRINTAFLT(outputOffset);
  vr64 VR_out, VR_q7_out;
  vr64 VR_outMultipler;
  vr64 VR_ouputOffset;
  vr64 VR_in1, VR_in2;
  replicate_ar(VR_outMultipler, 0x3, outMultipler.fr);

  replicate_ar(VR_ouputOffset, 0x3, outputOffset.fr);

  //ulsr32 UR_in1 = align_16x2_load(pin1);
  //ulsr32 UR_in2 = align_16x2_load(pin2);
  //ulsr32 UR_out = align_8x4_store(pOut);

  if (loop > 0) {
    load16x2_vr_postI(VR_in1, pin1, INC1);
    load16x2_vr_postI(VR_in2, pin2, INC1);

    convert_16I_to_32F_x2(VR_in1, 0);
    convert_16I_to_32F_x2(VR_in2, 0);
    for (int ii = 0; ii < loop - 1; ii++) {
      VR_out = vmuls(VR_in1, VR_in2, 0);
      VR_out = vmacs(VR_ouputOffset, VR_outMultipler, VR_out,0, 0);

      convert_32F_to_16I_x2(VR_out, -8 + 2, 1);

      rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, 0);
      store8x2_vr_postI(VR_out, pOut, INC1);

      load16x2_vr_postI(VR_in1, pin1, INC1);
      load16x2_vr_postI(VR_in2, pin2, INC1);

      convert_16I_to_32F_x2(VR_in1, 0);
      convert_16I_to_32F_x2(VR_in2, 0);
    }
    VR_out = vmuls(VR_in1, VR_in2, 0);
    // VR_out = vmuls(VR_outMultipler, VR_out, 0);
    VR_out = vmacs(VR_ouputOffset, VR_outMultipler, VR_out, 0, 0);
    convert_32F_to_16I_x2(VR_out, -8 + 2, 1);
    rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
    // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, 0);
    store8x2_vr_postI(VR_out, pOut, INC1);
    //flush_8x4(UR_out, pOut);
  }

  if (remain) {
    load16x1_vr_postI(VR_in1, pin1, INC1, VRQ0);
    load16x1_vr_postI(VR_in2, pin2, INC1, VRQ0);

    convert_16I_to_32F_x2(VR_in1, 0);
    convert_16I_to_32F_x2(VR_in2, 0);
    VR_out = vmuls(VR_in1, VR_in2, 0);
    VR_out = vmacs(VR_ouputOffset, VR_outMultipler, VR_out, 0, 0);
    convert_32F_to_16I_x2(VR_out, -8 + 2, 1);
    rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
    VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
      store8x1_vr_postI(VR_out, pOut, INC1, VRQ0);
    
  }
}

// Input and output have the same shape in LSTM
void Mul(const ArithmeticParams& params, const int16_t* input1_data,
         const int16_t* input2_data, int16_t* output_data, int32_t data_size) {
  // int dims_4D[4] = {1, 1, 1, data_size};
  // xa_nn_elm_mul_broadcast_4D_sym16sxsym16s_sym16s(
  //     output_data, dims_4D, params.output_shift, params.output_multiplier,
  //     params.quantized_activation_min, params.quantized_activation_max,
  //     input1_data, dims_4D, input2_data, dims_4D);
  KN_PRINTS("todo mul 16x16 = 16\n");
  return;
}

// Input and output have the same shape in LSTM
void Mul(const ArithmeticParams& params, const float* input1_data,
         const float* input2_data, float* output_data, int32_t data_size) {
  int dims_2D[2] = {1, data_size};
  RuntimeShape data_shape(2, reinterpret_cast<const int32_t*>(dims_2D));
  return reference_ops::Mul(params, data_shape, input1_data, data_shape,
                            input2_data, data_shape, output_data);
}
// API for external test
//

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const int16_t* input1_data, const int16_t* input2_data,
         int8_t* output_data) {
  KN_PRINT_Q15_SIZE(input1_data, shape.FlatSize());
  KN_PRINT_Q15_SIZE(input2_data, shape.FlatSize());
  KN_PRINTX(params.output_multiplier);
  KN_PRINTX(params.output_shift);
  KN_PRINTD(params.output_offset);
  reference_integer_ops::MulElementwise(shape.FlatSize(), params, input1_data,
                                        input2_data, output_data);

  KN_PRINT_Q7_SIZE(output_data, shape.FlatSize());
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const int16_t* input1_data, const int16_t* input2_data,
         int16_t* output_data) {
  KN_PRINT_Q15_SIZE(input1_data, shape.FlatSize());
  KN_PRINT_Q15_SIZE(input2_data, shape.FlatSize());
  /*
      const int32_t input1_val = params.input1_offset + input1_data[i];
    const int32_t input2_val = params.input2_offset + input2_data[i];
    const int32_t unclamped_result =
        params.output_offset +
        MultiplyByQuantizedMultiplier(input1_val * input2_val,
                                      params.output_multiplier,
                                      params.output_shift);
  */
  KN_PRINTD(params.input1_offset);
  KN_PRINTD(params.output_multiplier);
  KN_PRINTD(params.output_shift);
  KN_PRINTD(params.input2_offset);
  reference_integer_ops::MulElementwise(shape.FlatSize(), params, input1_data,
                                        input2_data, output_data);

  KN_PRINT_Q15_SIZE(output_data, shape.FlatSize());
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const float* input1_data, const float* input2_data,
         float* output_data) {
  return reference_ops::Mul(params, shape, input1_data, shape, input2_data,
                            shape, output_data);
}

// input MVM8bx8b with bias, output offset,mutlipler,shift
int FullyConnectedKernelLSTM(int32_t* x, const int32_t* A, const AScalar* bias,
                             int16_t* output, int m, int n,
                             const AScalar& outOffsetFr32,
                             const uint32_t input_offset_int8x4,  // xor 128
                             const AScalar& outMultiplerFr32, int signs) {
  int16_t* pY = output;

  const int32_t* pA = A;
  const int32_t* pX;
  const int32_t* pB = (const int32_t*)bias;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2), 31-

  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
  int processLastLoop = ((m & 3) != 0);

  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x4_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0) {
    return -1;
  }
  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  vr64 VR_inputOffset;
  atbool signSpec = atbool(signs);

  vr64 VR_outMult;
  vr64 VR_outOffset;
  vr64 VR_b0 = vseta_vr(kConstTable_Zero,  0);
 // vr64 UR_out = align_16x2_store(pY);
  replicate_ar(VR_outMult, 0x3, outMultiplerFr32.fr);
  replicate_ar(VR_outOffset, 0x3, outOffsetFr32.fr);
  replicate_ar(VR_inputOffset, 0x3, input_offset_int8x4);

  KN_PRINTAFLT(outMultiplerFr32);
  KN_PRINTAFLT(outOffsetFr32);
  KN_PRINTX(input_offset_int8x4);
  for (int i = 0; i < loopLimRow; i++) {
    VR_y = vseta_vr(0,  0);
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
    KN_PRINTX_VR(VR_y);
    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);



      vr64 VR_out;
      VR_out = vadds(VR_y, VR_b0, 0x0);

      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);

      convert_32F_to_16I_x2(VR_out, (unsigned int)1, 1);

      store16x2_vr_postI(VR_out,  pY, INC1);
      if (pB) {
        load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1, 1);

      store16x2_vr_postI(VR_out, pY, INC1);
    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      KN_PRINT_VR(VR_y);

      vr64 VR_out;
      KN_PRINT_VR(VR_b0);
      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1, 1);

     KN_PRINTX_VR(VR_out);
      VR_y = mov_vr_AccExtend();

      if (pB) {
        load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_out2 = vadds(VR_y, VR_b0, 0x0);
      VR_out2 = vmuls(VR_out2, VR_outMult, 0);
      VR_out2 = vadds(VR_out2, VR_outOffset, 0);
      convert_32F_to_16I_x2(VR_out2, (unsigned int)1, 1);
      switch (m & 0x3) {
        case 3:
          store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store16x1_vr_postI(VR_out, pY, INC1, VRQ1);
          store16x1_vr_postI(VR_out2, pY, INC1, VRQ0);
          break;
        case 2:
          store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store16x1_vr_postI(VR_out, pY, INC1, VRQ1);
          break;
        case 1:
          store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
          break;
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}

int FullyConnectedKernelInputOffsetLSTM(
    int32_t* x, const int32_t* A, const AScalar* bias, int16_t* output, int m,
    int n, const AScalar& outOffsetFr32,
    const int32_t* inputOffsetWithW,  // xor 128
    const AScalar& outMultiplerFr32, int signs) {
  int16_t* pY = output;

  const int32_t* pA = A;
  const int32_t* pX;
  const int32_t* pB = (const int32_t*)bias;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2), 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
  int processLastLoop = ((m & 3) != 0);

  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x4_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0) {
    return -1;
  }

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  //  vr128 VR_inputOffset;
  atbool signSpec = atbool(signs);
  //  xtbool2 signSpecInput = int_to_xt_bool2(3);
  const int32_t* inputOffsetW = inputOffsetWithW;

  vr64 VR_outMult;
  vr64 VR_outOffset;
  vr64 VR_b0 = vseta_vr(kConstTable_Zero,  0);
  //ulsr128 UR_out = align_8x4_load(pY);
  replicate_ar(VR_outMult, 0x3, outMultiplerFr32.fr);
  replicate_ar(VR_outOffset, 0x3, outOffsetFr32.fr);
  // replicate_ar(VR_inputOffset, 0xf, input_offset_int8x4);
  for (int i = 0; i < loopLimRow; i++) {
    if (inputOffsetWithW) {
      load32x2_vr_postI(VR_y, inputOffsetW, INC1);
      load32x2_vr_postI(VR_x, inputOffsetW, INC1);
      mov_AccExtend_vr(VR_x);
    } else {
      VR_y = vseta_vr(0,  0);
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
    KN_PRINTX_VR(VR_y);
    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      // vr128 VR_q7_out;

      vr64 VR_out;

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1, 1);
      store16x2_vr_postI(VR_out, pY, INC1);

      if (pB) {
        load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_out2 = vadds(VR_y, VR_b0, 0x0);
      VR_out2 = vmuls(VR_out2, VR_outMult, 0);
      VR_out2 = vadds(VR_out2, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out2, (unsigned int)1, 1);

      store16x2_vr_postI(VR_out, pY, INC1);

    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      //vr64 VR_q7_out;
      KN_PRINT_VR(VR_y);
      KN_PRINT_VR(VR_b0);
      vr64 VR_out;

      VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_out, VR_outMult, 0);
      VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      KN_PRINT_VR(VR_out);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1, 1);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      KN_PRINTX_VR(VR_out);
      VR_y = mov_vr_AccExtend();

      if (pB) {
        load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      }

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_out2 = vadds(VR_y, VR_b0, 0x0);
      VR_out2 = vmuls(VR_out2, VR_outMult, 0);
      VR_out2 = vadds(VR_out2, VR_outOffset, 0);
      convert_32F_to_16I_x2(VR_out2, (unsigned int)1, 1);
      switch (m & 0x3) {
        case 3:
          store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store16x1_vr_postI(VR_out, pY, INC1, VRQ1);
          store16x1_vr_postI(VR_out2, pY, INC1, VRQ0);
          break;
        case 2:
          store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store16x1_vr_postI(VR_out, pY, INC1, VRQ1);
          break;
        case 1:
          store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
          break;
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}

void FullyConnected(const FullyConnectedParams& params,
                    const int8_t* input_data, const int8_t* filter_data,
                    const int32_t* bias_data, int16_t* output_data,
                    const int num_batches, const int output_depth,
                    const int accum_depth) {
#pragma loop_count min = 1

  KN_PRINTD(params.input_offset);
  //			int input_aligned4 = data.is_input_align_4;
  int sign = (128 == params.input_offset)
                 ? 1
                 : 3;  // assumption: 128 + sign 8bit = unsigned

  KN_PRINT_Q7_SIZE(input_data, accum_depth);
  // ignore filter_data get from mapped_filter pointer;
  int32_t* map_filter_data = (params.mapped_filter);

  KN_PRINT_Q7_SIZE_ATMOST(map_filter_data,
                          ALIGN_COEFF_SIZE(accum_depth, output_depth), 64);

  KN_PRINTX(bias_data);
  KN_PRINTD(params.opt_constraint);
  const int8_t* inputLocal = input_data;
  int16_t* outputLocal = output_data;

  AScalar AoutputMultiplier = AScalar::Raw(params.outputMultipler);
  AScalar AoutputOffset = AScalar::Raw(params.outputOffset);

  for (int b = 0; b < num_batches; b++) {
    // xa_nn_matXvec_out_stride_sym8sxasym8s_16(
    //     output_data + b * output_depth, filter_data,
    //      input_data + b * accum_depth, bias_data, output_depth, accum_depth,
    //      accum_depth, 1, params.input_offset, params.output_multiplier,
    //      params.output_shift);
    if (params.opt_constraint == 2) {
      FullyConnectedKernelLSTM((int32_t*)inputLocal, (int32_t*)map_filter_data,
                               (AScalar*)params.bias_aflt,
                               (int16_t*)outputLocal, output_depth, accum_depth,
                               AoutputOffset, params.input_offset_int8,
                               AoutputMultiplier, sign);
      // input offset 80808080 or 0 xor input
    } else {
      FullyConnectedKernelInputOffsetLSTM(
          (int32_t*)inputLocal, (int32_t*)map_filter_data,
          (AScalar*)params.bias_aflt, (int16_t*)outputLocal, output_depth,
          accum_depth, AoutputOffset,

          params.inputOffsetWithW, AoutputMultiplier, sign);
    }

    inputLocal += accum_depth;
    outputLocal += output_depth;

    KN_PRINT_Q15_SIZE(output_data, output_depth);
  }

  return;
}

void FullyConnected(const FullyConnectedParams& params,
                    const int16_t* input_data, const int8_t* filter_data,
                    const int64_t* bias_data, int16_t* output_data,
                    const int num_batches, const int output_depth,
                    const int accum_depth) {
  // xa_nn_matmul_sym8sxsym16s_sym16s(
  //    output_data, filter_data, input_data, bias_data, output_depth,
  //    accum_depth, accum_depth, num_batches, accum_depth, output_depth, 1,
  //    params.input_offset, params.output_multiplier, params.output_shift,
  //    params.output_offset);
  KN_PRINTS("TODO: 16x8");
  // 16x8
  // TODO FIXME
  return;
}

void FullyConnected(const FullyConnectedParams& params, const float* input_data,
                    const float* filter_data, const float* bias_data,
                    float* output_data, const int num_batches,
                    const int output_depth, const int accum_depth) {
  int input_dims[2] = {num_batches, output_depth};
  RuntimeShape input_shape(2, reinterpret_cast<const int32_t*>(input_dims));
  RuntimeShape bias_shape(1, bias_data == NULL ? 0 : output_depth);
  int filter_dims[2] = {output_depth, accum_depth};
  RuntimeShape filter_shape(2, reinterpret_cast<const int32_t*>(filter_dims));
  int output_dims[2] = {num_batches, output_depth};
  RuntimeShape output_shape(2, reinterpret_cast<const int32_t*>(output_dims));

  KN_PRINT_FLOAT(input_data, input_shape.FlatSize());
  KN_PRINT_FLOAT(filter_data, filter_shape.FlatSize());
  KN_PRINT_FLOAT(bias_data, bias_shape.FlatSize());

  tflite::reference_ops::FullyConnected(params, input_shape, input_data,
                                        filter_shape, filter_data, bias_shape,
                                        bias_data, output_shape, output_data);
  KN_PRINT_FLOAT(output_data, output_shape.FlatSize());
}
#endif
// ref ops
#if !defined(DMX1A_LSTM_OPT) && !defined(HMD1A_LSTM_OPT)
void Sigmoid(const RuntimeShape& data_shape, int16_t* data) {
  KN_PRINT_Q15_SIZE(data, data_shape.FlatSize());
  reference_integer_ops::Logistic(
      0 /*data->input_multiplier*/, 0 /*data->input_left_shift */,
      data_shape.FlatSize() /*NumElements(input->dims)*/,
      data /* tflite::micro::GetTensorData<int16_t>(input) */,
      data /*tflite::micro::GetTensorData<int16_t>(output) */);
  KN_PRINT_Q15_SIZE(data, data_shape.FlatSize());
}

void Sigmoid(const RuntimeShape& data_shape, float* data) {
  reference_ops::Logistic(data_shape, data, data_shape, data);
}

void Tanh(int32_t cell_state_scale_power, const RuntimeShape& input_data_shape,
          int16_t* input_data, const RuntimeShape& output_data_shape,
          int16_t* output_data) {
  KN_PRINTS("tanh");
  KN_PRINT_Q15_SIZE(input_data, input_data_shape.FlatSize());
  int32_t tanh_input_left_shift = (15 + cell_state_scale_power) - 3;
  int32_t input_multiplier = 0;
  if (tanh_input_left_shift < 0) /* handling negative shift value */
  {
    tanh_input_left_shift = -tanh_input_left_shift;
    input_multiplier = 3;
  }
  reference_integer_ops::Tanh(input_multiplier, tanh_input_left_shift,
                              input_data_shape, input_data, output_data_shape,
                              output_data);
  KN_PRINT_Q15_SIZE(output_data, output_data_shape.FlatSize());
}

void Tanh(int32_t cell_state_scale_power, const RuntimeShape& input_data_shape,
          float* input_data, const RuntimeShape& output_data_shape,
          float* output_data) {
  reference_ops::Tanh(input_data_shape, input_data, output_data_shape,
                      output_data);
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const int16_t* input1_data, const int16_t* input2_data,
         int8_t* output_data) {
  KN_PRINT_Q15_SIZE(input1_data, shape.FlatSize());
  KN_PRINT_Q15_SIZE(input2_data, shape.FlatSize());
  KN_PRINTX(params.output_multiplier);
  KN_PRINTX(params.output_shift);
  KN_PRINTD(params.output_offset);
  reference_integer_ops::MulElementwise(shape.FlatSize(), params, input1_data,
                                        input2_data, output_data);

  KN_PRINT_Q7_SIZE(output_data, shape.FlatSize());
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const int16_t* input1_data, const int16_t* input2_data,
         int16_t* output_data) {
  reference_integer_ops::MulElementwise(shape.FlatSize(), params, input1_data,
                                        input2_data, output_data);

  KN_PRINT_Q15_SIZE(output_data, shape.FlatSize());
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const float* input1_data, const float* input2_data,
         float* output_data) {
  return reference_ops::Mul(params, shape, input1_data, shape, input2_data,
                            shape, output_data);
}

void FullyConnected(const FullyConnectedParams& params,
                    const RuntimeShape& input_shape, const int8_t* input_data,
                    const RuntimeShape& filter_shape, const int8_t* filter_data,
                    const RuntimeShape& bias_shape, const int32_t* bias_data,
                    const RuntimeShape& output_shape, int16_t* output_data) {
  //
  KN_PRINT_Q7_SIZE(input_data, input_shape.FlatSize());
  if (bias_data) {
    KN_PRINT_Q31_SIZE(bias_data, output_shape.FlatSize());
  }
  KN_PRINT_Q7_SIZE_ATMOST(filter_data, filter_shape.FlatSize(), 64);

  // offset

  KN_PRINTX(params.input_offset);
  KN_PRINTX(params.weights_offset);
  KN_PRINTX(params.output_offset);
  KN_PRINTX(params.output_multiplier);
  KN_PRINTX(params.output_shift);
  // dump inputOffset and bias
  // int in_dim = filter_shape.Dims(1);
  // int out_dim = filter_shape.Dims(0);

  tflite::reference_integer_ops::FullyConnected(
      params, input_shape, input_data, filter_shape, filter_data, bias_shape,
      bias_data, output_shape, output_data);

  KN_PRINT_Q15_SIZE(output_data, output_shape.FlatSize());
}

void FullyConnected(const FullyConnectedParams& params,
                    const RuntimeShape& input_shape, const int16_t* input_data,
                    const RuntimeShape& filter_shape, const int8_t* filter_data,
                    const RuntimeShape& bias_shape, const int64_t* bias_data,
                    const RuntimeShape& output_shape, int16_t* output_data) {
  return tflite::reference_integer_ops::FullyConnected(
      params, input_shape, input_data, filter_shape, filter_data, bias_shape,
      bias_data, output_shape, output_data);
}

void FullyConnected(const FullyConnectedParams& params,
                    const RuntimeShape& input_shape, const float* input_data,
                    const RuntimeShape& filter_shape, const float* filter_data,
                    const RuntimeShape& bias_shape, const float* bias_data,
                    const RuntimeShape& output_shape, float* output_data) {
  return tflite::reference_ops::FullyConnected(
      params, input_shape, input_data, filter_shape, filter_data, bias_shape,
      bias_data, output_shape, output_data);
}
//#endif

#endif // !defined LSMT_OPT
#if defined(DMX1A_LSTM_OPT)

void UpdateLstmCell(const LstmStepManager& step_info,
                    TfLiteEvalTensor* cell_state,
                    // Gate outputs
                    int16_t* forget_gate_output,
                    const int16_t* input_gate_output,
                    const int16_t* cell_gate_output,
                    // Mul parameters
                    const ArithmeticParams& forget_cell_mul_params,
                    const ArithmeticParams& input_mul_params,
                    const CellStateInfo& cell_state_info, int16_t* buffer) {
  auto cell_state_shape = step_info.StateShape();
  // Check offset validity to avoid memory overflow
  TFLITE_DCHECK_LE(step_info.CellStateOffset() + cell_state_shape.FlatSize(),
                   tflite::micro::GetTensorShape(cell_state).FlatSize());

  // Forget Gate x Cell State

  int ctof_exp = forget_cell_mul_params.output_shift + 16 - 2;
  int ctoi_exp = input_mul_params.output_shift + 16 - 2;
//  KN_PRINTD(ctoi_right_shift);
//  KN_PRINTD(ctof_right_shift);
  int cell_size = cell_state_shape.FlatSize();
  int loop = cell_size >> 2;
  int remain = cell_size & 3;

  int16_t* p_cs = tflite::micro::GetTensorData<int16_t>(cell_state) +
                  step_info.CellStateOffset();
  int16_t* p_cs_w = p_cs;
  int16_t* p_fg = forget_gate_output;
  const int16_t* p_cg = cell_gate_output;
  const int16_t* p_ig = input_gate_output;
  // forget_cell_mul_params
  vr128 VR_fg, VR_cs, VR_ig, VR_cg;
  vr128 VR_out;

  ulsr128 UR_cs = align_16x4_load(p_cs);
  ulsr128 UR_cs2 = align_16x4_store(p_cs_w);

  ulsr128 UR_fg = align_16x4_load(p_fg);
  ulsr128 UR_cg = align_16x4_load(p_cg);
  ulsr128 UR_ig = align_16x4_load(p_ig);

  if (loop > 0) {
    // vr128 VR_forget;

    load_16x4_vr_a(VR_fg, UR_fg, p_fg);
    load_16x4_vr_a(VR_cs, UR_cs, p_cs);
    load_16x4_vr_a(VR_cg, UR_cg, p_cg);
    load_16x4_vr_a(VR_ig, UR_ig, p_ig);

    convert_16I_to_32F_x4(VR_fg, ctof_exp);
    convert_16I_to_32F_x4(VR_cs, 0);

    convert_16I_to_32F_x4(VR_cg, 0);
    convert_16I_to_32F_x4(VR_ig, ctoi_exp);

    // cs*fg  co >> + cg*ig >> ci
    for (int ii = 0; ii < loop - 1; ii++) {
      VR_out = vmuls(VR_fg, VR_cs, 0);

      // KN_PRINT_VR(VR_out);
      // ctof_right shift
      VR_out = vmacs_adj(VR_out, VR_cg, VR_ig, 0, 0);
      // KN_PRINT_VR(VR_out);

      convert_32F_to_16I_x4(VR_out, 0, 1);

      // KN_PRINTX_VR(VR_out);
      store_16x4_vr_a(VR_out, UR_cs2, p_cs_w);

      load_16x4_vr_a(VR_fg, UR_fg, p_fg);
      load_16x4_vr_a(VR_cs, UR_cs, p_cs);
      load_16x4_vr_a(VR_cg, UR_cg, p_cg);
      load_16x4_vr_a(VR_ig, UR_ig, p_ig);

      convert_16I_to_32F_x4(VR_fg, ctof_exp);

      convert_16I_to_32F_x4(VR_cs, 0);
      convert_16I_to_32F_x4(VR_cg, 0);
      convert_16I_to_32F_x4(VR_ig, ctoi_exp);
    }

    VR_out = vmuls(VR_fg, VR_cs, 0);

    KN_PRINT_VR(VR_out);
    // ctof_right shift
    VR_out = vmacs_adj(VR_out, VR_cg, VR_ig, 0, 0);
    convert_32F_to_16I_x4(VR_out, 0, 1);

    KN_PRINTX_VR(VR_out);
    store_16x4_vr_a(VR_out, UR_cs2, p_cs_w);
    flush_16x4(UR_cs2, p_cs_w);
  }

  if (remain) {
    load_16x4_vr_a(VR_fg, UR_fg, p_fg);
    load_16x4_vr_a(VR_cs, UR_cs, p_cs);
    load_16x4_vr_a(VR_cg, UR_cg, p_cg);
    load_16x4_vr_a(VR_ig, UR_ig, p_ig);

    convert_16I_to_32F_x4(VR_fg, ctof_exp);
    convert_16I_to_32F_x4(VR_cs, 0);

    convert_16I_to_32F_x4(VR_cg, 0);
    convert_16I_to_32F_x4(VR_ig, ctoi_exp);
    VR_out = vmuls(VR_fg, VR_cs, 0);

    // KN_PRINT_VR(VR_out);
    // ctof_right shift
    VR_out = vmacs_adj(VR_out, VR_cg, VR_ig, 0, 0);
    // KN_PRINT_VR(VR_out);

    convert_32F_to_16I_x4(VR_out, 0, 1);

    // KN_PRINTX_VR(VR_out);
    // cs*fg  co >> + cg*ig >> ci
    for (int ii = 0; ii < remain; ii++) {
      store16x1_vr_postI(VR_out, p_cs_w, INC1, VRQ0);
      VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
    }
  }
#ifdef KN_DEBUG
  // int16_t* out_cell_state = tflite::micro::GetTensorData<int16_t>(cell_state)
  // +
  //                          step_info.CellStateOffset();
  // KN_PRINT_Q15_SIZE(out_cell_state, cell_size);
#endif

  // Multiplier is equivalent to 0.5 here so adding 1 to shifts
  // xa_nn_lstm_cell_state_update_16(
  //     tflite::micro::GetTensorData<int16_t>(cell_state) +
  //        step_info.CellStateOffset(),
  //    forget_gate_output, cell_gate_output, input_gate_output,
  //    forget_cell_mul_params.output_shift - 1,
  //    input_mul_params.output_shift - 1, cell_state_info.quantized_cell_clip,
  //    cell_state_shape.FlatSize());
}
#endif

#if defined(HMD1A_LSTM_OPT)

void UpdateLstmCell(const LstmStepManager& step_info,
                    TfLiteEvalTensor* cell_state,
                    // Gate outputs
                    int16_t* forget_gate_output,
                    const int16_t* input_gate_output,
                    const int16_t* cell_gate_output,
                    // Mul parameters
                    const ArithmeticParams& forget_cell_mul_params,
                    const ArithmeticParams& input_mul_params,
                    const CellStateInfo& cell_state_info, int16_t* buffer) {
  auto cell_state_shape = step_info.StateShape();
  // Check offset validity to avoid memory overflow
  TFLITE_DCHECK_LE(step_info.CellStateOffset() + cell_state_shape.FlatSize(),
                   tflite::micro::GetTensorShape(cell_state).FlatSize());

  // Forget Gate x Cell State

  int ctof_exp = forget_cell_mul_params.output_shift + 16 - 2;
  int ctoi_exp = input_mul_params.output_shift + 16 - 2;
//  KN_PRINTD(ctoi_right_shift);
//  KN_PRINTD(ctof_right_shift);
  int cell_size = cell_state_shape.FlatSize();
  int loop = cell_size >>1;
  int remain = cell_size & 1;

  int16_t* p_cs = tflite::micro::GetTensorData<int16_t>(cell_state) +
                  step_info.CellStateOffset();
  int16_t* p_cs_w = p_cs;
  int16_t* p_fg = forget_gate_output;
  const int16_t* p_cg = cell_gate_output;
  const int16_t* p_ig = input_gate_output;
  // forget_cell_mul_params
  vr64 VR_fg, VR_cs, VR_ig, VR_cg;
  vr64 VR_out;

  //ulsr32 UR_cs = align_16x2_load(p_cs);
  //ulsr32 UR_cs2 = align_16x2_store(p_cs_w);
  //
  //ulsr32 UR_fg = align_16x2_load(p_fg);
  //ulsr32 UR_cg = align_16x2_load(p_cg);
  //ulsr32 UR_ig = align_16x2_load(p_ig);

  if (loop > 0) {
    // vr128 VR_forget;

    load16x2_vr_postI(VR_fg,  p_fg, INC1);
    load16x2_vr_postI(VR_cs,  p_cs, INC1);
    load16x2_vr_postI(VR_cg,  p_cg, INC1);
    load16x2_vr_postI(VR_ig,  p_ig, INC1);

    convert_16I_to_32F_x2(VR_fg, ctof_exp);
    convert_16I_to_32F_x2(VR_cs, 0);

    convert_16I_to_32F_x2(VR_cg, 0);
    convert_16I_to_32F_x2(VR_ig, ctoi_exp);

    // cs*fg  co >> + cg*ig >> ci
    for (int ii = 0; ii < loop - 1; ii++) {
      VR_out = vmuls(VR_fg, VR_cs, 0);

      VR_out = vmacs(VR_out, VR_cg, VR_ig, 0, 0);
      // KN_PRINT_VR(VR_out);

      convert_32F_to_16I_x2(VR_out, 0, 1);

      // KN_PRINTX_VR(VR_out);
      store16x2_vr_postI(VR_out, p_cs_w, INC1);

      load16x2_vr_postI(VR_fg, p_fg, INC1);
      load16x2_vr_postI(VR_cs, p_cs, INC1);
      load16x2_vr_postI(VR_cg, p_cg, INC1);
      load16x2_vr_postI(VR_ig, p_ig, INC1);

      convert_16I_to_32F_x2(VR_fg, ctof_exp);
      convert_16I_to_32F_x2(VR_cs, 0);
      convert_16I_to_32F_x2(VR_cg, 0);
      convert_16I_to_32F_x2(VR_ig, ctoi_exp);
    }

    VR_out = vmuls(VR_fg, VR_cs, 0);

    KN_PRINT_VR(VR_out);
    // ctof_right shift
    VR_out = vmacs(VR_out, VR_cg, VR_ig, 0, 0);
    convert_32F_to_16I_x2(VR_out, 0, 1);

    KN_PRINTX_VR(VR_out);
    store16x2_vr_postI(VR_out, p_cs_w, INC1);

  }

  if (remain) {
    load16x1_vr_postI(VR_fg, p_fg, INC1, VRQ0);
    load16x1_vr_postI(VR_cs, p_cs, INC1, VRQ0);
    load16x1_vr_postI(VR_cg, p_cg, INC1, VRQ0);
    load16x1_vr_postI(VR_ig, p_ig, INC1, VRQ0);

    convert_16I_to_32F_x2(VR_fg, ctof_exp);
    convert_16I_to_32F_x2(VR_cs, 0);

    convert_16I_to_32F_x2(VR_cg, 0);
    convert_16I_to_32F_x2(VR_ig, ctoi_exp);
    VR_out = vmuls(VR_fg, VR_cs, 0);
    VR_out = vmacs(VR_out, VR_cg, VR_ig, 0, 0);

    convert_32F_to_16I_x2(VR_out, 0, 1);

    store16x1_vr_postI(VR_out, p_cs_w, INC1, VRQ0);


  }


  // Multiplier is equivalent to 0.5 here so adding 1 to shifts
  // xa_nn_lstm_cell_state_update_16(
  //     tflite::micro::GetTensorData<int16_t>(cell_state) +
  //        step_info.CellStateOffset(),
  //    forget_gate_output, cell_gate_output, input_gate_output,
  //    forget_cell_mul_params.output_shift - 1,
  //    input_mul_params.output_shift - 1, cell_state_info.quantized_cell_clip,
  //    cell_state_shape.FlatSize());
}
#endif

#if !defined(DMX1A_LSTM_OPT) && !defined(HMD1A_LSTM_OPT)

void Clipping(const int v_size, const CellStateInfo& cell_state_info,
              int16_t* vector) {
  for (int i = 0; i < v_size; i++) {
    vector[i] =
        std::max(std::min(cell_state_info.quantized_cell_clip, vector[i]),
                 static_cast<int16_t>(-cell_state_info.quantized_cell_clip));
  }
}

void Clipping(const int v_size, const CellStateInfo& cell_state_info,
              float* vector) {
  for (int i = 0; i < v_size; i++) {
    vector[i] = std::max(std::min(cell_state_info.cell_clip, vector[i]),
                         -cell_state_info.cell_clip);
  }
}

void UpdateLstmCell(const LstmStepManager& step_info,
                    TfLiteEvalTensor* cell_state,
                    // Gate outputs
                    float* forget_gate_output, const float* input_gate_output,
                    const float* cell_gate_output,
                    // Mul parameters
                    const ArithmeticParams& forget_cell_mul_params,
                    const ArithmeticParams& input_mul_params,
                    const CellStateInfo& cell_state_info, float* buffer) {
  // Check offset validity to avoid memory overflow
  TFLITE_DCHECK_LE(
      step_info.CellStateOffset() + step_info.StateShape().FlatSize(),
      tflite::micro::GetTensorShape(cell_state).FlatSize());

  auto cell_state_shape = step_info.StateShape();
  // Forget Gate x Cell State
  Mul(forget_cell_mul_params, forget_gate_output,
      tflite::micro::GetTensorData<float>(cell_state) +
          step_info.CellStateOffset(),
      tflite::micro::GetTensorData<float>(cell_state) +
          step_info.CellStateOffset(),
      cell_state_shape.FlatSize());
  // Input Gate x Cell Gate
  Mul(input_mul_params, input_gate_output, cell_gate_output, buffer,
      cell_state_shape.FlatSize());

  // Update the cell state
  AddElementWise(tflite::micro::GetTensorData<float>(cell_state) +
                     step_info.CellStateOffset(),
                 buffer,
                 /*n_batch=*/cell_state_shape.DimsData()[0],
                 /*n_state=*/cell_state_shape.DimsData()[1],
                 tflite::micro::GetTensorData<float>(cell_state) +
                     step_info.CellStateOffset());

  if (cell_state_info.cell_clip > 0) {
    Clipping(cell_state_shape.FlatSize(), cell_state_info,
             tflite::micro::GetTensorData<float>(cell_state) +
                 step_info.CellStateOffset());
  }
}

#endif

void UpdateLstmCellInteger(int n_batch, int n_cell, int16_t* cell_state,
                           int32_t cell_state_scale, const int16_t* input_gate,
                           int16_t* forget_gate, const int16_t* cell_gate,
                           bool use_cifg, int16_t clip) {
#if !defined(HIFI5)
  // Use the forget_gate array as scratch, as input_gate array is not allocated
  // in CIFG case. (Be careful not to write to the scratch before reading the
  // forget gate data.)
  int16_t* scratch = forget_gate;

  tensor_utils::PortableCwiseMul(forget_gate, cell_state, n_batch, n_cell, 15,
                                 cell_state);
  if (use_cifg) {
    tensor_utils::PortableSub1Vector(forget_gate, n_batch * n_cell, scratch);
    tensor_utils::PortableCwiseMul(scratch, cell_gate, n_batch, n_cell,
                                   30 + cell_state_scale, scratch);
  } else {
    tensor_utils::PortableCwiseMul(input_gate, cell_gate, n_batch, n_cell,
                                   30 + cell_state_scale, scratch);
  }

  tensor_utils::PortableCwiseAdd(cell_state, scratch, n_batch, n_cell,
                                 cell_state);

  if (clip > 0) {
    tensor_utils::PortableCwiseClipping(cell_state, n_batch * n_cell, clip);
  }
#else
  if (use_cifg) {
    calc_cell_state_with_cifg(cell_state, forget_gate, cell_gate, 15,
                              30 + cell_state_scale, clip, n_batch * n_cell);
  } else {
    calc_cell_state_without_cifg(cell_state, forget_gate, cell_gate, input_gate,
                                 15, 30 + cell_state_scale, clip,
                                 n_batch * n_cell);
  }

#endif  // !defined(HIFI5)
}

// Increment the data offset so the sigle time step invocation call can access
// the corresponding input/output tensor data at the time step
void LstmStepManager::UpdateTime() {
  current_time_ += 1;
  TFLITE_DCHECK_LE(current_time_, size_info_.time_steps);
  // default as one batch per inference
  int input_step = size_info_.input_dimension;
  int output_step = size_info_.state_dimension;
  // time major: batch inference
  if (size_info_.time_major) {
    input_step = input_step * size_info_.batch_size;
    output_step = output_step * size_info_.batch_size;
  }

  input_offset_ += input_step;
  output_offset_ += output_step;
}

// Increment the data offset so the sigle time step invocation call can access
// the corresponding hidden/cell state tensor data at the time step (for single
// batch inference only)
void LstmStepManager::UpdateBatch() {
  current_batch_ += 1;
  TFLITE_DCHECK_LE(current_batch_, size_info_.batch_size);
  // batch inference for time major: no action needed
  if (size_info_.time_major) {
    return;
  }
  // otherwise: singe batch inference, go to the next batch
  hidden_state_offset_ += size_info_.state_dimension;
  cell_state_offset_ += size_info_.state_dimension;
}

// Input shape for each single time LSTM invocation.
// Multi-batch for time_major input
RuntimeShape LstmStepManager::InputShape() const {
  int batch_size = 1;
  if (size_info_.time_major) {
    batch_size = size_info_.batch_size;
  }
  const int dims[2] = {batch_size, size_info_.input_dimension};
  const int32_t* dims_data = reinterpret_cast<const int32_t*>(dims);
  return RuntimeShape(2, dims_data);
}

// State shape (both hidden and cell) for each single time LSTM invocation.
// Multi-batch for time_major input
RuntimeShape LstmStepManager::StateShape() const {
  int batch_size = 1;
  if (size_info_.time_major) {
    batch_size = size_info_.batch_size;
  }
  const int dims[2] = {batch_size, size_info_.state_dimension};
  const int32_t* dims_data = reinterpret_cast<const int32_t*>(dims);
  return RuntimeShape(2, dims_data);
}
}  // namespace lstm_internal
}  // namespace tflite
