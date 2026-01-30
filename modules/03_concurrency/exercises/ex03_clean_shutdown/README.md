# 03_concurrency - ex03_clean_shutdown

## 1) Title + Mission
Mission: implement a worker thread that drains tasks and shuts down cleanly using a condition variable and cooperative stop. (Source: [cppreference: std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable))

## 2) What you are building (plain English)
You are building a worker that blocks while idle, processes tasks when they arrive, and exits only after all work is done and a stop has been requested. This is a standard building block for robotics pipelines. (Source: [cppreference: std::jthread](https://en.cppreference.com/w/cpp/thread/jthread))

## 3) Why it matters (embedded/robotics/defense relevance)
Clean shutdown is critical in mission systems: threads must not outlive their owners, and work must not be dropped silently. A deterministic shutdown path prevents resource leaks and inconsistent state during system stop. (Source: [cppreference: std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable))

## 4) Concepts (short lecture)
`std::condition_variable` allows a thread to sleep until a condition is met, avoiding busy-waiting. It is the standard mechanism for producer/consumer queues where workers wait for tasks. (Source: [cppreference: std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable))

`std::jthread` is a C++20 thread that joins on destruction and can receive a stop request through `std::stop_token`. This encourages cooperative cancellation: the worker checks the token and exits cleanly. (Source: [cppreference: std::jthread](https://en.cppreference.com/w/cpp/thread/jthread))

Example (not your solution): worker loop using condition variables with explicit comments.
```cpp
void worker_loop(std::stop_token st) {
    for (;;) {
        std::unique_lock<std::mutex> lock(m_);
        // Wait until there is work or a stop request.
        cv_.wait(lock, [&] { return st.stop_requested() || !tasks_.empty(); });
        if (tasks_.empty() && st.stop_requested()) {
            break; // clean shutdown
        }
        auto task = std::move(tasks_.front());
        tasks_.pop();
        lock.unlock();
        task();
    }
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
1) Read the `Worker` class in `learner/src/main.cpp`.
   The design uses a condition variable, a task queue, and a `std::jthread` with a stop token. Your task is to connect these pieces so the worker sleeps when idle and exits only after a stop is requested and the queue is empty. (Source: [cppreference: std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable))
   - **Expected result:** you can explain when the worker should wake up and when it should exit.

2) Implement `enqueue()` to push work and notify.
   Lock the mutex, push the task into the queue, then notify the condition variable. This ensures the worker wakes promptly. (Source: [cppreference: std::condition_variable::notify_one](https://en.cppreference.com/w/cpp/thread/condition_variable/notify_one))
   - **Expected result:** tasks enqueued from the main thread get processed by the worker.

3) Implement `stop()` to request shutdown.
   Set `stopped_ = true` under the lock, call `thread_.request_stop()`, and notify the condition variable. This wakes the worker and lets it exit once the queue is empty. (Source: [cppreference: std::jthread](https://en.cppreference.com/w/cpp/thread/jthread))
   - **Expected result:** the worker stops after draining remaining tasks.

4) Implement `run()` with correct wait logic.
   Use `cv_.wait(lock, predicate)` to sleep until there is work or a stop request. Drain tasks outside the lock to avoid holding the mutex during execution. Exit only when a stop is requested and the queue is empty. (Source: [cppreference: std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable))
   - **Expected result:** the worker thread does not busy-wait and exits cleanly.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex03_clean_shutdown`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex03_clean_shutdown --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: ensure `<condition_variable>` and `<thread>` are included and `#error` removed.
- If tests hang: verify you notify the condition variable on enqueue and on stop.

## 13) Stretch goals
- Add a bounded queue size and backpressure behavior.
- Add a timeout to the wait predicate and collect idle time metrics.
