# 03_concurrency - ex01_race_repro

## 1) Title + Mission
Mission: Implement a thread-safe counter using atomic operations to eliminate data races under parallel increments.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】
## 2) What you are building (plain English)
You are building a counter that remains correct under concurrent updates by multiple threads using atomic operations instead of unsynchronized reads/writes.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】
## 3) Why it matters (embedded/robotics/defense relevance)
Data races can silently corrupt state in robotics pipelines; atomics provide a low-level, deterministic fix for simple shared counters.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】
## 4) Concepts (short lecture)
std::atomic provides atomic operations for integral types, enabling safe concurrent increments without external locking.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】

When concurrency is simple, atomics are often the cheapest safe synchronization primitive and avoid the overhead of coarse locks.【https://en.cppreference.com/w/cpp/atomic/atomic†L603-L603】
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
Expected initial failure: compilation error due to `#error TODO_implement_exercise`.

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Open `learner/src/main.cpp` and read the TODOs.
   - Identify the required behavior for a thread-safe counter that increments correctly under contention.
   - **Expected result:** you can explain what `exercise()` must verify before it returns success.
2) Implement the required logic in `exercise()`.
   - Introduce helper classes or synchronization primitives as needed.
   - **Expected result:** the code compiles without `#error` and the logic enforces the required behavior.
3) Rebuild and run tests.
   - Run `cmake --build build_learner` and `ctest --test-dir build_learner --output-on-failure`.
   - **Expected result:** tests pass and return 0.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
Place these in `learner/artifacts/`:
- `build.log` - stdout/stderr from the build step.
- `ctest.log` - stdout/stderr from the test step.

## 11) Grade this exercise
- Learner attempt:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex01_race_repro`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex01_race_repro --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an extra test case that exercises an edge condition.
