#ifndef SPEECH_MICRO_TENSORFLOW_LITE_MICRO_EXAMPLES_HOTWORD_DSP_API_COMMON_H_
#define SPEECH_MICRO_TENSORFLOW_LITE_MICRO_EXAMPLES_HOTWORD_DSP_API_COMMON_H_

#include <cstring>
#include <cstdint>

// Returns 0 if successful, and a non-zero error code otherwise.
int RunHotwordDspApi(const void* model_buffer, size_t model_size,
               uint8_t* arena, size_t arena_size,
               const int16_t* audio_samples, size_t audio_samples_num);

#endif  // SPEECH_MICRO_TENSORFLOW_LITE_MICRO_EXAMPLES_HOTWORD_DSP_API_COMMON_H_
