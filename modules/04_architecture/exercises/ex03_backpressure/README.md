# 04_architecture - ex03_backpressure

## 1) Title + Mission
Mission: Implement a bounded queue that applies backpressure using a condition variable.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】
## 2) What you are building (plain English)
You are building a fixed-capacity queue that blocks producers when full and wakes consumers when items are available.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】
## 3) Why it matters (embedded/robotics/defense relevance)
Backpressure protects real-time pipelines from overload by forcing producers to respect downstream capacity limits.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】
## 4) Concepts (short lecture)
condition_variable lets threads block and wake based on queue state changes, which is essential for bounded producer/consumer designs.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】

Bounded queues are a core reliability tool because they turn unbounded memory growth into explicit, manageable waiting behavior.【https://en.cppreference.com/w/cpp/thread/condition_variable†L477-L477】
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
2) Implement the required logic in `exercise()`.
3) Rebuild and run tests.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex03_backpressure`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex03_backpressure --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
