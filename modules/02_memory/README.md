
# Module 02_memory – Memory

**Mission:** Allocators, bounded memory, UAF fix for mission-critical robotics/autonomy software. Self-contained; assume only this folder + repo tooling.

**Estimated time:** 2–4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt update && sudo apt install -y build-essential ninja-build cmake clang gdb gdbserver perf python3-pip`
- Verify compiler: `clang++ --version` → expect clang output (any recent 14+). On Windows native: use "x64 Native Tools" and `cl /?` should work.
- Repo root: confirm `CMakePresets.json` exists: `ls CMakePresets.json` → file listed.
- Build dir clean: `rm -rf build/*` (optional) to avoid stale configs.

## Start here
1. Configure debug preset: `cmake --preset dev`
2. Build tests only: `cmake --build --preset dev --target platform_core_tests`
3. Run this module's focused tests (filter): `ctest --preset dev -R Module02_memory` (will pass once you add/enable tests as instructed in exercises).
4. Code lives in repo root paths noted in each exercise; stage work-in-progress artifacts under `modules/02_memory_memory/artifacts/`.

## Exercises
| # | Title | Est. time | Skills | Verification |
|---|-------|-----------|--------|--------------|
| 1 | ex01 | ~45m | core topic | see exercises/ex01_*.md |
| 2 | ex02 | ~45m | core topic | see exercises/ex02_*.md |
| 3 | ex03 | ~45m | core topic | see exercises/ex03_*.md |

## Done definition
- All steps in exercises completed.
- Artifacts saved in `artifacts/` with naming convention.
- `ctest --preset dev` (or module-specific filters) passes.
- Benchmarks/sanitizers (if requested) run and logs saved.
- Checklist files in `checklists/` reviewed and ticked.

## Grade this module
- Run: python3 tools/grader/grade.py --module modules/02_memory
- JSON: python3 tools/grader/grade.py --module 02 --json
- Artifacts expected in modules/02_memory/artifacts/ per exercises.

