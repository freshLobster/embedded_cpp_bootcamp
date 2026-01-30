# 04_architecture - ex03_backpressure

## 1) Title + Mission
Mission: implement a bounded queue that enforces backpressure by dropping items when full and tracking drop counts. (Source: [cppreference: std::deque](https://en.cppreference.com/w/cpp/container/deque))

## 2) What you are building (plain English)
You are building a fixed-capacity queue that protects the system when producers are faster than consumers. When the queue is full, it drops incoming items and records the drop count. (Source: [cppreference: std::deque](https://en.cppreference.com/w/cpp/container/deque))

## 3) Why it matters (embedded/robotics/defense relevance)
Backpressure prevents unbounded memory growth and keeps systems responsive under overload. In autonomy pipelines, dropping less-critical data can be safer than allowing latency to grow without bound. (Source: [C++ Core Guidelines, resource management](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

## 4) Concepts (short lecture)
A bounded queue is a queue with a fixed capacity. When it fills, producers must either block, drop data, or apply another policy. This exercise uses a drop policy for simplicity. (Source: [cppreference: std::deque](https://en.cppreference.com/w/cpp/container/deque))

Tracking drops is important for observability. If you drop data without visibility, you cannot diagnose pipeline overload. A drop counter provides a simple metric that can be exported to telemetry. (Source: [C++ Core Guidelines, resource management](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

Example (not your solution): push with drop tracking.
```cpp
bool try_push(int v) {
    if (q_.size() >= cap_) {
        ++drops_;
        return false; // drop on overflow
    }
    q_.push_back(v);
    return true;
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
1) Read `BoundedQueue` in `learner/src/main.cpp`.
   The queue has a fixed capacity and a drop counter. Your goal is to implement `try_push` and `try_pop` so the queue behaves predictably under load. (Source: [cppreference: std::deque](https://en.cppreference.com/w/cpp/container/deque))
   - **Expected result:** you can describe what should happen when the queue is full.

2) Implement `try_push` with a drop policy.
   If `q_.size()` is greater than or equal to `cap_`, increment `drops_` and return false. Otherwise push and return true. This is a simple backpressure mechanism. (Source: [cppreference: std::deque::push_back](https://en.cppreference.com/w/cpp/container/deque/push_back))
   - **Expected result:** the third push into a capacity-2 queue returns false and increments drops.

3) Implement `try_pop` for FIFO behavior.
   If the queue is empty, return false. Otherwise read `front()`, pop it, and return true. (Source: [cppreference: std::deque::pop_front](https://en.cppreference.com/w/cpp/container/deque/pop_front))
   - **Expected result:** the first pop returns the oldest item (value 1).

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex03_backpressure`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex03_backpressure --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: ensure you removed `#error` and included `<deque>`.
- If tests fail: check the drop counter and FIFO order in `try_pop`.

## 13) Stretch goals
- Add a `peek()` method that inspects the front without popping.
- Add a `reset_drops()` method and log drops to a CSV file.
