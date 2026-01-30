# 03_concurrency - ex01_race_repro

## 1) Title + Mission
Mission: implement a thread-safe counter using `std::atomic` to eliminate data races under concurrent increments. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))

## 2) What you are building (plain English)
You are building a counter that multiple threads can increment at the same time without losing updates. The goal is correct results under concurrency without using locks. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))

## 3) Why it matters (embedded/robotics/defense relevance)
Shared counters are common in telemetry, diagnostics, and scheduling. If they are not atomic, you can silently drop increments, leading to incorrect health reports or missed deadlines. Atomics provide correctness with minimal overhead. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))

## 4) Concepts (short lecture)
A data race occurs when two threads access the same memory location concurrently and at least one access is a write, without synchronization. In C++, data races cause undefined behavior. `std::atomic` provides synchronized operations that eliminate data races for simple shared state. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))

Atomic operations like `fetch_add` and `load` perform indivisible read-modify-write or read actions. For counters, this ensures increments are not lost when many threads update the same variable. (Source: [cppreference: std::atomic::fetch_add](https://en.cppreference.com/w/cpp/atomic/atomic/fetch_add))

Example (not your solution): a minimal atomic counter with comments.
```cpp
class Counter {
public:
    void increment() {
        // fetch_add atomically increments the counter.
        value_.fetch_add(1);
    }
    int value() const {
        // load reads the current value atomically.
        return value_.load();
    }
private:
    std::atomic<int> value_{0};
};
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
1) Read `learner/src/main.cpp` and locate the shared state.
   The `Counter` holds a `std::atomic<int>` named `value_`. Every thread in the test calls `increment()` many times, so this is the contested shared variable. Your implementation must guarantee that no increments are lost. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))
   - **Expected result:** you can explain why a plain `int` would lose updates under this workload.

2) Implement `Counter::increment()` using `fetch_add`.
   `fetch_add(1)` performs an atomic read-modify-write that is indivisible. That means each thread's increment is applied exactly once even when many threads update concurrently. Do not use `value_++` because the test is designed to catch lost increments. (Source: [cppreference: std::atomic::fetch_add](https://en.cppreference.com/w/cpp/atomic/atomic/fetch_add))
   - **Expected result:** each thread contributes exactly `kIters` increments.

3) Implement `Counter::value()` using `load`.
   `load()` reads the atomic value safely. This avoids torn reads and ensures the returned value reflects the completed increments. This is the value the test checks at the end. (Source: [cppreference: std::atomic::load](https://en.cppreference.com/w/cpp/atomic/atomic/load))
   - **Expected result:** the final value equals `kThreads * kIters`.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If the test fails, check that you used atomic operations in both methods and that you did not accidentally shadow `value_` with a local variable. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. These logs are required evidence for grading. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))
   - **Expected result:** both log files exist and contain the command output.

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex01_race_repro`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex01_race_repro --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: confirm you removed `#error` and included `<atomic>`.
- If tests fail: ensure you used `fetch_add` and `load`, not non-atomic operations.

## 13) Stretch goals
- Add a second counter using a mutex and compare overhead.
- Add a test that checks behavior under more threads or iterations.
