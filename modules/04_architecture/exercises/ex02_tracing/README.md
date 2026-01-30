# 04_architecture - ex02_tracing

## 1) Title + Mission
Mission: Implement tracing spans with monotonic timestamps to support deterministic latency analysis.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】

## 2) What you are building (plain English)
You are building a span guard that records start and end times using a monotonic clock and stores durations in a tracer.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】【https://en.cppreference.com/w/cpp/chrono/duration†L450-L450】

## 3) Why it matters (embedded/robotics/defense relevance)
Tracing is only useful if timestamps are monotonic and comparable; otherwise latency analysis becomes noisy and misleading.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】

## 4) Concepts (short lecture)
`std::chrono::steady_clock` is a monotonic clock whose time points never go backward, which makes it the correct choice for latency measurement.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】

`std::chrono::duration` represents a time interval, which is the correct type for computing and storing span lengths.【https://en.cppreference.com/w/cpp/chrono/duration†L450-L450】

A span guard is a RAII object that starts timing in its constructor and records the elapsed time in its destructor, guaranteeing the span is closed even on early exits.【https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines†L10094-L10094】

Example (not your solution): a span guard that records durations.
```cpp
class SpanGuard {
public:
    SpanGuard(Tracer& t, std::string name)
        : tracer_(t), name_(std::move(name)), start_(std::chrono::steady_clock::now()) {}
    ~SpanGuard() {
        auto end = std::chrono::steady_clock::now();
        auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
        tracer_.record(std::move(name_), micros);
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
1) Open `learner/src/main.cpp` and inspect the `Tracer` and `SpanGuard` skeletons.
   - Identify which fields must be stored to compute elapsed time.
   - **Expected result:** you can explain when a span starts and ends.
2) Implement the `SpanGuard` constructor.
   - Capture the name and start time using `steady_clock::now()`.
   - **Expected result:** start time is saved for later computation.
3) Implement the `SpanGuard` destructor.
   - Compute elapsed time in microseconds and record it in the tracer.
   - **Expected result:** a span is recorded when the guard goes out of scope.
4) Remove `#error TODO_implement_exercise`, build, and run tests.
5) Save artifacts.

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
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a span depth counter to model nested spans.
- Add a `Tracer::clear()` method and test it.
