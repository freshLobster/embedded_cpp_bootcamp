# 03_concurrency - ex03_clean_shutdown

## 1) Title + Mission
Mission: Implement a worker thread that drains work and shuts down cleanly using condition variables and cooperative cancellation.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】【https://en.cppreference.com/w/cpp/thread/jthread†L460-L460】

## 2) What you are building (plain English)
You are building a worker that blocks on a condition variable, processes tasks, and exits when a stop request is issued.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】【https://en.cppreference.com/w/cpp/thread/jthread†L460-L460】

## 3) Why it matters (embedded/robotics/defense relevance)
Safe shutdown is as important as fast startup; autonomous systems must stop cleanly without losing data or leaving threads running.【https://en.cppreference.com/w/cpp/thread/jthread†L460-L460】

## 4) Concepts (short lecture)
`std::condition_variable` is a synchronization primitive that blocks a thread until a condition becomes true, then wakes it. It is the standard way to implement producer/consumer queues without busy-waiting.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】

`std::jthread` represents a joinable thread that can be requested to stop via a stop token. It integrates a clean shutdown path into the thread object itself and ensures the thread is joined on destruction.【https://en.cppreference.com/w/cpp/thread/jthread†L460-L460】

Example (not your solution): a worker loop that drains tasks until stop is requested.
```cpp
void run(std::stop_token st) {
    while (!st.stop_requested()) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(m_);
            cv_.wait(lock, [&] { return st.stop_requested() || !tasks_.empty(); });
            if (st.stop_requested() && tasks_.empty()) break;
            task = std::move(tasks_.front());
            tasks_.pop();
        }
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
1) Open `learner/src/main.cpp` and review the `Worker` skeleton.
   - Identify which data members need to be protected by a mutex.
   - **Expected result:** you can describe how tasks move from the queue to execution.
2) Implement `enqueue` to push tasks and notify the worker.
   - Hold the lock while modifying the queue.
   - **Expected result:** enqueued tasks wake the worker thread.
3) Implement `run` to wait on the condition variable and drain tasks.
   - Wait until either a stop is requested or the queue is non-empty.
   - Exit when stop is requested and the queue is empty.
   - **Expected result:** tasks execute, and shutdown is clean.
4) Implement `stop` to request stop and notify the worker.
   - Ensure repeated calls are safe.
   - **Expected result:** worker thread exits without deadlock.
5) Remove `#error TODO_implement_exercise`, build, and run tests.
6) Save artifacts.

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
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a bounded queue and have `enqueue` block when full.
- Add metrics for queue depth and number of tasks processed.
