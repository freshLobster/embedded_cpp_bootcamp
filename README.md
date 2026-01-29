I used GPT5.1-Codex-Max to create this rigorous course in advanced C++ for embedded scenarios. I hope it serves you well. 
Contributions and edits are welcome and encouraged. I would love to have collaborators on these training courses. I will be actively maintaining and updating this repo. If you find 
any errors or bugs or anything else, please feel free to email me at <aidanseine@gmail.com> 

The full training course is laid out in **[COURSE](COURSE.md)**

with additional notes in **[STYLE](STYLE.md)**


# platform_core_training

Hands-on modern C++20 training repo for autonomy/robotics platform engineers. Develop on Windows with WSL2 Ubuntu; deploy to Linux SBCs and selected MCUs. CUDA path optional.

## Quickstart (WSL2 Ubuntu)
- Install deps: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional perf tooling: `sudo apt-get install -y linux-tools-common linux-tools-generic`
- Optional heap profiling: `sudo apt-get install -y heaptrack valgrind`
- Optional QEMU (sim): `sudo apt-get install -y qemu-system-aarch64 qemu-user-static`
- Optional CUDA (WSL): `sudo apt-get install -y nvidia-cuda-toolkit` then verify `nvidia-smi` and `nvcc --version`.
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
- `modules/` self-contained training modules (see below)
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

## Modules
- Each module lives under `modules/NN_name/` and is self-contained with README, exercises, checklists, starter snippets, artifacts folder, troubleshooting, and references.
- To run a module:
  1) Open its `README.md` for setup and exercise table.
  2) Follow the exercise markdowns in `modules/NN_name/exercises/`.
  3) Use repo tooling only (`cmake --preset dev/release/...`, scripts in `scripts/`); do not rely on COURSE.md.
  4) Save logs/outputs to `modules/NN_name/artifacts/` with the naming conventions listed there.
- Full index: `docs/modules_index.md` (links to every module README).
- Grade a module: `python3 tools/grader/grade.py --module modules/01_foundations` or grade all with `--all`; add `--json` for machine-readable results.
- Per-exercise work lives under `modules/NN_name/exercises/exXX_slug/` with its own `learner/`, `solution/`, and `grading/`.
