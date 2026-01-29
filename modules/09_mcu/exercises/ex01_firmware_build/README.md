# 09_mcu - ex01_firmware_build

## 1) Title + Mission
Mission: Implement a UART sample framing function suitable for MCU-to-host communication.【https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html†L199-L199】
## 2) What you are building (plain English)
You are building a simple encoder that formats sensor samples for UART transport, mirroring how MCU telemetry is emitted.【https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html†L199-L199】
## 3) Why it matters (embedded/robotics/defense relevance)
UART remains a common MCU communication channel; clear framing is required to make logs and sensor streams reliable.【https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html†L199-L199】
## 4) Concepts (short lecture)
ESP-IDF UART documentation describes establishing communication between an ESP32-C3 and other UART devices using the UART driver APIs.【https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html†L199-L199】

A deterministic frame format is a prerequisite for debugging and validation in embedded bring-up workflows.【https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html†L199-L199】
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

## 7) Build instructions (learner + solution)
### Learner path (fails initially until you implement)
```
cmake -S learner -B build_learner -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_learner
ctest --test-dir build_learner --output-on-failure
```

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Open `learner/src/main.cpp` and read the TODOs.
2) Implement the required logic in `exercise()`.
3) Rebuild and run tests.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex01_firmware_build`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex01_firmware_build --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
