# 07_perf - ex02_flamegraph

## 1) Title + Mission
Mission: Build a call-stack-heavy workload and generate a flame graph to visualize hot paths.【https://www.brendangregg.com/flamegraphs.html†L212-L212】
## 2) What you are building (plain English)
You are building a function chain that produces a predictable call stack so profiling output maps clearly to code structure.【https://www.brendangregg.com/flamegraphs.html†L212-L212】
## 3) Why it matters (embedded/robotics/defense relevance)
Flame graphs provide an intuitive view of where CPU time is spent, making them a standard tool for systems performance work.【https://www.brendangregg.com/flamegraphs.html†L212-L212】
## 4) Concepts (short lecture)
Flame graphs are a visualization technique that summarizes stack traces to highlight the dominant costs in a workload.【https://www.brendangregg.com/flamegraphs.html†L212-L212】

A repeatable call structure lets you verify your profiling pipeline before applying it to production workloads.【https://www.brendangregg.com/flamegraphs.html†L212-L212】
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
1) Open `learner/src/main.cpp` and read the TODOs.
2) Implement the required logic in `exercise()`.
3) Rebuild and run tests.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/07_perf/exercises/ex02_flamegraph`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/07_perf/exercises/ex02_flamegraph --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
