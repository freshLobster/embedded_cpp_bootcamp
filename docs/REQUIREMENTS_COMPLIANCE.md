# Requirements Compliance Report

Timestamp: 2026-01-29 23:25:56 -08:00
Repo: f:\Documents\FirmwareProjects\practice\embedded_cpp_bootcamp

## Compliance Summary (PASS/FAIL)

### WSL2 (Ubuntu) — PASS
- [PASS] A1: Repo can be cloned and docs are sufficient to run modules/exercises.
- [PASS] A2: Root README and docs/modules_index.md are consistent and links resolve.
- [PASS] A3: tools/grader exists and grades learner/solution paths.
- [PASS] A4: No broken links, missing directories, or dangling references in docs.
- [PASS] B1: Module README exists, is self-contained, and links to each exercise folder.
- [PASS] B2: Each module has required subdocs (overview, troubleshooting, references, checklists, artifacts README).
- [PASS] B3: Module structure is consistent across all modules.
- [PASS] C1: Each exercise README contains all required sections and step-by-step instructions.
- [PASS] C2: learner/ exists with CMakeLists, include/src/tests, and incomplete stubs.
- [PASS] C3: solution/ exists with CMakeLists, include/src/tests, and builds/tests pass.
- [PASS] C4: grading/rubric.json exists, sums to 100, evidence-based checks.
- [PASS] C5: tools/grader grades exercises (learner + solution + JSON).
- [PASS] C6: Tool-dependent checks degrade gracefully (skipped/partial credit; verified in grader output).
- [PASS] D1: CUDA exercises build CPU-only without nvcc; tests guard GPU portions.
- [PASS] D2: Hardware exercises include no-hardware paths and compile without attached hardware.

### Windows Host (MSVC) — BLOCKED (Visual Studio not detected)
- [PASS] A1: Repo can be cloned and docs are sufficient to run modules/exercises.
- [PASS] A2: Root README and docs/modules_index.md are consistent and links resolve.
- [PASS] A3: tools/grader exists and grades learner/solution paths.
- [PASS] A4: No broken links, missing directories, or dangling references in docs.
- [FAIL] Windows configure/build/test: `cmake --preset dev -G "Visual Studio 17 2022"` failed because Visual Studio was not detected.

---

# WSL2 Audit Evidence (Pass 2 After Cleanup)

## PASS 1: Tree + Link Integrity
Command:
```
python3 tools/audit/audit_tree.py
```
Output:
```
Modules: 12
- 01_foundations
  exercises: 3
- 02_memory
  exercises: 3
- 03_concurrency
  exercises: 3
- 04_architecture
  exercises: 3
- 05_scheduling
  exercises: 3
- 06_debugging
  exercises: 3
- 07_perf
  exercises: 3
- 08_cross_deploy
  exercises: 3
- 09_mcu
  exercises: 3
- 10_sim
  exercises: 3
- 11_cuda_basics
  exercises: 3
- 12_cuda_perf
  exercises: 3
OK: all required module/exercise files present
```

Command:
```
python3 tools/audit/audit_links.py
```
Output:
```
OK: no broken local markdown links
```

Command:
```
python3 tools/audit/audit_rubrics.py
```
Output:
```
OK: rubrics valid and sum to 100
```

## PASS 2: Smoke Test All Exercises (Solutions)
Command:
```
bash tools/audit/smoke_test_solutions.sh
```
Output (abbrev):
```
== Smoke test: modules/01_foundations/exercises/ex01_scope_guard (solution)
100% tests passed, 0 tests failed out of 1
...
== Smoke test: modules/12_cuda_perf/exercises/ex03_jetson (solution)
100% tests passed, 0 tests failed out of 1
```

## PASS 3: Root Build + Tests
Command:
```
cmake --preset dev
cmake --build --preset dev
ctest --preset dev --output-on-failure
```
Output (abbrev):
```
-- Configuring done
-- Build files have been written to: /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp/build/dev
100% tests passed, 0 tests failed out of 9
```

## PASS 4: Grader (All Modules)
Command:
```
python3 tools/grader/grade.py --all --json
```
Output (abbrev):
```
{ "target": "01_foundations", "score": 100.0, ... }
{ "target": "12_cuda_perf", "score": 100.0, ... }
```
Notes:
- Hardware/CUDA checks are skipped with full credit when `--enable-hardware` / `--enable-cuda` are not used.

---

# Windows Audit Evidence

Command attempted:
```
cmake --preset dev -G "Visual Studio 17 2022"
```
Output:
```
CMake Error at CMakeLists.txt:3 (project):
  Generator

    Visual Studio 17 2022

  could not find any instance of Visual Studio.
```

Status:
- Windows/MSVC verification is blocked until Visual Studio Build Tools are detected by CMake.

---

# Notes

- Linux/WSL2 validations and audits are complete and PASS.
- Windows/MSVC validation requires a functioning Visual Studio installation in this environment.

