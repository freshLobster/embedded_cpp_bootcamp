# 02_memory - ex02_uaf_fix

## 1) Title + Mission
Mission: Fix a use-after-free pattern by enforcing correct ownership and lifetime in the API you implement.【https://en.cppreference.com/w/cpp/language/lifetime†L494-L494】
## 2) What you are building (plain English)
You are building a safe factory and access path for a payload so that consumers never access objects after their lifetime ends.【https://en.cppreference.com/w/cpp/language/lifetime†L494-L494】
## 3) Why it matters (embedded/robotics/defense relevance)
Use-after-free is undefined behavior with catastrophic consequences; eliminating it requires explicit ownership and a correct mental model of object lifetime.【https://en.cppreference.com/w/cpp/language/lifetime†L494-L494】
## 4) Concepts (short lecture)
C++ object lifetimes begin and end at precise points, and accessing an object after its lifetime ends is undefined behavior that can surface as rare field failures.【https://en.cppreference.com/w/cpp/language/lifetime†L494-L494】

AddressSanitizer is a practical tool that detects memory errors like use-after-free during testing, making lifetime bugs observable early.【https://clang.llvm.org/docs/AddressSanitizer.html†L85-L85】
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

Run these in **this exercise folder**:
```
cmake --version
```
Expected output (example): `cmake version 3.22.1`.

```
c++ --version
```
Expected output (example): `g++ (Ubuntu 11.4.0)` or `clang version 14.x`.

If you will use Ninja:
```
ninja --version
```
Expected output: a version number (e.g., `1.10.1`). If Ninja is missing, use the Visual Studio generator on Windows.

## 7) Build instructions (learner + solution)
### Learner path (fails initially until you implement)
```
cmake -S learner -B build_learner -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_learner
ctest --test-dir build_learner --output-on-failure
```
Expected initial failure: compilation error due to `#error TODO_implement_exercise`.

Windows (no Ninja):
```
cmake -S learner -B build_learner -G "Visual Studio 17 2022"
cmake --build build_learner --config Debug
ctest --test-dir build_learner -C Debug --output-on-failure
```

### Solution path (must pass immediately)
```
cmake -S solution -B build_solution -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build_solution
ctest --test-dir build_solution --output-on-failure
```
Expected output: `100% tests passed`.

Windows (no Ninja):
```
cmake -S solution -B build_solution -G "Visual Studio 17 2022"
cmake --build build_solution --config Debug
ctest --test-dir build_solution -C Debug --output-on-failure
```

## 8) Step-by-step implementation instructions
1) Open `learner/src/main.cpp` and read the TODOs.
   - Identify the required behavior for a safe factory that returns owned data without use-after-free.
   - **Expected result:** you can explain what `exercise()` must verify before it returns success.
2) Implement the required logic in `exercise()`.
   - Introduce any helper classes or functions directly in `learner/src/main.cpp` or in `learner/include/` if you prefer.
   - **Expected result:** the code compiles without `#error` and the logic enforces the required behavior.
3) Rebuild and run tests.
   - Run `cmake --build build_learner` and `ctest --test-dir build_learner --output-on-failure`.
   - **Expected result:** tests pass and return 0.
4) Save artifacts.
   - Copy build and test output to `learner/artifacts/build.log` and `learner/artifacts/ctest.log`.
   - **Expected result:** those files exist and contain your command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.
- If it fails, stop and read `troubleshooting.md`.

## 10) Artifacts to save
Place these in `learner/artifacts/`:
- `build.log` - stdout/stderr from the build step.
- `ctest.log` - stdout/stderr from the test step.

## 11) Grade this exercise
- Learner attempt:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex02_uaf_fix`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/02_memory/exercises/ex02_uaf_fix --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add an extra test case that exercises an edge condition.
- Move helper logic into `learner/include/` and keep the interface clean.
