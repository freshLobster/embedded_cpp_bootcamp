# 02_memory - ex03_heaptrack

## 1) Title + Mission
Mission: Implement a repeatable allocation workload and capture heap profiling artifacts from the run.【https://valgrind.org/docs/manual/ms-manual.html†L106-L106】

## 2) What you are building (plain English)
You are building a deterministic allocation workload and then recording its heap footprint so you can compare runs and reason about memory growth.【https://valgrind.org/docs/manual/ms-manual.html†L106-L106】

## 3) Why it matters (embedded/robotics/defense relevance)
Heap growth is a reliability risk in long-running autonomy software; profiling shows where memory expands and which patterns cause fragmentation.【https://valgrind.org/docs/manual/ms-manual.html†L106-L106】

## 4) Concepts (short lecture)
Massif is a heap profiler that measures how much heap memory a program uses. It is designed for comparing allocation behavior across runs and spotting unexpected growth.【https://valgrind.org/docs/manual/ms-manual.html†L106-L106】

A profiling workload must be deterministic: same input, same number of allocations, and the same lifetime boundaries. If the workload is noisy, the profiler output is not actionable.

Example (not your solution): a deterministic allocation loop that allocates, uses, and releases memory within scope.
```cpp
int allocate_and_sum(int n) {
    std::vector<int> v;
    for (int i = 0; i < n; ++i) v.push_back(i);
    int sum = 0;
    for (int x : v) sum += x;
    return sum; // v is freed when it goes out of scope
}
```

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

Optional heap profiling:
```
sudo apt-get install -y valgrind
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


## 8) Step-by-step implementation instructions
1) Open `learner/src/main.cpp` and find the allocation workload stub.
   - The function should allocate, use the data, and return a deterministic result.
   - **Expected result:** you can predict the sum for a given input.
2) Implement the workload using `std::vector`.
   - Ensure allocations happen inside the function so lifetime is bounded.
   - **Expected result:** the function returns the correct sum and frees memory when it returns.
3) Update `exercise()` to validate the workload and remove `#error`.
4) Build and run tests.
5) Save artifacts and, if you have Massif, capture a heap profile run.

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex03_heaptrack`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex03_heaptrack --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a second workload with a different allocation pattern and compare results.
- Capture a Massif report and save it in `learner/artifacts/` as `massif.out`.
