# Settings for Xtensa toolchain for the Knwoles ia700 hemilite kernels.
# REQUIRED:
#  Environment variables:
#   - XTENSA_BASE  must be set to location of
#     the Xtensa developer tools installation directory.
#  Command line arguments:
#   - XTENSA_TOOLS_VERSION: For example: RI-2019.2-linux
#   - XTENSA_CORE: The name of the Xtensa core to use
#      For example: hifi3

ifeq ($(TARGET), ia700)
  ifeq ($(HOST_OS), linux)
  SDK_ROOT := /home/jimchen/P4WS/AlgoSW/Product/shapiro-sdk-support-TFLu-dev/SDK/Audience_SDK_IA61x/DSPDev/
    XTENSA_SYSTEM_BASE := /home/jimchen/xtensa/XtDevTools/install/tools
    XTENSA_TOOLS_VERSION := RI-2020.4-linux
  else
  SDK_ROOT := p:/AlgoSW/Product/shapiro-sdk-support-TFLu-dev/SDK/Audience_SDK_IA61x/DSPDev/
  XTENSA_SYSTEM_BASE := c:/usr/xtensa/XtDevTools/install/tools
  XTENSA_TOOLS_VERSION := RI-2020.4-win32
  endif
  ifeq ($(findstring cstubs,$(TARGET_ARCH)), cstubs)
    TARGET_PF=CSTUBS
  endif
    XTENSA_CORE := hemilite_shapiro_RI04
	TARGET_ARCH_CFLAGS := \
	-DHEMILITE \
    -DAVL_HEMI 

   TARGET_ARCH := hml
  ifndef XTENSA_SYSTEM_BASE
    $(error XTENSA_SYSTEM_BASE is undefined)
  endif

  ifndef XTENSA_TOOLS_VERSION
    $(error XTENSA_TOOLS_VERSION is undefined)
  endif

  ifndef XTENSA_CORE
    $(error XTENSA_CORE is undefined)
  endif


  #D:/src/SDK/IA700_SDK/Knowles_IA700_SDK/DSPDev/
  SDK_CORE_INC := $(SDK_ROOT)/Source/HemiLitePlatform
#remove ML due to arguments too long
#  SDK_ML_INC   := $(SDK_ROOT)/Dist/MVM_VIPLib/Include
  SDK_DSP_INC  := $(SDK_ROOT)/Dist/CoreDSPLib/Include
  SDK_AVL_INC   := $(SDK_ROOT)/Dist/AVL
  SDK_DSP_LIB_PATH := $(SDK_ROOT)/Dist/CoreDSPLib/Libs/
  SDK_DSP_LIB := xccCoreDSPLib.a
  SDK_CSTUBS_INC   := $(SDK_ROOT)/Dist/HemiLiteIntrinsicLib/Include

  SDK_CSTUBS_LIB_PATH := $(SDK_ROOT)/Dist/HemiLiteIntrinsicLib//Libs
  SDK_CSTUBS_LIB := gccHemiLiteIntrinsicLib.a
###
#XtensaTools\config
   XTENSA_FLAGS := --xtensa-system=$(XTENSA_SYSTEM_BASE)/$(XTENSA_TOOLS_VERSION)/XtensaTools/config \
    --xtensa-core=$(XTENSA_CORE) \
    --xtensa-params= \
  
  TFLM_ARCH_INC := -Itensorflow/lite/micro/ia700 \
                   -Itensorflow/lite/micro/kernels/ia700
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
    -I$(SDK_CORE_INC) \
    -I$(SDK_AVL_INC) \
    -I$(SDK_DSP_INC)
### release build kernel exclude reference op macro in optimized kernels###
   ifeq ($(BUILD_TYPE), release)
     TF_LITE_MICRO_FLAGS += -DREMOVE_REFOP_SUPPORT 
   endif

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

     LIB_PREFIX := xcc
   else
      TF_LITE_MICRO_FLAGS +=    -I$(SDK_CSTUBS_INC) -m32 -D__int64="long long" -g
      CXX_TOOL := g++
      CC_TOOL := gcc
      LDFLAGS += $(SDK_CSTUBS_LIB_PATH)/$(SDK_CSTUBS_LIB)
      LIB_PREFIX := gcc
  endif


  CXXFLAGS +=  $(PLATFORM_ARGS) $(TF_LITE_MICRO_FLAGS)
  #TODO: Use -std=c11 ?
  CCFLAGS +=  $(PLATFORM_ARGS) $(TF_LITE_MICRO_FLAGS)
  ## disable warning for cstubs
  ifeq ($(TARGET_PF),CSTUBS)
  WARN_AS_ERROR :=  -Werror -Wall
  CXXFLAGS := $(filter-out $(WARN_AS_ERROR), $(CXXFLAGS))
  CCFLAGS := $(filter-out $(WARN_AS_ERROR), $(CCFLAGS))
  else
  ## exp remove virtual dtor
  CXXFLAGS := $(filter-out -Wnon-virtual-dtor, $(CXXFLAGS))
  endif
  TEST_SCRIPT := tensorflow/lite/micro/testing/test_xtensa_ia700_binary.sh
  #LDFLAGS += -l:$(SDK_DSP_LIB_PATH)/$(SDK_DSP_LIB)
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
