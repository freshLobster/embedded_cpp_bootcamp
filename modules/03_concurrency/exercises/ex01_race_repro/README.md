# 03_concurrency - ex01_race_repro

## 1) Title + Mission
Mission: Implement a thread-safe counter using atomic operations to eliminate data races under parallel increments.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】

## 2) What you are building (plain English)
You are building a counter that remains correct under concurrent updates by multiple threads using atomic operations instead of unsynchronized reads/writes.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】

## 3) Why it matters (embedded/robotics/defense relevance)
Data races can silently corrupt state in robotics pipelines; atomics provide a low-level, deterministic fix for simple shared counters.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】

## 4) Concepts (short lecture)
`std::atomic` provides atomic operations for integral types, enabling safe concurrent increments without external locking. This prevents undefined behavior caused by data races on shared variables.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】

Atomics are ideal for simple counters, flags, and sequence numbers that are shared between threads. They are cheaper than coarse-grained locks and still provide correctness for basic patterns.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】

Example (not your solution): a simple atomic counter.
```cpp
class Counter {
public:
    void increment() { value_.fetch_add(1); }
    int value() const { return value_.load(); }
private:
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
1) Open `learner/src/main.cpp` and review the `Counter` skeleton.
   - Identify where atomic operations should replace plain integer reads/writes.
   - **Expected result:** you can explain why a plain `int` is unsafe here.
2) Implement `increment()` and `value()` using atomic operations.
   - Use `fetch_add` for increments and `load` for reads.
   - **Expected result:** increments are thread-safe.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex01_race_repro`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex01_race_repro --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add a second counter that uses a mutex and compare performance under load.
- Track the expected final count in `exercise()` and assert it.
