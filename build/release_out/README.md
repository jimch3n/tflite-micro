# Model Benchmark Release Guide

## Overview

This release folder is meant to be the quickest path to three related tasks:

- build and run the Xtensa `model_benchmark` binary for `dmx1a` or `hmd1a`
- convert a standard `.tflite` model into a Knowles-mapped model with `kn_tflite_converter.sh`
- run a host-side Python reference with `model_benchmark_ref.py` to compare outputs against the Xtensa benchmark

For standard quantized INT8 TensorFlow Lite models, the recommended runtime flow is:

1. run `kn_tflite_converter.sh` first to convert the model into KN format
2. run `model_benchmark` with the converted KN model
3. use the original standard `.tflite` with `model_benchmark_ref.py` for host-side output comparison

The KN conversion pre-permutes coefficients offline, so the runtime does not need to remap them inside the interpreter. This saves tensor arena memory when the model runs on the Xtensa target.

The release supports these cores:

| Core | Release folder | Xtensa core | Compile macros |
|------|----------------|-------------|----------------|
| DeltaMax | `dmx1a/` | `dmx1aRI04` | `-DDMX1A -DAVL_DMX1A -DIA8201` |
| HemiDelta | `hmd1a/` | `hmd1aRI04` | `-DHMD1A -DAVL_HEMI -DIA8201` |

## Layout

```text
release_out/
├── Makefile                    # Build model_benchmark for dmx1a / hmd1a
├── README.md
├── examples/                   # Ready-to-run sample .tflite models
├── kn_tflite_converter.sh      # Wrapper for Knowles TFLite converter
├── model_benchmark_ref.py      # Host-side TFLite reference runner
├── package_release_tarball.sh  # Create a clean .tar.gz without generated logs/objects
├── src/                        # Local build-only source copies used by Makefile
├── third_party/
│   └── ia8201_sdk/Rome/Src/Cores/
│       ├── AVL/
│       ├── Core_Dmx1a/Include/
│       └── Core_Hmd1a/Include/
├── dmx1a/
│   ├── include/
│   ├── lib/
│   │   └── xccTFLuLib.a
│   └── model_benchmark/
│       └── model_benchmark.cc
└── hmd1a/
    ├── include/
    ├── lib/
    │   └── xccTFLuLib.a
    └── model_benchmark/
        └── model_benchmark.cc
```

When you regenerate the release with `build/release_xtensa.sh`, the script also packages per-core converter helper files under `<core>/tools/`.
If those helper files are not present, `kn_tflite_converter.sh` automatically falls back to the SDK tool directories inside the repo checkout.

The root `Makefile` now defaults to the headers and source files bundled inside `release_out/`, so the release can be zipped and built outside the repository tree without any external header dependency.

The release also includes a small curated model bundle under `examples/`:

- `examples/hello_world/hello_world_float.tflite`
- `examples/hello_world/hello_world_int8.tflite`
- `examples/micro_speech/micro_speech_quantized.tflite`
- `examples/lstm/trained_lstm.tflite`
- `examples/lstm/trained_lstm_int8.tflite`
- `examples/lstm/micro_speech_lstm.tflite`
- `examples/lstm/kn_dmx1a_micro_speech_lstm.tflite`
- `examples/lstm/kn_hmd1a_micro_speech_lstm.tflite`

## Prerequisites

| Requirement | Notes |
|-------------|-------|
| Xtensa toolchain | `RI-2020.4-linux` or `RI-2020.4-win32` |
| Python 3 | Needed for `kn_tflite_converter.sh` and `model_benchmark_ref.py` |
| Python packages | `numpy`, `flatbuffers`, and either `tensorflow` or `tflite_runtime` |

### Xtensa environment example

```bash
export XTENSA_VER=RI-2020.4-linux
export XTENSA_SYSTEM_BASE="${HOME}/xtensa/XtDevTools/install/tools"
export XTENSA_SYSTEM="${XTENSA_SYSTEM_BASE}/${XTENSA_VER}/XtensaTools/config"
export PATH="${XTENSA_SYSTEM_BASE}/${XTENSA_VER}/XtensaTools/bin:${PATH}"
```

On Windows, use the corresponding `C:\usr\xtensa\...` installation path in Git Bash or Cygwin.

## Build `model_benchmark`

Use the root `Makefile` in this folder.

### Build examples

```bash
# DeltaMax
make CORE=dmx1a

# HemiDelta
make CORE=hmd1a

# Clean
make clean
```

The output binary is written to:

- `build/dmx1a/model_benchmark`
- `build/hmd1a/model_benchmark`

### Run examples

```bash
# Build and run a single model on dmx1a
make CORE=dmx1a run MODEL=/path/to/model.tflite

# Run with NumPy input and verbose output
make CORE=dmx1a run MODEL=/path/to/model.tflite ARGS='-npy /path/to/input.npy -v'

# Stream mode
make CORE=hmd1a run MODEL=/path/to/stateful_model.tflite ARGS='-npy /path/to/stream.npy -str'
```

### Useful overrides

The root `Makefile` supports these overrides:

- `SDK_CORES_ROOT=/path/to/ia8201_sdk/Rome/Src/Cores`
- `RELEASE_SRC_ROOT=/path/to/local/release/src`
- `AVL_DIR=/path/to/AVL`
- `XTENSA_SYSTEM=/path/to/XtensaTools/config`
- `STRIP_ERROR_STRINGS=0` to keep `MicroPrintf` strings for debugging

These are optional. The packaged defaults already point at the standalone files shipped in `release_out/`.

By default the release `Makefile` enables `TF_LITE_STRIP_ERROR_STRINGS`, which strips TensorFlow Lite Micro error strings and turns `MicroPrintf(...)` into a no-op. This matches the intended smaller release-style build. If you need verbose framework logging while debugging, build with `STRIP_ERROR_STRINGS=0`.

## `model_benchmark` usage

The C benchmark accepts:

```text
model_benchmark <model1.tflite> [model2.tflite ...] [options]
```

| Option | Meaning |
|--------|---------|
| `<model.tflite>` | One or more model files, maximum 8 |
| `-npy <file.npy>` | NumPy file for the corresponding input tensor; repeat for multiple inputs |
| `-v` | Verbose output, including tensor dumps and copy-ready model size macros |
| `-t` | Tensor arena sizing test |
| `-str` | Streaming mode for stateful models |

### Typical examples

```bash
./build/dmx1a/model_benchmark my_model.tflite
./build/dmx1a/model_benchmark my_model.tflite -npy input.npy
./build/dmx1a/model_benchmark my_model.tflite -npy input.npy -v
./build/hmd1a/model_benchmark stateful_model.tflite -npy stream.npy -str
./build/dmx1a/model_benchmark model1.tflite model2.tflite -t
```

### Expected output shape

Typical output looks like:

```text
INPUT MODEL [my_model.tflite]
iteration: 1
invoke iteration:        0
output[  0] = size: 128, type: int8
...
arena:     204800
cycle:    1234567
```

With `-v`, the benchmark also prints copy-ready `INTERPRETER_MAX_MODEL_SIZE` macros for firmware integration.

## Convert a model with `kn_tflite_converter.sh`

The wrapper normalizes the core selection and forwards the remaining arguments to `kn_tflite_converter.py`.

### Recommended INT8 runtime flow

For a standard quantized INT8 model, convert it first and then run the benchmark with the converted KN model:

```bash
# Convert the standard INT8 TFLite model into KN runtime format
./kn_tflite_converter.sh dmx examples/hello_world/hello_world_int8.tflite hello_world_int8_dmx_kn.tflite

# Run the Xtensa benchmark with the KN model
./build/dmx1a/model_benchmark hello_world_int8_dmx_kn.tflite

# Compare against the original standard model on the host
python3 model_benchmark_ref.py examples/hello_world/hello_world_int8.tflite
```

Use the same pattern for `hmd` / `hmd1a`.

`model_benchmark_ref.py` should keep using the original standard `.tflite` model. The converted KN model is intended for target runtime execution, not for loading into the standard host TFLite interpreter.

### Wrapper usage

```text
./kn_tflite_converter.sh <dmx|dmx1a|hmd|hmd1a> <input.tflite> <output.tflite> [converter options...]
```

### Examples

```bash
# Convert for dmx
./kn_tflite_converter.sh dmx model.tflite kn_model.tflite

# Convert for hmd and strip strings
./kn_tflite_converter.sh hmd model.tflite kn_model.tflite -s

# Convert using float16 quantization option
./kn_tflite_converter.sh dmx model.tflite kn_model.tflite -q 1

# Limit mapped ops explicitly
./kn_tflite_converter.sh hmd model.tflite kn_model.tflite -m fc lstm conv ds_conv

# Append CRC32 in the converted output if desired by downstream tooling
./kn_tflite_converter.sh dmx model.tflite kn_model.tflite --crc32
```

### Common forwarded converter flags

| Option | Meaning |
|--------|---------|
| `-s`, `--strip` | Strip strings from the output model |
| `-q`, `--quantize_option` | `1=float16`, `2=8bit_scale` |
| `-m`, `--map_ops` | Choose mapped ops, for example `fc lstm conv ds_conv svdf` |
| `-v`, `--verbose` | Dump more conversion details |
| `--crc32` | Append CRC32 to the output model |

### Wrapper lookup behavior

`kn_tflite_converter.sh` searches in this order:

1. `release_out/<core>/tools/`
2. the repo SDK path under `third_party/ia8201_sdk/Rome/Src/Cores/...`

You can force repo discovery with:

```bash
export KN_TFLITE_CONVERTER_ROOT=/path/to/tflite-micro
```

## Compare against host TFLite with `model_benchmark_ref.py`

`model_benchmark_ref.py` is a host-side reference runner with a CLI intentionally similar to the C benchmark.

### Reference usage

```text
./model_benchmark_ref.py <model1.tflite> [model2.tflite ...] [-npy input.npy] [-v] [-t] [-str]
```

### Examples

```bash
# Single inference
python3 model_benchmark_ref.py my_model.tflite

# Use host-side NumPy input
python3 model_benchmark_ref.py my_model.tflite -npy input.npy

# Verbose comparison run
python3 model_benchmark_ref.py my_model.tflite -npy input.npy -v

# Stateful / stream comparison
python3 model_benchmark_ref.py stateful_model.tflite -npy stream.npy -str
```

### Reference runner notes

- `-t` is accepted for CLI compatibility but ignored on the host runner.
- If the model input is quantized and the `.npy` file is floating-point, the script quantizes the input using the tensor quantization parameters before invoking the interpreter.
- In `-str` mode, output tensors after index 0 are fed back into input tensors after index 0 to emulate simple state-carrying models.
- For KN-converted INT8 runtime models, keep the host reference on the original standard `.tflite` model. The KN model stores remapped coefficients for target execution and is not the reference-runner input format.

## Full flow verification with `verify_release_flow.py`

`verify_release_flow.py` is an end-to-end test driver for the release package. It verifies:

- release assets exist
- `model_benchmark` builds through the release `Makefile`
- standard INT8 models are converted to KN format before benchmark execution
- the Xtensa benchmark runs on the KN runtime model
- the host Python reference runs on the original standard model
- benchmark outputs match the Python reference outputs

### Default verification

By default it checks both cores with the quantized hello-world model, converts it to KN format first, and then compares the Xtensa KN-model run against the original host-side TFLite reference:

```bash
python3 verify_release_flow.py
```

### Useful options

```bash
# Verify only one core
python3 verify_release_flow.py --core dmx1a

# Include extra speech and LSTM examples
python3 verify_release_flow.py --extended

# Skip the KN conversion step and run the raw standard model directly
python3 verify_release_flow.py --skip-converter

# Reuse already-built binaries
python3 verify_release_flow.py --skip-build
```

### Output artifacts

The script writes logs, any generated KN models, and a machine-readable summary to:

- `release_out/verify_flow/`

The default summary file is:

- `release_out/verify_flow/summary.json`

## Regenerate the release package

From the repo root:

```bash
./build/release_xtensa.sh [optional_output_dir]
```

## Create a clean tarball

To package the release folder into a distributable `.tar.gz` while skipping generated build outputs and verification logs:

```bash
./package_release_tarball.sh
```

Optional arguments:

```bash
# Package a specific release folder
./package_release_tarball.sh /path/to/release_out

# Choose the output tarball path
./package_release_tarball.sh ./release_out ./release_out_clean.tar.gz
```

The tarball script excludes generated content such as:

- `build/`
- `verify_flow*`
- `*.o`
- `*.obj`
- `*.log`
- `*.pyc`
- `__pycache__/`

The release script now packages:

- `Makefile`
- `kn_tflite_converter.sh`
- `package_release_tarball.sh`
- `model_benchmark_ref.py`
- `verify_release_flow.py`
- `src/tensorflow/lite/micro/micro_log.cc`
- `src/tensorflow/lite/micro/ia8201/debug_log.cc`
- `third_party/ia8201_sdk/Rome/Src/Cores/AVL/`
- `third_party/ia8201_sdk/Rome/Src/Cores/Core_Dmx1a/Include/`
- `third_party/ia8201_sdk/Rome/Src/Cores/Core_Hmd1a/Include/`
- `dmx1a/model_benchmark/model_benchmark.cc`
- `hmd1a/model_benchmark/model_benchmark.cc`
- per-core converter support files under `<core>/tools/`

## Troubleshooting

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| `xt-clang++: command not found` | Xtensa tools are not on `PATH` | Add the Xtensa `bin` directory to `PATH` |
| `--xtensa-core=... not found` | Wrong `XTENSA_SYSTEM` | Point `XTENSA_SYSTEM` to the toolchain `config/` directory |
| `AVL.h: No such file or directory` | Standalone SDK headers are missing or `AVL_DIR` was overridden incorrectly | Recreate the release package or point `SDK_CORES_ROOT` / `AVL_DIR` to the bundled SDK headers |
| `Cannot find kn_tflite_converter.py` | Wrapper could not locate the SDK tools | Set `KN_TFLITE_CONVERTER_ROOT` or regenerate the release package |
| `TensorFlow or tflite_runtime is required` | Host Python runtime is missing | Install `tensorflow` or `tflite_runtime` plus `numpy` |
| `Input shape mismatch` in `model_benchmark_ref.py` | `.npy` shape does not match the model input | Regenerate the `.npy` file with the model input shape or batch layout |
