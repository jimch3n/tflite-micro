#!/bin/bash
# -------------------------------------------------------------
# This script is to build and test tensorflow-microlite library.
# Specify 'test' as first arguemnt to test the built library.
# If no arguemnt provided, library is only built but not tested.
# -------------------------------------------------------------

export SHELLOPTS

ROME_SDK_ROOT=../third_party/ia8201_sdk/Rome
# For Linux platform
if [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then


 export XTENSA_VER=RI-2020.4-linux
 export XTENSA_SYSTEM_BASE=${HOME}/xtensa/XtDevTools/install/tools
 export XTENSA_SYSTEM=$XTENSA_SYSTEM_BASE/$XTENSA_VER/XtensaTools/config
# For Cygwin (in Windows) platform
elif [ "$(expr substr $(uname -s) 1 6)" == "CYGWIN" ]; then
 set -o igncr
 export XTENSA_CORE=dmx1aRI04
 export XTENSA_VER=RI-2020.4-win32

 export PATH=/cygdrive/c/usr/xtensa/Xplorer-8.0.13:/cygdrive/c/usr/xtensa/XtDevTools/install/tools/$XTENSA_VER/XtensaTools/bin:$PATH
 export XTENSA_SYSTEM_BASE=$(cygpath -m /cygdrive/c/usr/xtensa/XtDevTools/install/tools)
 export XTENSA_SYSTEM=$XTENSA_SYSTEM_BASE/$XTENSA_VER/XtensaTools/config
fi
build_dmx_hmd()
{
  
	#
	echo "==="
	echo "XTENSA_CORE:" $XTENSA_CORE
	echo "XTENSA_VER:" $XTENSA_VER
	echo "XTENSA_SYSTEM:" $XTENSA_SYSTEM
	echo "==="

	#
	local core=$1"1a"
	local target=$2
	#CORES="dmx1a hmd1a"
	echo target: [$target]
  if [[ "$target" =~ test ]]; then
    BUILD_TYPE=release_with_logs
    RTS=0
  else
    BUILD_TYPE=release
    RTS=1
  fi
	#for core in $CORES;
	#do 
	cd ../
	#
	echo build CORE $core type: $BUILD_TYPE
	if [ "$target" == "clean" ]; then
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=ia8201 TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=ia8201 clean
	 #make -f tensorflow/lite/micro/tools/make/Makefile TARGET=ia8201 TARGET_ARCH=$core BUILD_TYPE=release OPTIMIZED_KERNEL_DIR=ia8201 clean
	elif [ "$target" == "test" ]; then
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=ia8201 TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=ia8201 -k test
	 #make -f tensorflow/lite/micro/tools/make/Makefile TARGET=ia8201 TARGET_ARCH=$core BUILD_TYPE=release_with_logs OPTIMIZED_KERNEL_DIR=ia8201 test -j3
	elif [ "$target" == "install" ]; then
#	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=ia8201 TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=ia8201 RM_TFLM_SIGNAL=1 -j4 install
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=ia8201 TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=ia8201 -j4 install
	elif [ "$target" == "dinstall" ]; then
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=ia8201 TARGET_ARCH=$core BUILD_TYPE=debug OPTIMIZED_KERNEL_DIR=ia8201 RM_TFLM_SIGNAL=1 -j4 install
	else
	 #make -f tensorflow/lite/micro/tools/make/Makefile TARGET=ia8201 TARGET_ARCH=$core BUILD_TYPE=release OPTIMIZED_KERNEL_DIR=ia8201 -j3  $target
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=ia8201 TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=ia8201 $target 
	fi
	cd -
	#done
}
build_hml()
{
  
  export XTENSA_CORE=hemilite_shapiro_RI04
	#
	echo "==="
	echo "XTENSA_CORE:" $XTENSA_CORE
	echo "XTENSA_VER:" $XTENSA_VER
	echo "XTENSA_SYSTEM:" $XTENSA_SYSTEM
	echo "==="
  TG=ia700
	#
  core=hml
	local target=$1
	  if [[ "$target" =~ test ]]; then
    BUILD_TYPE=release_with_logs
    RTS=0
  else
    BUILD_TYPE=release
    RTS=1
  fi
  echo BUILD: $BUILD_TYPE
	cd ../
	#
	echo build CORE $core
	if [ "$target" == "clean" ]; then
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=$TG clean
	 #make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=$TG clean
	elif [ "$target" == "test" ]; then
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=$TG -k
	 #make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=$TG test -j3
	elif [ "$target" == "install" ]; then
	 #make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=$TG RM_TFLM_SIGNAL=1 -j4 install
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=$TG RM_TFLM_SIGNAL=0 -j4 install
	elif [ "$target" == "dinstall" ]; then
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=debug OPTIMIZED_KERNEL_DIR=$TG RM_TFLM_SIGNAL=1 -j4 install
	elif [ "$target" == "rro_install" ]; then
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=$TG RM_TFLM_SIGNAL=1 -j4 install
	else
	 #make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=release OPTIMIZED_KERNEL_DIR=$TG -j3  $target
	 make -f tensorflow/lite/micro/tools/make/Makefile TARGET=$TG TARGET_ARCH=$core BUILD_TYPE=$BUILD_TYPE OPTIMIZED_KERNEL_DIR=$TG $target 
	fi
	cd -
	#done
}


build_hifi3_hmd1a()
{
  source $ROME_SDK_ROOT/Src/Cores/Core_Hmd1a/CommonMake/setEnvVariables.sh
  local target=$1
  #regexp='^test[0-9a-z_]+$'
  echo target: [$target]
  if [[ "$target" =~ test ]]; then
    BUILD_TYPE=release_with_logs
    RTS=0
    TM=1
  else
  ## kernel_hack mode, replacing svdf/fc
    BUILD_TYPE=release
    RTS=1
    TM=0
  fi
  echo BUILD: $BUILD_TYPE
	cd ../
	echo make -f tensorflow/lite/micro/tools/make/Makefile TARGET=xtensa OPTIMIZED_KERNEL_DIR=xtensa TARGET_ARCH=hifi3 \
  XTENSA_TOOLS_VERSION=$XTENSA_VER XTENSA_CORE=hmd1aRI04 XTENSA_BASE=${XTENSA_SYSTEM_BASE%tools} BUILD_TYPE=$BUILD_TYPE RM_TFLM_SIGNAL=$RTS TEST_MODE=$TM $target

	make -f tensorflow/lite/micro/tools/make/Makefile TARGET=xtensa OPTIMIZED_KERNEL_DIR=xtensa TARGET_ARCH=hifi3 \
  XTENSA_TOOLS_VERSION=$XTENSA_VER XTENSA_CORE=hmd1aRI04 XTENSA_BASE=${XTENSA_SYSTEM_BASE%tools} BUILD_TYPE=$BUILD_TYPE RM_TFLM_SIGNAL=$RTS TEST_MODE=$TM $target
	cd -
}

case "$1" in
	hml)
	build_hml $2
	;;
	dmx|hmd)
	build_dmx_hmd $1 $2
	;;
	hifi)
	build_hifi3_hmd1a $2
	;;
	*)
	echo "unknown target $1"
	;;
  esac 
