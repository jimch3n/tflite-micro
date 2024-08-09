

#include "iaxxx_tflite_model_converter.h"


int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("usage: %s <tflite> <out-tflite>\n", argv[0]);
    return -2;
  }

  FILE *fp_model = fopen(argv[1], "rb");
  uint8_t *model_data, *kn_model_data;

  if (!fp_model) { return -1; }

  printf("open model: %s\n", argv[1]);
  fseek(fp_model, 0, SEEK_END);
  size_t fsize = ftell(fp_model);
  fseek(fp_model, 0, SEEK_SET);

  model_data = (uint8_t *)malloc(fsize);
  kn_model_data = (uint8_t *)malloc(fsize + 16);
  if (!model_data) { return -3; }

  printf("model size: %d bytes\n", fsize);
  // std::cout << "Hello World!\n";
  int frs = fread(model_data, 1, fsize, fp_model);
  if (frs != fsize) { return -4; }

  uint32_t kn_model_size =
      iaxxx_tflite_model_converter(model_data, kn_model_data, 1, 1);

  std::ofstream ofs(argv[2], std::ofstream::binary);
  if (!ofs.is_open()) return false;
  ofs.write(reinterpret_cast<char *>(kn_model_data), kn_model_size);

  ofs.close();

  free(model_data);
  free(kn_model_data);
  fprintf(stderr, "knowles converted model size: %d\n", kn_model_data);
  return 0;
}
