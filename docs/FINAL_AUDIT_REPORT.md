# Final Audit Report

Timestamp: 2026-01-29 23:25:56 -08:00
Repo: f:\Documents\FirmwareProjects\practice\embedded_cpp_bootcamp

## Orphan / Vestigial Cleanup

Actions performed:
- Removed generated build directories to keep the repo clean after validation runs.
- Removed temporary workspace directory if present.
- Kept required empty placeholders (grading/checks, grading/expected, tools/) that are part of the exercise layout.

| Path | Action | Reason |
| --- | --- | --- |
| `build/` | removed | Generated root build output from validation runs. |
| `modules/*/exercises/*/build_solution` (36 dirs) | removed | Generated per-exercise smoke-test builds. |
| `tools/tmp` | removed | Temporary workspace dir not part of repo structure. |

## WSL2 Verification (Linux) — Pass 2 After Cleanup

Commands executed:
```
cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp
bash tools/audit/smoke_test_solutions.sh
python3 tools/audit/audit_tree.py
python3 tools/audit/audit_links.py
python3 tools/audit/audit_rubrics.py
cmake --preset dev
cmake --build --preset dev
ctest --preset dev --output-on-failure
python3 tools/grader/grade.py --all --json
```

Results (abbrev):
- Smoke tests: all 36 solution exercises configured/built/tested successfully (100% pass for each exercise).
- Audits: `audit_tree.py`, `audit_links.py`, `audit_rubrics.py` all reported OK.
- `cmake --preset dev`: configured successfully (CMake FetchContent CMP0135 warnings only).
- `cmake --build --preset dev`: succeeded and produced `platform_core_app`, `platform_core_tests`, `platform_core_bench`.
- `ctest --preset dev --output-on-failure`: 9/9 tests passed.
- `python3 tools/grader/grade.py --all --json`: all 12 modules scored 100; hardware/CUDA/tool-gated checks skipped as designed when flags/tools absent.

Selected outputs:
```
100% tests passed, 0 tests failed out of 1
```
```
OK: all required module/exercise files present
OK: no broken local markdown links
OK: rubrics valid and sum to 100
```
```
100% tests passed, 0 tests failed out of 9
Total Test time (real) =   0.22 sec
```

Notes on skipped checks (per grader JSON):
- Hardware-gated checks were skipped without penalty because `--enable-hardware` was not used.
- CUDA-gated checks were skipped without penalty because `--enable-cuda` was not used.
- Simulation tool checks (`qemu-aarch64`, `renode`) were skipped if tools are missing.

## Windows/MSVC Verification

Command attempted:
```
cmake --preset dev -G "Visual Studio 17 2022"
```

Result:
- FAIL: `Generator Visual Studio 17 2022 could not find any instance of Visual Studio.`

Notes:
- Windows/MSVC tests could not run in this environment because Visual Studio was not detected.
- WSL2 verification is complete and clean. Windows verification remains blocked until VS Build Tools are available in PATH.

## Grader Confirmation (WSL2)

Command executed:
```
python3 tools/grader/grade.py --all --json
```

Result:
- All modules scored 100. Hardware/CUDA checks were skipped when flags/tools were not enabled.

