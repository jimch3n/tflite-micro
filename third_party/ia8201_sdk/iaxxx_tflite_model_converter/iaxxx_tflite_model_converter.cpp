/*
 * iaxxx_tflite_model_converter.c  --  google hotword model conversion for IAXXX
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "iaxxx_tflite_model_converter.h"

//using namespace tflite;

static const uint32_t crc_table_mvm[] = {
  0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
  0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
  0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
  0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
  0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
  0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
  0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
  0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
  0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
  0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
  0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
  0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
  0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
  0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
  0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
  0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
  0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
  0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
  0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
  0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
  0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
  0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
  0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
  0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
  0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
  0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
  0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
  0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
  0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
  0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
  0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
  0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
  0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
  0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
  0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
  0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
  0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
  0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
  0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
  0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
  0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
  0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
  0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

#define LO_SHIFT -1
#define HI_SHIFT 6
#define MVM16BX8B_FAST_Q 23
#define MVM16BX8B_FAST_EXP_FXP (32 - MVM16BX8B_FAST_Q)

// optimize me
// input pCoeffs order is  filter_val = filter_data[out_c * accum_depth + d];
int FullyConnectedMap8bitCoeffs(int8_t *pMapped, const int8_t *pCoeffs, int m,
                                int n) {
  int nFullRowGroups =
      (m + (1 << LOG2_ROWS_PER_GROUP) - 1) >> LOG2_ROWS_PER_GROUP;

  int nFullColBlocks = (n + 1) >> LOG2_COLS_PER_BLOCK;
  int nFullBlockColsAligned2 = nFullColBlocks << LOG2_COLS_PER_BLOCK;

  const int8_t *src = pCoeffs;
  int8_t *dst = pMapped;

  int mappedSize = nFullRowGroups * nFullColBlocks * BLOCK_SIZE;
  // int weightSize = m*n;
  if (pMapped && pCoeffs) {
    // Half column blocks from full row groups
    for (int group = 0; group < nFullRowGroups; group++) {
      for (int block = 0; block < nFullBlockColsAligned2; block++) {
        for (int j = 0; j < ROWS_PER_GROUP; j++) {
          int blkIdx = block;
          int grpIdx = group * ROWS_PER_GROUP + j;

          int dstIdx = group * ROWS_PER_GROUP * nFullBlockColsAligned2 +
                       block * ROWS_PER_GROUP + j;

          if (block < n && grpIdx < m) {
            dst[dstIdx] = src[grpIdx * n + blkIdx];

          } else {
            dst[dstIdx] = 0;
          }
        }
      }
    }
  }
  return mappedSize;
}

uint32_t Crc32(const void *array, size_t len) {
  const uint8_t *ptr = (const uint8_t *)array;

  uint32_t crc = ~kCrc32Seed;

  for (; len > 0; len--) {
    crc = crc_table_mvm[*ptr++ ^ (crc & 0xFF)] ^ (crc >> 8);
  }

  return ~crc;
}



static void write_model_buffers(const tflite::Model *model,
    flatbuffers::FlatBufferBuilder &fbb, int buffer_idx,
  void *src, size_t size) {
  //fprintf(stderr, "model version: 0x%x\n", model->version());
  // This is a pointer to a vector of offsets:
  const flatbuffers::Vector<flatbuffers::Offset<tflite::Buffer>> *buffers =
      model->buffers();
  //fprintf(stderr, "buffers: 0x%p\n", buffers);
  const flatbuffers::Vector<flatbuffers::Offset<tflite::Buffer>>
      &buffer_offsets = *buffers;
  int number_of_buffers = buffer_offsets.size();
  //fprintf(stderr, "number of buffers: %d\n", buffer_offsets.size());
  //for (int i = 0; i < number_of_buffers; ++i)
  int i = buffer_idx;
  {
    // C++ magic returns the actual buffer pointer here, rather than the
    // expected Offset that the Vector seems to hold:
    const tflite::Buffer *buffer = buffer_offsets[i];
    const flatbuffers::Vector<uint8_t> *data = buffer->data();
    // Only the weight buffers are allocated in the flatbuffer:
    if (data) {
        size_t buffer_size = data->size();
        const uint8_t *buffer_addr = data->Data();
        int buffer_offset =
            buffer_addr - reinterpret_cast<const uint8_t *>(model);
        // force write up
        int8_t *buffer_addrw = (int8_t *)data->Data();
        memcpy(buffer_addrw, src, size);

        fprintf(stderr, "buffer %d size: %zu, addr: 0x%p, offset: 0x%x\n", i,
                buffer_size, buffer_addr, buffer_offset);
        fprintf(stderr, "buffer contents: %x %x %x %x %x %x %x %x\n",
                buffer_addr[0], buffer_addr[1], buffer_addr[2], buffer_addr[3],
                buffer_addr[4], buffer_addr[5], buffer_addr[6], buffer_addr[7]);
    }
  }
}

void dump_model_buffers(const tflite::Model *model) {
  fprintf(stderr, "model version: 0x%x\n", model->version());
  // This is a pointer to a vector of offsets:
  const flatbuffers::Vector<flatbuffers::Offset<tflite::Buffer>> *buffers =
      model->buffers();
  fprintf(stderr, "buffers: 0x%p\n", buffers);
  const flatbuffers::Vector<flatbuffers::Offset<tflite::Buffer>>
      &buffer_offsets = *buffers;
  int number_of_buffers = buffer_offsets.size();
  fprintf(stderr, "number of buffers: %d\n", buffer_offsets.size());
  for (int i = 0; i < number_of_buffers; ++i) {
    // C++ magic returns the actual buffer pointer here, rather than the
    // expected Offset that the Vector seems to hold:
    const tflite::Buffer *buffer = buffer_offsets[i];
    const flatbuffers::Vector<uint8_t> *data = buffer->data();
    // Only the weight buffers are allocated in the flatbuffer:
    if (data) {
      size_t buffer_size = data->size();
      const uint8_t *buffer_addr = data->Data();

      int buffer_offset =
          buffer_addr - reinterpret_cast<const uint8_t *>(model);
           //force write up 
   
      fprintf(stderr, "buffer %d size: %zu, addr: 0x%p, offset: 0x%x\n", i,
              buffer_size, buffer_addr, buffer_offset);
      fprintf(stderr, "buffer contents: %x %x %x %x %x %x %x %x\n",
              buffer_addr[0], buffer_addr[1], buffer_addr[2], buffer_addr[3],
              buffer_addr[4], buffer_addr[5], buffer_addr[6], buffer_addr[7]);
 
    }
  }
}
// TODO(b/192589496): Ops must always be there. Remove this function when fixed
uint32_t NumSubgraphOperators(const tflite::SubGraph* subgraph) {
    if (subgraph->operators() != nullptr) {
        return subgraph->operators()->size();
    }
    else {
        return 0;
    }
}
// TODO(b/192589496): Ops must always be there. Remove this function when fixed
uint32_t NumSubgraphOperators(const tflite::Model* model, int subgraph_idx) {
    const tflite::SubGraph* subgraph = model->subgraphs()->Get(subgraph_idx);
    return NumSubgraphOperators(subgraph);
}

// interface
uint32_t 
iaxxx_tflite_model_converter(uint8_t *model_data, uint8_t *output, int verbose, int append_crc32)
{

  
  const tflite::Model *model = tflite::GetModel(model_data);

  flatbuffers::DefaultAllocator allocator;
  flatbuffers::FlatBufferBuilder fbb{ 2048, &allocator };

  for (size_t subgraph_idx = 0; subgraph_idx < model->subgraphs()->size();
       subgraph_idx++) {

    printf("sub graph: %d\n", subgraph_idx);
    uint32_t operators_size = NumSubgraphOperators(model, subgraph_idx);

    const tflite::SubGraph *subgraph = model->subgraphs()->Get(subgraph_idx);
    for (size_t i = 0; i < operators_size; ++i) {
      // TfLiteNode *node =
      //    &(subgraph_allocations_[subgraph_idx].node_and_registrations[i].node);
      const auto op = subgraph->operators()->Get(i);
      // auto opt;
      if (op->builtin_options_as_FullyConnectedOptions()) {
        if (verbose) printf("fully connected! op idx %d\n", i);

        auto tensor_idx = op->inputs()->Get(1);

        const tflite::Tensor *tensor = subgraph->tensors()->Get(tensor_idx);

        tflite::TensorT *tt = tensor->UnPack();
        if (tensor->type() == tflite::TensorType_INT8) {
          if (verbose)
            printf("tensor : %d name: %s\n", tensor->buffer(), tensor->name());
          const ::flatbuffers::Vector<int32_t> *shape = tensor->shape();
          auto *shape_array = shape->data();
          const int32_t *shape_data =
              reinterpret_cast<const int32_t *>(shape_array);
          if (verbose) printf("shape : %d, %d\n", shape_data[0], shape_data[1]);
          //->shape();
          int32_t input_dim = shape_data[1];
          int32_t output_dim = shape_data[0];
          // unaligned out 4, in 2
          if ((output_dim & 3) != 0) {
            if (verbose) printf("!!!!! skip unaligned: %d !!!!\n", output_dim);
            continue;
          }
          if ((input_dim & 1) != 0) {
            if (verbose) printf("!!!!! skip unaligned: %d !!!!\n", input_dim);
            continue;
          }

          int map_size = FullyConnectedMap8bitCoeffs(
              NULL, NULL, output_dim, input_dim);

          int8_t *mapped_buf = (int8_t *)malloc(map_size);

          int weight_idx = tensor->buffer();
          const flatbuffers::Vector<flatbuffers::Offset<tflite::Buffer>> *buffers =
              model->buffers();

          auto *buffer = (*buffers)[weight_idx];

          // buffer->Pack();
          auto *array = buffer->data();
          const int8_t *weight_buffer =
              reinterpret_cast<const int8_t *>(array->data());
          FullyConnectedMap8bitCoeffs(mapped_buf, weight_buffer,
                                              output_dim, input_dim);

          write_model_buffers(model, fbb, weight_idx, mapped_buf, map_size);

          free(mapped_buf);
        }
        // tensor->
        // auto *buf = model->buffers()[0];

      } else if (op->builtin_options_as_SVDFOptions()) {
        printf("svdf! op idx %d\n", i);

        auto tensor_idx = op->inputs()->Get(1);

        const tflite::Tensor *tensor = subgraph->tensors()->Get(tensor_idx);

        tflite::TensorT *tt = tensor->UnPack();
        if (tensor->type() == tflite::TensorType_INT8) {
          printf("tensor : %d name: %s\n", tensor->buffer(), tensor->name());
          const ::flatbuffers::Vector<int32_t> *shape = tensor->shape();
          auto *shape_array = shape->data();
          const int32_t *shape_data =
              reinterpret_cast<const int32_t *>(shape_array);
          if(verbose)printf("shape : %d, %d\n", shape_data[0], shape_data[1]);
          //->shape();
          int32_t input_dim = shape_data[1];
          int32_t output_dim = shape_data[0];
          // unaligned out 4, in 2
          if ((output_dim & 3) != 0) {
            if (verbose) printf("!!!!! skip unaligned: %d !!!!\n", output_dim);
            continue;
            //  shape_data[1] = input_dim + 1;
            // tt->shape[0] = ((output_dim + 3) >> 2) << 2;
            //((int32_t *)shape_data)[0] = tt->shape[0];
          } else if ((input_dim & 1) != 0) {
            if (verbose) printf("!!!!! skip unaligned: %d !!!!\n", input_dim);
            continue;
            // tt->shape[1] = ((input_dim + 1) >> 1) << 1;
            //((int32_t *)shape_data)[1] = tt->shape[1];
          }
      

          int map_size = FullyConnectedMap8bitCoeffs(
              NULL, NULL, output_dim, input_dim);

          int8_t *mapped_buf = (int8_t *)malloc(map_size);

          int weight_idx = tensor->buffer();
          const flatbuffers::Vector<flatbuffers::Offset<tflite::Buffer>> *buffers =
              model->buffers();

          auto *buffer = (*buffers)[weight_idx];

          auto *array = buffer->data();
          const int8_t *weight_buffer =
              reinterpret_cast<const int8_t *>(array->data());

          FullyConnectedMap8bitCoeffs(mapped_buf, weight_buffer,
                                              output_dim, input_dim);

          write_model_buffers(model, fbb, weight_idx, mapped_buf, map_size);

          free(mapped_buf);
        }
      }
    }  // operator loop

  }  /// loop subgraph

  // if (1) dump_model_buffers(model);
  auto new_model = tflite::Model::Pack(fbb, model->UnPack());

  fbb.Finish(new_model, tflite::ModelIdentifier());

  uint32_t fbb_size = fbb.GetSize();
  // append crc32
  uint32_t crc32 = Crc32(fbb.GetBufferPointer(), fbb_size);
  
  // utils
  memcpy(output, fbb.GetBufferPointer(), fbb_size);
  if (append_crc32) {
    memcpy(output + fbb_size, &crc32, sizeof(uint32_t));
    if(verbose) printf("crc32: %08x\n",crc32);
  }
  int size = fbb_size + (append_crc32 ? sizeof(uint32_t) : 0);
  return size;
}
