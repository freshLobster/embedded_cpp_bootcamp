# 03_concurrency - ex02_deadlock

## 1) Title + Mission
Mission: implement deadlock-free transfers by locking multiple mutexes safely using `std::scoped_lock`. (Source: [cppreference: std::scoped_lock](https://en.cppreference.com/w/cpp/thread/scoped_lock))

## 2) What you are building (plain English)
You are building a transfer function that moves funds between two accounts while two threads run in opposite directions. Your job is to lock both accounts without deadlock. (Source: [cppreference: std::scoped_lock](https://en.cppreference.com/w/cpp/thread/scoped_lock))

## 3) Why it matters (embedded/robotics/defense relevance)
Deadlocks freeze control loops and can bring down autonomous systems under load. The safest way to prevent them is to structure your code so deadlock is impossible, not just unlikely. (Source: [cppreference: std::scoped_lock](https://en.cppreference.com/w/cpp/thread/scoped_lock))

## 4) Concepts (short lecture)
Deadlock happens when two threads each hold a lock and wait for the other lock, creating a cycle. The typical cause is locking resources in inconsistent order. (Source: [cppreference: std::mutex](https://en.cppreference.com/w/cpp/thread/mutex))

`std::scoped_lock` can lock multiple mutexes at once using a deadlock-avoidance algorithm. It also unlocks automatically when it goes out of scope, which aligns with RAII practices. (Source: [cppreference: std::scoped_lock](https://en.cppreference.com/w/cpp/thread/scoped_lock))

Example (not your solution): lock two mutexes with a single `scoped_lock`.
```cpp
void safe_transfer(Account& a, Account& b, int amount) {
    // scoped_lock atomically acquires both mutexes.
    std::scoped_lock lock(a.m, b.m);
    a.balance -= amount;
    b.balance += amount;
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
1) Read `learner/src/main.cpp` and understand the deadlock scenario.
   Two threads call `transfer` in opposite directions. If you lock `a.m` then `b.m` in one thread and `b.m` then `a.m` in another, you can deadlock. The fix is to lock both mutexes in one atomic step. (Source: [cppreference: std::scoped_lock](https://en.cppreference.com/w/cpp/thread/scoped_lock))
   - **Expected result:** you can explain why naive lock ordering can deadlock here.

2) Implement `transfer` using `std::scoped_lock`.
   Construct `std::scoped_lock lock(a.m, b.m);` to acquire both mutexes safely. Then update balances while the lock is held. This ensures total balance remains constant and prevents deadlock. (Source: [cppreference: std::scoped_lock](https://en.cppreference.com/w/cpp/thread/scoped_lock))
   - **Expected result:** transfers complete under load without hanging.

3) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   - **Expected result:** `ctest` reports `100% tests passed`.

4) Capture artifacts.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex02_deadlock`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex02_deadlock --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: ensure you included `<mutex>` and removed `#error`.
- If tests hang: verify you used `std::scoped_lock` and not separate `lock()` calls.

## 13) Stretch goals
- Add a transfer validation that rejects negative balances.
- Add a stress test with more threads and a larger iteration count.
