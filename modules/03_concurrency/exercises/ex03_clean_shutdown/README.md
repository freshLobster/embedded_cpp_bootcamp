# 03_concurrency - ex03_clean_shutdown

## 1) Title + Mission
Mission: Implement a worker thread that drains work and shuts down cleanly using condition variables and cooperative cancellation.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】【https://en.cppreference.com/w/cpp/thread/jthread†L460-L460】
## 2) What you are building (plain English)
You are building a worker that blocks on a condition variable, processes tasks, and exits when a stop request is issued.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】【https://en.cppreference.com/w/cpp/thread/jthread†L460-L460】
## 3) Why it matters (embedded/robotics/defense relevance)
Safe shutdown is as important as fast startup; autonomous systems must stop cleanly without losing data or leaving threads running.【https://en.cppreference.com/w/cpp/thread/jthread†L460-L460】
## 4) Concepts (short lecture)
std::condition_variable is a synchronization primitive used with a mutex to block and wake threads when work becomes available.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】

std::jthread represents a joinable thread of execution and integrates with cooperative stop mechanisms for clean shutdown.【https://en.cppreference.com/w/cpp/thread/jthread†L460-L460】
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
   - Identify the required behavior for a worker thread that drains a task queue and stops cleanly on request.
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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex03_clean_shutdown`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/03_concurrency/exercises/ex03_clean_shutdown --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an extra test case that exercises an edge condition.
