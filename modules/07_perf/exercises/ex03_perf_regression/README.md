# 07_perf - ex03_perf_regression

## 1) Title + Mission
Mission: implement a string join routine that avoids unnecessary reallocations to prevent performance regressions. (Source: [cppreference: std::string::reserve](https://en.cppreference.com/w/cpp/string/basic_string/reserve))

## 2) What you are building (plain English)
You are building a function that joins a list of strings with commas. The goal is to do this efficiently by precomputing the final size and reserving capacity once. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))

## 3) Why it matters (embedded/robotics/defense relevance)
Small inefficiencies in hot paths can cause tail latency spikes. Repeated string reallocations are a classic hidden cost; avoiding them is a simple way to prevent regressions in telemetry or logging paths. (Source: [cppreference: std::string::reserve](https://en.cppreference.com/w/cpp/string/basic_string/reserve))

## 4) Concepts (short lecture)
`std::string` grows dynamically. If you repeatedly append without reserving, the string may reallocate multiple times, copying data each time. Reserving the final size once avoids these copies. (Source: [cppreference: std::string::reserve](https://en.cppreference.com/w/cpp/string/basic_string/reserve))

Precomputing total size is a common optimization: sum the lengths of all parts and account for delimiters. This ensures the buffer is large enough before the first append. (Source: [cppreference: std::string::size](https://en.cppreference.com/w/cpp/string/basic_string/size))

Example (not your solution): reserve then append.
```cpp
std::string out;
// Reserve once to avoid repeated reallocations.
out.reserve(total);
for (...) {
    // Append each part and delimiter in order.
    out += part;
    out += ',';
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
1) Read `learner/src/main.cpp` and identify the performance risk.
   The goal is to join strings without repeated reallocations. If you append blindly, `std::string` may reallocate multiple times and copy data repeatedly. Your implementation should reserve the final size up front. (Source: [cppreference: std::string::reserve](https://en.cppreference.com/w/cpp/string/basic_string/reserve))
   How: locate `join_with_commas` and note the TODO list. The missing steps map directly to how you will compute size, reserve, and append.
   - **Expected result:** you can explain why repeated `+=` without reserve can be slow.

2) Compute the total output length.
   Sum the sizes of all parts, then add the number of delimiters (parts.size() - 1). This gives the exact number of characters in the final string. (Source: [cppreference: std::string::size](https://en.cppreference.com/w/cpp/string/basic_string/size))
   How: write a loop that adds `parts[i].size()` to a `size_t total`. After the loop, add the delimiter count. Handle the empty vector case first to avoid underflow when `parts.size()` is 0.
   - **Expected result:** for {"a","b","c"} the total is 5 (3 letters + 2 commas).

3) Reserve the capacity once.
   Create the output string and call `out.reserve(total)` before appending. This ensures the string allocates once and does not grow repeatedly as you append. (Source: [cppreference: std::string::reserve](https://en.cppreference.com/w/cpp/string/basic_string/reserve))
   How: declare `std::string out;` then call `out.reserve(total);` before any appends. This is the key performance fix.
   - **Expected result:** appends do not trigger repeated reallocations.

4) Append parts and delimiters in order.
   Loop over the vector, append each part, and append a comma only between elements. This produces correct formatting and avoids a trailing comma. (Source: [cppreference: std::string::append](https://en.cppreference.com/w/cpp/string/basic_string/append))
   How: use a for-loop over indices. Append the part first, then if `i + 1 < parts.size()`, append `','`. This pattern avoids an extra comma at the end.
   - **Expected result:** joining {"a","b","c"} produces "a,b,c".

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check that you handle the empty-vector case and that your delimiter logic avoids a trailing comma. (Source: [cppreference: std::string](https://en.cppreference.com/w/cpp/string/basic_string))
   How: remove `#error`, rebuild, and run `ctest`. A failure often means you forgot the empty-input guard or miscounted commas.
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [cppreference: std::string::reserve](https://en.cppreference.com/w/cpp/string/basic_string/reserve))
   How: use `> file 2>&1` so both stdout and stderr are preserved.
   - **Expected result:** logs exist and contain command output.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/07_perf/exercises/ex03_perf_regression`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/07_perf/exercises/ex03_perf_regression --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: include `<string>` and `<vector>`.
- Test fails: verify delimiter logic and empty input handling.

## 13) Stretch goals
- Add a version that joins with a custom delimiter string.
- Add a perf comparison between reserved and non-reserved versions.
