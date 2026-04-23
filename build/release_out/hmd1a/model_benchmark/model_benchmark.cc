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
  
#include <stdint.h>
#ifndef KN_SUPPORT_ISS_PROF
#define KN_SUPPORT_ISS_PROF
#endif

#ifdef _MSC_VER
//#define DUMP_RNDINPUT
#endif
#ifdef DUMP_RNDINPUT
#include "cnpy.h"
#endif
#define NPY_HEADER_OFFSET 0x80 //HARDCODE:FIXME NPY header change some times
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/types.h"
//#include "tensorflow/lite/micro/all_ops_resolver.h"

#include "tensorflow/lite/micro/recording_micro_allocator.h"
#include "tensorflow/lite/micro/recording_micro_interpreter.h"
#include "tensorflow/lite/micro/micro_op_resolver.h"
#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount
//#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/memory_helpers.h"
#include "tensorflow/lite/micro/kernels/micro_ops.h"
//
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/tools/benchmarking/op_resolver.h"
//#include "tensorflow/lite/micro/benchmarks/micro_benchmark.h"
#ifdef IA8201
#include "tensorflow/lite/micro/ia8201/debug_log_callback.h"
#include "tensorflow/lite/micro/ia8201/xt_profiler.h"
#include "AVL.h"
#endif
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "crc32.h"
#include "tensorflow/lite/micro/tools/benchmarking/op_resolver.h"
#define TENSOR_ARENA_FACTOR (1.05f) // actuall allocate and plus 5%
#define MAX_MODEL_NUM 8
#define MAX_MODEL_INPUTS 8
#define KMM_ALIGNUP(x, a) ((((uintptr_t)(x))+((a)-1)) & ~(((uintptr_t)(a))-1))
void* aligned_malloc(uint32_t size, uint32_t align, void **alloc_ptr=nullptr) {
	void* p;
	p = malloc(size + align);
	if (alloc_ptr) *alloc_ptr = p;
	p = (void*)KMM_ALIGNUP(p, align);
	return p;
}

/**
 * Tests to ensure arena memory allocation does not regress by more than 3%.
 */

namespace {

//const bool kIs64BitSystem = (sizeof(void*) == 8);

constexpr int kKeywordModelTensorArenaSize = 1024 * 1024; // ~ 1MB
//uint8_t keyword_model_tensor_arena[kKeywordModelTensorArenaSize];

}  // namespace


 //static tflite::MicroErrorReporter error_reporter;
 //static tflite::AllOpsResolver all_ops_resolver;
using TflmOpResolver = tflite::MicroMutableOpResolver<113>;//98 + 2 + 9 > ;
 //static VAR_ALIGN_16 uint8_t interpreter_buffer[MAX_MODEL_NUM][sizeof(tflite::RecordingMicroInterpreter)];
 static uint32_t model_size[MAX_MODEL_NUM];
 int verbose = 0;
 int stream = 0;
 int test_tensor = 0;
 int check_crc32 = 0;
 static int usage(const char *prog)
 {

	 printf("\n%s  <model1.tflite> <model2.tflite> -n [numpy file for input test] -v ... \n", prog);
	 printf("\tinput multiple models share the same tensor arena buffer\n"
		    "\tmaximum number of models is %d\n"
		    "\tEnter models in order of downloading\n", MAX_MODEL_NUM);

	
	 //printf("%s <model 1> <model 2> ... \n", prog);

	 return -1;
 }

// static float temp_feat_float[1024 * 64];
 //template<typename inputT>

 // static float temp_feat_float[1024 * 64];
 template <typename inputT>
 void read_from_npy(tflite::MicroInterpreter* interpreter, const char* filename,
                    inputT* buf, unsigned int bytes) {
   char header[16];
#if 0//def _MSC_VER

   cnpy::NpyArray array_np = cnpy::npy_load(filename);
   inputT* data = array_np.data<inputT>();

   // check size
   assert(array_np.word_size == sizeof(inputT));
   assert(bytes == array_np.num_bytes());

   memcpy(buf, data, bytes);

#else
   FILE* fp = fopen(filename, "rb");
   if (!fp) {
     fprintf(stderr, "npy [%s] is not found!\n", filename);
     return;
   };
   fread(header, sizeof(char), 6, fp);

   if (header[1] == 'N' && header[2] == 'U' && header[3] == 'M' &&
       header[4] == 'P' && header[5] == 'Y') {
     // check size
     fseek(fp, 0, SEEK_END);
     unsigned int file_size = ftell(fp) - (NPY_HEADER_OFFSET);  // minus header
     fseek(fp, (NPY_HEADER_OFFSET), SEEK_SET);
     unsigned int bytes_read;
     if (file_size == bytes) {
       bytes_read = fread(buf, sizeof(int8_t), bytes, fp);
       if (bytes_read != bytes) {
         fprintf(stderr, "npy [%s] is size error!\n", filename);
       }
     }
     /*else if (file_size == bytes * sizeof(float)) {
             // consider npy is float type
             bytes_read = fread(temp_feat_float, sizeof(float), bytes, fp);
             if (bytes_read != bytes)
             {
                     fprintf(stderr, "npy [%s] is size error!\n", filename);
             }
            Convert_IeeeFloat_to_8bit((uint32_t *)buf, temp_feat_float,
                    bytes, input->params.scale,
                     input->params.zero_point);
     }*/
     else {
       printf("NPY SIZE error! file size - 128 = %d expected: %d\n", file_size,
              bytes);
     }
   } else {
     printf("not a numpy file, read in raw type");
   }
   fclose(fp);
#endif
 }
 void * read_from_npy(tflite::MicroInterpreter* interpreter, const char* filename,
                    uint32_t* size_out) {
   char header[16];
#ifdef DUMP_RNDINPUT

   cnpy::NpyArray array_np = cnpy::npy_load(filename);
   inputT* data = array_np.data<inputT>();

   // check size
   assert(array_np.word_size == sizeof(inputT));
   assert(bytes == array_np.num_bytes());

   memcpy(buf, data, bytes);

#else
   FILE* fp = fopen(filename, "rb");
   void* buf;
   if (!fp) {
     fprintf(stderr, "npy [%s] is not found!\n", filename);
     return NULL;
   };
   fread(header, sizeof(char), 6, fp);

   if (header[1] == 'N' && header[2] == 'U' && header[3] == 'M' &&
       header[4] == 'P' && header[5] == 'Y') 
   {
     // check size
     fseek(fp, 0, SEEK_END);
     unsigned int file_size = ftell(fp) - (NPY_HEADER_OFFSET);  // minus header
     fseek(fp, (NPY_HEADER_OFFSET), SEEK_SET);
     unsigned int bytes_read;
     buf = malloc(file_size);

     if (size_out) *size_out = file_size;
     if (!buf) return  0;
     
       bytes_read = fread(buf, sizeof(int8_t), file_size, fp);

	 }
	 else {
		 printf("not a numpy file, read in raw type");
           return NULL;
	 }

	 fclose(fp);
   return buf;
#endif
 }
 template < typename inputT>
 void SetRandomInput( const int random_seed, tflite::MicroInterpreter *interpreter_,
	 int input_idx =0, int is_float16 = 0, const char *prefix="model") {
	 // The pseudo-random number generator is initialized to a constant seed
	 std::srand(random_seed);
	 TfLiteTensor* input = interpreter_->input(input_idx);
	 if (0==is_float16)
	 {
		 // Pre-populate input tensor with random values.
		 int input_length = input->bytes / sizeof(inputT);
		 inputT* input_values = tflite::GetTensorData<inputT>(input);
		 std::vector<inputT> vect;

		 {
			 for (int i = 0; i < input_length; i++) {
				 // Pre-populate input tensor with a random value based on a constant seed.
				 input_values[i] = static_cast<inputT>(
					 static_cast <inputT> (std::rand()) / static_cast <inputT> (RAND_MAX));
				
				 vect.push_back(input_values[i]);
			 }
		 }
	 }
	 else {
		 //-populate input tensor with random values.
			 int input_length = input->bytes / sizeof(int16_t);
			 int16_t* input_values = tflite::GetTensorData<int16_t>(input);
		 std::vector<int16_t> vect;

		 {
			 for (int i = 0; i < input_length; i++) {
				 // Pre-populate input tensor with a random value based on a constant seed.
				float input_rand = static_cast<float>(
					 static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX));
				AScalar aflt = AScalar(input_rand);
				input_values[i] = aflt.to_float16();
				 vect.push_back(input_values[i]);
	 }
 }
	 }
 // dump reandom inputs in npy
#ifdef DUMP_RNDINPUT
	 char input_name[256];
	// const RuntimeShape input_shape = tflite::micro::GetTensorShape(input);
	
	 snprintf(input_name, 256, "%s_input_%02d.npy",prefix, input_idx);
	 cnpy::npy_save(input_name, vect, "w");
#endif
 }
#ifdef __XTENSA__
#define KN_GET_ISS_CYCLES_IF_CC_NO_FUNC(c,x,b,a)                  \
{                                                         \
    if (c)                                                \
    {                                                     \
        xt_iss_switch_mode(XT_ISS_CYCLE_ACCURATE);        \
        xt_iss_client_command("all", "enable");           \
        xt_iss_profile_enable();                          \
        b = XT_RSR_CCOUNT();                              \
        x;                                                \
        a = XT_RSR_CCOUNT();                              \
        xt_iss_profile_disable();                         \
        xt_iss_client_command("all", "disable");          \
    }                                                     \
    else                                                  \
    {                                                     \
        x;                                                \
    }                                                     \
}
#else
#define KN_GET_ISS_CYCLES_IF_CC_NO_FUNC(c,x,b,a)          x        
#endif

#if defined (DMX1A)
 void Convert_IEEE_Float_to_8bit(int8_t* pOut, float* pIn, uint16_t size, const AScalar& inv_scale, const AScalar& zero_point)
 {

   int loopLim = size >> 2;
   vr128 VR_dataIn;
   vr128 VR_scale = vseta_vr(0, 0, 0);
   vr128 VR_zeroPoint = vseta_vr(0, 0, 0);
   vr128 VR_out;
   vr128 VR_q7_out = vseta_vr(0, 0, 0);
   ulsr128 UR_dataIn = align_32x4_load(pIn);
   load_32x4_vr_a(VR_dataIn, UR_dataIn, pIn);
   replicate_ar(VR_scale, 0xf, inv_scale.fr);
   replicate_ar(VR_zeroPoint, 0xf, zero_point.fr);
   convert_IEEE_float_to_32F_x4(VR_dataIn);
   uint32_t* pDst = (uint32_t*)pOut;
   for (int i = 0; i < loopLim - 1; i++)
   {
     VR_out = vmacs_adj(VR_zeroPoint, VR_scale, VR_dataIn, 0, 0);
     VR_out = vexp_adji(VR_out, 8);
     convert_32F_to_16I_x4(VR_out, 15, 1);
     rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
     store32x1_vr_postI(VR_q7_out, pDst, INC1, VRQ0);
     load_32x4_vr_a(VR_dataIn, UR_dataIn, pIn);
     convert_IEEE_float_to_32F_x4(VR_dataIn);
   }

   VR_out = vmacs_adj(VR_zeroPoint, VR_scale, VR_dataIn, 0, 0);
   VR_out = vexp_adji(VR_out, 8);
   convert_32F_to_16I_x4(VR_out, 15, 1);

   rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
   store32x1_vr_postI(VR_q7_out, pDst, INC1, VRQ0);
 }

#endif

#ifdef HMD1A


 void Convert_IEEE_Float_to_8bit(int8_t* pOut, float* pIn, uint16_t size, const AScalar& inv_scale, const AScalar& zero_point)
 {

   int loopLim = size >> 2;
   vr64 VR_dataIn, VR_dataIn2;
   vr64 VR_scale = vseta_vr(0, 0);
   vr64 VR_zeroPoint = vseta_vr(0, 0);
   vr64 VR_out;
   vr64 VR_q7_out = vseta_vr(0, 0);
   ulsr32 UR_dataIn = align_32x2_load(pIn);
   load_32x2_vr_a(VR_dataIn, UR_dataIn, pIn);
   replicate_ar(VR_scale, 0x3, inv_scale.fr);
   replicate_ar(VR_zeroPoint, 0x3, zero_point.fr);

   uint32_t* pDst = (uint32_t*)pOut;
   for (int i = 0; i < loopLim; i++)
   {
     load_32x2_vr_a(VR_dataIn2, UR_dataIn, pIn);
     convert_IEEE_float_to_32F_x2(VR_dataIn);
     convert_IEEE_float_to_32F_x2(VR_dataIn2);
     VR_out = vmacs(VR_zeroPoint, VR_scale, VR_dataIn, 0, 0);
     VR_out = vexp_adji(VR_out, 8);
     convert_32F_to_16I_x2(VR_out, 15, 1);

     vr64 VR_out2 = vmacs(VR_zeroPoint, VR_scale, VR_dataIn2, 0, 0);
     VR_out2 = vexp_adji(VR_out2, 8);
     convert_32F_to_16I_x2(VR_out2, 15, 1);

     rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out2, 1);

     store32x1_vr_postI(VR_q7_out, pDst, INC1, VRQ0);
     load_32x2_vr_a(VR_dataIn, UR_dataIn, pIn);
   }

   //VR_out = vmacs(VR_zeroPoint, VR_scale, VR_dataIn, 0, 0 );
   //VR_out = vexp_adji(VR_out, 8);
   //convert_32F_to_16I_x2(VR_out, 15, 1);

   //rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
   //store32x1_vr_postI(VR_q7_out, pDst, INC1, VRQ0);
 }

#endif

 static int
	 generic_inferenc(tflite::MicroInterpreter* interpreter,  char* input_npy[], uint32_t* cycle_count)
 {
	 int input_size = interpreter->inputs_size();

	 uint32_t t0 = 0;
	 uint32_t t1 = 0;
   int input_iteration = 0;
	 TfLiteTensor* input0 = interpreter->input(0);
	 int input_random = 0;
  if (input_size > MAX_MODEL_INPUTS) {
    printf("too many inputs: %d\n", input_size);
    return -1;
  }
  void* input_buf[MAX_MODEL_INPUTS] = {0}; 
   uint32_t input_file_size[MAX_MODEL_INPUTS]={0};
	 for (int jj = 0; jj < input_size; jj++)
	 {
     //int input_count = 1;
		 if (input_npy && input_npy[jj])
		 {
        input_buf[jj] =
            read_from_npy(interpreter, input_npy[jj], &input_file_size[jj]);

		 } else {
          TfLiteTensor* input = interpreter->input(jj);
          input_buf[jj] = malloc(input->bytes);
          input_file_size[jj] = input->bytes;
          memset(input_buf[jj], 0, input->bytes);
     }
		
	 }
   //all input size divide sould equal integer .

   int input_quantize = 0;
  // TfLiteTensor* input = interpreter->inputs(0);
   if (interpreter->input(0)->type == kTfLiteFloat32)
   {
     input_iteration = input_file_size[0] / input0->bytes;
   }
   else {
     input_iteration = 1;
     input_quantize = 1;
   }
         printf("iteration: %d\n", input_iteration);
         for (int iter = 0; iter < input_iteration; iter++) {

           printf("invoke iteration: %8d\n", iter);
           TfLiteStatus invoke_status;
           // printf("arena size: %10d\n",
           // int(interpreter[idx]->arena_used_bytes()*1.05));
           TfLiteTensor* inputx;
           for (int jj = 0; jj < input_size; jj++)
           {
             inputx  = interpreter->input(jj);
             int isize = inputx->bytes;
             switch (jj) {
               case 0:
                 if (!input_quantize)
                 {
                   memcpy(inputx->data.int8,
                     (int8_t*)input_buf[jj] + iter * isize, isize);
                 }
                 else {

                   Convert_IEEE_Float_to_8bit(inputx->data.int8, (float*)((int8_t*)input_buf[jj] + iter * isize),
                     isize,
                     AScalar(1.0 / inputx->params.scale), AScalar(inputx->params.zero_point));
                 }
                 break;
               default:

                 printf("cache no copy\n");
               //case 1:  // copy cache
               //  memcpy(inputx->data.int8, (int8_t*)input_buf[jj], isize);
                 break;
             }
           }// end of cache
           KN_GET_ISS_CYCLES_IF_CC_NO_FUNC(
               1, invoke_status = interpreter->Invoke(), t0, t1);
           if (cycle_count) {
             *cycle_count = t1 - t0;
           }
           if (invoke_status != kTfLiteOk) {
             printf("invoke error: %d\n", invoke_status);
             break;
           }
#ifdef __XTENSA__
      printf("cycle: %d\n", *cycle_count);
#endif
           // save_as_file(name, (int8_t*)output->data.int8, output->bytes);
           int output_size = interpreter->outputs_size();

           for (int jj = 0; jj < output_size; jj++) {
             // dump  save as_files
             TfLiteTensor* output = interpreter->output(jj);
             printf("output[%3d] = size: %d, type: %s\n", jj, output->bytes,
                    TfLiteTypeGetName(output->type));
             if (!verbose && input_random) continue;
             if (output->type == kTfLiteInt8) {
               for (size_t m = 0; m < output->bytes; m++) {
                 printf("0x%02x (%4d), %c", (0xff & output->data.int8[m]),
                        output->data.int8[m], ((m + 1) & 7) == 0 ? '\n' : ' ');
               }
             } else if (output->type == kTfLiteFloat32) {
               // if(j < start)
               if (jj == 0) {
                 // dump logits
                 size_t out_size = output->bytes / sizeof(float);
                 for (size_t m = 0; m < out_size && m < 8; m++) {
                   printf("%.10f %c", (double)(output->data.f[m]),
                          ((m + 1) % 5) == 0 ? '\n' : ' ');
                 }
               }
                 // copy output cache to input feedback
                 //if (jj == 1) {
                 //  memcpy(input_buf[jj], output->data.f, output->bytes);
                 //}
               
             } else if (output->type == kTfLiteFloat16) {
               // float16
             }
             printf("\n");
           }
         }
         for (int jj = 0; jj < input_size; jj++) {

           if (input_buf[jj]) free(input_buf[jj]);
         }
	 return  0; //invoke_status;
 }
 int tensor_arena_test(int arena_size, uint8_t **model_buf, int nModels)
 {
	 
	 void* ptr;
	uint8_t *arena_buf = (uint8_t *)aligned_malloc(arena_size,16, &ptr);
	printf("arena addr: %p size: %d bytes\n", arena_buf, arena_size );
#if 0


	pckpt[0] = 0xdeadbeef;
	sckpt[0] = 0xdeadc0de;
#endif
	//tflite::MicroMemoryPlanner *mplanner  = CreateMem;
	//tflite::MemoryPlannerType mt = (tflite::MemoryPlannerType)0;//tflte::MemoryPlannerType::kGreedy; 
	tflite::MicroAllocator* gpAllocator2 = tflite::MicroAllocator::Create(arena_buf, arena_size);
	TflmOpResolver op_resolver;
	tflite::CreateOpResolver(op_resolver);
	for (int midx = 0; midx < nModels; midx++)
	{
		tflite::MicroInterpreter* interpreter2 = new tflite::MicroInterpreter(
			tflite::GetModel(model_buf[midx]), op_resolver, gpAllocator2);
		//write at bottom

		TfLiteStatus allocate_status = interpreter2->AllocateTensors();

		
		generic_inferenc(interpreter2, NULL, NULL);
		if (allocate_status != kTfLiteOk)
		{
			printf("***ERROR*** cannot allocate tensor successful!\n");
			return -1;
		}
#if 0
		if (*pckpt != 0xdeadbeef)
		{
			printf("***ERROR*** memory corrupt at head!\n");
			return -2;
		}
		if (*sckpt != 0xdeadc0de)
		{
			printf("***ERROR*** memory corrupt at tail!\n");
			return -1;
		}
#endif
	}
	printf("testing allocate arena %d  buffer for %d models successfully!\n", arena_size, nModels);
	free(ptr);
	 return 0;
 }

 
 int
 stream_inference(tflite::MicroInterpreter *interpreter, const char *input_stream_npy, uint32_t *cycle_count)
 {

	 uint32_t t0 = 0;
	 uint32_t t1 = 0;
	 int status = 0;
	 printf("stream mode\n");
	 TfLiteTensor* input0 = interpreter->input(0);
	 int input_size = 1;
	 void* buf;
	 // allocaltion 
#ifdef DUMP_RNDINPUT
	 cnpy::NpyArray array_np = cnpy::npy_load(input_stream_npy);
	 int read_bytes = array_np.num_bytes();
	 
#else
	 FILE* fp = fopen(input_stream_npy, "rb");
	 if (!fp) { fprintf(stderr, "npy [%s] is not found!\n", input_stream_npy); return -1; };
	 //fread(header, sizeof(char), 6, fp);

	 
		 // check size 

		 fseek(fp, 0, SEEK_END);
		 unsigned int read_bytes = ftell(fp) - (NPY_HEADER_OFFSET);// minus header

#endif
	 buf = malloc(read_bytes);
	 int input_total;
	 {

		 switch (input0->type) {
		 case kTfLiteInt8:
			 read_from_npy<int8_t>(interpreter, input_stream_npy, (int8_t*)buf, read_bytes);
			 input_size = input0->bytes / sizeof(int8_t);
			 input_total = read_bytes / sizeof(int8_t);
			 break;
		 case kTfLiteFloat32:
			 read_from_npy<float>(interpreter, input_stream_npy, (float*)buf, read_bytes);
			 input_size = input0->bytes / sizeof(float);
			 input_total = read_bytes / sizeof(float);
			 break;
		 default:
			 printf("un support input type");
			 break;
		 }

	 }
	 //DUMP_FLOAT_C("input_feat.cc", buf, input_total);

	 // allocate external status and init
	 int num_inputs = interpreter->inputs_size();
	 int num_outputs = interpreter->outputs_size();

	 float **external_states = (float **)malloc(sizeof(float**)*(num_inputs - 1));
	 for (int idx = 1 ; idx < num_inputs;  idx++)
	 {
		 int si = idx - 1;
		 TfLiteTensor *state = interpreter->input(idx);
		 external_states[si] = (float*)malloc(state->bytes);
		 memset(external_states[si], 0, state->bytes);
	 }
	 TfLiteStatus invoke_status;
	 
	 
	 int input_stream_times = input_total / input_size;
	 uint32_t max_cycle = 0;
	 int state_out_start_idx = 1;

	 for (int ii = 0; ii < input_stream_times; ii++)
	 {
		 // copy to input
		 memcpy(input0->data.f, (float*)buf + ii * input_size, input0->bytes);
		 // copy external state
		 for (int idx = 1; idx < num_inputs; idx++)
		 {
			 int si = idx - 1;
			 TfLiteTensor* state = interpreter->input(idx);
			 memcpy(state->data.f , external_states[si], state->bytes);
		 }

		 //invoke_status = interpreter->Invoke();
		 KN_GET_ISS_CYCLES_IF_CC_NO_FUNC(1, invoke_status = interpreter->Invoke(), t0,
			 t1);
		 if (max_cycle < t1 - t0)
		 {
			 max_cycle = t1 - t0;
			 printf("cycle max update: %u\n", max_cycle);
		 }
		 if (invoke_status != kTfLiteOk)
		 {
			 printf("Invoke Error: %d\n", invoke_status);
			 status = 1;
			 break;
		 }
		 for (int idx = state_out_start_idx; idx < num_outputs; idx++)
		 {
			 int si = idx - state_out_start_idx;
			 TfLiteTensor* state = interpreter->output(idx);
			 memcpy( external_states[si], state->data.f, state->bytes);
		 }
		 for (int jj = 0; jj < state_out_start_idx; jj++)
		 {
			 // dump  save as_files
			 TfLiteTensor* output = interpreter->output(jj);
			 printf("%10d output[%3d] = size: %d, type: %d\n", ii, jj, output->bytes, output->type);
			 if (!verbose)
				 continue;
			 if (output->type == kTfLiteInt8)
			 {
				 for (size_t m = 0; m < output->bytes; m++) {
					 printf("0x%02x (%4d), %c", (0xff & output->data.int8[m]), output->data.int8[m], ((m + 1) & 7) == 0 ? '\n' : ' ');
				 }
			 }
			 else if (output->type == kTfLiteFloat32)
			 {
				 //if(jj < )
				 for (size_t m = 0; m < output->bytes / sizeof(float); m++) {
					 printf("%.10f %c", (double)(output->data.f[m]), ((m + 1) % 5) == 0 ? '\n' : ' ');
				 }
			 }
			 printf("\n");
		 }
	 }
	 if (cycle_count)
	 {
		 *cycle_count = max_cycle;
	 }

	 return status;
 }

 int 
 multiple_models_size(char *model[], char *npy[], int num_model) //int argc, char *argv[])
 {
	 constexpr int allocator_buffer_size = kKeywordModelTensorArenaSize;// TENSOR_ARENA_SIZE
	 static VAR_ALIGN_16 uint8_t allocator_buffer[allocator_buffer_size];

	 //constexpr int persist_buffer_size = kKeywordModelTensorArenaSize;// TENSOR_ARENA_SIZE
	 //static VAR_ALIGN_8 uint8_t persist_buffer[persist_buffer_size];
	 //char name[256];


	 tflite::MicroInterpreter* interpreter[MAX_MODEL_NUM] = { NULL };
	 /*tflite::RecordingMicroAllocator* gpAllocator =
		 tflite::RecordingMicroAllocator::Create(allocator_buffer,
			 allocator_buffer_size, &error_reporter);*/
	// tflite::SimpleMemoryAllocator * simple_allocator = tflite::SimpleMemoryAllocator::Create(&error_reporter,
	//	 allocator_buffer, allocator_buffer_size, persist_buffer, persist_buffer_size);

	 tflite::RecordingMicroAllocator* gpAllocator =
		 tflite::RecordingMicroAllocator::Create(allocator_buffer, allocator_buffer_size);
	 uint32_t cycles_count[MAX_MODEL_NUM] = { 0 };
	 int last_model_idx = -1;
	 int run_model = 0;
		//int total_persist_used=0, total_scratch_used = 0;
		unsigned char* pKwModel[MAX_MODEL_NUM];
	 for (int ii = 0; ii < num_model && ii < MAX_MODEL_NUM; ii++)
	 {
		 FILE *fInDat;
		 char kwModelFileName[256];
		 strncpy(kwModelFileName, model[ii], 256);

		 fInDat = fopen(kwModelFileName, "rb");
		 if (fInDat == NULL) {
			 printf("Failed to open the input model file %s\n", model[ii]);
		     return -2;
		 }

		 fseek(fInDat, 0L, SEEK_END);
		 uint32_t modelSize = ftell(fInDat);
		 fseek(fInDat, 0, SEEK_SET);
		 pKwModel[ii] = (unsigned char*)aligned_malloc(modelSize, 8);
		 fread(pKwModel[ii], sizeof(char), modelSize, fInDat);
		 fclose(fInDat);
		 // dummy allocator
		int crcerr=0;
		 // check crc32 tail
		if (check_crc32)
		{

			if (modelSize <= 8)
			{
				printf("crc size error: %d", modelSize);
				crcerr = 1;
				break;
			}

			// Get signature 'TFL3' @ 4-7 bytes
			char* TFL_sig = (char*)pKwModel[ii];

			if (!(TFL_sig[4] == 'T' &&
				TFL_sig[5] == 'F' &&
				TFL_sig[6] == 'L' &&
				TFL_sig[7] == '3'))
			{
				fprintf(stderr, "crc32 wrong signature error: %02x %02x %02x %02x",
					TFL_sig[4], TFL_sig[5], TFL_sig[6], TFL_sig[7]);
				crcerr = 1;
				break;

			}

			// The last 32-bit are the CRC. Exclude them from the CRC calculation.
			uint32_t crc = tflite::Crc32(pKwModel[ii], modelSize - sizeof(uint32_t));
			uint32_t expected_crc =
				*reinterpret_cast<const uint32_t*>(
					&(reinterpret_cast<const int8_t*>(pKwModel[ii])
						[modelSize - sizeof(uint32_t)]));
			if (crc != expected_crc) {
				fprintf(stderr, "Wrong CRC: 0x%x, expected: 0x%x\n", crc, expected_crc);
				crcerr = 1;
				break;
			}
		}
		 if(crcerr==1)
		 {
		 	printf("error break!\n"); return -4;
		 }
		 int idx = ii; // from 0 as begin;
		 printf("INPUT MODEL [%s] tflite model size = %d bytes\n", kwModelFileName, modelSize);
		 model_size[idx] = modelSize;
		 TflmOpResolver ops_resolver;
		 tflite::CreateOpResolver(ops_resolver);
		 interpreter[idx] = new tflite::MicroInterpreter(
			 tflite::GetModel(pKwModel[ii]), ops_resolver, gpAllocator
			 );

		 TfLiteStatus allocate_status =  interpreter[idx]->AllocateTensors();

		//exit(1);
		 if (allocate_status != kTfLiteOk)
		 {
			 printf("***ERROR*** cannot allocate tensor successful! status: %d\n",allocate_status);
			 break;
		 }
		 
		 
		if (stream)
		{
			stream_inference(interpreter[idx], npy[0], &cycles_count[idx]);
		}
		else {
			generic_inferenc(interpreter[idx], npy, &cycles_count[idx]);
		}
		//cycles_count[idx] = t1 - t0;
		run_model = 1;
		last_model_idx = idx;

    gpAllocator->PrintAllocations();
		//int persist_used = tflite::AlignSizeUp(int(gpAllocator->*1.05), 4);
		//int scratch_used = tflite::AlignSizeUp(int(simple_allocator->scratch_size()*1.05), 4);
		// verify memory allocator
		printf("arena: %10d\n\t\n", int(interpreter[idx]->arena_used_bytes()* TENSOR_ARENA_FACTOR));
		
		//total_persist_used = persist_used; // the allocator is accumulate, get the last one
		//total_scratch_used = scratch_used;
		//simple_allocator->GetUsedBytes();
	 }
#if 1  // ndef NDEBUG
	 if (last_model_idx >= 0)
	 {
		 printf("model per cycles: ");
		 uint32_t total_cycles = 0;
		 for (int ii = 0; ii < num_model; ii++) {
			 printf(" %10d", cycles_count[ii]);
			 total_cycles += cycles_count[ii];
		 }
		 printf("\ncycle: %10d\n", total_cycles);
		 printf("arena: %10d\n", int(interpreter[last_model_idx]->arena_used_bytes()* TENSOR_ARENA_FACTOR));
	 }
#endif
	 if (test_tensor)
	 {
		 tensor_arena_test(int(gpAllocator->used_bytes() * TENSOR_ARENA_FACTOR), pKwModel, num_model);
	 }
 	 if (verbose) {
		// gpAllocator->PrintAllocations();
		// int tensor_arena_alloc = (int)(TENSOR_ARENA_FACTOR * gpAllocator->GetSimpleMemoryAllocator()->GetUsedBytes());
		// const tflite::RecordingSimpleMemoryAllocator* alloc = gpAllocator->GetSimpleMemoryAllocator();
		 // dump c macro
		 printf("// ======== copy following maximum model size info and arena size to RAF plugin ==========\n\n");
		 int total_model_size = 0;
		 printf("static const uint32_t INTERPRETER_MAX_MODEL_SIZE[%d] = {\n", num_model);
		 for (int ii = 0; ii < num_model; ii++)
		 {
			 int idx = ii ;
			 printf(" %d%c // %s \n", model_size[idx], ii == num_model -1 ? ' ' : ',', model[ii]);
			 total_model_size += model_size[idx];
		 }
		 printf("};\n#define INTERPRETER_MAX_MODEL_SIZE_TOTAL %d //(with 3%% extra guard)\n\n", total_model_size);
		// printf("#define TENSOR_ARENA_SIZE %d \n", tensor_arena_alloc);
		// printf("#define TENSOR_ARENA_HEAD %d \n", (int)(alloc->GetHeadUsedBytes()*1.05f));
		// printf("#define TENSOR_ARENA_TAIL %d \n", (int)(alloc->GetTailUsedBytes()*1.05f));

	 }
	 if (run_model)
	 {
		 for (int ii = 0; ii < num_model; ii++)
		 {
			 if (interpreter[ii])
				 delete interpreter[ii];
		 }
	 }
	 return kTfLiteOk;
 }

 int
 get_options(int argc, char *argv[],  char **model, char **input_npy, int *out_verbose, int *test_tensor) {

	 int midx = 0;
	 int nidx = 0;
	 argc--;
	 for(int ii = 1;argc; ii++)
	 {
		 if(strncmp(argv[ii], "-npy",4)==0)
		 {
			 input_npy[nidx] = argv[ii + 1];
			 printf("npy[%d]: %s for %d\n", nidx, input_npy[nidx], nidx);
			 argc--; ii++;
			 nidx++;
		 } else if (strncmp(argv[ii], "-v", 2) == 0) {
			 *out_verbose = 1;
		 }
		 else if (strncmp(argv[ii], "-t", 2) == 0) {
			 *test_tensor = 1;
		 }
		 else if (strncmp(argv[ii], "-str", 4) == 0) {
			 stream = 1;
		 }
		 else if (strncmp(argv[ii], "-crc", 4) == 0) {
			 check_crc32 = 1;
		 }
		 else{// if (strncmp(argv[ii], "-npy", 2) == 0) {
			 model[midx] = argv[ii];
			
			 printf("model[%d]: %s\n",midx,  model[midx]);
			 //argc--;
			 midx++;
		 }
		 argc--;
	 }
	 return midx;
 }




int main(int argc, char** argv) 
{
  
	static char *models[MAX_MODEL_NUM] = { 0 };
	static char *input_npy[MAX_MODEL_NUM] = { 0 };
  if (argc <= 1) return usage(argv[0]);
  else {
#ifndef __XTENSA__
	  RegisterDebugLogCallback(debug_log_printf, 0);
#endif
	  int num_model = get_options(argc, argv, models, input_npy, &verbose, & test_tensor);

	  return multiple_models_size( models, input_npy, num_model);
  }

  return kTfLiteOk;

}
