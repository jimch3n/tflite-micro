# Settings for Xtensa toolchain for the Knwoles ia8201 deltamax/hemidelta kernels.
# REQUIRED:
#  Environment variables:
#   - XTENSA_BASE  must be set to location of
#     the Xtensa developer tools installation directory.
#  Command line arguments:
#   - XTENSA_TOOLS_VERSION: For example: RI-2019.2-linux
#   - XTENSA_CORE: The name of the Xtensa core to use
#      For example: hifi3

ifeq ($(TARGET), ia8201)
  ifeq ($(HOST_OS), linux)
    XTENSA_SYSTEM_BASE := ${HOME}/xtensa/XtDevTools/install/tools
    XTENSA_TOOLS_VERSION := RI-2020.4-linux
  else
    XTENSA_SYSTEM_BASE := c:/usr/xtensa/XtDevTools/install/tools
    XTENSA_TOOLS_VERSION := RI-2020.4-win32
  endif
  
  ifeq ($(findstring cstubs,$(TARGET_ARCH)), cstubs)
    TARGET_PF=CSTUBS
  endif
  ifeq ($(findstring dmx1a,$(TARGET_ARCH)), dmx1a)
    XTENSA_CORE := dmx1aRI04
	TARGET_ARCH_CFLAGS := \
	-DDMX1A \
    -DAVL_DMX1A 
	CORE := Dmx1a
  endif
  ifeq ($(findstring hmd1a,$(TARGET_ARCH)), hmd1a)
    XTENSA_CORE := hmd1aRI04
	TARGET_ARCH_CFLAGS := \
	-DHMD1A \
    -DAVL_HEMI 
	CORE := Hmd1a
  endif
  ifndef XTENSA_SYSTEM_BASE
    $(error XTENSA_SYSTEM_BASE is undefined)
  endif

  ifndef XTENSA_TOOLS_VERSION
    $(error XTENSA_TOOLS_VERSION is undefined)
  endif

  ifndef XTENSA_CORE
    $(error XTENSA_CORE is undefined)
  endif

  ROME_SDK_ROOT := third_party/ia8201_sdk/Rome
  ROME_CORE_INC := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/Include
  ROME_ML_INC   := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/MachineLearning/Include
  ROME_DSP_INC   := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/DSP/Include
  ROME_AVL_INC   := $(ROME_SDK_ROOT)/Src/Cores/AVL
  ROME_CSTUBS_INC   := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/SimulationEnvironment/Include
  ROME_DSP_LIB_PATH := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/DSP/Libs

  ROME_CSTUBS_LIB_PATH := $(ROME_SDK_ROOT)/Src/Cores/Core_$(CORE)/SimulationEnvironment/Libs
  ROME_CSTUBS_LIB := gccSimulationEnvironment.a
###
#XtensaTools\config
   XTENSA_FLAGS := --xtensa-system=$(XTENSA_SYSTEM_BASE)/$(XTENSA_TOOLS_VERSION)/XtensaTools/config \
    --xtensa-core=$(XTENSA_CORE) \
    --xtensa-params= \
  
  TFLM_ARCH_INC := -Itensorflow/lite/micro/ia8201 \
                   -Itensorflow/lite/micro/kernels/ia8201
  PLATFORM_ARGS = \
    -fmessage-length=0 \
    -fno-strict-aliasing \
    -fsigned-char \
    -fno-exceptions \
    -INLINE:requested \
    -fno-zero-initialized-in-bss \
    -fno-unsafe-math-optimizations

  TF_LITE_MICRO_FLAGS = \
    $(TARGET_ARCH_CFLAGS) \
    -DTF_LITE_MCU_DEBUG_LOG \
    -I$(ROME_CORE_INC) \
    -I$(ROME_AVL_INC) \
    -I$(ROME_DSP_INC)
### release build kernel exclude reference op macro in optimized kernels###
   #ifeq ($(BUILD_TYPE), release)
   #  TF_LITE_MICRO_FLAGS += -DREMOVE_REFOP_SUPPORT 
   #endif
  export PATH := $(XTENSA_SYSTEM_BASE)/$(XTENSA_TOOLS_VERSION)/XtensaTools/bin:$(PATH)
 ifneq ($(TARGET_PF),CSTUBS)
     TARGET_TOOLCHAIN_PREFIX := xt-
     TF_LITE_MICRO_FLAGS +=     $(XTENSA_FLAGS) \
     -mcoproc \
     -mtext-section-literals \
     -mlongcalls \
     -Wno-unused-private-field \
     --stdlib=libc++
     CXX_TOOL := clang++
     CC_TOOL := clang
     CXXFLAGS := $(filter-out -Wnon-virtual-dtor, $(CXXFLAGS))
     LIB_PREFIX := xcc
   else
      TF_LITE_MICRO_FLAGS +=    -I$(ROME_CSTUBS_INC) -m32 -D__int64="long long" -g
      CXX_TOOL := g++
      CC_TOOL := gcc
      LDFLAGS += $(ROME_CSTUBS_LIB_PATH)/$(ROME_CSTUBS_LIB)
      LIB_PREFIX := gcc
  endif
## remove TFLM_SIGNAL namespace in signal processing
ifeq ($(RM_TFLM_SIGNAL),1)
   TF_LITE_MICRO_FLAGS += -DREMOVE_TFLM_SIGNAL
endif

  CXXFLAGS +=  $(PLATFORM_ARGS) $(TF_LITE_MICRO_FLAGS)
  #TODO: Use -std=c11 ?
  CCFLAGS +=  $(PLATFORM_ARGS) $(TF_LITE_MICRO_FLAGS)
  ## disable warning for cstubs
  ifeq ($(TARGET_PF),CSTUBS)
  WARN_AS_ERROR :=  -Werror -Wall
  CXXFLAGS := $(filter-out $(WARN_AS_ERROR), $(CXXFLAGS))
  CCFLAGS := $(filter-out $(WARN_AS_ERROR), $(CCFLAGS))
  endif
  TEST_SCRIPT := tensorflow/lite/micro/testing/test_xtensa_ia8201_binary.sh
  #LDFLAGS += -l:$(ROME_DSP_LIB_PATH)/xccDSPLib.a
  EXCLUDED_EXAMPLE_TESTS := \
    tensorflow/lite/micro/examples/image_recognition_experimental/Makefile.inc \
    tensorflow/lite/micro/examples/person_detection/Makefile.inc \
    tensorflow/lite/micro/examples/person_detection_experimental/Makefile.inc
  MICRO_LITE_EXAMPLE_TESTS := $(filter-out $(EXCLUDED_EXAMPLE_TESTS), $(MICRO_LITE_EXAMPLE_TESTS))

# logistic output in afloat domain is more accuracy than fixed-point
  EXCLUDED_TESTS := \
    tensorflow/lite/micro/micro_interpreter_test.cc \
    tensorflow/lite/micro/micro_allocator_test.cc \
    tensorflow/lite/micro/memory_helpers_test.cc \
    tensorflow/lite/micro/memory_arena_threshold_test.cc
  
  MICROLITE_TEST_SRCS := $(filter-out $(EXCLUDED_TESTS), $(MICROLITE_TEST_SRCS))



endif
