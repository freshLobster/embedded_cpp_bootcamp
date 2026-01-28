# platform_core_training

Hands-on modern C++20 training repo for autonomy/robotics platform engineers. Develop on Windows with WSL2 Ubuntu; deploy to Linux SBCs and selected MCUs. CUDA path optional.

## Quickstart (WSL2 Ubuntu)
- Install deps: `sudo apt update && sudo apt install -y build-essential ninja-build cmake git clang gdb gdbserver perf python3-pip libc++-dev libc++abi-dev`
- Optional CUDA (WSL): install NVIDIA drivers + CUDA toolkit per NVIDIA docs, then verify `nvidia-smi` and `nvcc --version`.
- Configure & build: `./scripts/build_debug.sh`
- Run tests: `./scripts/run_tests.sh`
- Run release + benchmark: `./scripts/build_release.sh && ./build/release/platform_core_bench`
- Sanitizers (Linux/WSL): `./scripts/run_sanitizers.sh`

## Cross-compile aarch64 (Raspberry Pi/Orange Pi)
- Install toolchain: `sudo apt install -y gcc-aarch64-linux-gnu g++-aarch64-linux-gnu`
- Build: `./scripts/cross_compile_aarch64.sh`
- Deploy: `./scripts/deploy_to_sbc.sh pi@raspberrypi.local /home/pi/bin`

## Windows native notes
- Install Visual Studio Build Tools (C++ workload) so `kernel32.lib` and friends exist; launch builds from a "x64 Native Tools" prompt or set `CC=cl` `CXX=cl`.
- Use Visual Studio Build Tools or MSVC + Ninja; `cmake --preset dev` works with MSVC generator if Ninja unavailable (`cmake -G "Visual Studio 17 2022"`).
- CUDA on Windows: install CUDA toolkit; build with `cmake --preset cuda`.

## Repo layout
- `src/` platform core library + app
- `include/` public headers
- `tests/` GoogleTest suites
- `benchmarks/` Google Benchmark
- `docs/hardware/` SBC + MCU wiring/bring-up
- `docs/cuda/` CUDA labs and profiling steps
- `scripts/` build/test/deploy helpers

## Failure-mode toggles
Enable one at a time to practice debugging:
- `-DPLATFORM_FAILURE_RACE=ON`
- `-DPLATFORM_FAILURE_DEADLOCK=ON`
- `-DPLATFORM_FAILURE_UAF=ON`
- `-DPLATFORM_FAILURE_PERF=ON`

Example: `cmake --preset dev -DPLATFORM_FAILURE_RACE=ON && cmake --build --preset dev && ctest --preset dev`

## Style / lint
- Enforced via `.clang-format`, `.clang-tidy`, and `STYLE.md`. Warnings are errors in CI-equivalent workflows.
