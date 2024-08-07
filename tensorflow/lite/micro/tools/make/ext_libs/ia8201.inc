# Explicitly add kernel sources specific to the Xtensa optimized
# implementations.
MICROLITE_CC_KERNEL_SRCS += \
tensorflow/lite/micro/kernels/ia8201/mvm_helper.cc  \
  tensorflow/lite/micro/ia8201/platform.cc
