# 11_cuda_basics - ex01_env

## 1) Title + Mission
Mission: Detect CUDA availability and report the environment readiness for GPU execution.【https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html†L69-L69】
## 2) What you are building (plain English)
You are building an environment probe that determines whether the CUDA programming model can be used on the current system.【https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html†L69-L69】
## 3) Why it matters (embedded/robotics/defense relevance)
GPU code must fail fast when toolchains or drivers are missing; explicit detection avoids silent fallbacks.【https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html†L69-L69】
## 4) Concepts (short lecture)
The CUDA programming guide defines the programming model and execution environment for GPU kernels, which drives environment requirements.【https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html†L69-L69】

Validating the environment early prevents wasted profiling time on configurations that cannot run GPU code.【https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html†L69-L69】
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
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex01_env`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex01_env --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
