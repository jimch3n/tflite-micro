# Settings for Xtensa toolchain for the kernels.
# REQUIRED:
#  Environment variables:
#   - XTENSA_BASE  must be set to location of
#     the Xtensa developer tools installation directory.
#  Command line arguments:
#   - XTENSA_TOOLS_VERSION: For example: RI-2019.2-linux
#   - XTENSA_CORE: The name of the Xtensa core to use
#      For example: HIFI_190304_swupgrade

TARGET_ARCH :=
XTENSA_USE_LIBC := true

# Allow additional flags on the command line for debugging.
XTENSA_EXTRA_CFLAGS :=

ifndef XTENSA_BASE
  $(error XTENSA_BASE is undefined)
endif

ifndef XTENSA_TOOLS_VERSION
  $(error XTENSA_TOOLS_VERSION is undefined)
endif

ifndef XTENSA_CORE
  $(error XTENSA_CORE is undefined)
endif

ifeq ($(TARGET_ARCH), )
  $(error TARGET_ARCH must be specified on the command line)
endif

# Create a cflag based on the specified TARGET_ARCH. For example:
#   TARGET_ARCH=hifi4 --> -DHIFI4
TARGET_ARCH_DEFINES := -D$(shell echo $(TARGET_ARCH) | tr [a-z] [A-Z])
####### HMD TIE ####
	TARGET_ARCH_CFLAGS := \
	-DHMD1A \
    -DAVL_HEMI 
	CORE := Hmd1a

  ROME_SDK_ROOT := third_party/ia8201_sdk/Rome
  ROME_CORE_INC := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/Include
  #ROME_ML_INC   := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/MachineLearning/Include
  ROME_UTILS_INC   := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/Utility/Include
  ROME_DSP_INC   := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/DSP/Include
  ROME_AVL_INC   := $(ROME_SDK_ROOT)/Src/Cores/AVL
  ROME_CSTUBS_INC   := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/SimulationEnvironment/Include
  ROME_DSP_LIB_PATH := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/DSP/Libs

  ROME_CSTUBS_LIB_PATH := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/SimulationEnvironment/Libs
  ROME_CSTUBS_LIB := gccSimulationEnvironment.a


HMD_FLAGS :=     -I$(ROME_CORE_INC) \
    -I$(ROME_AVL_INC) \
    -I$(ROME_DSP_INC) \
    -I$(ROME_UTILS_INC) \
    $(TARGET_ARCH_CFLAGS)

PLATFORM_FLAGS = \
  -DTF_LITE_MCU_DEBUG_LOG \
  -DTF_LITE_USE_CTIME \
  --xtensa-core=$(XTENSA_CORE) \
  -mcoproc \
  -DMAX_RFFT_PWR=9 \
  -DMIN_RFFT_PWR=MAX_RFFT_PWR \
  $(TARGET_ARCH_DEFINES) \
  -mlongcalls

export PATH := $(XTENSA_BASE)/tools/$(XTENSA_TOOLS_VERSION)/XtensaTools/bin:$(PATH)
TARGET_TOOLCHAIN_PREFIX := xt-
CXX_TOOL := clang++
CC_TOOL := clang

# Unused exception related symbols make their way into a binary that links
# against TFLM as described in https://github.com/tensorflow/tensorflow/issues/47575.
# We have two options to avoid this. The first involves using -stdlib=libc++ and
# the second involves stubbing out and modifying some of the files in the Xtensa
# toolchain to prevent inclusion of the exception handling code
# (http://b/182209217#comment3). This Makefile supports building TFLM in a way
# that is compatible with either of the two approaches.
ifeq ($(XTENSA_USE_LIBC), true)
  PLATFORM_FLAGS += -stdlib=libc++
else
  # TODO(b/150240249): Do not filter-out -fno-rtti once that works for the
  # Xtensa toolchain.
  CXXFLAGS := $(filter-out -fno-rtti, $(CXXFLAGS))
endif
ifeq ($(RM_TFLM_SIGNAL),1)
   XTENSA_EXTRA_CFLAGS += -DREMOVE_TFLM_SIGNAL
endif

ifeq ($(TEST_MODE), 1)
## test with log, always enable for remap coeff at runtime SVDF/FC
    XTENSA_EXTRA_CFLAGS += -DKERNEL_COEFF_MAP_ENABLE
endif

#enable hmd core mvm
XTENSA_EXTRA_CFLAGS += -DUSE_HMD_MVM_OPT
XTENSA_EXTRA_CFLAGS += $(HMD_FLAGS)
CXXFLAGS += $(PLATFORM_FLAGS)
CCFLAGS += $(PLATFORM_FLAGS)

## remove for micro-allocator
CXXFLAGS := $(filter-out -Wnon-virtual-dtor, $(CXXFLAGS))
  
CCFLAGS += $(XTENSA_EXTRA_CFLAGS)
CXXFLAGS += $(XTENSA_EXTRA_CFLAGS)
## remove for build error in ndsplib-hifi4
CCFLAGS := $(filter-out -Werror, $(CCFLAGS))

TEST_SCRIPT := $(TENSORFLOW_ROOT)tensorflow/lite/micro/testing/test_xtensa_binary.sh
SIZE_SCRIPT := $(TENSORFLOW_ROOT)tensorflow/lite/micro/testing/size_xtensa_binary.sh

# TODO(b/158651472): Fix the memory_arena_threshold_test
# TODO(b/174707181): Fix the micro_interpreter_test
EXCLUDED_TESTS := \
  $(TENSORFLOW_ROOT)tensorflow/lite/micro/memory_arena_threshold_test.cc
MICROLITE_TEST_SRCS := $(filter-out $(EXCLUDED_TESTS), $(MICROLITE_TEST_SRCS))

# TODO(b/156962140): This manually maintained list of excluded examples is
# quite error prone.
EXCLUDED_EXAMPLE_TESTS := \
  $(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hello_world/Makefile.inc \
  $(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/image_recognition_experimental/Makefile.inc \
  $(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/network_tester/Makefile.inc
MICRO_LITE_EXAMPLE_TESTS := $(filter-out $(EXCLUDED_EXAMPLE_TESTS), $(MICRO_LITE_EXAMPLE_TESTS))
MICRO_LITE_EXAMPLE_TESTS += $(shell find $(TENSORFLOW_ROOT)third_party/xtensa/examples/ -name Makefile.inc)

# Needed for LSTM support.
MICROLITE_CC_KERNEL_SRCS := $(MICROLITE_CC_KERNEL_SRCS) \
$(TENSORFLOW_ROOT)tensorflow/lite/kernels/internal/reference/portable_tensor_utils.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/kernels/kernel_util.cc

ifeq ($(OPTIMIZED_KERNEL_DIR), xtensa)
  MICROLITE_CC_KERNEL_SRCS := $(MICROLITE_CC_KERNEL_SRCS) \
  $(TENSORFLOW_ROOT)tensorflow/lite/micro/kernels/xtensa/lstm_eval.cc \
  $(TENSORFLOW_ROOT)tensorflow/lite/micro/kernels/xtensa/lstm_eval_hifi.cc \
  $(TENSORFLOW_ROOT)tensorflow/lite/micro/kernels/xtensa/unidirectional_sequence_lstm.cc \
  $(TENSORFLOW_ROOT)tensorflow/lite/micro/kernels/xtensa/mvm_helper.cc
endif
