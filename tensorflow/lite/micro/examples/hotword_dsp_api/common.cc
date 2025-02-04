#include "tensorflow/lite/micro/examples/hotword_dsp_api/common.h"
#if MEASURE_CYCLES
#include "tensorflow/lite/micro/examples/utils/cycle_count.h"
#endif

#include <cassert>
#include <cinttypes>
#include <cstdint>

#include "tensorflow/lite/micro/api/hotword_dsp_api.h"
#include "google/application/crc32/crc32.h"

#if DISABLE_LOG
#define LOG(...)
#else
#include <cstdio>
#define LOG(...) printf(__VA_ARGS__)
#endif

int RunHotwordDspApi(const void* model_buffer, size_t model_size,
               uint8_t* arena, size_t arena_size,
               const int16_t* audio_samples, size_t audio_samples_num) {
  assert((reinterpret_cast<std::uintptr_t>(model_buffer) &
            (kGoogleHotwordRequiredDataAlignment - 1)) == 0);
  assert((reinterpret_cast<std::uintptr_t>(arena) &
            (kGoogleHotwordRequiredDataAlignment - 1)) == 0);

  // Print the binary information
  int version = GoogleHotwordVersion();
  LOG("Hotword DSP library version is %d\n", version);

  const char *dsp_identifier = GoogleHotwordDspIdentifier();
  LOG("Hotword DSP identifier is %s\n", dsp_identifier);

  const int max_preamble_ms = GoogleHotwordDspGetMaximumAudioPreambleMs();
  LOG("Maximum Hotword Preamble %d\n", max_preamble_ms);

  // The last 32-bit are the CRC. Exclude them from the CRC calculation.
  uint32_t crc = tflite::Crc32(model_buffer, model_size - sizeof(uint32_t));
printf("crc32: %08x size: %d\n", crc,  model_size - sizeof(uint32_t));
int8_t *model_byte = (int8_t *)model_buffer;
printf("model bytes: %02x %02x %02x %02x\n", model_byte[0],model_byte[1],model_byte[2],model_byte[3]);
  uint32_t expected_crc =
      *reinterpret_cast<const uint32_t*>(
      &(reinterpret_cast<const int8_t*>(model_buffer)
                                              [model_size - sizeof(uint32_t)]));
  if (crc != expected_crc) {
    LOG("Wrong CRC: 0x%" PRIx32 ", expected: 0x%" PRIx32, crc, expected_crc);
    return -1;
  }
#if MEASURE_CYCLES
  cycle_count_t cycles_start = 0, cycles_end = 0, cycle_diff = 0;
  cycle_count_t cycles_max = 0, cycles_accum = 0;
  cycle_count_t cycle_count_acc = 0;
  CycleCountInit();
  cycles_start = CycleCountRead();
#endif

  // Initialize the hotword detector.
  int result = GoogleHotwordDspLoad(
      model_buffer, model_size, arena, arena_size);
  if (result) {
    LOG("Unable to initialize Hotword. Error %d.\n", result);
    return result;
  }

#if MEASURE_CYCLES
  cycles_end = CycleCountRead();
  cycle_diff = cycles_end - cycles_start;
  LOG("Load Cycles: %" CYCLE_COUNT_FORMAT "\n", cycle_diff);
#endif

  int sample_index = 0;
  int block_index = 0;

  while (sample_index < (int)audio_samples_num &&
         (audio_samples_num - sample_index) >= kGoogleHotwordInBlockSize) {
    int preamble_length_ms_unused;
#if MEASURE_CYCLES
    cycles_start = CycleCountRead();
#endif
    int hotword_detected =
        GoogleHotwordDspProcess(&audio_samples[sample_index],
                         kGoogleHotwordInBlockSize, &preamble_length_ms_unused);
#if MEASURE_CYCLES
    cycles_end = CycleCountRead();
    cycle_diff = cycles_end - cycles_start;
    if (cycle_diff > cycles_max) {
      cycles_max = cycle_diff;
    }
    cycles_accum += cycle_diff;
    LOG("Invoke Cycles: %" CYCLE_COUNT_FORMAT "\n", cycle_diff);
    cycle_count_acc += cycle_diff;

#endif

    if (hotword_detected) {
      LOG("%d: Hotword %d detected\n", block_index, hotword_detected - 1);
      GoogleHotwordDspReset();
    }
    sample_index += kGoogleHotwordInBlockSize;
    block_index++;  
  }
  #if MEASURE_CYCLES
LOG("total %d cycle frame: %d\n", cycle_count_acc, block_index);
  #endif
  return 0;
}
