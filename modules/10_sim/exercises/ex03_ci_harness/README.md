# 10_sim - ex03_ci_harness

## 1) Title + Mission
Mission: Generate a CI artifact manifest for simulation outputs and verification logs.【https://www.qemu.org/†L98-L98】
## 2) What you are building (plain English)
You are building a manifest file that records the artifacts produced by simulation-based tests, enabling deterministic CI checks.【https://www.qemu.org/†L98-L98】
## 3) Why it matters (embedded/robotics/defense relevance)
A manifest creates traceability from a test run to its logs and traces, which is essential for regression analysis.【https://www.qemu.org/†L98-L98】
## 4) Concepts (short lecture)
Simulation tools like QEMU are commonly used to automate pre-hardware validation, making artifact tracking a first-class CI requirement.【https://www.qemu.org/†L98-L98】

Explicit manifests prevent lost evidence and make audit trails reproducible under certification workflows.【https://www.qemu.org/†L98-L98】
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
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/10_sim/exercises/ex03_ci_harness`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/10_sim/exercises/ex03_ci_harness --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
