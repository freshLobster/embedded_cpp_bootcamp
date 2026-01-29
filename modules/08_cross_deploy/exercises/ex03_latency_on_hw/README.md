# Module 08_cross_deploy - ex03_latency_on_hw

## 1) Title + Mission
Mission: Measure latency on SBC. You will use a tiny, isolated codebase to practice the build/test/grade loop in a deterministic way.

## 2) What you are building (plain English)
A minimal C++ program with a single function `exercise()` that must return a specific value (42). The program is intentionally incomplete in `learner/` and complete in `solution/`.

## 3) Why it matters (embedded/robotics/defense relevance)
In safety-critical systems, you must be able to build, test, and validate components in isolation. This exercise enforces the habit of verifying outputs with deterministic tests and artifacts before integration into larger autonomy stacks.

## 4) Concepts (short lecture)
- **Isolated builds**: each exercise builds without the root CMake.
- **Single-function contract**: a tiny function provides a clean, testable contract.
- **Deterministic grading**: outputs are scored from build/test logs and artifacts.
Example: `int exercise();` must return 42, and the test asserts it.

- **Hardware stub path:** `read_sensor_fake()` returns a constant sample so the code runs without devices.
- **Hardware path:** `read_sensor_hw()` exists as a stub. To use it, build with `-DENABLE_HARDWARE=ON` and call it in `exercise()`.

## 5) Repo context (this folder only)
- `learner/`: incomplete code you must finish. Contains its own `CMakeLists.txt`, `include/`, `src/`, `tests/`, and `artifacts/`.
- `solution/`: working reference that compiles and passes tests immediately.
- `grading/`: rubric.json used by the grader.
- `tools/`: optional helper scripts (if any).
- `troubleshooting.md`: common failure modes.
- `references.md`: links to repo-level conventions.

## 6) Prerequisites checks
Install tools (Ubuntu/WSL2, run once):
```
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb
```

Run these in **this exercise folder**:
```
cmake --version
```
Expected output (example): `cmake version 3.22.1`.

```
c++ --version
```
Expected output (example): `g++ (Ubuntu 11.4.0)` or `clang version 14.x`.

If you will use Ninja:
```
ninja --version
```
Expected output: a version number (e.g., `1.10.1`). If Ninja is missing, use the Visual Studio generator on Windows.

### Hardware required (optional, SBC path)
BOM (generic):
- SBC: Raspberry Pi 4/5 or Orange Pi 5
- I2C sensor: MPU6050 or BMP280
- LED + resistor or micro-servo
- Jumper wires, breadboard

Pin table (Raspberry Pi example):
- 3V3 -> sensor VCC
- GND -> sensor GND
- GPIO2 (SDA) -> sensor SDA
- GPIO3 (SCL) -> sensor SCL
- GPIO18 -> LED/servo signal

ASCII wiring:
```
Pi 3V3 --- VCC (sensor)
Pi GND --- GND (sensor)
Pi SDA --- SDA
Pi SCL --- SCL
Pi GPIO18 -> LED/servo
```

No hardware path:
- Do not set `-DENABLE_HARDWARE=ON`.
- The code will use `read_sensor_fake()` and run without devices.

## 7) Build instructions (learner + solution)
### Learner path (fails initially until you implement)
```
cmake -S learner -B build_learner -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_learner
ctest --test-dir build_learner --output-on-failure
```
Expected initial failure: compilation error due to `#error TODO_implement_exercise`.

Windows (no Ninja):
```
cmake -S learner -B build_learner -G "Visual Studio 17 2022"
cmake --build build_learner --config Debug
ctest --test-dir build_learner -C Debug --output-on-failure
```

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```
Expected output: `100% tests passed`.

Windows (no Ninja):
```
cmake -S solution -B build_solution -G "Visual Studio 17 2022"
cmake --build build_solution --config Debug
ctest --test-dir build_solution -C Debug --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Open `learner/src/main.cpp`.
   - Find the line `#error TODO_implement_exercise`.
   - Replace it with `return 42;`.
   - **Expected result:** the file compiles; `exercise()` now satisfies the contract.
2) Rebuild the learner target:
   - Run `cmake --build build_learner`.
   - **Expected result:** build succeeds without errors.
3) Run tests:
   - Run `ctest --test-dir build_learner --output-on-failure`.
   - **Expected result:** test exits 0 and reports 1/1 passed.
4) Save artifacts:
   - Copy build and test output to `learner/artifacts/build.log` and `learner/artifacts/ctest.log`.
   - **Expected result:** those files exist and contain your command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.
- If it fails, stop and read `troubleshooting.md`.

## 10) Artifacts to save
Place these in `learner/artifacts/`:
- `build.log` - stdout/stderr from the build step.
- `ctest.log` - stdout/stderr from the test step.
Example snippet for `ctest.log`:
```
1/1 Test #1: ...   Passed
100% tests passed, 0 tests failed out of 1
```

## 11) Grade this exercise
- Learner attempt:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex03_latency_on_hw`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex03_latency_on_hw --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If Ninja missing: use Visual Studio generator.
- If tests fail: confirm `exercise()` returns 42.

## 13) Stretch goals
- Add a second test that checks a different input/output.
- Replace `assert` with a tiny custom test macro and update tests.
