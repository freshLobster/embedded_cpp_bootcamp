# Final Audit Report

Date: 2026-01-29  
Repo: f:\Documents\FirmwareProjects\practice\embedded_cpp_bootcamp

## Orphan Cleanup

| Path | Action | Reason |
| --- | --- | --- |
| `modules/08_cross_deploy/artifacts/artifacts/` | removed | nested artifacts directory (orphaned README) |
| `modules/01_foundations/exercises/ex01_scope_guard/solution/artifacts/build.log` | removed | leftover build output from prior smoke test |
| `modules/01_foundations/exercises/ex01_scope_guard/solution/artifacts/ctest.log` | removed | leftover test output from prior smoke test |
| `modules/06_debugging/exercises/ex01_asan/solution/artifacts/build.log` | removed | leftover build output from prior smoke test |
| `modules/06_debugging/exercises/ex01_asan/solution/artifacts/ctest.log` | removed | leftover test output from prior smoke test |
| `modules/11_cuda_basics/exercises/ex01_env/solution/artifacts/build.log` | removed | leftover build output from prior smoke test |
| `modules/11_cuda_basics/exercises/ex01_env/solution/artifacts/ctest.log` | removed | leftover test output from prior smoke test |
| `build/dev/` | removed | cleared to avoid generator mismatch before MSVC configure |

## WSL2 Verification (Linux)

Commands executed:
```
cd /mnt/f/Documents/FirmwareProjects/practice/embedded_cpp_bootcamp
cmake --preset dev
cmake --build --preset dev
ctest --preset dev --output-on-failure
python3 tools/grader/grade.py --all --json
python3 tools/audit/audit_tree.py
python3 tools/audit/audit_links.py
python3 tools/audit/audit_rubrics.py
```

Results (abbrev):
- `cmake --preset dev` configured successfully (warnings only from FetchContent CMP0135 policy).
- `cmake --build --preset dev` succeeded; built `platform_core_app`, `platform_core_tests`, `platform_core_bench`.
- `ctest --preset dev --output-on-failure` passed 9/9 tests.
- `python3 tools/grader/grade.py --all --json` returned score 100 for all 12 modules.
- Audits: `audit_tree.py`, `audit_links.py`, `audit_rubrics.py` all reported OK.

Selected command outputs:
```
100% tests passed, 0 tests failed out of 9
Total Test time (real) =   0.24 sec
```

```
[
  { "target": "01_foundations", "score": 100.0, "earned": 100, "possible": 100, "results": [ ... ] },
  { "target": "02_memory", "score": 100.0, "earned": 100, "possible": 100, "results": [ ... ] }
  ...
]
```

```
OK: all required module/exercise files present
OK: no broken local markdown links
OK: rubrics valid and sum to 100
```

Tool availability (WSL checks run):
- Present: `cmake`, `ninja`, `clang++`, `clang-format`, `gdb`, `perf`, `ssh`, `scp`, `python3`, `nvidia-smi`.
- Missing: `qemu-aarch64`, `renode`, `nsys`, `aarch64-linux-gnu-g++`, `idf.py`.

Package installation attempt:
- `sudo apt-get update` and `sudo apt-get install -y qemu-user-static qemu-system-aarch64 gcc-aarch64-linux-gnu g++-aarch64-linux-gnu python3-serial` timed out in this environment, so those tools remain missing for this run.

Notes on skipped checks:
- Hardware-gated checks (cross-build, deploy logs, MCU tools/logs) were skipped with full credit because `--enable-hardware` was not used.
- CUDA-gated checks (CUDA build/test, nsys) were skipped with full credit because `--enable-cuda` was not used.
- Simulation tools (qemu/renode) were missing; their checks were skipped with full credit per rubric policy.

## Windows/MSVC Verification

Command executed:
```
cmake --preset dev -G "Visual Studio 17 2022"
```

Result:
- FAIL: `Generator Visual Studio 17 2022 could not find any instance of Visual Studio.`

Static compatibility scan (Windows fallback):
```
rg -n "<unistd.h>|<pthread.h>|<sys/|<netinet/|<arpa/|<fcntl.h>" include src tests benchmarks modules firmware
```
Output:
- No matches (no POSIX-only headers in the codebase).

Notes:
- Windows build was not possible in this environment due to missing Visual Studio instance. The codebase is C++20 and uses `std::jthread` (MSVC-supported), with no POSIX-only headers detected.

## Grader Confirmation

Command executed:
```
python3 tools/grader/grade.py --all --json
```

Result:
- All modules scored 100. Hardware/CUDA checks skipped when corresponding flags were not enabled, as intended.

