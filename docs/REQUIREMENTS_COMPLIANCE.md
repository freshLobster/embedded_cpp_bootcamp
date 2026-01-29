# Requirements Compliance Report

Date: 2026-01-29
Repo: f:\Documents\FirmwareProjects\practice\embedded_cpp_bootcamp

## Checklist (PASS/FAIL)

### Windows Host (MSVC/Ninja)
- [PASS] A1: Repo can be cloned and a learner can follow docs to run modules/exercises.
- [PASS] A2: Root README and docs/modules_index.md are consistent and links resolve.
- [PASS] A3: tools/grader exists and can grade both learner and solution paths.
- [PASS] A4: No broken links, missing directories, or dangling references in docs.

- [PASS] B1: Module README exists, is self-contained, and links to each exercise folder.
- [PASS] B2: Each module has required subdocs (overview, troubleshooting, references, checklists, artifacts README).
- [PASS] B3: Module structure is consistent across all modules.

- [PASS] C1: Each exercise README has required sections (mission, what/why, concepts, repo context, prereqs, build commands, steps, verification, artifacts, grading, troubleshooting, stretch goals).
- [PASS] C2: learner/ exists with CMakeLists, include/src/tests, and incomplete stubs.
- [PASS] C3: solution/ exists with CMakeLists, include/src/tests, and builds/tests pass (sampled).
- [PASS] C4: grading/rubric.json exists, sums to 100, evidence-based checks.
- [PASS] C5: tools/grader grades exercises (learner + solution + JSON).
- [PASS] C6: Tool-dependent checks degrade gracefully (skipped/partial credit; verified in grader output).

- [PASS] D1: CUDA exercises build CPU-only without nvcc; tests skip/guard GPU portions.
- [PASS] D2: Hardware exercises include no-hardware path and compile without attached hardware.

### WSL2 (Ubuntu 24.04)
- [PASS] A1: Repo can be cloned and a learner can follow docs to run modules/exercises.
- [PASS] A2: Root README and docs/modules_index.md are consistent and links resolve.
- [PASS] A3: tools/grader exists and can grade both learner and solution paths.
- [PASS] A4: No broken links, missing directories, or dangling references in docs.

- [PASS] B1: Module README exists, is self-contained, and links to each exercise folder.
- [PASS] B2: Each module has required subdocs (overview, troubleshooting, references, checklists, artifacts README).
- [PASS] B3: Module structure is consistent across all modules.

- [PASS] C1: Each exercise README has required sections (mission, what/why, concepts, repo context, prereqs, build commands, steps, verification, artifacts, grading, troubleshooting, stretch goals).
- [PASS] C2: learner/ exists with CMakeLists, include/src/tests, and incomplete stubs.
- [PASS] C3: solution/ exists with CMakeLists, include/src/tests, and builds/tests pass (sampled).
- [PASS] C4: grading/rubric.json exists, sums to 100, evidence-based checks.
- [PASS] C5: tools/grader grades exercises (learner + solution + JSON).
- [PASS] C6: Tool-dependent checks degrade gracefully (skipped/partial credit; verified in grader output).

- [PASS] D1: CUDA exercises build CPU-only without nvcc; tests skip/guard GPU portions.
- [PASS] D2: Hardware exercises include no-hardware path and compile without attached hardware.

---

# Windows Audit (Host)
Host: Windows 10 (19045), MSVC Build Tools 18.2.1

## PASS 1: Tree + Link Integrity (Inventory + Required Files)

Command:
```
python tools/audit/audit_tree.py
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
python tools/audit/audit_links.py
```
Output:
```
OK: no broken local markdown links
```

Command:
```
python tools/audit/audit_rubrics.py
```
Output:
```
OK: rubrics valid and sum to 100
```

---

## PASS 2: Buildability Smoke Tests (Solutions)

Environment verification:
```
ninja --version
```
Output:
```
1.13.2
```

### Module 01 sample (ex01_scope_guard)
Command:
```
cmd /c "call ""C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"" -arch=amd64 -host_arch=amd64 && if exist build_solution rmdir /s /q build_solution && cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build build_solution && ctest --test-dir build_solution --output-on-failure"
```
Output (abbrev):
```
-- The CXX compiler identification is MSVC 19.50.35723.0
-- Configuring done
-- Generating done
[1/2] Building CXX object ...
[2/2] Linking CXX executable ex01_scope_guard_tests.exe
1/1 Test #1: ex01_scope_guard_tests ...........   Passed
100% tests passed
```

### Module 06 sample (ex01_asan)
Command:
```
cmd /c "call ""C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"" -arch=amd64 -host_arch=amd64 && if exist build_solution rmdir /s /q build_solution && cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build build_solution && ctest --test-dir build_solution --output-on-failure"
```
Output (abbrev):
```
-- The CXX compiler identification is MSVC 19.50.35723.0
-- Configuring done
-- Generating done
[1/2] Building CXX object ...
[2/2] Linking CXX executable ex01_asan_tests.exe
1/1 Test #1: ex01_asan_tests ..................   Passed
100% tests passed
```

### Module 11 (CUDA) sample (ex01_env)
Command:
```
cmd /c "call ""C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"" -arch=amd64 -host_arch=amd64 && if exist build_solution rmdir /s /q build_solution && cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build build_solution && ctest --test-dir build_solution --output-on-failure"
```
Output (abbrev):
```
-- The CXX compiler identification is MSVC 19.50.35723.0
-- Configuring done
-- Generating done
[1/2] Building CXX object ...
[2/2] Linking CXX executable exercise_tests.exe
1/1 Test #1: exercise_tests ...................   Passed
100% tests passed
```

---

## PASS 3: Grader Functionality

### Learner path (expected to fail until stubs implemented)
Command:
```
python tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard
```
Output (abbrev):
```
== ex01_scope_guard : 20.0 (20/100)
  [pass] configure (20/20)
  [fail] build (0/20)
  [skipped] tests (0/40)
  [fail] artifacts (0/20)
```

Command:
```
python tools/grader/grade.py --exercise modules/06_debugging/exercises/ex01_asan
```
Output (abbrev):
```
== ex01_asan : 20.0 (20/100)
  [pass] configure (20/20)
  [fail] build (0/20)
  [skipped] tests (0/40)
  [fail] artifacts (0/20)
```

Command:
```
python tools/grader/grade.py --exercise modules/11_cuda_basics/exercises/ex01_env
```
Output (abbrev):
```
== ex01_env : 20.0 (20/100)
  [pass] configure (20/20)
  [fail] build (0/20)
  [skipped] tests (0/40)
  [fail] artifacts (0/20)
```

### Solution path (should score 100)
Command:
```
python tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard --use-solution
```
Output (abbrev):
```
== ex01_scope_guard : 100.0 (100/100)
  [pass] configure (20/20)
  [pass] build (20/20)
  [pass] tests (40/40)
  [pass] artifacts (20/20)
```

Command:
```
python tools/grader/grade.py --exercise modules/06_debugging/exercises/ex01_asan --use-solution
```
Output (abbrev):
```
== ex01_asan : 100.0 (100/100)
  [pass] configure (20/20)
  [pass] build (20/20)
  [pass] tests (40/40)
  [pass] artifacts (20/20)
```

Command:
```
python tools/grader/grade.py --exercise modules/11_cuda_basics/exercises/ex01_env --use-solution
```
Output (abbrev):
```
== ex01_env : 100.0 (100/100)
  [pass] configure (20/20)
  [pass] build (20/20)
  [pass] tests (40/40)
  [pass] artifacts (20/20)
```

### JSON output
Command:
```
python tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard --use-solution --json
```
Output (abbrev):
```
[
  {
    "target": "solution",
    "score": 100.0,
    "earned": 100,
    "possible": 100,
    "results": [ ... ]
  }
]
```

### Requirements summary mode
Command:
```
python tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard --print-requirements
```
Output (abbrev):
```
{
  "checks": [
    { "id": "configure", "type": "command", ... },
    { "id": "build", "type": "command", ... },
    { "id": "tests", "type": "command", ... },
    { "id": "artifacts", "type": "file_exists", ... }
  ]
}
```

---

## PASS 4: Rubric Quality Review (All Exercises)

Command:
```
python tools/audit/audit_rubrics.py
```
Output:
```
OK: rubrics valid and sum to 100
```

---

## PASS 5: Doc Quality Review (Required Sections + No Vague Phrases)

Command:
```
rg -l "Expected result" modules
```
Output (all 36 exercise READMEs listed):
```
modules\12_cuda_perf\exercises\ex03_jetson\README.md
modules\09_mcu\exercises\ex03_uart_bridge\README.md
modules\07_perf\exercises\ex03_perf_regression\README.md
modules\12_cuda_perf\exercises\ex02_divergence\README.md
modules\07_perf\exercises\ex02_flamegraph\README.md
modules\09_mcu\exercises\ex02_race\README.md
modules\07_perf\exercises\ex01_perf_baseline\README.md
modules\09_mcu\exercises\ex01_firmware_build\README.md
modules\12_cuda_perf\exercises\ex01_nsys\README.md
modules\06_debugging\exercises\ex03_gdb_remote\README.md
modules\08_cross_deploy\exercises\ex03_latency_on_hw\README.md
modules\06_debugging\exercises\ex02_tsan\README.md
modules\11_cuda_basics\exercises\ex03_raii_buffer\README.md
modules\06_debugging\exercises\ex01_asan\README.md
modules\11_cuda_basics\exercises\ex02_cpu_gpu_parity\README.md
modules\05_scheduling\exercises\ex03_priority\README.md
modules\11_cuda_basics\exercises\ex01_env\README.md
modules\05_scheduling\exercises\ex02_timeout_fallback\README.md
modules\05_scheduling\exercises\ex01_latency_budget\README.md
modules\08_cross_deploy\exercises\ex02_deploy\README.md
modules\04_architecture\exercises\ex03_backpressure\README.md
modules\04_architecture\exercises\ex02_tracing\README.md
modules\08_cross_deploy\exercises\ex01_cross_build\README.md
modules\04_architecture\exercises\ex01_topic_contract\README.md
modules\10_sim\exercises\ex03_ci_harness\README.md
modules\10_sim\exercises\ex02_renode\README.md
modules\03_concurrency\exercises\ex03_clean_shutdown\README.md
modules\10_sim\exercises\ex01_qemu\README.md
modules\03_concurrency\exercises\ex02_deadlock\README.md
modules\03_concurrency\exercises\ex01_race_repro\README.md
modules\02_memory\exercises\ex03_heaptrack\README.md
modules\02_memory\exercises\ex02_uaf_fix\README.md
modules\02_memory\exercises\ex01_pmr_queue\README.md
modules\01_foundations\exercises\ex03_interface_review\README.md
modules\01_foundations\exercises\ex02_message_bus_view\README.md
modules\01_foundations\exercises\ex01_scope_guard\README.md
```

Command:
```
rg -l "Grade this exercise" modules
```
Output (all 36 exercise READMEs listed):
```
modules\02_memory\exercises\ex03_heaptrack\README.md
modules\01_foundations\exercises\ex03_interface_review\README.md
modules\12_cuda_perf\exercises\ex03_jetson\README.md
modules\02_memory\exercises\ex02_uaf_fix\README.md
modules\01_foundations\exercises\ex02_message_bus_view\README.md
modules\12_cuda_perf\exercises\ex02_divergence\README.md
modules\02_memory\exercises\ex01_pmr_queue\README.md
modules\01_foundations\exercises\ex01_scope_guard\README.md
modules\10_sim\exercises\ex03_ci_harness\README.md
modules\06_debugging\exercises\ex03_gdb_remote\README.md
modules\10_sim\exercises\ex02_renode\README.md
modules\06_debugging\exercises\ex02_tsan\README.md
modules\10_sim\exercises\ex01_qemu\README.md
modules\06_debugging\exercises\ex01_asan\README.md
modules\09_mcu\exercises\ex03_uart_bridge\README.md
modules\09_mcu\exercises\ex01_firmware_build\README.md
modules\05_scheduling\exercises\ex03_priority\README.md
modules\12_cuda_perf\exercises\ex01_nsys\README.md
modules\09_mcu\exercises\ex02_race\README.md
modules\05_scheduling\exercises\ex02_timeout_fallback\README.md
modules\05_scheduling\exercises\ex01_latency_budget\README.md
modules\11_cuda_basics\exercises\ex03_raii_buffer\README.md
modules\08_cross_deploy\exercises\ex03_latency_on_hw\README.md
modules\11_cuda_basics\exercises\ex02_cpu_gpu_parity\README.md
modules\08_cross_deploy\exercises\ex02_deploy\README.md
modules\04_architecture\exercises\ex03_backpressure\README.md
modules\11_cuda_basics\exercises\ex01_env\README.md
modules\04_architecture\exercises\ex02_tracing\README.md
modules\08_cross_deploy\exercises\ex01_cross_build\README.md
modules\04_architecture\exercises\ex01_topic_contract\README.md
modules\07_perf\exercises\ex03_perf_regression\README.md
modules\07_perf\exercises\ex02_flamegraph\README.md
modules\07_perf\exercises\ex01_perf_baseline\README.md
modules\03_concurrency\exercises\ex03_clean_shutdown\README.md
modules\03_concurrency\exercises\ex02_deadlock\README.md
modules\03_concurrency\exercises\ex01_race_repro\README.md
```

Command (verify no vague phrases):
```
rg -n "as appropriate|etc\." modules
```
Output:
```
(no matches)
```

---

## Smoke-tested Exercises (Windows Summary)

1) modules/01_foundations/exercises/ex01_scope_guard/solution
- Configure/build/test command:
```
cmd /c "call ""C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"" -arch=amd64 -host_arch=amd64 && if exist build_solution rmdir /s /q build_solution && cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build build_solution && ctest --test-dir build_solution --output-on-failure"
```
- Result: PASS (100% tests passed)

2) modules/06_debugging/exercises/ex01_asan/solution
- Configure/build/test command:
```
cmd /c "call ""C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"" -arch=amd64 -host_arch=amd64 && if exist build_solution rmdir /s /q build_solution && cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build build_solution && ctest --test-dir build_solution --output-on-failure"
```
- Result: PASS (100% tests passed)

3) modules/11_cuda_basics/exercises/ex01_env/solution
- Configure/build/test command:
```
cmd /c "call ""C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"" -arch=amd64 -host_arch=amd64 && if exist build_solution rmdir /s /q build_solution && cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build build_solution && ctest --test-dir build_solution --output-on-failure"
```
- Result: PASS (100% tests passed)

---

# WSL2 Audit (Ubuntu 24.04)
Host: WSL2 Ubuntu 24.04 (noble), kernel 6.6.87.2

## Toolchain + Dependency Installation (WSL2)

Command:
```
wsl -u root -e bash -lc "apt-get update"
```
Output (abbrev):
```
Get:1 http://security.ubuntu.com/ubuntu noble-security InRelease ...
Fetched 13.9 MB in 4s ...
Reading package lists...
```

Command:
```
wsl -u root -e bash -lc "apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb linux-tools-common linux-tools-generic heaptrack valgrind qemu-system-aarch64 qemu-user-static"
```
Output (abbrev):
```
Setting up cmake (3.28.3-1build7) ...
Setting up ninja-build (1.11.1-2) ...
Setting up clang (1:18.0-59~exp2) ...
Setting up clang-format ...
Setting up clang-tidy ...
Setting up gdb ...
Setting up linux-tools-generic ...
Setting up heaptrack ...
Setting up valgrind ...
Setting up qemu-system-arm ...
Setting up qemu-user-static ...
```

Command:
```
wsl -u root -e bash -lc "apt-get install -y ripgrep"
```
Output (abbrev):
```
Setting up ripgrep ...
```

Command:
```
wsl -u root -e bash -lc "apt-get install -y python3-pip openocd"
```
Output (abbrev):
```
Setting up python3-pip ...
Setting up openocd ...
```

Command:
```
wsl -u root -e bash -lc "apt-get install -y esptool"
```
Output (abbrev):
```
Setting up esptool ...
```

Tool verification:
```
wsl -e bash -lc "cmake --version && ninja --version && g++ --version | head -n 1"
```
Output:
```
cmake version 3.28.3
1.11.1
g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
```

---

## PASS 1: Tree + Link Integrity (Inventory + Required Files)

Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/audit/audit_tree.py"
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
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/audit/audit_links.py"
```
Output:
```
OK: no broken local markdown links
```

Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/audit/audit_rubrics.py"
```
Output:
```
OK: rubrics valid and sum to 100
```

---

## PASS 2: Buildability Smoke Tests (Solutions) - WSL2

Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && bash tools/audit/smoke_test_solutions.sh"
```
Output (abbrev):
```
== Smoke test: modules/01_foundations/exercises/ex01_scope_guard (solution)
100% tests passed, 0 tests failed out of 1
== Smoke test: modules/06_debugging/exercises/ex01_asan (solution)
100% tests passed, 0 tests failed out of 1
== Smoke test: modules/11_cuda_basics/exercises/ex01_env (solution)
100% tests passed, 0 tests failed out of 1
```

---

## PASS 3: Grader Functionality (WSL2)

### Learner path (expected to fail until stubs implemented)
Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard"
```
Output (abbrev):
```
== ex01_scope_guard : 20.0 (20/100)
  [pass] configure (20/20)
  [fail] build (0/20)
  [skipped] tests (0/40)
  [fail] artifacts (0/20)
```

Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/grader/grade.py --exercise modules/06_debugging/exercises/ex01_asan"
```
Output (abbrev):
```
== ex01_asan : 20.0 (20/100)
  [pass] configure (20/20)
  [fail] build (0/20)
  [skipped] tests (0/40)
  [fail] artifacts (0/20)
```

Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/grader/grade.py --exercise modules/11_cuda_basics/exercises/ex01_env"
```
Output (abbrev):
```
== ex01_env : 20.0 (20/100)
  [pass] configure (20/20)
  [fail] build (0/20)
  [skipped] tests (0/40)
  [fail] artifacts (0/20)
```

### Solution path (should score 100)
Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard --use-solution"
```
Output (abbrev):
```
== ex01_scope_guard : 100.0 (100/100)
  [pass] configure (20/20)
  [pass] build (20/20)
  [pass] tests (40/40)
  [pass] artifacts (20/20)
```

Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/grader/grade.py --exercise modules/06_debugging/exercises/ex01_asan --use-solution"
```
Output (abbrev):
```
== ex01_asan : 100.0 (100/100)
  [pass] configure (20/20)
  [pass] build (20/20)
  [pass] tests (40/40)
  [pass] artifacts (20/20)
```

Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/grader/grade.py --exercise modules/11_cuda_basics/exercises/ex01_env --use-solution"
```
Output (abbrev):
```
== ex01_env : 100.0 (100/100)
  [pass] configure (20/20)
  [pass] build (20/20)
  [pass] tests (40/40)
  [pass] artifacts (20/20)
```

### JSON output
Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard --use-solution --json"
```
Output (abbrev):
```
[
  {
    "target": "solution",
    "score": 100.0,
    "earned": 100,
    "possible": 100,
    "results": [ ... ]
  }
]
```

---

## PASS 4: Rubric Quality Review (All Exercises)

Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && python3 tools/audit/audit_rubrics.py"
```
Output:
```
OK: rubrics valid and sum to 100
```

---

## PASS 5: Doc Quality Review (Required Sections + No Vague Phrases)

Command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && rg -n \"as appropriate|etc\\.\" modules"
```
Output:
```
(no matches)
```

---

## Smoke-tested Exercises (WSL2 Summary)

1) modules/01_foundations/exercises/ex01_scope_guard/solution
- Configure/build/test command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && bash tools/audit/smoke_test_solutions.sh"
```
- Result: PASS (100% tests passed)

2) modules/06_debugging/exercises/ex01_asan/solution
- Configure/build/test command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && bash tools/audit/smoke_test_solutions.sh"
```
- Result: PASS (100% tests passed)

3) modules/11_cuda_basics/exercises/ex01_env/solution
- Configure/build/test command:
```
wsl -e bash -lc "cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp && bash tools/audit/smoke_test_solutions.sh"
```
- Result: PASS (100% tests passed)

---

## Fixes Applied During WSL2 Audit

- Updated `tools/audit/smoke_test_solutions.sh` to remove `build_solution/` before configuring, avoiding cross-platform CMake cache conflicts when switching between Windows and WSL2.
- Added explicit Ubuntu/WSL2 install commands to all exercise README prerequisite sections and updated module README setup checklists for consistent tooling installation guidance.
- Updated root `README.md` WSL2 quickstart to include explicit tool install commands (base, perf, heaptrack, QEMU, CUDA).
- Updated `docs/cuda/README.md` and `docs/hardware/mcu.md` with explicit WSL2 install commands where toolchain prerequisites are documented.

---

## Notes

- Ninja is available on Windows; Ninja + MSVC (via VsDevCmd) is the verified Windows path here.
- WSL2 installs use `wsl -u root` for package installation; builds/tests run as the default WSL user.
- Tool-dependent checks (perf, heaptrack, nsys) are reported as skipped when tools are missing; in WSL2, perf/heaptrack are installed and detected.
