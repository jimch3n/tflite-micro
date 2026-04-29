#!/bin/bash
# -------------------------------------------------------------
# Build release libs for dmx1a and hmd1a (xtensa/ia8201),
# then package lib, headers, and model_benchmark test app
# into a destination release folder.
#
# Usage:
#   ./release_xtensa.sh [dest_folder]
#
# If dest_folder is not provided, defaults to ./release_out
# -------------------------------------------------------------

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

DEST="${1:-$SCRIPT_DIR/release_out}"

IA8201_SDK_ROOT="$REPO_ROOT/third_party/ia8201_sdk/Rome"

# ---- Xtensa toolchain setup --------------------------------
if [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
  export XTENSA_VER=RI-2020.4-linux
  export XTENSA_SYSTEM_BASE="${HOME}/xtensa/XtDevTools/install/tools"
  export XTENSA_SYSTEM="$XTENSA_SYSTEM_BASE/$XTENSA_VER/XtensaTools/config"
elif [ "$(expr substr $(uname -s) 1 6)" == "CYGWIN" ]; then
  set -o igncr
  export XTENSA_VER=RI-2020.4-win32
  export PATH=/cygdrive/c/usr/xtensa/Xplorer-8.0.13:/cygdrive/c/usr/xtensa/XtDevTools/install/tools/$XTENSA_VER/XtensaTools/bin:$PATH
  export XTENSA_SYSTEM_BASE=$(cygpath -m /cygdrive/c/usr/xtensa/XtDevTools/install/tools)
  export XTENSA_SYSTEM="$XTENSA_SYSTEM_BASE/$XTENSA_VER/XtensaTools/config"
else
  echo "Unsupported OS: $(uname -s)"
  exit 1
fi

# ---- Build ia8201 (dmx1a or hmd1a) and install lib ----------
build_and_install()
{
  local chip="$1"   # dmx or hmd
  local core="${chip}1a"
  local xcore="${core}RI04"

  export XTENSA_CORE="$xcore"

  echo "============================================"
  echo " Building $core  (XTENSA_CORE=$xcore)"
  echo "============================================"

  cd "$REPO_ROOT"
  make -f tensorflow/lite/micro/tools/make/Makefile \
       TARGET=ia8201 \
       TARGET_ARCH="$core" \
       BUILD_TYPE=release \
       OPTIMIZED_KERNEL_DIR=ia8201 \
       -j"$(nproc 2>/dev/null || echo 4)"

  make -f tensorflow/lite/micro/tools/make/Makefile \
       TARGET=ia8201 \
       TARGET_ARCH="$core" \
       BUILD_TYPE=release \
       OPTIMIZED_KERNEL_DIR=ia8201 \
       install
  cd "$SCRIPT_DIR"
}

# ---- Package: lib + headers + model_benchmark ---------------
package_core()
{
  local chip="$1"   # dmx or hmd
  local core="${chip}1a"

  # Capitalise first letter for SDK path component (Dmx1a / Hmd1a)
  local CORE="$(tr '[:lower:]' '[:upper:]' <<< "${core:0:1}")${core:1}"

  local SDK_CORE="$IA8201_SDK_ROOT/Src/Cores/Core_${CORE}"
  local LIB_SRC="$SDK_CORE/TFLu/Libs/xccTFLuLib.a"
  local INC_SRC="$SDK_CORE/TFLu/Include"

  # model_benchmark sources: Dmx1a uses lowercase 'tools', Hmd1a uses 'Tools'
  local BM_SRC
  if [ -d "$SDK_CORE/TFLu/tools/model_benchmark" ]; then
    BM_SRC="$SDK_CORE/TFLu/tools/model_benchmark"
  else
    BM_SRC="$SDK_CORE/TFLu/Tools/model_benchmark"
  fi

  local TOOL_SRC
  if [ -d "$SDK_CORE/TFLu/tools" ]; then
    TOOL_SRC="$SDK_CORE/TFLu/tools"
  else
    TOOL_SRC="$SDK_CORE/TFLu/Tools"
  fi

  local DEST_CORE="$DEST/$core"

  echo "--------------------------------------------"
  echo " Packaging $core -> $DEST_CORE"
  echo "--------------------------------------------"

  # lib
  mkdir -p "$DEST_CORE/lib"
  cp -f "$LIB_SRC" "$DEST_CORE/lib/xccTFLuLib.a"
  echo "  [lib] xccTFLuLib.a"

  # headers (preserve sub-tree)
  mkdir -p "$DEST_CORE/include"
  cp -rf "$INC_SRC/." "$DEST_CORE/include/"
  echo "  [include] $(find "$DEST_CORE/include" -name '*.h' | wc -l) header files"

  # model_benchmark test app sources
  mkdir -p "$DEST_CORE/model_benchmark"
  for f in model_benchmark.cc; do
    if [ -f "$BM_SRC/$f" ]; then
      cp -f "$BM_SRC/$f" "$DEST_CORE/model_benchmark/"
      echo "  [model_benchmark] $f"
    fi
  done

  # converter support files
  mkdir -p "$DEST_CORE/tools"
  for f in kn_tflite_converter.py schema_py_generated.py; do
    if [ -f "$TOOL_SRC/$f" ]; then
      cp -f "$TOOL_SRC/$f" "$DEST_CORE/tools/"
      echo "  [tools] $f"
    fi
  done

  if [ -f "$TOOL_SRC/kut.dll" ]; then
    cp -f "$TOOL_SRC/kut.dll" "$DEST_CORE/tools/kut.dll"
    echo "  [tools] kut.dll"
  fi
}

package_release_support()
{
  mkdir -p "$DEST"
  if [ -f "$SCRIPT_DIR/release_out/README.md" ] && [ "$DEST/README.md" != "$SCRIPT_DIR/release_out/README.md" ]; then
    cp -f "$SCRIPT_DIR/release_out/README.md" "$DEST/README.md"
    echo "  [release] README.md"
  fi
  cp -f "$SCRIPT_DIR/kn_tflite_converter.sh" "$DEST/kn_tflite_converter.sh"
  cp -f "$SCRIPT_DIR/package_release_tarball.sh" "$DEST/package_release_tarball.sh"
  cp -f "$SCRIPT_DIR/model_benchmark.Makefile" "$DEST/Makefile"
  cp -f "$SCRIPT_DIR/model_benchmark_ref.py" "$DEST/model_benchmark_ref.py"
  cp -f "$SCRIPT_DIR/verify_release_flow.py" "$DEST/verify_release_flow.py"
  chmod +x "$DEST/kn_tflite_converter.sh"
  chmod +x "$DEST/package_release_tarball.sh"
  echo "  [release] kn_tflite_converter.sh"
  echo "  [release] package_release_tarball.sh"
  echo "  [release] Makefile"
  echo "  [release] model_benchmark_ref.py"
  echo "  [release] verify_release_flow.py"
}

package_standalone_build_support()
{
  local DEST_SDK_CORES="$DEST/third_party/ia8201_sdk/Rome/Src/Cores"
  local DEST_SRC_ROOT="$DEST/src/tensorflow/lite/micro"

  mkdir -p "$DEST_SDK_CORES"
  cp -rf "$IA8201_SDK_ROOT/Src/Cores/AVL" "$DEST_SDK_CORES/AVL"
  mkdir -p "$DEST_SDK_CORES/Core_Dmx1a"
  mkdir -p "$DEST_SDK_CORES/Core_Hmd1a"
  cp -rf "$IA8201_SDK_ROOT/Src/Cores/Core_Dmx1a/Include" "$DEST_SDK_CORES/Core_Dmx1a/Include"
  cp -rf "$IA8201_SDK_ROOT/Src/Cores/Core_Hmd1a/Include" "$DEST_SDK_CORES/Core_Hmd1a/Include"
  echo "  [release] standalone SDK headers"

  mkdir -p "$DEST_SRC_ROOT/ia8201"
  cp -f "$REPO_ROOT/tensorflow/lite/micro/micro_log.cc" "$DEST_SRC_ROOT/micro_log.cc"
  cp -f "$REPO_ROOT/tensorflow/lite/micro/ia8201/debug_log.cc" "$DEST_SRC_ROOT/ia8201/debug_log.cc"
  echo "  [release] standalone build sources"
}

package_example_models()
{
  mkdir -p "$DEST/examples/hello_world"
  mkdir -p "$DEST/examples/micro_speech"
  mkdir -p "$DEST/examples/lstm"

  cp -f "$REPO_ROOT/tensorflow/lite/micro/examples/hello_world/models/hello_world_float.tflite" \
    "$DEST/examples/hello_world/hello_world_float.tflite"
  cp -f "$REPO_ROOT/tensorflow/lite/micro/examples/hello_world/models/hello_world_int8.tflite" \
    "$DEST/examples/hello_world/hello_world_int8.tflite"

  cp -f "$REPO_ROOT/tensorflow/lite/micro/examples/micro_speech/models/micro_speech_quantized.tflite" \
    "$DEST/examples/micro_speech/micro_speech_quantized.tflite"

  cp -f "$REPO_ROOT/tensorflow/lite/micro/examples/mnist_lstm/trained_lstm.tflite" \
    "$DEST/examples/lstm/trained_lstm.tflite"
  cp -f "$REPO_ROOT/tensorflow/lite/micro/examples/mnist_lstm/trained_lstm_int8.tflite" \
    "$DEST/examples/lstm/trained_lstm_int8.tflite"
  cp -f "$REPO_ROOT/third_party/xtensa/examples/micro_speech_lstm/micro_speech_lstm.tflite" \
    "$DEST/examples/lstm/micro_speech_lstm.tflite"
  cp -f "$REPO_ROOT/third_party/xtensa/examples/micro_speech_lstm/kn_dmx1a_micro_speech_lstm.tflite" \
    "$DEST/examples/lstm/kn_dmx1a_micro_speech_lstm.tflite"
  cp -f "$REPO_ROOT/third_party/xtensa/examples/micro_speech_lstm/kn_hmd1a_micro_speech_lstm.tflite" \
    "$DEST/examples/lstm/kn_hmd1a_micro_speech_lstm.tflite"

  echo "  [examples] hello_world_float.tflite"
  echo "  [examples] hello_world_int8.tflite"
  echo "  [examples] micro_speech_quantized.tflite"
  echo "  [examples] trained_lstm.tflite"
  echo "  [examples] trained_lstm_int8.tflite"
  echo "  [examples] micro_speech_lstm.tflite"
  echo "  [examples] kn_dmx1a_micro_speech_lstm.tflite"
  echo "  [examples] kn_hmd1a_micro_speech_lstm.tflite"
}

# ---- Main ---------------------------------------------------
echo ""
echo "Destination: $DEST"
echo ""

build_and_install dmx
build_and_install hmd

package_core dmx
package_core hmd
package_release_support
package_standalone_build_support
package_example_models

echo ""
echo "============================================"
echo " Release package ready: $DEST"
echo " tools:"
echo "   kn_tflite_converter.sh"
echo "   package_release_tarball.sh"
echo "   Makefile"
echo "   model_benchmark_ref.py"
echo "   verify_release_flow.py"
echo "   src/tensorflow/lite/micro/..."
echo "   third_party/ia8201_sdk/Rome/Src/Cores/..."
echo " examples/"
echo "   hello_world/"
echo "   micro_speech/"
echo "   lstm/"
echo " dmx1a/"
echo "   lib/xccTFLuLib.a"
echo "   include/  (TFLu headers)"
echo "   model_benchmark/  (model_benchmark.cc)"
echo "   tools/  (kn_tflite_converter.py, schema_py_generated.py, kut.dll)"
echo " hmd1a/"
echo "   lib/xccTFLuLib.a"
echo "   include/  (TFLu headers)"
echo "   model_benchmark/  (model_benchmark.cc)"
echo "   tools/  (kn_tflite_converter.py, schema_py_generated.py, kut.dll)"
echo "============================================"
