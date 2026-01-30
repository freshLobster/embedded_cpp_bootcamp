# 10_sim - ex03_ci_harness

## 1) Title + Mission
Mission: build a simple artifact manifest generator for CI-style simulation runs. (Source: [CTest documentation](https://cmake.org/cmake/help/latest/manual/ctest.1.html))

## 2) What you are building (plain English)
You are building a function that takes a list of artifact filenames and returns a JSON-like manifest string. This mirrors how CI systems collect logs and outputs from simulation runs. (Source: [CTest documentation](https://cmake.org/cmake/help/latest/manual/ctest.1.html))

## 3) Why it matters (embedded/robotics/defense relevance)
Simulation pipelines generate logs, traces, and reports that must be collected consistently. A manifest is a simple contract between the simulator and the CI system, ensuring nothing is lost. (Source: [CTest documentation](https://cmake.org/cmake/help/latest/manual/ctest.1.html))

## 4) Concepts (short lecture)
CTest is the testing driver used by CMake. It is commonly integrated into CI to run tests and collect artifacts. A manifest provides a machine-readable summary of outputs. (Source: [CTest documentation](https://cmake.org/cmake/help/latest/manual/ctest.1.html))

Building a JSON-like string by hand is acceptable for a small exercise, but it must be deterministic and correctly formatted so downstream tools can parse it. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))

Example (not your solution): manifest format with comments.
```cpp
std::string out = "{\"artifacts\":[\"a.log\",\"b.csv\"]}";
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
1) Read `learner/src/main.cpp` and confirm the expected JSON shape.
   The manifest must look like `{"artifacts":["a.log","b.csv"]}`. The tests only check for substring presence, but you should still produce a valid JSON-like structure. (Source: [CTest documentation](https://cmake.org/cmake/help/latest/manual/ctest.1.html))
   - **Expected result:** you can write the exact output string for a sample list.

2) Build the manifest string step by step.
   Start with `{"artifacts":[`, then append each artifact in quotes. Insert commas between elements and close with `]}`. This ensures deterministic formatting. (Source: [cppreference: std::string::append](https://en.cppreference.com/w/cpp/string/basic_string/append))
   - **Expected result:** a list of two artifacts produces `{"artifacts":["a.log","b.csv"]}`.

3) Handle empty lists gracefully.
   If the list is empty, the manifest should still be valid: `{"artifacts":[]}`. Do not add trailing commas. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))
   - **Expected result:** empty input yields a correctly formatted empty array.

4) Implement `exercise()` to validate the manifest.
   Create a list with two filenames, call the manifest function, and ensure both filenames appear in the string. Return 0 on success. (Source: [cppreference: std::string::find](https://en.cppreference.com/w/cpp/string/basic_string/find))
   - **Expected result:** `exercise()` returns 0 when the manifest includes both names.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check your quote placement and comma logic. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [CTest documentation](https://cmake.org/cmake/help/latest/manual/ctest.1.html))
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/10_sim/exercises/ex03_ci_harness`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/10_sim/exercises/ex03_ci_harness --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: include `<string>` and `<vector>`.
- Test fails: verify commas and quotes are placed correctly.

## 13) Stretch goals
- Output pretty-printed JSON with indentation.
- Add a timestamp field to the manifest.
