# 09_mcu - ex03_uart_bridge

## 1) Title + Mission
Mission: Implement a UART bridge framing format with checksum verification to guard against corrupt payloads.【https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html†L199-L199】【https://www.rfc-editor.org/rfc/rfc1071.txt†L20-L22】
## 2) What you are building (plain English)
You are building a frame checksum and parser that can detect corrupted UART payloads before they enter the system.【https://www.rfc-editor.org/rfc/rfc1071.txt†L20-L22】
## 3) Why it matters (embedded/robotics/defense relevance)
Embedded links are noisy; a checksum provides a cheap, measurable integrity check before higher-level processing.【https://www.rfc-editor.org/rfc/rfc1071.txt†L20-L22】
## 4) Concepts (short lecture)
The Internet checksum is a widely used integrity check technique and provides a clear model for checksum computation.【https://www.rfc-editor.org/rfc/rfc1071.txt†L20-L22】

UART-based workflows require framing and integrity checks to make serial links reliable during bring-up and testing.【https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/peripherals/uart.html†L199-L199】
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
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex03_uart_bridge`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex03_uart_bridge --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
