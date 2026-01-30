# 05_scheduling - ex02_timeout_fallback

## 1) Title + Mission
Mission: Implement a timeout wrapper that uses wait_for and returns a fallback on expiry.【https://en.cppreference.com/w/cpp/thread/future/wait_for†L476-L476】

## 2) What you are building (plain English)
You are building a wrapper around an asynchronous task that waits up to a timeout duration and returns a fallback result if the task is too slow.【https://en.cppreference.com/w/cpp/thread/future/wait_for†L476-L476】

## 3) Why it matters (embedded/robotics/defense relevance)
Timeouts bound tail latency in control systems and prevent upstream stalls from cascading into missed deadlines.【https://en.cppreference.com/w/cpp/thread/future/wait_for†L476-L476】

## 4) Concepts (short lecture)
`future::wait_for` blocks until a timeout duration has elapsed or the result becomes available. This is the standard building block for timeouts in C++ concurrency.【https://en.cppreference.com/w/cpp/thread/future/wait_for†L476-L476】

`std::async` runs a function asynchronously (often on a separate thread), which is why it pairs naturally with `wait_for` when you need a timeout boundary.【https://en.cppreference.com/w/cpp/thread/async†L473-L473】

A timeout wrapper must return a deterministic fallback when the task is late. This gives the caller a predictable worst-case behavior instead of indefinite blocking.

Example (not your solution): wrap a task with `std::async` and `wait_for`.
```cpp
int run_with_timeout(std::function<int()> fn, std::chrono::milliseconds timeout, int fallback) {
    auto fut = std::async(std::launch::async, std::move(fn));
    if (fut.wait_for(timeout) == std::future_status::ready) return fut.get();
    return fallback;
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
1) Open `learner/src/main.cpp` and review the `run_with_timeout` stub.
   - Identify the inputs (callable, timeout, fallback) and the required behavior.
   - **Expected result:** you can explain what happens when the task is late.
2) Implement the asynchronous call and waiting logic.
   - Use `std::async` with `std::launch::async`.
   - Use `wait_for` to compare against the timeout.
   - **Expected result:** fast tasks return their value; slow tasks return fallback.
3) Remove `#error TODO_implement_exercise`, build, and run tests.
4) Save artifacts.

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/05_scheduling/exercises/ex02_timeout_fallback`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/05_scheduling/exercises/ex02_timeout_fallback --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a timeout status enum and return it alongside the result.
- Add a test that uses a very short timeout to force the fallback path.
