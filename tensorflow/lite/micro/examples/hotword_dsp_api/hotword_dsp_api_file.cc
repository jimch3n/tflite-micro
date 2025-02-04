#include <cstdint>
#include <cstddef>
#include <cstdio>

#include <cstring>
#include <initializer_list>
#include <memory>
#include <random>
#include <type_traits>

//#include "tensorflow/python/graphs/testdata/hotword_y_google_large_model_data.h"
#include "tensorflow/python/graphs/testdata/okgoogle_audio_data.h"
#include "tensorflow/lite/micro/examples/hotword_dsp_api/common.h"
#include "tensorflow/lite/micro/micro_log.h"
// The maximum amount of tensor data that the interpreter can allocate
// TODO(b/193235829): this should be auto-generated
constexpr int g_tensor_arena_size = 45 * 1024;
uint8_t g_tensor_arena[g_tensor_arena_size] __attribute__((aligned(16)));

constexpr size_t kModelSize = 2e6;

struct FileCloser {
  void operator()(FILE* file) { fclose(file); }
};
bool ReadFile(const char* file_name, void* buffer, size_t buffer_size, size_t *read_size) {
  std::unique_ptr<FILE, FileCloser> file(fopen(file_name, "rb"));

  const size_t bytes_read =
      fread(buffer, sizeof(char), buffer_size, file.get());
  if (ferror(file.get())) {
    printf("Unable to read model file: %d\n", ferror(file.get()));
    return false;
  }
  if (!feof(file.get())) {
    // Note that http://b/297592546 can mean that this error message is
    // confusing.
    printf(
        "Model buffer (%d bytes) is too small for the model (%d bytes).\n",
        buffer_size, bytes_read);
    return false;
  }
  if (bytes_read == 0) {
    printf("No bytes read from model file.\n");
    return false;
  }
  if(read_size)
    {*read_size = bytes_read;}
  return true;
}
int main(int argc, char* argv[]) {
    if(argc < 1)
    {
        printf("need input tflite model as arg!\n");
        return -1;
    }
    // copy from generic_model_benchmark
  const char* model_filename = argv[1];
  alignas(16) static uint8_t model_data[kModelSize];
  size_t modelSize;
  if (!ReadFile(model_filename, model_data, kModelSize, &modelSize)) {
    printf("open file Error %s \n", model_filename);
    return -1;
  }
  printf("kModelSize: %d allocate: %d\n",kModelSize, modelSize);

  return RunHotwordDspApi(
      model_data,
      modelSize,
      g_tensor_arena, g_tensor_arena_size,
      reinterpret_cast<const int16_t*>(g_okgoogle_audio_data),
      g_okgoogle_audio_data_size);
}

