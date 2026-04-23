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

#ifndef THIRD_PARTY_TFLITE_MICRO_GOOGLE_TOOLS_CRC32_CRC32_H_
#define THIRD_PARTY_TFLITE_MICRO_GOOGLE_TOOLS_CRC32_CRC32_H_

#include <cstddef>
#include <cstdint>

namespace tflite {

// ISO/IEC/IEEE 802-3 CRC32 error-detecting code:
// Also known as CRC32B. It uses with the polynomial:
// x^32 + x^26 + x^23 + x^22 + x^16 + x^12
//                           + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
// commonly represented as 0x04C11DB7 and implementated using
// the bit-reversed polynomial 0xEDB88320. The reason to use the
// bit-reversed (aka reciprocal) representation is to use right shifts rather
// than left shifts.
// For an introduction of the CRC error-detecting code, see:
// https://en.wikipedia.org/wiki/Cyclic_redundancy_check
// And the CRC32 alogrithm in particular:
// https://en.wikipedia.org/wiki/Cyclic_redundancy_check#CRC-32_algorithm

constexpr uint32_t kCrc32Polynomial = 0xEDB88320;
constexpr uint32_t kCrc32Seed = 0x0;

// An implementation of CRC32 that processes its input one byte at a time.
// It's faster than Crc32Bitwise() implementation, but uses a 1KB lookup table.
uint32_t Crc32(const void* array, size_t len);

// An implementation of CRC32 that processes its input one bit at a time.
// It's slower than Crc32() but doesn't use a lookup table.
uint32_t Crc32Bitwise(const void* array, size_t len);

}  // namespace tflite

#endif  // THIRD_PARTY_TFLITE_MICRO_GOOGLE_TOOLS_CRC32_CRC32_H_
