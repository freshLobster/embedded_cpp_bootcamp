# Module 08_cross_deploy - Cross & Deploy

**Mission:** aarch64 cross, SBC deploy, systemd, remote checks.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.

## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_cross_build | [ex01_cross_build](exercises/ex01_cross_build/README.md) |
| ex02_deploy | [ex02_deploy](exercises/ex02_deploy/README.md) |
| ex03_latency_on_hw | [ex03_latency_on_hw](exercises/ex03_latency_on_hw/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/08_cross_deploy/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/08_cross_deploy`
- JSON: `python3 tools/grader/grade.py --module 08 --json`
- Per-exercise grading is done inside each exercise folder README.
- Hardware checks require `--enable-hardware` to score full points.
