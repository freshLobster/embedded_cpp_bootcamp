# 02_memory - ex03_heaptrack

## 1) Title + Mission
Mission: Implement a repeatable allocation workload and capture heap profiling artifacts from the run.【https://valgrind.org/docs/manual/ms-manual.html†L106-L106】
## 2) What you are building (plain English)
You are building a deterministic allocation workload and then recording its heap footprint so you can compare runs and reason about memory growth.【https://valgrind.org/docs/manual/ms-manual.html†L106-L106】
## 3) Why it matters (embedded/robotics/defense relevance)
Heap growth is a reliability risk in long-running autonomy software; profiling shows where memory expands and which patterns cause fragmentation.【https://valgrind.org/docs/manual/ms-manual.html†L106-L106】
## 4) Concepts (short lecture)
Massif is a heap profiler that measures how much heap memory a program uses, making allocation-heavy paths visible and comparable across runs.【https://valgrind.org/docs/manual/ms-manual.html†L106-L106】

Allocator strategy and lifetime boundaries determine peak memory, so reproducible workloads are a prerequisite for meaningful profiling.【https://en.cppreference.com/w/cpp/memory/memory_resource†L463-L463】
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
1) Open `learner/src/main.cpp` and read the TODOs.
   - Identify the required behavior for a small allocation workload with explicit RAII cleanup to support heap tooling.
   - **Expected result:** you can explain what `exercise()` must verify before it returns success.
2) Implement the required logic in `exercise()`.
   - Introduce any helper classes or functions directly in `learner/src/main.cpp` or in `learner/include/` if you prefer.
   - **Expected result:** the code compiles without `#error` and the logic enforces the required behavior.
3) Rebuild and run tests.
   - Run `cmake --build build_learner` and `ctest --test-dir build_learner --output-on-failure`.
   - **Expected result:** tests pass and return 0.
4) Save artifacts.
   - Copy build and test output to `learner/artifacts/build.log` and `learner/artifacts/ctest.log`.
   - **Expected result:** those files exist and contain your command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.
- If it fails, stop and read `troubleshooting.md`.

## 10) Artifacts to save
Place these in `learner/artifacts/`:
- `build.log` - stdout/stderr from the build step.
- `ctest.log` - stdout/stderr from the test step.

## 11) Grade this exercise
- Learner attempt:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex03_heaptrack`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex03_heaptrack --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add an extra test case that exercises an edge condition.
- Move helper logic into `learner/include/` and keep the interface clean.
