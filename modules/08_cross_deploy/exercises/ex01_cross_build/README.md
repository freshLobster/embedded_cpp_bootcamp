# 08_cross_deploy - ex01_cross_build

## 1) Title + Mission
Mission: implement a target-architecture probe and use it to validate cross-compile outputs. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))

## 2) What you are building (plain English)
You are building a small function that reports the target architecture based on compiler-defined macros. This lets you confirm that your cross-compile toolchain is producing the expected target binary. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))

## 3) Why it matters (embedded/robotics/defense relevance)
Cross-compiling is standard in embedded pipelines. If you accidentally build for the host instead of the target, deployment fails or, worse, tests pass on the wrong platform. A simple architecture probe is a cheap safety check. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))

## 4) Concepts (short lecture)
CMake toolchains let you select a compiler and sysroot to build for a different target architecture. Your code can use predefined macros like `__aarch64__` and `__x86_64__` to identify the compile target at build time. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))

Compile-time architecture checks are not a substitute for runtime testing, but they provide a fast sanity check that your build configuration is correct before you deploy. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))

Example (not your solution): a simple architecture probe.
```cpp
std::string target_arch() {
#if defined(__aarch64__)
    return "aarch64";
#elif defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#else
    return "unknown";
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

If you plan to cross-compile for aarch64 on WSL, install a cross toolchain:
```
sudo apt-get install -y g++-aarch64-linux-gnu
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
1) Read `learner/src/main.cpp` and identify the expected outputs.
   The goal is to return a string describing the target architecture. The test fails if the result is "unknown", so your implementation must cover the expected targets. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))
   - **Expected result:** you can list which architectures you will detect.

2) Implement `target_arch()` with preprocessor checks.
   Use `#if defined(__aarch64__)` for ARM64, and `#elif defined(__x86_64__) || defined(_M_X64)` for x86_64. Return "unknown" only if none match. This ensures the test can identify the host or target. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))
   - **Expected result:** the function returns "x86_64" on typical WSL/Windows builds.

3) Implement `exercise()` to validate the probe.
   Call `target_arch()` and return non-zero only if it returns "unknown". This makes the test a sanity check for your macro logic. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))
   - **Expected result:** `exercise()` returns 0 on a known architecture.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If the test fails, verify that your macro names match the compiler you are using. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))
   - **Expected result:** `ctest` reports `100% tests passed`.

5) (Optional) Cross-compile to aarch64.
   Configure with a toolchain or set `CMAKE_CXX_COMPILER=aarch64-linux-gnu-g++`, then rebuild. Run `strings` or `file` on the output binary to confirm the architecture. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))
   - **Expected result:** the binary reports `aarch64` when cross-compiled.

6) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. Save `file` output to `learner/artifacts/arch.txt` if you cross-compiled. (Source: [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html))
   - **Expected result:** artifacts exist with command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log`, `ctest.log`.
- `arch.txt` if you cross-compiled.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex01_cross_build`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex01_cross_build --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: check include for `<string>`.
- Test fails: ensure your macro logic covers the current host architecture.

## 13) Stretch goals
- Add support for 32-bit ARM or x86.
- Emit a compile-time static_assert for unknown architectures.
