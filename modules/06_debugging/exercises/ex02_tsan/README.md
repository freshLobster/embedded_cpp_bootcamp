# 06_debugging - ex02_tsan

## 1) Title + Mission
Mission: eliminate a data race using a thread-safe log and validate it with ThreadSanitizer. (Source: [LLVM ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html))

## 2) What you are building (plain English)
You are building a log aggregator that can safely accept entries from multiple threads and then compute a correct sum. The implementation must be race-free and deterministic. (Source: [cppreference: std::mutex](https://en.cppreference.com/w/cpp/thread/mutex))

## 3) Why it matters (embedded/robotics/defense relevance)
Data races silently corrupt state in concurrent systems and can invalidate safety metrics or telemetry. ThreadSanitizer (TSan) helps you prove that your synchronization is correct before deployment. (Source: [LLVM ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html))

## 4) Concepts (short lecture)
ThreadSanitizer detects data races by instrumenting memory accesses in multithreaded programs. It is effective for catching races that only appear under load or specific timing. (Source: [LLVM ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html))

The simplest synchronization tool in C++ is `std::mutex` combined with `std::lock_guard`. Use it to serialize access to shared data structures like vectors. (Source: [cppreference: std::lock_guard](https://en.cppreference.com/w/cpp/thread/lock_guard))

Example (not your solution): protecting a log with a mutex.
```cpp
class ThreadSafeLog {
public:
    void log(int v) {
        // Lock before touching shared state.
        std::lock_guard<std::mutex> lock(m_);
        // Push the new entry while holding the lock.
        entries_.push_back(v);
    }
private:
    // Mutex guards the vector below.
    std::mutex m_;
    std::vector<int> entries_;
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

Verify clang for TSan:
```
clang++ --version
```
Expected output: a version string such as `clang version 14.x`.

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

Optional TSan build (WSL/Linux):
```
cmake -S learner -B build_tsan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fsanitize=thread"
cmake --build build_tsan
ctest --test-dir build_tsan --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Read `learner/src/main.cpp` and identify the shared state.
   The shared state is the log container that multiple threads will write into. Without synchronization, this causes data races and undefined behavior. Your goal is to protect all accesses to shared state with a mutex. (Source: [cppreference: std::mutex](https://en.cppreference.com/w/cpp/thread/mutex))
   How: locate the `ThreadSafeLog` class and note which member holds the entries. Then find each method that touches that member. Those methods are the ones that must lock.
   - **Expected result:** you can point to the exact data structure that needs protection and the methods that access it.

2) Define a `ThreadSafeLog` class with a mutex and a vector.
   Store entries in a `std::vector<int>` and guard it with a `std::mutex`. This establishes the synchronization primitive you will use for both writes and reads. (Source: [cppreference: std::lock_guard](https://en.cppreference.com/w/cpp/thread/lock_guard))
   How: ensure the mutex is a member of the class, not a local variable. A local mutex would only protect a single call, not the shared state.
   - **Expected result:** the class has a clear ownership boundary and a single lock.

3) Implement `log(int v)` with a lock guard.
   Use `std::lock_guard<std::mutex>` to lock the mutex before pushing to the vector. Release happens automatically when the guard leaves scope. This prevents concurrent writes from corrupting the vector. (Source: [cppreference: std::lock_guard](https://en.cppreference.com/w/cpp/thread/lock_guard))
   How: add `std::lock_guard<std::mutex> lock(m_);` as the first line in `log`, then call `entries_.push_back(v);`. Keep the critical section short and do not call other functions from inside the lock unless necessary.
   - **Expected result:** multiple threads can call `log` without races or crashes.

4) Implement `sum()` with the same lock.
   Protect reads with the same mutex so you are not reading while another thread writes. Compute the sum deterministically inside the critical section. (Source: [cppreference: std::mutex](https://en.cppreference.com/w/cpp/thread/mutex))
   How: lock the mutex, create a local `int total = 0`, iterate over `entries_`, and return the total. Do not modify `entries_` while summing.
   - **Expected result:** the sum equals the number of logged entries.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check that you used the mutex in both `log` and `sum`. A missing lock in either function still leaves a data race. (Source: [LLVM ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html))
   How: remove the `#error` line only after `log` and `sum` are complete, then rebuild and run `ctest`. The self-test creates multiple threads, so missing locks usually show up immediately.
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Run TSan to confirm the race is gone (optional but recommended).
   Build with `-fsanitize=thread` and run the tests. TSan will report data races if any remain. Save the output if it reports issues. (Source: [LLVM ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html))
   How: configure a separate build:
   `cmake -S learner -B build_tsan -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-fsanitize=thread -fno-omit-frame-pointer"`
   Then run `ctest --test-dir build_tsan --output-on-failure`.
   - **Expected result:** no data race warnings.

7) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. Save `tsan.log` if you run TSan. (Source: [LLVM ThreadSanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html))
   How: run:
   `cmake --build build_learner > learner/artifacts/build.log 2>&1`
   `ctest --test-dir build_learner --output-on-failure > learner/artifacts/ctest.log 2>&1`
   `ctest --test-dir build_tsan --output-on-failure > learner/artifacts/tsan.log 2>&1` (if you ran TSan)
   - **Expected result:** all required logs exist in the artifacts folder.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.
- `tsan.log` if you ran TSan.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/06_debugging/exercises/ex02_tsan`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/06_debugging/exercises/ex02_tsan --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: check includes for `<mutex>` and `<vector>`.
- Test fails: ensure both `log` and `sum` take the lock.

## 13) Stretch goals
- Add a `size()` method that also uses the lock.
- Add a TSan run that intentionally uses an unsafe version to capture a report.
