# Explicitly add kernel sources specific to the Xtensa optimized
# implementations.
MICROLITE_CC_KERNEL_SRCS += \
  tensorflow/lite/micro/kernels/ia700/mvm_helper.cc  \
  tensorflow/lite/micro/ia700/platform.cc
