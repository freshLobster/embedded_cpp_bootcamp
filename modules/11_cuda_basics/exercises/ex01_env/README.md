# 11_cuda_basics - ex01_env

## 1) Title + Mission
Mission: implement a CUDA environment probe that cleanly reports whether CUDA compilation is enabled. (Source: [CUDA NVCC documentation](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html))

## 2) What you are building (plain English)
You are building a small compile-time check that returns true when the code is compiled with NVCC and false otherwise. This is the simplest building block for CUDA-enabled code paths. (Source: [CUDA NVCC documentation](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html))

## 3) Why it matters (embedded/robotics/defense relevance)
CUDA is often optional in mixed CPU/GPU deployments. You must reliably detect whether GPU code is available and select the correct code path to avoid runtime failures. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

## 4) Concepts (short lecture)
When compiling with NVCC, the macro `__CUDACC__` is defined. This is the standard way to detect CUDA compilation at build time and to conditionally compile GPU-specific code. (Source: [CUDA NVCC documentation](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html))

Compile-time detection is different from runtime device checks. This exercise focuses on build-time selection so that the same codebase can compile with or without CUDA. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

Example (not your solution): compile-time CUDA check.
```cpp
constexpr bool cuda_available() {
#if defined(__CUDACC__)
    return true;
#else
    return false;
#endif
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

If CUDA is available, verify NVCC:
```
nvcc --version
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
1) Read `learner/src/main.cpp` and locate the CUDA detection function.
   The exercise expects a compile-time check, not a runtime device query. Your implementation should rely on `__CUDACC__` which is defined only when NVCC is compiling the translation unit. (Source: [CUDA NVCC documentation](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html))
   - **Expected result:** you can explain the difference between build-time and runtime detection.

2) Implement `cuda_available()` using preprocessor checks.
   Use `#if defined(__CUDACC__)` to return true and false otherwise. Keep the function `constexpr` so it can be evaluated at compile time. (Source: [CUDA NVCC documentation](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html))
   - **Expected result:** the function returns true only when compiled with NVCC.

3) Implement `exercise()` to validate the check.
   Compare `cuda_available()` against itself as a sanity check and return 0 if consistent. This is a simple guard that ensures the function compiles in both modes. (Source: [CUDA NVCC documentation](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html))
   - **Expected result:** `exercise()` returns 0 regardless of CUDA availability.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, ensure you included the preprocessor logic and that the function is `constexpr`. (Source: [CUDA NVCC documentation](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html))
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. If you verified NVCC, note the version in `learner/artifacts/nvcc_version.txt`. (Source: [CUDA NVCC documentation](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html))
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.
- `nvcc_version.txt` if CUDA is installed.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex01_env`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/11_cuda_basics/exercises/ex01_env --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: ensure you used `#if defined(__CUDACC__)`.
- Test fails: ensure the function is `constexpr` and returns both paths.

## 13) Stretch goals
- Add a runtime device count check guarded behind `#ifdef __CUDACC__`.
- Add a compile-time static_assert for CUDA builds.
