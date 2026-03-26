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
#include "tensorflow/lite/micro/micro_profiler.h"

#include <cinttypes>
#include <cstdint>
#include <cstring>

#include "tensorflow/lite/kernels/internal/compatibility.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_time.h"

namespace tflite {

uint32_t MicroProfiler::BeginEvent(const char* tag) {
  if (num_events_ == kMaxEvents) {
    MicroPrintf(
        "MicroProfiler errored out because total number of events exceeded the "
        "maximum of %d.",
        kMaxEvents);
    TFLITE_ASSERT_FALSE;
  }

  tags_[num_events_] = tag;
  start_ticks_[num_events_] = GetCurrentTimeTicks();
  end_ticks_[num_events_] = start_ticks_[num_events_] - 1;
#if defined(IA8201)
  mac8b_counts_[num_events_] = 0;
  macaflt_counts[num_events_] = 0;
#endif
  return num_events_++;
}

void MicroProfiler::EndEvent(uint32_t event_handle) {
  TFLITE_DCHECK(event_handle < kMaxEvents);
  end_ticks_[event_handle] = GetCurrentTimeTicks();
}

uint32_t MicroProfiler::GetTotalTicks() const {
  int32_t ticks = 0;
  for (int i = 0; i < num_events_; ++i) {
    ticks += end_ticks_[i] - start_ticks_[i];
  }
  return ticks;
}
#if defined(IA8201)
void MicroProfiler::AccumuateMacCount(uint32_t mac_count)
{
  // minuse1
  if (num_events_ -1 < kMaxEvents)
  {
    mac8b_counts_[num_events_-1] += mac_count;
  }
}
void MicroProfiler::LogMacCount() const {
#if !defined(TF_LITE_STRIP_ERROR_STRINGS)
  uint32_t total_mac_inst = 0;
  uint32_t total_mac_op = 0;
  MicroPrintf("\"OpID\",\"Tag\",\"Mac Instruction (8b)\",\"Mac Op\"");
  for (int i = 0; i < num_events_; ++i) {

    uint32_t mac_counts = mac8b_counts_[i]; //end_ticks_[i] - start_ticks_[i];
    if (mac_counts == 0)
      continue;
    uint32_t mac_ops =
#if defined(DMX1A)
      mac_counts * 16;
#elif defined(HMD1A)
      mac_counts * 8;
#else
      0;
#endif
    MicroPrintf("%-5d,%-16s,%-16d,%-16d" , i, tags_[i], mac_counts, mac_ops  );
    total_mac_inst += (uint32_t)mac_counts;
    total_mac_op += (uint32_t)mac_ops;
  }
  MicroPrintf("\ntotal Mac Instruction: %-16d  Mac operations: %-16d\n\n", total_mac_inst,
    total_mac_op);
#endif
}
#endif
void MicroProfiler::Log() const {
#if !defined(TF_LITE_STRIP_ERROR_STRINGS)
  for (int i = 0; i < num_events_; ++i) {
    uint32_t ticks = end_ticks_[i] - start_ticks_[i];
    MicroPrintf("%s took %u ticks (%d ms).", tags_[i], ticks, TicksToMs(ticks));
  }

  // mac count estimation
#endif
}


void MicroProfiler::LogCsv() const {
#if !defined(TF_LITE_STRIP_ERROR_STRINGS)
  uint32_t total_ticks = 0;
  for (int i = 0; i < num_events_; ++i) {
    uint32_t ticks = end_ticks_[i] - start_ticks_[i];
    TFLITE_DCHECK(tags_[i] != nullptr);
    //int position = FindExistingOrNextPosition(tags_[i]);
    //TFLITE_DCHECK(position >= 0);
    //total_ticks_per_tag_[position].tag = tags_[i];
    //total_ticks_per_tag_[position].ticks =
    //  total_ticks_per_tag_[position].ticks + ticks;
    total_ticks += ticks;
  }

  MicroPrintf("\"Event\",\"Tag\",\"Ticks\", \"Percentage\"");
  for (int i = 0; i < num_events_; ++i) {
#if defined(HEXAGON) || defined(CMSIS_NN)
    int ticks = end_ticks_[i] - start_ticks_[i];
    MicroPrintf("%d,%s,%d", i, tags_[i], ticks);
#else
    uint32_t ticks = end_ticks_[i] - start_ticks_[i];
    float percentage = (float)ticks / (float)total_ticks * 100.0f;

    MicroPrintf("%-5d,%-16s,%-16d,%-2.2f%%", i, tags_[i], ticks, (double)percentage);
#endif
  }
#endif
}

void MicroProfiler::LogTicksPerTagCsv() {
#if !defined(TF_LITE_STRIP_ERROR_STRINGS)
  MicroPrintf(
      "\"Unique Tag\",\"Total ticks across all events with that tag.\"");
  int total_ticks = 0;
  for (int i = 0; i < num_events_; ++i) {
    uint32_t ticks = end_ticks_[i] - start_ticks_[i];
    TFLITE_DCHECK(tags_[i] != nullptr);
    int position = FindExistingOrNextPosition(tags_[i]);
    TFLITE_DCHECK(position >= 0);
    total_ticks_per_tag_[position].tag = tags_[i];
    total_ticks_per_tag_[position].ticks =
        total_ticks_per_tag_[position].ticks + ticks;
    total_ticks += ticks;
  }

  for (int i = 0; i < num_events_; ++i) {
    TicksPerTag each_tag_entry = total_ticks_per_tag_[i];
    if (each_tag_entry.tag == nullptr) {
      break;
    }
    MicroPrintf("%s, %d", each_tag_entry.tag, each_tag_entry.ticks);
  }
  MicroPrintf("\"total number of ticks\", %d", total_ticks);
#endif
}

// This method finds a particular array element in the total_ticks_per_tag array
// with the matching tag_name passed in the method. If it can find a
// matching array element that has the same tag_name, then it will return the
// position of the matching element. But if it unable to find a matching element
// with the given tag_name, it will return the next available empty position
// from the array.
int MicroProfiler::FindExistingOrNextPosition(const char* tag_name) {
  int pos = 0;
  for (; pos < num_events_; pos++) {
    TicksPerTag each_tag_entry = total_ticks_per_tag_[pos];
    if (each_tag_entry.tag == nullptr ||
        strcmp(each_tag_entry.tag, tag_name) == 0) {
      return pos;
    }
  }
  return pos < num_events_ ? pos : -1;
}

void MicroProfiler::ClearEvents() {
  for (int i = 0; i < num_events_; i++) {
    total_ticks_per_tag_[i].tag = nullptr;
#if defined(IA8201)
    mac8b_counts_[i] = 0;
    macaflt_counts[i] = 0;
#endif
  }

  num_events_ = 0;
}

}  // namespace tflite
