# 02_memory - ex03_heaptrack

## 1) Title + Mission
Mission: build a deterministic allocation workload and collect heap profiling artifacts that prove memory behavior over time. (Source: [Valgrind Massif manual](https://valgrind.org/docs/manual/ms-manual.html))

## 2) What you are building (plain English)
You are building a tiny program that performs predictable allocations and then recording its heap usage with profiling tools. The goal is to make memory growth visible and repeatable. (Source: [Valgrind Massif manual](https://valgrind.org/docs/manual/ms-manual.html))

## 3) Why it matters (embedded/robotics/defense relevance)
Long-running autonomy software must avoid slow memory growth and fragmentation. Profiling lets you catch leaks and unexpected spikes early, before they appear in the field. (Source: [Valgrind Massif manual](https://valgrind.org/docs/manual/ms-manual.html))

## 4) Concepts (short lecture)
Heap profiling measures how much memory a program allocates over time. A deterministic workload makes it possible to compare runs and spot regressions. If your workload is random, your results will be noisy and unreliable. (Source: [Valgrind Massif manual](https://valgrind.org/docs/manual/ms-manual.html))

Valgrind Massif is a heap profiler that records snapshots of heap usage and can be visualized with `ms_print`. It is especially useful on Linux when you need a low-dependency memory profile. (Source: [Valgrind Massif manual](https://valgrind.org/docs/manual/ms-manual.html))

Example (not your solution): a deterministic allocation loop with comments explaining why it is stable across runs.
```cpp
int workload(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        // Allocate a vector of predictable size each iteration.
        std::vector<int> v(static_cast<size_t>(i));
        for (int j = 0; j < i; ++j) {
            v[static_cast<size_t>(j)] = j + 1;
            sum += j + 1;
        }
        // v is freed here, creating a clear allocation/deallocation pattern.
    }
    return sum;
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
sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb valgrind
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

Verify Valgrind is available (optional but recommended):
```
valgrind --version
```
Expected output: a version string such as `valgrind-3.18.x`.

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
1) Read `learner/src/main.cpp` and decode the expected sum.
   The test calls `allocate_and_free(4)` and expects a sum of 10, which is 1+2+3+4. This tells you the exact deterministic workload the tests want: each iteration adds a known sequence so the sum can be predicted. (Source: [Valgrind Massif manual](https://valgrind.org/docs/manual/ms-manual.html))
   - **Expected result:** you can explain how your loop will produce the sum 10.

2) Implement a deterministic allocation workload in `allocate_and_free`.
   For `i` from 1 to `n`, allocate a `std::vector<int>` of size `i`, fill it with values `1..i`, and add those values to a running sum. The vector must go out of scope each iteration so allocations and frees are visible to the profiler. This creates a predictable, repeatable allocation pattern. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   - **Expected result:** each call to `allocate_and_free(n)` performs the same allocations and returns the same sum.

3) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If the test fails, check your sum math and ensure the loop bounds are correct (1..n). (Source: [Valgrind Massif manual](https://valgrind.org/docs/manual/ms-manual.html))
   - **Expected result:** `ctest` reports `100% tests passed`.

4) Run heap profiling and save artifacts.
   If Valgrind is available, run Massif and save the output to `learner/artifacts/massif.out`. Then convert it to readable text:
   ```
   valgrind --tool=massif --massif-out-file=learner/artifacts/massif.out ./build_learner/ex03_heaptrack
   ms_print learner/artifacts/massif.out > learner/artifacts/massif.txt
   ```
   If Valgrind is not available, capture the program output to `learner/artifacts/heap_profile.txt` and note that it is the fallback. (Source: [Valgrind Massif manual](https://valgrind.org/docs/manual/ms-manual.html))
   - **Expected result:** the artifact files exist and contain heap profile data.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.
- If it fails, stop and read `troubleshooting.md`.

## 10) Artifacts to save
Place these in `learner/artifacts/`:
- `build.log` - stdout/stderr from the build step.
- `ctest.log` - stdout/stderr from the test step.
- `massif.out` and `massif.txt` (if Valgrind available) or `heap_profile.txt` (fallback).

## 11) Grade this exercise
- Learner attempt:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex03_heaptrack`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex03_heaptrack --use-solution`
- High-level scoring:
  - Configure/build: 30 points
  - Tests: 40 points
  - Artifacts present: 30 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify you removed `#error` and included `<vector>`.
- If tests fail: ensure your sum calculation matches 1+2+3+4 for input 4.

## 13) Stretch goals
- Run with a larger `n` and compare Massif profiles between runs.
- Add a second workload function that intentionally allocates more memory and compare profiles.
