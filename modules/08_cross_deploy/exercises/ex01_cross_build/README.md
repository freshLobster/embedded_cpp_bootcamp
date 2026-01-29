# 08_cross_deploy - ex01_cross_build

## 1) Title + Mission
Mission: Configure a cross-build using a CMake toolchain file and verify the target architecture settings.【https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html†L71-L71】
## 2) What you are building (plain English)
You are building a small utility that reports the target architecture, driven by a toolchain file that configures cross-compilation.【https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html†L71-L71】
## 3) Why it matters (embedded/robotics/defense relevance)
Cross-compiling is mandatory for embedded deployment; a correct toolchain file is the contract between your build and the target.【https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html†L71-L71】
## 4) Concepts (short lecture)
CMake uses a toolchain file to define the compiler and target settings for cross-compilation workflows.【https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html†L71-L71】

Validating the reported target architecture prevents subtle deployment failures on SBC or MCU targets.【https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html†L71-L71】
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
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex01_cross_build`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex01_cross_build --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`.

## 13) Stretch goals
- Add an edge-case test.
