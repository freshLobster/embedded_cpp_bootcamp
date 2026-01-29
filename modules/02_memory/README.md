# Module 02_memory - Memory

**Mission:** Allocators, bounded memory, UAF fix.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional (heap profiling): `sudo apt-get install -y heaptrack valgrind`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.

## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_pmr_queue | [ex01_pmr_queue](exercises/ex01_pmr_queue/README.md) |
| ex02_uaf_fix | [ex02_uaf_fix](exercises/ex02_uaf_fix/README.md) |
| ex03_heaptrack | [ex03_heaptrack](exercises/ex03_heaptrack/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/02_memory/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/02_memory`
- JSON: `python3 tools/grader/grade.py --module 02 --json`
- Per-exercise grading is done inside each exercise folder README.
