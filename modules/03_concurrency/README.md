# Module 03_concurrency - Concurrency

**Mission:** Queues, deadlocks, races, clean shutdown.

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
| ex01_race_repro | [ex01_race_repro](exercises/ex01_race_repro/README.md) |
| ex02_deadlock | [ex02_deadlock](exercises/ex02_deadlock/README.md) |
| ex03_clean_shutdown | [ex03_clean_shutdown](exercises/ex03_clean_shutdown/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/03_concurrency/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/03_concurrency`
- JSON: `python3 tools/grader/grade.py --module 03 --json`
- Per-exercise grading is done inside each exercise folder README.
