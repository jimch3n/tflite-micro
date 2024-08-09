
#ifndef _IAXXX_TFLITE_MODEL_CONVERTER_H_
#  define _IAXXX_TFLITE_MODEL_CONVERTER_H_
#include <iostream>
#include <fstream>
#include "schema_generated.h" // tflite 23.5.26
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"


constexpr uint32_t kCrc32Polynomial = 0xEDB88320;
constexpr uint32_t kCrc32Seed = 0x0;

#if 1
#  define BLOCK_SIZE 8
#  define LOG2_ROWS_PER_GROUP 2
#  define ROWS_PER_GROUP (1 << LOG2_ROWS_PER_GROUP)
#  define LOG2_COLS_PER_BLOCK 1
#  define COLS_PER_BLOCK (1 << LOG2_COLS_PER_BLOCK)

// float depthwise map
#  define BLOCK_SIZE_FLT 8
#  define LOG2_ROWS_PER_GROUP_FLT 1
#  define ROWS_PER_GROUP_FLT (1 << LOG2_ROWS_PER_GROUP_FLT)
#  define LOG2_COLS_PER_BLOCK_FLT 1
#  define COLS_PER_BLOCK_FLT (1 << LOG2_COLS_PER_BLOCK_FLT)

#endif

int FullyConnectedMap8bitCoeffs(int8_t *pMapped, const int8_t *pCoeffs, int m,
                                int n);

// An implementation of CRC32 that processes its input one byte at a time.
// It's faster than Crc32Bitwise() implementation, but uses a 1KB lookup table.
uint32_t Crc32(const void *array, size_t len);

uint32_t iaxxx_tflite_model_converter(uint8_t *model_data, uint8_t *output,
                                      int verbose = 0,
                                      int append_crc32 = 0);

#endif

