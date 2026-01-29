# 01_foundations - ex02_message_bus_view

## 1) Title + Mission
Mission: Implement a const-correct, non-owning bus view that exposes subscribers without copying or allowing mutation.【https://en.cppreference.com/w/cpp/container/span†L400-L400】
## 2) What you are building (plain English)
You are building a read-only view type that provides non-owning access to subscriber metadata, so callers can inspect without taking ownership or modifying the underlying storage.【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】
## 3) Why it matters (embedded/robotics/defense relevance)
In autonomy pipelines, passing views instead of owning copies preserves performance and keeps ownership boundaries explicit, which reduces accidental allocations and data races.【https://en.cppreference.com/w/cpp/container/span†L400-L400】
## 4) Concepts (short lecture)
Non-owning view types such as span or string_view describe contiguous ranges without owning them, enabling zero-copy inspection when you only need read access.【https://en.cppreference.com/w/cpp/container/span†L400-L400】【https://en.cppreference.com/w/cpp/string/basic_string_view†L389-L389】

Clear ownership boundaries improve modular architecture because the producer remains responsible for data lifetime while consumers use read-only views.【https://en.cppreference.com/w/cpp/container/span†L400-L400】
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
   - Identify the required behavior for a const-correct read-only view over a message bus subscriber list.
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
Example snippet for `ctest.log`:
```
1/1 Test #1: ...   Passed
100% tests passed, 0 tests failed out of 1
```

## 11) Grade this exercise
- Learner attempt:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex02_message_bus_view`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/01_foundations/exercises/ex02_message_bus_view --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add an extra test case that exercises an edge condition.
- Refactor helper logic into `learner/include/` and keep the interface clean.
