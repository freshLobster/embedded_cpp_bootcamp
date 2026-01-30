# 05_scheduling - ex02_timeout_fallback

## 1) Title + Mission
Mission: implement a timeout wrapper that uses `future::wait_for` and returns a fallback when a task exceeds its deadline. (Source: [cppreference: std::future::wait_for](https://en.cppreference.com/w/cpp/thread/future/wait_for))

## 2) What you are building (plain English)
You are building a helper that runs a task asynchronously and returns either the task result or a fallback value if the task is too slow. This is a simple building block for deadline-aware systems. (Source: [cppreference: std::async](https://en.cppreference.com/w/cpp/thread/async))

## 3) Why it matters (embedded/robotics/defense relevance)
Timeouts bound tail latency so a slow component cannot stall an entire control loop. Returning a fallback keeps the system responsive even when an upstream sensor or service is slow. (Source: [cppreference: std::future::wait_for](https://en.cppreference.com/w/cpp/thread/future/wait_for))

## 4) Concepts (short lecture)
`std::async` launches a function asynchronously and returns a `std::future`. The future holds the eventual result and provides synchronization with `wait_for` or `get`. (Source: [cppreference: std::async](https://en.cppreference.com/w/cpp/thread/async))

`future::wait_for` blocks until the result is ready or a timeout expires. It returns a status that lets you decide whether to return the real result or a fallback. (Source: [cppreference: std::future::wait_for](https://en.cppreference.com/w/cpp/thread/future/wait_for))

Example (not your solution): run a task with a timeout.
```cpp
// Launch a task asynchronously.
auto fut = std::async(std::launch::async, [] { return 42; });
// Wait for up to 5ms for completion.
if (fut.wait_for(5ms) == std::future_status::ready) {
    // Task finished in time; return the real result.
    return fut.get();
}
// Timeout expired; return fallback instead.
return fallback;
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
1) Read `run_with_timeout` in `learner/src/main.cpp`.
   The function must run a task asynchronously and return either the result or a fallback if the timeout expires. This is a direct application of `std::future::wait_for`. (Source: [cppreference: std::future::wait_for](https://en.cppreference.com/w/cpp/thread/future/wait_for))
   - **Expected result:** you can describe the success and timeout paths.

2) Launch the task with `std::async`.
   Use `std::launch::async` to force asynchronous execution, then store the returned future. (Source: [cppreference: std::async](https://en.cppreference.com/w/cpp/thread/async))
   - **Expected result:** you have a future that represents the running task.

3) Wait for the result with `wait_for`.
   If `wait_for(timeout)` returns `std::future_status::ready`, call `get()` and return the result. Otherwise return the fallback. (Source: [cppreference: std::future::wait_for](https://en.cppreference.com/w/cpp/thread/future/wait_for))
   - **Expected result:** fast tasks return their real result; slow tasks return the fallback.

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/05_scheduling/exercises/ex02_timeout_fallback`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/05_scheduling/exercises/ex02_timeout_fallback --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: ensure you included `<future>` and removed `#error`.
- If tests fail: confirm you used `wait_for` and return fallback on timeout.

## 13) Stretch goals
- Add a timeout error code enum rather than an integer fallback.
- Add a variant that accepts a cancellation token and cancels the task if possible.
