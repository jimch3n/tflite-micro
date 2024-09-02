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
#define KN_SUPPORT_ISS_PROF
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/examples/dtln/dtln_inout_data.h"

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/testing/micro_test.h"
#include "tensorflow/lite/schema/schema_generated.h"

#include "tensorflow/lite/micro/ia8201/xt_profiler.h"
#ifdef DMX1A
#include "tensorflow/lite/micro/examples/dtln/kn_dmx1a_dtln_noise_suppression_model_data.h"
#else
#include "tensorflow/lite/micro/examples/dtln/dtln_noise_suppression_model_data.h"
#endif
TF_LITE_MICRO_TESTS_BEGIN

MicroPrintf(
    "\nThis example demonstrates LSTM layers on HiFi DSP, NOT for evaluating "
    "noise suppression quality.\n");
TF_LITE_MICRO_TEST(TestInvoke) {
  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.

  #ifdef DMX1A
  const tflite::Model* model = ::tflite::GetModel(g_kn_dmx1a_dtln_noise_suppression_model_data);
  #else
  const tflite::Model* model =
      ::tflite::GetModel(g_dtln_noise_suppression_model_data);

  #endif
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    MicroPrintf(
        "Model pr ovided is schema version %d not equal "
        "to supported version %d.\n",
        model->version(), TFLITE_SCHEMA_VERSION);
  }

  // Pull in only the operation implementations we need.
  // This relies on a complete list of all the ops needed by this graph.

  tflite::MicroMutableOpResolver<3> micro_op_resolver;
  micro_op_resolver.AddUnidirectionalSequenceLSTM();
  micro_op_resolver.AddFullyConnected();
  micro_op_resolver.AddLogistic();

// Create an area of memory to use for input, output, and intermediate arrays.
//#if defined(IA8201) || defined(IA700) || defined(XTENSA)
//  constexpr int tensor_arena_size = 16 * 1024;  // remap coefficients
//#else
  constexpr int tensor_arena_size = 16 * 1024;
//#endif
  alignas(16) uint8_t tensor_arena[tensor_arena_size];

  // Build an interpreter to run the model with.
  tflite::MicroInterpreter interpreter(model, micro_op_resolver, tensor_arena,
                                       tensor_arena_size);
  TfLiteStatus alloc_status =  interpreter.AllocateTensors();

  TFLITE_CHECK_EQ(alloc_status, kTfLiteOk);
  printf("allocate tensor size: %d bytes\n",interpreter.arena_used_bytes());
  // Get information about the memory area to use for the model's input.
  TfLiteTensor* input = interpreter.input(0);

  // Make sure the input has the properties we expect.
  TF_LITE_MICRO_EXPECT(input != nullptr);
  TF_LITE_MICRO_EXPECT_EQ(3, input->dims->size);
  TF_LITE_MICRO_EXPECT_EQ(1, input->dims->data[0]);
  TF_LITE_MICRO_EXPECT_EQ(1, input->dims->data[1]);
  TF_LITE_MICRO_EXPECT_EQ(257, input->dims->data[2]);
  TF_LITE_MICRO_EXPECT_EQ(kTfLiteInt8, input->type);

  // Copy a spectrogram created from a noisy.wav audio file,
  // into the memory area used for the input.
  for (size_t i = 0; i < input->bytes; ++i) {
    input->data.int8[i] = feature_data[i];
  }
  TfLiteStatus invoke_status;
  unsigned int c0,c1;
  c0=c1=0;
  KN_GET_ISS_CYCLES_IF_CC(1,
  invoke_status = interpreter.Invoke(),c0, c1);
  printf("cycle: %d\n",c1-c0);
  // Run the model on this input and make sure it succeeds.
  //TfLiteStatus invoke_status = interpreter.Invoke();
  if (invoke_status != kTfLiteOk) {
    MicroPrintf("Invoke failed\n");
  }
  TF_LITE_MICRO_EXPECT_EQ(kTfLiteOk, invoke_status);

  // Get the output from the model, and make sure it's the expected size and
  // type.
  TfLiteTensor* output = interpreter.output(0);
  TF_LITE_MICRO_EXPECT_EQ(3, output->dims->size);
  TF_LITE_MICRO_EXPECT_EQ(1, output->dims->data[0]);
  TF_LITE_MICRO_EXPECT_EQ(1, output->dims->data[1]);
  TF_LITE_MICRO_EXPECT_EQ(257, output->dims->data[2]);
  TF_LITE_MICRO_EXPECT_EQ(kTfLiteInt8, output->type);

  int output_size =
      output->dims->data[0] * output->dims->data[1] * output->dims->data[2];
  for (int i = 0; i < output_size; i++)
    TF_LITE_MICRO_EXPECT_EQ(output->data.int8[i], golden_ref[i]);

  MicroPrintf("Ran successfully\n");
}

TF_LITE_MICRO_TESTS_END
