# Model Benchmark — Build and Run Guide

## Overview

`model_benchmark` is a command-line tool that loads one or more `.tflite` models, runs inference, and reports:

- Cycle counts per model (on Xtensa targets via `XT_RSR_CCOUNT`)
- Per-operator profiler ticks (CSV and MAC count)
- Tensor arena size required (with a 5 % guard margin)
- Output tensor values (optional)

The release package ships prebuilt libraries and benchmark sources for two ia8201 cores:

| Core | Directory | Xtensa core name | Chip macro |
|------|-----------|-----------------|------------|
| DeltaMax | `dmx1a/` | `dmx1aRI04` | `-DDMX1A -DAVL_DMX1A` |
| HemiDelta | `hmd1a/` | `hmd1aRI04` | `-DHMD1A -DAVL_HEMI` |

---

## Release Package Layout

```
release_out/
├── dmx1a/
│   ├── lib/
│   │   └── xccTFLuLib.a          # TFLite Micro static library (xt-clang++)
│   ├── include/                  # All TFLu public headers
│   │   ├── tensorflow/lite/...
│   │   └── FrontEnd/...
│   └── model_benchmark/
│       └── model_benchmark.cc    # Main benchmark application
└── hmd1a/                        # Same layout for HemiDelta
    ├── lib/xccTFLuLib.a
    ├── include/
    └── model_benchmark/
```

---

## Prerequisites

| Requirement | Details |
|-------------|---------|
| Xtensa toolchain | `RI-2020.4` (Linux or Win32) |
| Xtensa core config | `dmx1aRI04` or `hmd1aRI04` |
| ia8201 SDK | Available under `third_party/ia8201_sdk/Rome` in the repo |
| Host OS | Linux (preferred) or Cygwin/Windows |

### Set Up the Xtensa Environment (Linux)

```bash
export XTENSA_VER=RI-2020.4-linux
export XTENSA_BASE="${HOME}/xtensa/XtDevTools/install/tools"
export XTENSA_SYSTEM="${XTENSA_BASE}/${XTENSA_VER}/XtensaTools/config"
export PATH="${XTENSA_BASE}/${XTENSA_VER}/XtensaTools/bin:${PATH}"
```

On **Cygwin / Windows**, replace the paths with the corresponding `C:\usr\xtensa\...` equivalents and use `cygpath -m` where needed.

---

## Building model_benchmark

### Recommended: Use the Provided Makefile

Create a `Makefile` inside the target core directory (e.g., `dmx1a/`) or in a separate build directory that points to the release package. A template is shown below.

#### `Makefile` (for `dmx1a`)

```makefile
# ------------------------------------------------------------
# model_benchmark Makefile for dmx1a (DeltaMax / ia8201)
# ------------------------------------------------------------
# Prerequisites:
#   export XTENSA_VER=RI-2020.4-linux
#   export XTENSA_BASE=${HOME}/xtensa/XtDevTools/install/tools
#   export PATH=${XTENSA_BASE}/${XTENSA_VER}/XtensaTools/bin:${PATH}
# Usage:
#   make                        # build
#   make CORE=hmd1a             # build for HemiDelta instead
#   make clean
# ------------------------------------------------------------

CORE      ?= dmx1a
RELEASE   := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# ---- Toolchain -------------------------------------------
XTENSA_VER    ?= RI-2020.4-linux
XTENSA_BASE   ?= $(HOME)/xtensa/XtDevTools/install/tools
XTENSA_SYSTEM := $(XTENSA_BASE)/$(XTENSA_VER)/XtensaTools/config

ifeq ($(CORE),dmx1a)
  XTENSA_CORE := dmx1aRI04
  CHIP_FLAGS  := -DDMX1A -DAVL_DMX1A -DIA8201
else ifeq ($(CORE),hmd1a)
  XTENSA_CORE := hmd1aRI04
  CHIP_FLAGS  := -DHMD1A -DAVL_HEMI -DIA8201
else
  $(error CORE must be dmx1a or hmd1a)
endif

XTENSA_FLAGS := \
  --xtensa-system=$(XTENSA_SYSTEM) \
  --xtensa-core=$(XTENSA_CORE) \
  --xtensa-params=

CXX := xt-clang++
CC  := xt-clang

# ---- Paths -----------------------------------------------
CORE_DIR  := $(RELEASE)$(CORE)
INC_DIR   := $(CORE_DIR)/include
LIB_DIR   := $(CORE_DIR)/lib
BM_DIR    := $(CORE_DIR)/model_benchmark

# ---- Flags -----------------------------------------------
CXXFLAGS := \
  $(XTENSA_FLAGS) \
  $(CHIP_FLAGS) \
  -std=c++17 \
  -O2 \
  -mcoproc \
  -mtext-section-literals \
  -mlongcalls \
  -fno-exceptions \
  -fno-strict-aliasing \
  -fsigned-char \
  -INLINE:requested \
  -DTF_LITE_MCU_DEBUG_LOG \
  -I$(INC_DIR) \
  -I$(BM_DIR) \
  --stdlib=libc++

LDFLAGS := \
  $(XTENSA_FLAGS) \
  --stdlib=libc++ \
  -L$(LIB_DIR) \
  -lxccTFLuLib \
  -lc -lm

# ---- Sources / Objects ------------------------------------
SRCS := $(BM_DIR)/model_benchmark.cc

OBJS := $(patsubst $(BM_DIR)/%.cc, build_$(CORE)/%.o, $(SRCS))

TARGET_BIN := build_$(CORE)/model_benchmark

# ---- Rules ------------------------------------------------
.PHONY: all clean

all: $(TARGET_BIN)

build_$(CORE)/%.o: $(BM_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET_BIN): $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@
	@echo "Built: $@"

clean:
	rm -rf build_$(CORE)
```

> **Note for HemiDelta:** pass `CORE=hmd1a` on the make command line; all paths and macros are updated automatically.

#### Build Commands

```bash
# Build for DeltaMax (dmx1a) – default
make

# Build for HemiDelta (hmd1a)
make CORE=hmd1a

# Build both
make && make CORE=hmd1a

# Clean
make clean
make CORE=hmd1a clean
```

The binary is placed at `build_<core>/model_benchmark`.

---

## Running model_benchmark

### Usage

```
model_benchmark <model1.tflite> [model2.tflite ...] [options]
```

| Option | Description |
|--------|-------------|
| `<model.tflite>` | One or more `.tflite` model files (max 8) |
| `-npy <file.npy>` | NumPy input file for the corresponding input tensor. Repeat for multiple inputs: `-npy feat.npy -npy state.npy` |
| `-v` | Verbose — dump output tensor values and model-size macros for RAF plugin |
| `-t` | Test tensor arena allocation (verify the reported arena size is sufficient) |
| `-str` | Stream mode — treat the `.npy` file as a frame-by-frame stream and iterate |

### Examples

**Run a single model with random inputs:**
```bash
./build_dmx1a/model_benchmark my_model.tflite
```

**Run with a NumPy input file:**
```bash
./build_dmx1a/model_benchmark my_model.tflite -npy input_feat.npy
```

**Run with verbose output (dumps output tensors and arena-size macros):**
```bash
./build_dmx1a/model_benchmark my_model.tflite -npy input_feat.npy -v
```

**Load two models into a shared arena:**
```bash
./build_dmx1a/model_benchmark model1.tflite model2.tflite
```

**Stream mode (stateful/RNN models):**
```bash
./build_dmx1a/model_benchmark rnn_model.tflite -npy stream_input.npy -str
```

**Arena test — verify reported arena size is sufficient:**
```bash
./build_dmx1a/model_benchmark my_model.tflite -t
```

---

## Understanding the Output

```
INPUT MODEL [my_model.tflite] tflite model size = 123456 bytes
iteration: 1
invoke iteration:        0
output[  0] = size: 128, type: INT8
...
[csv profiler output per operator]
arena:     204800          ← recommended tensor arena size (bytes, +5% guard)
cycle:    1234567          ← total Xtensa cycle count
```

### Verbose Mode (`-v`) — Copy-Ready Arena Macros

When `-v` is used the tool also prints constants you can paste directly into the RAF plugin configuration:

```c
static const uint32_t INTERPRETER_MAX_MODEL_SIZE[1] = {
 123456  // my_model.tflite
};
#define INTERPRETER_MAX_MODEL_SIZE_TOTAL 123456 //(with 3% extra guard)
```

---

## Building the Release Package from Source

To rebuild `xccTFLuLib.a` and regenerate the release package from the repository:

```bash
cd /path/to/tflite-micro
./build/release_xtensa.sh [optional_output_dir]
```

This script:
1. Builds TFLite Micro for both `dmx1a` and `hmd1a` targets using the main `Makefile`.
2. Installs the library into the ia8201 SDK tree.
3. Copies `xccTFLuLib.a`, all public headers, and the `model_benchmark` sources into the `release_out/` directory.

---

## Troubleshooting

| Symptom | Likely Cause | Fix |
|---------|-------------|-----|
| `xt-clang++: command not found` | Xtensa tools not on `PATH` | Set `PATH` to include the Xtensa `bin/` directory |
| `--xtensa-core=... not found` | Wrong `XTENSA_SYSTEM` path | Verify `XTENSA_SYSTEM` points to the `config/` directory of the correct toolchain version |
| `cannot allocate tensor successfully` | Tensor arena too small (hard-coded at 2 MB) | Increase `kKeywordModelTensorArenaSize` in `model_benchmark.cc` |
| `NPY SIZE error!` | NPY header offset mismatch | Check `NPY_HEADER_OFFSET` (default `0x80`); regenerate the NumPy file with standard `np.save()` |
| Linker errors (`undefined reference`) | Missing `-lxccTFLuLib` or wrong `LIB_DIR` | Confirm `LIB_DIR` points to the correct `lib/` folder for the chosen core |
