#!/usr/bin/python
#
# @copyright
# Copyright (c) 2021 by Knowles Corporation. All rights reserved.
# <br>
# This software is the confidential and proprietary information of Knowles
# Corporation. ("Confidential Information"). You shall not disclose such
# Confidential Information and shall use it only in accordance with the Terms
# of Sale of Knowles Corporation products and the terms of any license
# agreement you entered into with Knowles Corporation for such products.
# <br>
# KNOWLES CORPORATION SOURCE CODE STRICTLY "AS IS" WITHOUT ANY WARRANTY
# WHATSOEVER, AND KNOWLES CORPORATION EXPRESSLY DISCLAIMS ALL WARRANTIES,
# EXPRESS, IMPLIED OR STATUTORY WITH REGARD THERETO, INCLUDING THE IMPLIED
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE OR
# NON-INFRINGEMENT OF THIRD PARTY RIGHTS. KNOWLES CORPORATION SHALL NOT BE
# LIABLE FOR ANY DAMAGES SUFFERED BY YOU AS A RESULT OF USING, MODIFYING OR
# DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.


from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

#import tensorflow as tf
#import h5py
from typing import Any, Union
import re
import struct
import numpy as np
import os
import flatbuffers
import copy
import random
#from tensorflow.lite.tools import test_utils
import platform
#from itertools import izip
import sys
import zlib
#sys.path.append(r'/home/jimchen/src/tensorflow-r2.4/tensorflow/lite/micro/tools/make/downloads/flatbuffers')
#sys.path.append(r'/home/jimchen/src/tensorflow-r2.4/tensorflow/lite/micro/tools/make/downloads/flatbuffers/tflite')
#print(sys.path)

#import tflite
from schema_py_generated import Model
from schema_py_generated import ModelT
from schema_py_generated import FullyConnectedOptionsT
from schema_py_generated import DepthwiseConv2DOptionsT
from schema_py_generated import Conv2DOptionsT
from schema_py_generated import SVDFOptionsT
from schema_py_generated import UnidirectionalSequenceLSTMOptionsT
#from tflite.FullyConnectedOptionsWeightsFormat import FullyConnectedOptionsWeightsFormat

import argparse

import ctypes as ct
dir_path = os.path.dirname(os.path.realpath(__file__))
#vpDevRoot = os.environ["KSPL_ROOT"]
dllPath = os.path.join(dir_path,'kut')
hDll = ct.cdll.LoadLibrary(dllPath) #load kut.dll

_TFLITE_FILE_IDENTIFIER = b'TFL3'

def get_ksp_float_t_typedef(target='AVL_DMX1A'):
    """ get_ksp_float_t_typedef: Return native C type for "ksp_float_t" typedef
    based on target

    Returns
    -------
    ksp_float_t     PyCSimpleType (ctype class)
    """

    ksp_float_t = ct.c_uint32
    py_float_t = np.uint32

    return ksp_float_t, py_float_t


def to_ksp_minifloat16_t(inp, exp_bits, bias, rounding=0, is_signed=1, output=None):
    """ TO_KSP_FLOAT: Convert IEEE floating point data to native ata format for minifloat16

    Parameters
    usage       localOut = to_ksp_float_t(inp,localOut)  when inp is a numpy array, or
                localOut = to_ksp_float_t(inp) when inp is a float32, or an int32
    inp         Input IEEE float vector (numpy array, dtype=float32), or a float32 (or an int32) scalar
    output      array of py_float_t for the output if inp is a numpy array. The size, shape, must match the inp array
                if inp is a scalar, this argument should be None (or skipped)
    exp_bits    exponent bits
    bias        bias for mini-float
    rounding    rounding
    is_signed   signed
    Returns
    -------
    out         If target == AVL_GENERIC, do nothing. If inp is a numpy array copy inp to output
                If target == AVL_DMX1A, inp is converted to AFloat_t.
                If inp is a numpy array delivered in the 'output' array
                If inp is not a numpy array, second argument should be None, and the converted scalar is simply returned
    """
    if inp is None or np.size(inp) == 0:
        return inp

    ksp_float_t, py_float_t = get_ksp_float_t_typedef()

    single = None

    if inp.__class__ == int or inp.__class__ == ct.c_int32 \
            or inp.__class__ == ct.c_long or inp.__class__ == ct.c_uint32 \
            or inp.__class__ == float or inp.__class__ == np.float32 \
            or inp.__class__ == np.float64:
        single = np.array(inp, dtype="float64")

    if inp.__class__ == np.ndarray:
        if output is None:
            raise AssertionError("Error: output array must be provided for type %s" % inp.__class__)
    else:
        if single is None:
            raise AssertionError("Error: Incorrect input type: %s" % inp.__class__)

    if 1:  # ksp_float_t == ct.c_float:  # IEEE Float
        if output is None:
            out = single
        else:
            # np.copyto(output, inp)
            # asc_input = inp
            out = output
        status = hDll.DblToAft16(
            inp.ctypes.data_as(ct.POINTER(ct.c_double)),
            out.ctypes.data_as(ct.POINTER(ct.c_int16)),
             np.size(inp), is_signed, exp_bits, bias, 0)
    else:
        raise AssertionError("Error: Unknown Target %s" % target)

    return out

def quantize_to_minifloat(x, exp=5, bias=15):
    """
        Decompose into mantissa and exponent
        Convert data to 8-bit signed integer by normalizing by maxval and scaling by (2^7)
        See doubleToInt8WithExp.m

    Parameters
    ----------
    x           - data vector to be quantized

    Returns
    -------
    y
    y_exp
    """
    # convert float x to afloat kn_format
    xIn = np.asarray(np.ascontiguousarray(x, dtype=np.float32), dtype=np.float64)
    #xFlt = np.asarray(xIn, dtype=ksp_float_t)
    yMiniFlt = np.zeros_like(xIn, dtype=ct.c_int16)
    yMiniFlt = to_ksp_minifloat16_t(xIn, exp, bias, 0, 1, yMiniFlt)
    return yMiniFlt
def map_conv_weights(weight_tab, filter_width, filter_height, output_depth, input_depth, arch='hmd'):
    # filter shape input_ch*filter_height* filter_width
    nInput = filter_width*filter_height*input_depth
    nOutput = output_depth
    if arch=='dmx':
        group_align = 8
    elif arch=='hmd':
        group_align = 4
    else:
        raise print("unknown arch: {}".format(arch))
    nFullRowGroups = (nOutput+group_align-1)//group_align
    nFullColBlocks = (nInput+1)//2
    nFullColBlocksAligned2 = nFullColBlocks*2
    tab_out = np.zeros((nFullRowGroups*group_align*nFullColBlocks*2),dtype=np.int8) # 2d ? compatible with original size
    for out_ch in range(0, output_depth):
        for fy in range(0, filter_height):
            for fx in range(0, filter_width):
                for in_ch in range(0, input_depth):
                    #out_ch = (in_ch*output_depth)+dm
                    group = out_ch//group_align
                    j = out_ch%group_align
                    input_idx = (fy*filter_width+fx)*input_depth+in_ch

                    dst_idx = group*group_align*(nFullColBlocksAligned2)+input_idx*group_align+j
                    #print("conv tab idx {} inch: {} fy: {} fx: {} out_ch: {}".format(dst_idx, out_ch, fy, fx, in_ch))
                    tab_out[dst_idx] = weight_tab[out_ch][fy][fx][in_ch]
    #reshape to aligned size

    mapW = np.reshape(tab_out, (1, nFullRowGroups*group_align, nFullColBlocksAligned2, 1))

    return mapW, 1, nFullRowGroups*group_align, nFullColBlocksAligned2, 1

def map_ds_conv_weights(weight_tab, filter_width, filter_height, depth_multi, input_depth, arch='hmd', mapped_type='1'):
    # filter shape input_ch*filter_height* filter_width
    if mapped_type != 2:
        nInput = filter_width*filter_height *input_depth
    else:
        # 1 or 3
        nInput = filter_width * filter_height  # *input_depth
        #mapped_type == 2

    nOutput = depth_multi*input_depth

    if arch=='dmx':
        group_align = 8
    elif arch=='hmd':
        group_align = 4
    else:
        raise print("unknown arch: {}".format(arch))

    nFullRowGroups = (nOutput+group_align-1)//group_align
    nFullColBlocks = (nInput+1)//2
    nFullColBlocksAligned2 = nFullColBlocks*2
    tab_out = np.zeros((nFullRowGroups*group_align*nFullColBlocksAligned2), dtype=np.int8)

    for dm in range(0, depth_multi):
        for fy in range(0, filter_height):
            for fx in range(0, filter_width):
                for in_ch in range(0, input_depth):
                    out_ch = (in_ch*depth_multi)+dm
                    group = out_ch//group_align
                    j = out_ch%group_align
                    #input_idx = (fy*filter_width+fx)*input_depth+in_ch
                    if mapped_type != 2:
                        input_idx = (fy * filter_width+fx)*input_depth+in_ch #filter_width * filter_height * input_depth
                    else:
                        input_idx = (fy * filter_width + fx)
                    dst_idx = group * group_align * (nFullColBlocksAligned2) + input_idx * group_align + j
                    tab_out[dst_idx] = weight_tab[0][fy][fx][out_ch]

    return tab_out, 1, nFullRowGroups*group_align, nFullColBlocksAligned2, 1


def map_ds_conv_float_weights(weight_tab, filter_width, filter_height, depth_multi, input_depth, arch='hmd',
                              mapped_type='1', w_type=np.float32):
    # filter shape input_ch*filter_height* filter_width
    if mapped_type == 1:
        nInput = filter_width*filter_height *input_depth
    else:
        nInput = filter_width * filter_height  # *input_depth
        #mapped_type == 2

    nOutput = depth_multi*input_depth

    if arch=='dmx':
        row_per_group_flt = 4
    elif arch=='hmd':
        row_per_group_flt = 2
    else:
        raise print("unknown arch: {}".format(arch))

    #nFullRowGroups = (nOutput+group_align-1)//group_align
    #nFullColBlocks = (nInput+1)//2
    #nFullColBlocksAligned2 = nFullColBlocks*2
    tab_out = np.zeros((nInput*nOutput), dtype=w_type)

    for dm in range(0, depth_multi):
        for fy in range(0, filter_height):
            for fx in range(0, filter_width):
                for in_ch in range(0, input_depth):
                    out_ch = (in_ch*depth_multi)+dm
                    input_idx = (fy*filter_width) + fx
                    group = out_ch//row_per_group_flt
                    j = out_ch%row_per_group_flt
                    if mapped_type == 1:
                        block = ((fy*filter_width +fx) * input_depth + in_ch)
                    else:
                        block = input_idx
                    #input_idx = (fy*filter_width+fx)*input_depth+in_ch
                    if mapped_type == 1:
                        dst_idx =out_ch*nInput + block
                    else:
                        dst_idx = (group * row_per_group_flt*nInput ) + block * row_per_group_flt + j
                    #dst_idx = group * group_align * (nFullColBlocksAligned2) + input_idx * group_align + j
                    srcIdx = input_idx * depth_multi*input_depth+out_ch
                    #print(f"srcIdx: {srcIdx} dstIdx {dst_idx} val: {weight_tab[0][fy][fx][out_ch]} {fy} {fx} {in_ch}")
                    tab_out[dst_idx] = weight_tab[0][fy][fx][out_ch]

    return tab_out


# transpose =True, input weight is grp * blk,
# transpose = False input weight is blk*grp
def map_fc_weights(weight_tab, blkSize, grpSize, arch='hmd', transpose=True):
    offset = 0

    tab_out = np.empty(shape=(0), dtype=np.int8)

    if arch=='dmx':
        group_align = 8
    elif arch=='hmd':
        group_align = 4
    else:
        raise print("unknown arch: {}".format(arch))
    grpSize8 = (grpSize + (group_align-1)) // group_align
    blkSize2 = (blkSize + 1) // 2
    weightOut = []
    for g in range(grpSize8):
        for b in range(blkSize2):
            for e1 in range(group_align):
                # hiddenweight indexing is blk_id*grp_size +grp_id
                idx = (2 * b) + (g * group_align + e1)*blkSize if transpose else (2 * b) * grpSize + g * group_align + e1

                weight = weight_tab[idx] if (2 * b < blkSize and g * group_align + e1 < grpSize) else 0
                weightOut.append(weight)
            for e2 in range(group_align):  # second blk
                idx = (2 * b + 1) + (g * group_align + e2)*blkSize if transpose else (2*b+1)*grpSize+g*group_align+e2

                weight = weight_tab[idx] if (2 * b + 1 < blkSize and g * group_align + e2 < grpSize) else 0
                weightOut.append(weight)
    tab_mant = np.asarray(weightOut, dtype=np.int8).reshape((grpSize8*group_align, blkSize2*2))
    return tab_mant, grpSize8*group_align, blkSize2*2
def convert_bytearray_to_object(model_bytearray):
  """Converts a tflite model from a bytearray to an object for parsing."""
  model_object = Model.GetRootAsModel(model_bytearray, 0)
  return ModelT.InitFromObj(model_object), model_object


def read_model(input_tflite_file):
  """Reads a tflite model as a python object.

  Args:
    input_tflite_file: Full path name to the input tflite file

  Raises:
    RuntimeError: If input_tflite_file path is invalid.
    IOError: If input_tflite_file cannot be opened.

  Returns:
    A python object corresponding to the input tflite file.
  """
  if not os.path.exists(input_tflite_file):
    raise RuntimeError('Input file not found at %r\n' % input_tflite_file)
  with open(input_tflite_file, 'rb') as file_handle:
    model_bytearray = bytearray(file_handle.read())
  return convert_bytearray_to_object(model_bytearray)


def read_model_with_mutable_tensors(input_tflite_file):
  """Reads a tflite model as a python object with mutable tensors.

  Similar to read_model() with the addition that the returned object has
  mutable tensors (read_model() returns an object with immutable tensors).

  Args:
    input_tflite_file: Full path name to the input tflite file

  Raises:
    RuntimeError: If input_tflite_file path is invalid.
    IOError: If input_tflite_file cannot be opened.

  Returns:
    A mutable python object corresponding to the input tflite file.
  """
  return copy.deepcopy(read_model(input_tflite_file))


def convert_object_to_bytearray(model_object):
  """Converts a tflite model from an object to a immutable bytearray."""
  # Initial size of the buffer, which will grow automatically if needed
  builder = flatbuffers.Builder(1024)
  model_offset = model_object.Pack(builder)
  builder.Finish(model_offset, file_identifier=_TFLITE_FILE_IDENTIFIER)
  model_bytearray = bytes(builder.Output())
  return model_bytearray


def write_model(model_object, output_tflite_file, crc32=False):
  """Writes the tflite model, a python object, into the output file.

  Args:
    model_object: A tflite model as a python object
    output_tflite_file: Full path name to the output tflite file.

  Raises:
    IOError: If output_tflite_file path is invalid or cannot be opened.
  """


  model_bytearray = convert_object_to_bytearray(model_object)

  if crc32:
      crc_out = zlib.crc32(model_bytearray)
      print(f"CRC32: {crc_out:08x}")
      model_bytearray = bytearray(model_bytearray)
      model_bytearray += bytearray(struct.pack("<I", crc_out)) # append
  with open(output_tflite_file, 'wb+') as out_file:
    out_file.write(model_bytearray)
  return len(model_bytearray)

def strip_strings(model, verbose=False):
  """Strips all nonessential strings from the model to reduce model size.

  We remove the following strings:
  (find strings by searching ":string" in the tensorflow lite flatbuffer schema)
  1. Model description
  2. SubGraph name
  3. Tensor names
  We retain OperatorCode custom_code and Metadata name.

  Args:
    model: The model from which to remove nonessential strings.

  """
  strip_char_number = 0
  #model.description = ''
  for subgraph in model.subgraphs:
    if verbose:
        print("subgraph: {}".format(subgraph.name))
    subgraph.name = ''
    for tensor in subgraph.tensors:
      #if verbose:
      #    print("tensor: {}".format(tensor.name))
      strip_char_number += len(tensor.name)
      #if tensor.name == b'input':
      #    continue
      tensor.name = ''
  print(f"strip tensor's name total: {strip_char_number} bytes")

def randomize_weights(model, random_seed=0):
  """Randomize weights in a model.

  Args:
    model: The model in which to randomize weights.
    random_seed: The input to the random number generator (default value is 0).

  """

  # The input to the random seed generator. The default value is 0.
  random.seed(random_seed)

  # Parse model buffers which store the model weights
  buffers = model.buffers
  for i in range(1, len(buffers)):  # ignore index 0 as it's always None
    buffer_i_data = buffers[i].data
    buffer_i_size = 0 if buffer_i_data is None else buffer_i_data.size

    # Raw data buffers are of type ubyte (or uint8) whose values lie in the
    # range [0, 255]. Those ubytes (or unint8s) are the underlying
    # representation of each datatype. For example, a bias tensor of type
    # int32 appears as a buffer 4 times it's length of type ubyte (or uint8).
    # TODO(b/152324470): This does not work for float as randomized weights may
    # end up as denormalized or NaN/Inf floating point numbers.
    for j in range(buffer_i_size):
      buffer_i_data[j] = random.randint(0, 255)


def xxd_output_to_bytes(input_cc_file):
  """Converts xxd output C++ source file to bytes (immutable)

  Args:
    input_cc_file: Full path name to th C++ source file dumped by xxd

  Raises:
    RuntimeError: If input_cc_file path is invalid.
    IOError: If input_cc_file cannot be opened.

  Returns:
    A bytearray corresponding to the input cc file array.
  """
  # Match hex values in the string with comma as separator
  pattern = re.compile(r'\W*(0x[0-9a-fA-F,x ]+).*')

  model_bytearray = bytearray()

  with open(input_cc_file) as file_handle:
    for line in file_handle:
      values_match = pattern.match(line)

      if values_match is None:
        continue

      # Match in the parentheses (hex array only)
      list_text = values_match.group(1)

      # Extract hex values (text) from the line
      # e.g. 0x1c, 0x00, 0x00, 0x00, 0x54, 0x46, 0x4c,
      values_text = filter(None, list_text.split(','))

      # Convert to hex
      values = [int(x, base=16) for x in values_text]
      model_bytearray.extend(values)

  return bytes(model_bytearray)


def xxd_output_to_object(input_cc_file):
  """Converts xxd output C++ source file to object

  Args:
    input_cc_file: Full path name to th C++ source file dumped by xxd

  Raises:
    RuntimeError: If input_cc_file path is invalid.
    IOError: If input_cc_file cannot be opened.

  Returns:
    A python object corresponding to the input tflite file.
  """
  model_bytes = xxd_output_to_bytes(input_cc_file)
  return convert_bytearray_to_object(model_bytes)
def model_mapping_by_operators(model, enable_map_op,subgraph_idx=0, FLAGS=None):
    ops_mapped = f's{subgraph_idx}.' #bytearray()
    verbose = FLAGS.verbose
    msg = model.subgraphs[subgraph_idx]
    if msg.operators is None:
        return ops_mapped.rstrip('.').encode()
    for opidx, operator in enumerate(msg.operators):
        # assert model.subgraphs[0].tensors[operator.inputs[0]].type == 9
        if 'fc' in enable_map_op.keys()  and \
            isinstance(operator.builtinOptions, FullyConnectedOptionsT) and\
            msg.tensors[operator.inputs[0]].type == 9: #tensor input type is int8
            tensor_idx = operator.inputs[1] # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            buf_idx = tensor.buffer
            if verbose:
                print("fc idx: {} tensor name: {} dim: {}".format(buf_idx, tensor.name, tensor.shape.size))
            weight = np.array(model.buffers[buf_idx].data).reshape((tensor.shape[0], tensor.shape[1])).astype(np.int8)
            mapW, grpAligned, blkAlgined = map_fc_weights(weight.flatten(),
                                                         weight.shape[1], weight.shape[0],FLAGS.arch)
            model.buffers[buf_idx].data = copy.deepcopy(mapW.flatten())
            #tensor.shape[0] = grpAligned
            #tensor.shape[1] = blkAlgined
            #operator.builtinOptions.weightsFormat=FullyConnectedOptionsWeightsFormat.SHUFFLED4x16INT8
            if verbose:
                print("fc tensor idx: {} \naligned( {} {})".format(tensor_idx, blkAlgined,grpAligned))
            ops_mapped  += str(opidx)+'.'
        if 'lstm' in enable_map_op.keys() and \
          isinstance(operator.builtinOptions, UnidirectionalSequenceLSTMOptionsT) and \
          len(operator.inputs) == 24:  # tensor input type is int8
            ### input to forget weight #... weights
            # input to forget W 2 , recurrent to forget 6
            # input to input W 1, recurrent to input 5
            # input to cell W 3,  recurrent to cell 7
            # input to output 4, recurrent to cell 8
            lstm_remap_tensor_idx = [2, 6, 1, 5, 3, 7, 4, 8]

            for wi in lstm_remap_tensor_idx:
              tensor_idx = operator.inputs[wi]  # fixed index weight put
              tensor = msg.tensors[tensor_idx]
              buf_idx = tensor.buffer
              if verbose:
                print("lstm idx: {} tensor name: {} dim: {}".format(buf_idx, tensor.name, tensor.shape.size))
              weight = np.array(model.buffers[buf_idx].data).reshape((tensor.shape[0], tensor.shape[1])).astype(np.int8)
              mapW, grpAligned, blkAlgined = map_fc_weights(weight.flatten(),
                                                            weight.shape[1], weight.shape[0], FLAGS.arch)
              model.buffers[buf_idx].data = copy.deepcopy(mapW.flatten())
              # tensor.shape[0] = grpAligned
              # tensor.shape[1] = blkAlgined
              # operator.builtinOptions.weightsFormat=FullyConnectedOptionsWeightsFormat.SHUFFLED4x16INT8
              if verbose:
                print("lstm tensor idx: {} tensor:{} \naligned( {} {})".format(tensor_idx, wi, blkAlgined, grpAligned))
            ops_mapped += str(opidx) + '.'
        if 'svdf' in enable_map_op.keys()  and \
            isinstance(operator.builtinOptions, SVDFOptionsT) and\
            msg.tensors[operator.inputs[0]].type == 9: #tensor input type is int8

            tensor_idx = operator.inputs[1] # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            buf_idx = tensor.buffer
            if verbose:
                print("svdf idx: {} tensor name: {} dim: {}".format(buf_idx, tensor.name, tensor.shape.size))
            weight = np.array(model.buffers[buf_idx].data).reshape((tensor.shape[0], tensor.shape[1])).astype(np.int8)
            mapW, grpAligned, blkAlgined = map_fc_weights(weight.flatten(),
                                                         weight.shape[1], weight.shape[0],FLAGS.arch)
            model.buffers[buf_idx].data = copy.deepcopy(mapW.flatten())
            #tensor.shape[0] = grpAligned
            #tensor.shape[1] = blkAlgined
            #operator.builtinOptions.weightsFormat=FullyConnectedOptionsWeightsFormat.SHUFFLED4x16INT8
            if verbose:
                print("svdf tensor idx: {} \naligned( {} {})".format(tensor_idx, blkAlgined,grpAligned))
            ops_mapped  += str(opidx)+'.'
        elif 'conv' in enable_map_op.keys()  and \
                isinstance(operator.builtinOptions, Conv2DOptionsT) and \
                msg.tensors[operator.inputs[0]].type == 9: #integer-8 only
            tensor_idx = operator.inputs[1]  # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            buf_idx = tensor.buffer
            if verbose:
                print("conv idx: {} tensor name: {} dim: {}".format(buf_idx, tensor.name, tensor.shape.size))
            output_depth = tensor.shape[0]
            filter_height = tensor.shape[1]
            filter_width = tensor.shape[2]
            input_depth = tensor.shape[3]
            weight = np.array(model.buffers[buf_idx].data).reshape((tensor.shape[0],
                                                                    tensor.shape[1],
                                                                    tensor.shape[2],
                                                                    tensor.shape[3])).astype(np.int8)
            mapW, inch, fy, fx, dm = map_conv_weights(weight,filter_width, filter_height, output_depth,
                                                      input_depth, FLAGS.arch)
            model.buffers[buf_idx].data = copy.deepcopy(mapW.flatten())
            #tensor.shape[0] = inch
            #tensor.shape[1] = fy
            #tensor.shape[2] = fx
            #tensor.shape[3] = dm
            # operator.builtinOptions. = FullyConnectedOptionsWeightsFormat.SHUFFLED4x16INT8
            if verbose:
                print(f"conv tensor idx: {tensor_idx} \naligned( {inch} {fy} {fx} {dm})")
            ops_mapped  += str(opidx)+'.'
        elif 'ds_conv' in enable_map_op.keys()  and \
                isinstance(operator.builtinOptions, DepthwiseConv2DOptionsT) and \
                msg.tensors[operator.inputs[0]].type == 9:
            w_tensor_idx = operator.inputs[1]  # fixed index weight put
            out_tensor_idx = operator.outputs[0]
            in_tensor_idx = operator.inputs[0]
            w_tensor = msg.tensors[w_tensor_idx]
            out_tensor = msg.tensors[out_tensor_idx]
            in_tensor = msg.tensors[in_tensor_idx]
            w_buf_idx = w_tensor.buffer
            out_buf_idx= out_tensor.buffer
            if verbose:
                print("ds conv weight idx: {} tensor name: {} dim: {}".format(w_buf_idx, w_tensor.name, w_tensor.shape.size))
                print("ds conv output: {} tensor name {} ".format(out_buf_idx, out_tensor.name))
            output_depth = w_tensor.shape[0]
            filter_height = w_tensor.shape[1]
            filter_width = w_tensor.shape[2]
            input_depth = in_tensor.shape[3]
            depth_multipler = operator.builtinOptions.depthMultiplier
            weight = np.array(model.buffers[w_buf_idx].data).reshape((1,
                                                                    filter_height,
                                                                    filter_width,
                                                                    depth_multipler*input_depth)).astype(np.int8)
            #check output channel multiple of 8 and channel multipler is 1
            #if mapped_type =
            input_offset = in_tensor.quantization.zeroPoint[0]

            if depth_multipler == 1:
                mapped_type = 2 #DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE
            else:
                mapped_type = 1
                     # FIXME or 3
            mapW, inch, fy, fx, dm = map_ds_conv_weights(weight,
                                                        filter_width, filter_height, depth_multipler,
                                                      input_depth, FLAGS.arch, mapped_type)
            model.buffers[w_buf_idx].data = copy.deepcopy(mapW.flatten())
            #tensor.shape[0] = inch
            #tensor.shape[1] = fy
            #tensor.shape[2] = fx
            #tensor.shape[3] = dm
            # operator.builtinOptions. = FullyConnectedOptionsWeightsFormat.SHUFFLED4x16INT8
            if verbose:
                print("ds conv tensor idx: {} \nmapped_type: {} \n \naligned( {} {} {} {})".format(w_tensor_idx, mapped_type,
                                                                                                     inch, fy, fx, dm))
            ops_mapped  += str(opidx)+'.'
        ####  ds_conv weight float type remapping ##
        # exclude quantize option
        elif 'ds_conv' in enable_map_op.keys() and FLAGS.quantize_option == 0 and \
                isinstance(operator.builtinOptions, DepthwiseConv2DOptionsT) and  \
                msg.tensors[operator.inputs[0]].type == 0:

            w_tensor_idx = operator.inputs[1]  # fixed index weight put
            out_tensor_idx = operator.outputs[0]
            in_tensor_idx = operator.inputs[0]
            w_tensor = msg.tensors[w_tensor_idx]
            out_tensor = msg.tensors[out_tensor_idx]
            in_tensor = msg.tensors[in_tensor_idx]
            w_buf_idx = w_tensor.buffer
            out_buf_idx = out_tensor.buffer
            ## buffer data could be none type from dequantized float16
            if model.buffers[w_buf_idx].data is None:
                print(f"ds conv float {opidx} buffer None (from dequantized op)")
                continue
            if verbose:
                buf_len = len(bytes(model.buffers[w_buf_idx].data))
                print("ds conv weight idx: {} tensor name: {} dim: {} len: {} bytes".format(w_buf_idx, w_tensor.name,
                                                                              w_tensor.shape.size,buf_len))
                print("ds conv output: {} tensor name {} ".format(out_buf_idx, out_tensor.name))
            output_depth = w_tensor.shape[0]
            filter_height = w_tensor.shape[1]
            filter_width = w_tensor.shape[2]
            input_depth = in_tensor.shape[3]
            depth_multipler = operator.builtinOptions.depthMultiplier
            filter_size = filter_height* filter_width * input_depth
            if w_tensor.type == 0:
                weight_as_float = struct.unpack(f'<{filter_size}f', bytes(model.buffers[w_buf_idx].data))
            else:
                ##
                print("WARN: ERROR cannot convert int8 wieghts for hybrid convolution is not supported")
            weight = np.array(weight_as_float).reshape((1,
                                                                      filter_height,
                                                                      filter_width,
                                                                      depth_multipler * input_depth)).astype(np.float32)
            # check output channel multiple of 8 and channel multipler is 1
            # if mapped_type =
            if (out_tensor.shape[3] & 3) == 0 and depth_multipler == 1:
                mapped_type = 2
            else:
                mapped_type = 1
            mapWFlt = map_ds_conv_float_weights(weight,
                                                         filter_width, filter_height, depth_multipler,
                                                         input_depth, FLAGS.arch, mapped_type)
            model.buffers[w_buf_idx].data = copy.deepcopy(mapWFlt.flatten())
            # tensor.shape[0] = inch
            # tensor.shape[1] = fy
            # tensor.shape[2] = fx
            # tensor.shape[3] = dm
            # operator.builtinOptions. = FullyConnectedOptionsWeightsFormat.SHUFFLED4x16INT8
            if verbose:
                print("conv tensor idx: {}  )".format(w_tensor_idx))
            ops_mapped += str(opidx) + '.'
    return ops_mapped.rstrip('.').encode()
"""
model convert IEEE float to mini float 16
default mini float is follow IEEE mini float
sign:1
exp: 5, bias=14
man: 10

min val: 2.98023e-8
min norm: 3.0518e-5
max val: 6.5504e+4

"""
def model_float_coeff_to_minifloat(model, enable_map_op,subgraph_idx =0, FLAGS=None):
    ops_mapped = '.' #bytearray()
    verbose = FLAGS.verbose
    msg = model.subgraphs[subgraph_idx]
    for opidx, operator in enumerate(msg.operators):
        # assert msg.tensors[operator.inputs[0]].type == 9
        if 'fc' in enable_map_op.keys()  and \
            isinstance(operator.builtinOptions, FullyConnectedOptionsT) and\
            msg.tensors[operator.inputs[0]].type == 0: #tensor input type is int8
            tensor_idx = operator.inputs[1] # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            buf_idx = tensor.buffer
            if verbose:
                print("fc idx: {} tensor name: {} dim: {}".format(buf_idx, tensor.name, tensor.shape.size))
            weight = tuple(struct.iter_unpack('<f',bytes(model.buffers[buf_idx].data)))
            #mapW, grpAligned, blkAlgined = map_fc_weights(weight.flatten(),
            #                                             weight.shape[1], weight.shape[0],FLAGS.arch)
            #model.buffers[buf_idx].data = copy.deepcopy(mapW.flatten())
            w_float16 = quantize_to_minifloat(weight, 5, 14).reshape(tensor.shape).flatten().astype(np.uint16)

            model.buffers[buf_idx].data = np.array(tuple(struct.iter_unpack("<B",w_float16))).astype(np.uint8).squeeze()
            msg.tensors[operator.inputs[1]].type = 1  # kTfLiteFloat16 = 10,
            #tensor.shape[0] = grpAligned
            #tensor.shape[1] = blkAlgined
            #operator.builtinOptions.weightsFormat=FullyConnectedOptionsWeightsFormat.SHUFFLED4x16INT8
            if verbose:
                print(f"fc tensor idx: {tensor_idx} ")
            ops_mapped  += str(opidx)+'.'
        elif 'conv' in enable_map_op.keys()  and \
                isinstance(operator.builtinOptions, Conv2DOptionsT) and \
                msg.tensors[operator.inputs[0]].type == 0: #integer-8 only
            tensor_idx = operator.inputs[1]  # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            buf_idx = tensor.buffer
            if verbose:
                print("conv idx: {} tensor name: {} dim: {}".format(buf_idx, tensor.name, tensor.shape.size))
            output_depth = tensor.shape[0]
            filter_height = tensor.shape[1]
            filter_width = tensor.shape[2]
            input_depth = tensor.shape[3]
            weight = tuple(struct.iter_unpack('<f',bytes(model.buffers[buf_idx].data)))
            #mapW, inch, fy, fx, dm = conv_weights16(weight,filter_width, filter_height, output_depth,
            #                                          input_depth, FLAGS.arch)
            w_float16 = quantize_to_minifloat(weight, 5, 14).reshape(output_depth, filter_width,
                                                                                       filter_height, input_depth).flatten() #copy.deepcopy(mapW.flatten())
            model.buffers[buf_idx].data = np.array(tuple(struct.iter_unpack("<B",w_float16))).astype(np.uint8).squeeze()
            msg.tensors[tensor_idx].type = 1 #  kTfLiteFloat16 = 10,
            if verbose:
                print(f"conv float16 tensor idx: {tensor_idx} \n")
            ops_mapped  += str(opidx)+'.'
        elif 'ds_conv' in enable_map_op.keys()  and \
                isinstance(operator.builtinOptions, DepthwiseConv2DOptionsT) and \
                msg.tensors[operator.inputs[0]].type == 0: #float input
            tensor_idx = operator.inputs[1]  # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            buf_idx = tensor.buffer
            if verbose:
                print("ds conv idx: {} tensor name: {} dim: {}".format(buf_idx, tensor.name, tensor.shape.size))
            output_depth = tensor.shape[0]
            filter_height = tensor.shape[1]
            filter_width = tensor.shape[2]
            input_depth = tensor.shape[3]

            out_tensor_idx = operator.outputs[0]
            out_tensor = msg.tensors[out_tensor_idx]
            weight_flt = tuple(struct.iter_unpack('<f',bytes(model.buffers[buf_idx].data)))
            #mapW, inch, fy, fx, dm = conv_weights16(weight,filter_width, filter_height, output_depth,
            #                                          input_depth, FLAGS.arch)
            depth_multipler = operator.builtinOptions.depthMultiplier
            ### REMAP first
            if (out_tensor.shape[3] & 3) == 0 and depth_multipler == 1:
                flt_mapped_type = 2
            else:
                flt_mapped_type = 1
            weight_flt = np.array(weight_flt).reshape((1, filter_height, filter_width,
                                                       depth_multipler * input_depth)).astype(np.float32)

            weight_map_flt = map_ds_conv_float_weights(weight_flt,
                                                       filter_width, filter_height, depth_multipler,
                                                       input_depth, FLAGS.arch, flt_mapped_type)

            w_float16 = quantize_to_minifloat(weight_map_flt, 5, 14).reshape(output_depth, filter_width,
                                                                                       filter_height, input_depth).flatten() #copy.deepcopy(mapW.flatten())
            model.buffers[buf_idx].data = np.array(tuple(struct.iter_unpack("<B",w_float16))).astype(np.uint8).squeeze()
            msg.tensors[tensor_idx].type = 1 #  kTfLiteFloat16 = 10,
            if verbose:
                print(f"ds_conv float16 tensor idx: {tensor_idx} flt_mapped_type: {flt_mapped_type}\n")
            ops_mapped  += str(opidx)+'.'

    return ops_mapped.rstrip('.').encode()


def doubleToInt8Scale(x, log2N):
    """ floating-point data convert to fixed pointer with Q(log2N) format
    :param x: input data
    :param log2N: Q format, number of default exponent, only for 7, 15, 31
    :return: fixed-pointer data with maximum scaling ,(zero_point 0)
    """
    #if (log2N =! 7 || log2N != 15 || log2N != 3):
    #    return x, 0
    if log2N == 7:
        data_type = np.int8
    elif log2N ==15:
        data_type = np.int16
    elif log2N ==31:
        data_type = np.int32


    scale = 1./np.max(np.abs(x))
    fac = (np.power(2., log2N) - 1)
    w = x * scale  # FIXME
    #fac = np.power(2., fac)
    y = np.around(w * fac).astype(data_type)

    return y, np.array(1.0/fac/scale).astype(np.float32)
def model_float_coeff_to_8bit(model, enable_map_op, subgraph_idx = 0, FLAGS=None):
    ops_mapped = '.' #bytearray()
    verbose = FLAGS.verbose
    msg = model.subgraphs[subgraph_idx]
    for opidx, operator in enumerate(msg.operators):
        # assert msg.tensors[operator.inputs[0]].type == 9
        if 'fc' in enable_map_op.keys()  and \
            isinstance(operator.builtinOptions, FullyConnectedOptionsT) and\
            msg.tensors[operator.inputs[1]].type == 0: #tensor input type is int8
            tensor_idx = operator.inputs[1] # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            buf_idx = tensor.buffer

            weight = np.array(tuple(struct.iter_unpack('<f',bytes(model.buffers[buf_idx].data)))).astype(np.float32)

            #w_float16 = quantize_to_minifloat(weight, 5, 14).reshape(tensor.shape).flatten().astype(np.uint16)
            quantized8bit, scale = doubleToInt8Scale(weight, 7)
            model.buffers[buf_idx].data = np.array(tuple(struct.iter_unpack("<B",quantized8bit))).astype(np.uint8).squeeze()
            msg.tensors[operator.inputs[1]].type = 9  # kTfLiteFloat16 = 10,
            msg.tensors[operator.inputs[1]].quantization.scale = [scale]
            msg.tensors[operator.inputs[1]].quantization.zeroPoint = [int(0)]
            if verbose:
                    print(f"fc idx: {buf_idx} tensor name: {tensor.name} dim: {tensor.shape.size} scale: {scale}")
            weight = np.array(model.buffers[buf_idx].data).reshape((tensor.shape[0], tensor.shape[1])).astype(np.int8)
            mapW, grpAligned, blkAlgined = map_fc_weights(weight.flatten(),
                                                          weight.shape[1], weight.shape[0], FLAGS.arch)
            model.buffers[buf_idx].data = copy.deepcopy(mapW.flatten())
            ops_mapped += str(opidx)+'.'

        elif 'conv' in enable_map_op.keys()  and \
                isinstance(operator.builtinOptions, Conv2DOptionsT) and \
                msg.tensors[operator.inputs[1]].type == 0: #integer-8 only
            tensor_idx = operator.inputs[1]  # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            buf_idx = tensor.buffer

            output_depth = tensor.shape[0]
            filter_height = tensor.shape[1]
            filter_width = tensor.shape[2]
            input_depth = tensor.shape[3]
            weight = np.array(tuple(struct.iter_unpack('<f',bytes(model.buffers[buf_idx].data))))
            #mapW, inch, fy, fx, dm = conv_weights16(weight,filter_width, filter_height, output_depth,
            #                                          input_depth, FLAGS.arch)

            quantized8bit, scale = doubleToInt8Scale(weight, 7)
            model.buffers[buf_idx].data = np.array(tuple(struct.iter_unpack("<B",quantized8bit))).astype(np.uint8).squeeze()
            msg.tensors[tensor_idx].type = 9 #
            msg.tensors[operator.inputs[1]].quantization.scale = [scale]
            msg.tensors[operator.inputs[1]].quantization.zeroPoint = [int(0)]
            if verbose:
                print(f"conv idx: {buf_idx} tensor name: {tensor.name} dim: {tensor.shape.size} scale: {scale}")

            ## check PW CONV ONLY##
            if filter_height == 1 and filter_width == 1 and \
                operator.builtinOptions.dilationHFactor == 1 and \
                operator.builtinOptions.dilationWFactor == 1 and \
                operator.builtinOptions.strideH == 1 and \
                operator.builtinOptions.strideW == 1 and \
                operator.builtinOptions.padding == 1: #valid
                weight = np.array(model.buffers[buf_idx].data).reshape((tensor.shape[0],
                                                                        tensor.shape[1],
                                                                        tensor.shape[2],
                                                                        tensor.shape[3])).astype(np.int8)
                mapW, inch, fy, fx, dm = map_conv_weights(weight, filter_width, filter_height, output_depth,
                                                          input_depth, FLAGS.arch)
                model.buffers[buf_idx].data = copy.deepcopy(mapW.flatten())

                if verbose:
                    print(f"MAP PWCONV conv idx: {buf_idx} tensor name: {tensor.name} dim: {tensor.shape.size} scale: {scale}")

                ops_mapped  += str(opidx)+'.'
        elif 'ds_conv' in enable_map_op.keys()  and \
                isinstance(operator.builtinOptions, DepthwiseConv2DOptionsT) and \
                msg.tensors[operator.inputs[1]].type == 0: #float
            tensor_idx = operator.inputs[1]  # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            buf_idx = tensor.buffer
            out_tensor_idx = operator.outputs[0]
            out_tensor = msg.tensors[out_tensor_idx]
            output_depth = tensor.shape[0]
            filter_height = tensor.shape[1]
            filter_width = tensor.shape[2]
            input_depth = tensor.shape[3]
            depth_multipler = operator.builtinOptions.depthMultiplier
            weight_flt = np.array(tuple(struct.iter_unpack('<f',bytes(model.buffers[buf_idx].data))))
            #mapW, inch, fy, fx, dm = conv_weights16(weight,filter_width, filter_height, output_depth,
            #                                          input_depth, FLAGS.arch)
            ## COMPLICATE 1-> map by float
            ## if no use FLOAT map
            ## else use int8 map
            if (out_tensor.shape[3] & 3) == 0 and depth_multipler == 1:
                flt_mapped_type = 2
            else:
                flt_mapped_type = 1
            weight_flt = np.array(weight_flt).reshape((1,filter_height,filter_width,
                                                    depth_multipler * input_depth)).astype(np.float32)

            weight_map_flt = map_ds_conv_float_weights(weight_flt,
                                                filter_width, filter_height, depth_multipler,
                                                input_depth, FLAGS.arch, flt_mapped_type)

            quantized8bit, scale = doubleToInt8Scale(weight_map_flt, 7)
            model.buffers[buf_idx].data = np.array(tuple(struct.iter_unpack("<B",quantized8bit))).astype(np.uint8).squeeze()
            msg.tensors[tensor_idx].type = 9 #
            msg.tensors[operator.inputs[1]].quantization.scale = [scale]
            msg.tensors[operator.inputs[1]].quantization.zeroPoint = [int(0)]

            ops_mapped += str(opidx) + '.'

            if verbose:
                print(f"ds_conv idx: {buf_idx} tensor name: {tensor.name} dim: {tensor.shape.size} scale: {scale}")

            ## USE KERNEL INT8 x float MVM mapping

        elif 'ds_conv' in enable_map_op.keys() and \
                isinstance(operator.builtinOptions, DepthwiseConv2DOptionsT) and \
                msg.tensors[operator.inputs[1]].type == 9:  # int8 OPT by TF Converter
            tensor_idx = operator.inputs[1]  # fixed index weight put
            tensor = msg.tensors[tensor_idx]
            w_buf_idx = tensor.buffer
            out_tensor_idx = operator.outputs[0]
            out_tensor = msg.tensors[out_tensor_idx]
            filter_height = tensor.shape[1]
            filter_width = tensor.shape[2]
            input_depth = tensor.shape[3]
            depth_multipler = operator.builtinOptions.depthMultiplier
            #w_buf_idx = w_tensor.buffer
            weight = np.array(model.buffers[w_buf_idx].data).reshape((1,
                                                                      filter_height,
                                                                      filter_width,
                                                                      depth_multipler * input_depth)).astype(np.int8)
            # check output channel multiple of 8 and channel multipler is 1
            # if mapped_type =
            #input_offset = in_tensor.quantization.zeroPoint[0]

            if depth_multipler == 1:
                mapped_type = 2  # DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE
            else:
                mapped_type = 1
                # FIXME or 3
            if (out_tensor.shape[3] & 3) == 0 and depth_multipler == 1:
                mapped_type = 2
            else:
                mapped_type = 1
            mapWFlt = map_ds_conv_float_weights(weight,
                                                filter_width, filter_height, depth_multipler,
                                                input_depth, FLAGS.arch, mapped_type, w_type=np.int8)
            model.buffers[w_buf_idx].data = copy.deepcopy(mapWFlt.flatten())

            #mapW, inch, fy, fx, dm = map_ds_conv_weights(weight,
            #                                             filter_width, filter_height, depth_multipler,
            #                                             input_depth, FLAGS.arch, mapped_type)
            #model.buffers[w_buf_idx].data = copy.deepcopy(mapW.flatten())
            # tensor.shape[0] = inch
            # tensor.shape[1] = fy
            # tensor.shape[2] = fx
            # tensor.shape[3] = dm
            if verbose:
                print("ds conv tensor idx: {} \nmapped_type: {} \n \naligned( {} {} {} {})".format(tensor_idx,
                                                                                                   mapped_type,
                                                                                                   input_depth, filter_height,
                                                                                                   filter_width, depth_multipler))
            ops_mapped += str(opidx) + '.'

    return ops_mapped.rstrip('.').encode()

def model_convert(FLAGS, input_model = None):

    if input_model is None:
        model, model_obj = read_model(FLAGS.input[0])
    else:
        model, model_obj = read_model(input_model)
    print("model description: {}".format(model.description))
    print("arch: {}".format(FLAGS.arch))
    # skip remap if it's been a
    if model.description is not None:
        if model.description.startswith(b'KTL.'):
            print (f'warn:  {FLAGS.input[0]} already KTL format')
        #return FLAGS.output, model
    model.description = b'KTL.' + FLAGS.arch.encode()

    enable_map_op = {}
    for op in FLAGS.map_ops:
        enable_map_op[op] = 1
    for subgidx in range(0, len(model.subgraphs)):
        print(f"==> sugraph {subgidx}")
        map_ops = model_mapping_by_operators(model, enable_map_op, subgidx, FLAGS )

        if FLAGS.quantize_option == 1:
            miniflt_ops = model_float_coeff_to_minifloat(model, enable_map_op, subgidx, FLAGS )
            model.description += map_ops + miniflt_ops
        elif FLAGS.quantize_option == 2: #8 bit block exponent mix with float
            q8_ops = model_float_coeff_to_8bit(model, enable_map_op, subgidx, FLAGS)
            model.description += map_ops + q8_ops
        #else:
        if map_ops is not None:
            model.description += map_ops
    return FLAGS.output, model

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-i',
        '--input',
        type=str,
        nargs='+',
        required=True,
        default='[model.tflite]',
        help="input tflite_model"
    )

    parser.add_argument(
        '-o',
        '--output',
        type=str,
        required=True,
        help="output tflite model"
    )
    parser.add_argument(
        '--arch',
        type=str,
        default='hmd',
        help="output architecture: dmx or hmd"
    )
    parser.add_argument('-s',
                        '--strip',
                        action="count",
                        default=0,
                        help="string strip"
                        )
    """
    
    
    parser.add_argument('-r',
        '--remove_qntz',
        action="count",
        default=0,
        help="quantize/dequantize op strip"
    )
    """
    parser.add_argument('-v',
        '--verbose',
        action="count",
        default=0,
        help="dump converted mapped coefficients"
    )
    parser.add_argument(
                        '--crc32',
        action="store_true",
                        help="enable crc at tail"
                        )
    parser.add_argument('-m',
        '--map_ops',
       # action="count",
        type=str,
        nargs="+",
        default=['svdf', 'fc', 'lstm'], #conv, ds_conv
        help="mapping coefficients op"
    )
    parser.add_argument('-q',
                        '--quantize_option',
                        type=int,
                        default=0,
                        help="quantize option:\n\tfloat16=1\n\t8bit_scale=2"
                        )
    FLAGS, unparsed = parser.parse_known_args()
    _, model = model_convert(FLAGS)
    if(FLAGS.strip):
        #model.description += b'_Strip'
        strip_strings(model, verbose=FLAGS.verbose)
    output_model_len = write_model(model, FLAGS.output, FLAGS.crc32)

    input_model_size = os.stat(FLAGS.input[0]).st_size
    print("input tflite model: {} size: ".format(FLAGS.input[0]), input_model_size)
    increase_rate = float(output_model_len / input_model_size)

    print(f"output tflite model: {FLAGS.output} size:{output_model_len} {input_model_size} {increase_rate}")

    ## append crc32 at the end

    print("done")
