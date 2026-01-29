# Module 11_cuda_basics - CUDA Basics

**Mission:** Environment, CPU/GPU parity, RAII CUDA buffer.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional (CUDA toolkit): `sudo apt-get install -y nvidia-cuda-toolkit`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.

## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_env | [ex01_env](exercises/ex01_env/README.md) |
| ex02_cpu_gpu_parity | [ex02_cpu_gpu_parity](exercises/ex02_cpu_gpu_parity/README.md) |
| ex03_raii_buffer | [ex03_raii_buffer](exercises/ex03_raii_buffer/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/11_cuda_basics/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/11_cuda_basics`
- JSON: `python3 tools/grader/grade.py --module 11 --json`
- Per-exercise grading is done inside each exercise folder README.
- CUDA checks require `--enable-cuda` to score full points.
