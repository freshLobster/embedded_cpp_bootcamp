# 03_concurrency - ex02_deadlock

## 1) Title + Mission
Mission: Implement deadlock-free transfers by acquiring multiple mutexes safely with a scoped lock.【https://en.cppreference.com/w/cpp/thread/scoped_lock†L470-L470】

## 2) What you are building (plain English)
You are building a transfer function that locks two accounts without deadlock, using a single scoped lock to acquire both mutexes consistently.【https://en.cppreference.com/w/cpp/thread/scoped_lock†L470-L470】

## 3) Why it matters (embedded/robotics/defense relevance)
Deadlocks halt autonomy pipelines under load; structured lock acquisition makes the failure mode impossible rather than unlikely.【https://en.cppreference.com/w/cpp/thread/scoped_lock†L470-L470】

## 4) Concepts (short lecture)
`std::scoped_lock` can lock multiple mutexes at once and releases them automatically when the lock object goes out of scope. This avoids deadlocks that can occur when two threads lock the same mutexes in different orders.【https://en.cppreference.com/w/cpp/thread/scoped_lock†L470-L470】

Deadlock avoidance is an architectural concern. If every transfer function uses the same lock acquisition strategy, the system cannot form a cycle of waiting threads.

Example (not your solution): locking two accounts safely.
```cpp
void transfer(Account& a, Account& b, int amount) {
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
1) Open `learner/src/main.cpp` and inspect the `Account` and `transfer` stubs.
   - Identify where both mutexes must be held simultaneously.
   - **Expected result:** you can explain why naive lock ordering can deadlock.
2) Implement `transfer` using a single `std::scoped_lock`.
   - Do not lock one mutex at a time.
   - **Expected result:** transfers complete without deadlock.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex02_deadlock`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex02_deadlock --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a check to prevent overdraft and return a status code.
- Add a test that performs many transfers in both directions.
