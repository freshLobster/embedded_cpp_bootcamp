# 11_cuda_basics - ex02_cpu_gpu_parity

## 1) Title + Mission
Mission: Implement a CPU reference vector add used for parity checks in a self-contained exercise that builds and tests locally.

## 2) What you are building (plain English)
You are building a CPU reference vector add used for parity checks. The implementation lives in `learner/src/main.cpp`, and the tests in the same file validate the required behavior.

## 3) Why it matters (embedded/robotics/defense relevance)
GPU work requires a clear CPU baseline and explicit resource ownership. This exercise enforces those practices even when CUDA is not available.

## 4) Concepts (short lecture)
GPU kernels must match CPU reference behavior. Implementing a clear CPU baseline is the first step toward parity testing. This exercise builds that baseline.

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
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex02_cpu_gpu_parity`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex02_cpu_gpu_parity --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
