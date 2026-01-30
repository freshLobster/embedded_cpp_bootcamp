# 04_architecture - ex02_tracing

## 1) Title + Mission
Mission: implement a span guard that records elapsed time using a monotonic clock so latency measurements are deterministic. (Source: [cppreference: std::chrono::steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock))

## 2) What you are building (plain English)
You are building a small tracing utility: create a guard, run some work, and when the guard leaves scope it records how long that work took. This is the backbone of latency instrumentation. (Source: [cppreference: std::chrono::duration](https://en.cppreference.com/w/cpp/chrono/duration))

## 3) Why it matters (embedded/robotics/defense relevance)
Control systems need accurate latency measurements to verify real-time budgets. If your clock jumps backward or forward, your metrics are meaningless. A steady clock avoids these problems and keeps trace data reliable. (Source: [cppreference: std::chrono::steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock))

## 4) Concepts (short lecture)
`std::chrono::steady_clock` is a monotonic clock whose time points never go backward. This makes it the correct choice for measuring durations, because system clock adjustments will not affect it. (Source: [cppreference: std::chrono::steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock))

`std::chrono::duration` represents a time interval. Converting from one duration type to another uses `duration_cast`, which makes the unit conversion explicit and safe. (Source: [cppreference: std::chrono::duration](https://en.cppreference.com/w/cpp/chrono/duration))

A span guard is an RAII object: it records the start time in the constructor and the end time in the destructor, ensuring the span closes even on early return. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

Example (not your solution): RAII span guard with comments.
```cpp
class SpanGuard {
public:
    // Start timing at construction.
    SpanGuard(Tracer& t, std::string name)
        : tracer_(t), name_(std::move(name)), start_(std::chrono::steady_clock::now()) {}
    ~SpanGuard() {
        // Capture end time using a monotonic clock.
        auto end = std::chrono::steady_clock::now();
        // Convert duration to microseconds for storage.
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
        // Record the span name and duration.
        tracer_.record(std::move(name_), us);
    }
private:
    Tracer& tracer_;
    std::string name_;
    std::chrono::steady_clock::time_point start_;
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
1) Read `SpanGuard` and `Tracer` in `learner/src/main.cpp`.
   The guard should record start time on construction and record elapsed time on destruction. This is a classic RAII pattern where the destructor finalizes a measurement. (Source: [C++ Core Guidelines, RAII (R.1)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))
   - **Expected result:** you can describe the lifecycle of a span from begin to end.

2) Implement `SpanGuard::~SpanGuard()` to compute duration.
   Use `steady_clock::now()` for the end time, then compute the difference and convert to microseconds with `duration_cast`. This ensures your timestamps are monotonic and consistent. (Source: [cppreference: std::chrono::duration_cast](https://en.cppreference.com/w/cpp/chrono/duration_cast))
   - **Expected result:** you can derive a positive duration in microseconds.

3) Call `tracer_.record` with the name and duration.
   Store spans in the tracer's vector so the test can verify them. Use `std::move` for the name to avoid extra copies. (Source: [cppreference: std::move](https://en.cppreference.com/w/cpp/utility/move))
   - **Expected result:** `t.spans()` contains one span with name "io".

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build and test output into `learner/artifacts/build.log` and `learner/artifacts/ctest.log`.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex02_tracing`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex02_tracing --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: ensure you removed `#error` and included `<chrono>`.
- If tests fail: confirm you used `steady_clock` and `duration_cast` to microseconds.

## 13) Stretch goals
- Add nested spans and record parent/child relationships.
- Add a method to export spans to CSV and save in `learner/artifacts/trace.csv`.
