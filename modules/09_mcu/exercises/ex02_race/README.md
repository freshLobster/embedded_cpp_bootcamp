# 09_mcu - ex02_race

## 1) Title + Mission
Mission: implement a thread-safe shared counter and validate that concurrent updates are race-free. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))

## 2) What you are building (plain English)
You are building a shared counter that can be incremented by multiple threads without losing updates. This models ISR/task interactions in MCU firmware. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))

## 3) Why it matters (embedded/robotics/defense relevance)
Race conditions are common in firmware where interrupts and tasks update shared state. A correct atomic counter is a baseline skill for safe telemetry, scheduling, and diagnostics. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))

## 4) Concepts (short lecture)
`std::atomic` provides race-free operations for shared variables. For counters, `fetch_add` and `load` are the simplest correct primitives. (Source: [cppreference: std::atomic::fetch_add](https://en.cppreference.com/w/cpp/atomic/atomic/fetch_add))

Even though this is a desktop test, the same pattern applies to MCU firmware: shared state must be updated atomically or under a lock to avoid lost updates. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))

Example (not your solution): atomic counter with comments.
```cpp
class SharedCounter {
public:
    // Atomic increment (relaxed ordering is enough for a simple counter).
    void increment() { value_.fetch_add(1, std::memory_order_relaxed); }
    // Atomic load of the current value.
    int value() const { return value_.load(std::memory_order_relaxed); }
private:
    // Shared state protected by atomic operations.
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

## 7) Build instructions (learner + solution)
### Learner path (fails initially until you implement)
```
cmake -S learner -B build_learner -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_learner
ctest --test-dir build_learner --output-on-failure
```

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Read `learner/src/main.cpp` and identify the shared state.
   The counter must be updated by multiple threads concurrently. This is exactly the kind of shared state that is unsafe without atomic operations. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))
   How: locate the `SharedCounter` class and the `value_` member. This is the state that multiple threads will touch.
   - **Expected result:** you can describe why a plain `int` would lose updates.

2) Implement `SharedCounter` using `std::atomic<int>`.
   Store the counter in an atomic and provide `increment()` and `value()` methods. Use `fetch_add(1)` and `load()` so operations are race-free. (Source: [cppreference: std::atomic::fetch_add](https://en.cppreference.com/w/cpp/atomic/atomic/fetch_add))
   How: in `increment()`, call `value_.fetch_add(1, std::memory_order_relaxed);`. In `value()`, return `value_.load(std::memory_order_relaxed);`. Relaxed ordering is enough for a pure counter.
   - **Expected result:** increments are not lost under concurrency.

3) Implement `exercise()` to validate the counter.
   Spawn multiple threads that call `increment()` many times. After joining, check that the final count equals the expected number of increments. (Source: [cppreference: std::thread](https://en.cppreference.com/w/cpp/thread/thread))
   How: keep the thread count and iteration count small but deterministic (e.g., 4 threads * 1000 increments). This makes the expected total clear.
   - **Expected result:** the final value equals threads * iterations.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check that you used atomic operations in both methods and that all threads are joined. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))
   How: remove the `#error` line, rebuild, and run `ctest`. If the result is less than expected, your atomic operations are missing or not used.
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [cppreference: std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic))
   How: redirect output with `> file 2>&1` so both stdout and stderr are captured.
   - **Expected result:** logs exist and contain your command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex02_race`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/09_mcu/exercises/ex02_race --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: include `<atomic>` and `<thread>`.
- Test fails: ensure you used `fetch_add` and joined threads.

## 13) Stretch goals
- Add a second counter using a mutex and compare results.
- Run ThreadSanitizer and save a report.
