# 10_sim - ex02_renode

## 1) Title + Mission
Mission: parse a Renode-style log and count initialized peripherals to validate simulation setup. (Source: [Renode documentation](https://renode.readthedocs.io/))

## 2) What you are building (plain English)
You are building a function that counts how many times a keyword appears in a log. This is used to confirm that expected peripherals were initialized in simulation. (Source: [Renode documentation](https://renode.readthedocs.io/))

## 3) Why it matters (embedded/robotics/defense relevance)
Simulation environments must mirror hardware configuration. A quick log-based check prevents you from running tests on an incorrectly configured model. (Source: [Renode documentation](https://renode.readthedocs.io/))

## 4) Concepts (short lecture)
Renode emits logs when peripherals are created or attached. Counting these entries is a simple validation technique that can be run in CI. (Source: [Renode documentation](https://renode.readthedocs.io/))

String scanning using `find` in a loop is an efficient and deterministic way to count substring occurrences. (Source: [cppreference: std::string_view::find](https://en.cppreference.com/w/cpp/string/basic_string_view/find))

Example (not your solution): count occurrences.
```cpp
int count = 0;
size_t pos = 0;
while ((pos = log.find(token, pos)) != std::string_view::npos) {
    ++count;
    pos += token.size();
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
1) Read `learner/src/main.cpp` and identify the token to count.
   The log parsing function looks for a specific substring (e.g., "peripheral"). Your job is to count every occurrence in the log string. (Source: [cppreference: std::string_view::find](https://en.cppreference.com/w/cpp/string/basic_string_view/find))
   - **Expected result:** you can name the token and explain why it is important.

2) Implement a loop that repeatedly calls `find`.
   Start at position 0, call `find(token, pos)`, and if found, increment the count and advance `pos` by `token.size()`. This avoids infinite loops and counts non-overlapping occurrences. (Source: [cppreference: std::string_view::find](https://en.cppreference.com/w/cpp/string/basic_string_view/find))
   - **Expected result:** the counter increments once per token occurrence.

3) Implement `exercise()` to validate the count.
   Use a short log string containing two "peripheral" lines and ensure the function returns 2. Return 0 for success. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   - **Expected result:** `exercise()` returns 0.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check your loop increment and ensure you are not skipping or double-counting occurrences. (Source: [cppreference: std::string_view::find](https://en.cppreference.com/w/cpp/string/basic_string_view/find))
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [Renode documentation](https://renode.readthedocs.io/))
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/10_sim/exercises/ex02_renode`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/10_sim/exercises/ex02_renode --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: ensure `<string_view>` is included.
- Test fails: check token value and loop logic.

## 13) Stretch goals
- Add case-insensitive matching.
- Add validation for a minimum expected peripheral count.
