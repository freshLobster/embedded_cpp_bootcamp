# 04_architecture - ex02_tracing

## 1) Title + Mission
Mission: Implement tracing spans with monotonic timestamps to support deterministic latency analysis.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】
## 2) What you are building (plain English)
You are building a span type that records start/stop timestamps using a monotonic clock so elapsed durations remain stable across runs.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】
## 3) Why it matters (embedded/robotics/defense relevance)
Tracing is only useful if timestamps are monotonic and comparable; otherwise latency analysis becomes noisy and misleading.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】
## 4) Concepts (short lecture)
std::chrono::steady_clock is monotonic, so its time points never go backward and are appropriate for latency measurement.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】

std::chrono::duration represents a time interval, which is the correct type for expressing span length and budget calculations.【https://en.cppreference.com/w/cpp/chrono/duration†L450-L450】
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
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex02_tracing`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/04_architecture/exercises/ex02_tracing --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
