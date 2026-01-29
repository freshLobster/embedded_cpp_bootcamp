# Module 12_cuda_perf - CUDA Perf

**Mission:** Nsight/CLI profiling, divergence, Jetson awareness.

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
| ex01_nsys | [ex01_nsys](exercises/ex01_nsys/README.md) |
| ex02_divergence | [ex02_divergence](exercises/ex02_divergence/README.md) |
| ex03_jetson | [ex03_jetson](exercises/ex03_jetson/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/12_cuda_perf/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/12_cuda_perf`
- JSON: `python3 tools/grader/grade.py --module 12 --json`
- Per-exercise grading is done inside each exercise folder README.
- CUDA checks require `--enable-cuda` to score full points.
