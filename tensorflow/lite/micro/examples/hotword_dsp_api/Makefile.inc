# Arguments are:
# 1 - Name of target. "nb" "wb_small" "wb_large" "y_google_small" "y_google_large" 
# 2 - C/C++ source files
# 3 - C/C++ header files
# 4 - Model sources and model test inputs in.tflite, .wav, .bmp or .csv format.
# Calling eval on the output will create the targets that you need.
define hotword_model_test

$(info hotword input target: [$(1)])
$(1)_HOTWORD_DSP_API_TEST_SRCS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/common.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/hotword_dsp_api_$(1).cc \


#HOTWORD_DSP_API_SRCS := \
#$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/hotword_dsp_api_y_google_large.cc

#HOTWORD_DSP_API_HDRS :=

$(1)_HOTWORD_DSP_API_GENERATOR_INPUTS := \
$$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/models/$(1)_en_all.tflite 

$(1)_HOTWORD_DSP_API_GENERATED_SRCS := \
$$(GENERATED_SRCS_DIR)$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/models/hotword_$(1)_models/$(1)_en_all_data.cc

$(1)_HOTWORD_DSP_API_GENERATED_HDRS := \
$$(GENERATED_SRCS_DIR)$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/models/$(1)_model_data.h \
$$(GENERATED_SRCS_DIR)$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/models/$(1)_model_data.h

# Tests loading and running the hotword model.
$(info target $$($(1)_HOTWORD_DSP_API_TEST_SRCS), $$($(1)_HOTWORD_DSP_API_GENERATOR_INPUTS))
$(eval $(call microlite_test,hotword_dsp_api_$(1)_test,\
$($(1)_HOTWORD_DSP_API_TEST_SRCS),, $($(1)_HOTWORD_DSP_API_GENERATOR_INPUTS)))
endef


######## IA8201 HMD Core use MVM optimization and signal HIFI/afloat opt ############
ifeq ($(TARGET), xtensa)
TARGET_OBJ_DIR := $(KERNEL_OBJDIR)/tensorflow/lite/micro/kernels/
TARGET_OBJS := $(addprefix $(TARGET_OBJ_DIR), xtensa/svdf.o svdf_common.o xtensa/fully_connected_int8.o)

TARGET_OBJ_SIG_DIR := $(KERNEL_OBJDIR)/signal/src/
#TARGET_SRC_DIR := $(TENSORFLOW_ROOT)/signal/src/
#SIGNAL_OPT_SRC := $(addprefix $(TARGET_OBJ_SIG_DIR), energy.cc filter_bank_spectral_subtraction.cc filter_bank_square_root.cc window.cc)
#remove filter_bank_square_root.o
SIGNAL_OPT_OBJS := $(addprefix $(TARGET_OBJ_SIG_DIR), energy.o filter_bank.o filter_bank_spectral_subtraction.o  window.o filter_bank_log.o)
#SIGNAL_OPT_OBJS := $(addprefix $(TARGET_OBJ_SIG_DIR), energy.o filter_bank.o filter_bank_spectral_subtraction.o  window.o filter_bank_log.o)

XTENSA_OBJ_SIG_DIR :=  $(KERNEL_OBJDIR)/signal/micro/kernels/xtensa/
SIGNAL_OPT_OBJS_2 := $(addprefix $(XTENSA_OBJ_SIG_DIR), filter_bank_square_root.o)

MVM_HELPER_OBJ := $(KERNEL_OBJDIR)tensorflow/lite/micro/kernels/xtensa/mvm_helper.o
FB_SQRT_AFLT_OBJ := $(KERNEL_OBJDIR)/signal/src/square_root_afloat.o

#TARGET_OBJS += $(SIGNAL_OPT_OBJS)
#$(info TARGET_OBJS : $(TARGET_OBJS) $(HOST_OS))
#$(info signal objs: $(SIGNAL_OPT_OBJS))
BUILD_HK_OBJS := $(findstring $(TARGET_OBJS), $(MICROLITE_KERNEL_OBJS))
MICROSPEECH_LIB := $(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/lib/libtensorflow-speech-micro.a
MODE_CONFIG_LIB := $(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/lib/model_config_wideband.a
GOOFLE_TF_MICROLITE_LIB := $(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/lib/libtensorflow-microlite.a


TARGET_TFLIB := $(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/lib/libtensorflow-microlite-kn.a


$(TARGET_OBJS): $(TARGET_TFLIB) $(MICROLITE_LIB_PATH)
	@echo archieve  $< $@
	$(AR) d $< $(notdir $@) && \
  $(AR) rcu $< $@
##
### replace x.2.o , delete second object xN 2 due to common name objects has 4.
### the second  is target
$(SIGNAL_OPT_OBJS): $(MICROLITE_LIB_PATH)
	@echo archieve  IN $@  OUT $(subst .o,.2.o,$(notdir $@))
	cp $@ $(subst .o,.2.o,$(notdir $@)) &&   $(AR) dN 2 $(TARGET_TFLIB) $(notdir $@) && \
  $(AR) rcu $(TARGET_TFLIB) $(subst .o,.2.o,$(notdir $@))

## replace XTENSA ###
$(SIGNAL_OPT_OBJS_2): $(MICROLITE_LIB_PATH)
	@echo archieve  IN $@  OUT $(subst .o,.4.o,$(notdir $@))
	@echo delete all other object
	$(AR) dN 3 $(TARGET_TFLIB) $(notdir $@) && \
	$(AR) dN 4 $(TARGET_TFLIB) $(notdir $@) && \
	cp $@ $(subst .o,.4.o,$(notdir $@)) &&   $(AR) dN 1 $(TARGET_TFLIB) $(notdir $@) && \
  $(AR) rcu $(TARGET_TFLIB) $(subst .o,.4.o,$(notdir $@))

copy_lib: $(GOOFLE_TF_MICROLITE_LIB) $(MICROLITE_LIB_PATH)
	rm -f $(TARGET_TFLIB)
	cp -f $(GOOFLE_TF_MICROLITE_LIB) $(TARGET_TFLIB)
kernel_replace: $(TARGET_TFLIB)  $(TARGET_OBJS)
	$(AR) rcu $(TARGET_TFLIB) $(MVM_HELPER_OBJ) $(FB_SQRT_AFLT_OBJ)
signal_replace: $(TARGET_TFLIB)  $(SIGNAL_OPT_OBJS) $(SIGNAL_OPT_OBJS_2)

endif

y_google_large_HOTWORD_DSP_API_TEST_SRCS := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/common.cc \
$(TENSORFLOW_ROOT)google/application/crc32/crc32.cc \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/hotword_dsp_api_file.cc \
$(TENSORFLOW_ROOT)tensorflow/python/graphs/testdata/okgoogle_audio_data.cc 

MODEL_INTPUT := \
$(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/models/hotword_large_y_google_models/y_google_large_en_all.tflite 

CXXFLAGS += -DMEASURE_CYCLES=1 -DDISABLE_LOG=0

ifeq ($(TARGET),xtensa)
# Tests loading and running the hotword model.
#$(info target $(y_google_large_HOTWORD_DSP_API_TEST_SRCS), $(y_google_large_HOTWORD_DSP_API_GENERATOR_INPUTS))
#$(eval $(call microlite_test,hotword_dsp_api_y_google_large_test,$(y_google_large_HOTWORD_DSP_API_TEST_SRCS),,))
hotword_local_obj = $(addprefix $(CORE_OBJDIR), \
$(patsubst %.S,%.o,$(patsubst %.cc,%.o,$(patsubst %.c,%.o,$(y_google_large_HOTWORD_DSP_API_TEST_SRCS)))))

hotword_dsp_api_BINARY := $(BINDIR)/hotword_dsp_api_test
$(hotword_dsp_api_BINARY): $(hotword_local_obj) $(GOOFLE_TF_MICROLITE_LIB)  $(MICROSPEECH_LIB) $(MODE_CONFIG_LIB)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) \
	-o $(hotword_dsp_api_BINARY) $(hotword_local_obj) $(LDFLAGS) \
	 -Wl,--start-group $(GOOFLE_TF_MICROLITE_LIB)  $(MICROLITE_LIBS) $(MICROSPEECH_LIB) $(MODE_CONFIG_LIB)  -Wl,--end-group 

hotword_dsp_api_test: $(hotword_dsp_api_BINARY)
	@test -f $(TEST_SCRIPT) || (echo 'Unable to find the test script. Is the software emulation available in $(TARGET)?'; exit 1)
	xt-run $<  $(MODEL_INTPUT)

###############
# convert model
##############
IAXXX_MODEL_CONVERTER_SRC :=  $(TENSORFLOW_ROOT)third_party/ia8201_sdk/iaxxx_tflite_model_converter/iaxxx_tflite_model_converter.cpp \
$(TENSORFLOW_ROOT)third_party/ia8201_sdk/iaxxx_tflite_model_converter/test_app.cpp


$(CORE_OBJDIR)%.o: %.cpp $(THIRD_PARTY_TARGETS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CORE_OPTIMIZATION_LEVEL) $(INCLUDES) -c $< -o $@

TFLITE_MODEL := $(TENSORFLOW_ROOT)tensorflow/lite/micro/examples/hotword_dsp_api/models/hotword_large_y_google_models/y_google_large_en_all.tflite
#native compile
KN_TFLITE_MODEL := $(addprefix $(BINDIR), $(subst  .tflite,_kn.tflite,$(notdir $(TFLITE_MODEL))))
model_converter_obj = $(addprefix $(CORE_OBJDIR), \
$(patsubst %.cpp,%.o,$(IAXXX_MODEL_CONVERTER_SRC)))
#$(info model obj: $(model_converter_obj))
#$(info kn_tflite_model: $(KN_TFLITE_MODEL))
hotword_model_convert := $(BINDIR)/iaxxx_model_converter
$(hotword_model_convert): $(model_converter_obj)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS)  $(INCLUDES) $(model_converter_obj) -o $@  $(LDFLAGS)

$(KN_TFLITE_MODEL): $(hotword_model_convert) $(TFLITE_MODEL)
	xt-run $(hotword_model_convert) $(TFLITE_MODEL) $(KN_TFLITE_MODEL)

### replace optimized object ###
tflite_replace_obj: copy_lib signal_replace kernel_replace


### mvm opt ###
hotword_dsp_api_mvm_opt_BINARY := $(BINDIR)/hotword_dsp_api_mvm_opt_test
$(hotword_dsp_api_mvm_opt_BINARY): $(hotword_local_obj) $(TARGET_TFLIB)  $(MICROSPEECH_LIB) $(MODE_CONFIG_LIB)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) \
	-o $(hotword_dsp_api_mvm_opt_BINARY) $(hotword_local_obj) $(LDFLAGS) \
	 -Wl,--start-group $(TARGET_TFLIB)  $(MICROLITE_LIBS) $(MICROSPEECH_LIB) $(MODE_CONFIG_LIB)  -Wl,--end-group 

hotword_dsp_api_mvm_opt_test: tflite_replace_obj $(hotword_dsp_api_mvm_opt_BINARY) $(KN_TFLITE_MODEL)
	@test -f $(TEST_SCRIPT) || (echo 'Unable to find the test script. Is the software emulation available in $(TARGET)?'; exit 1)
	xt-run $(hotword_dsp_api_mvm_opt_BINARY)  $(KN_TFLITE_MODEL)

endif
