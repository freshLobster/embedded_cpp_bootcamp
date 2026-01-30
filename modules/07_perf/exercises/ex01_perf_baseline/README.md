# 07_perf - ex01_perf_baseline

## 1) Title + Mission
Mission: implement a dot-product routine and use it as a baseline workload for performance measurements. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))

## 2) What you are building (plain English)
You are building a simple dot-product function that multiplies corresponding elements of two vectors and sums the result. This function serves as a stable baseline for perf tooling and timing comparisons. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))

## 3) Why it matters (embedded/robotics/defense relevance)
A baseline workload lets you validate profiling setup and detect regressions later. In robotics systems, you often need to prove that a math kernel meets a latency budget before it becomes part of a control loop. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))

## 4) Concepts (short lecture)
Dot product is a core linear algebra operation. Even a trivial implementation provides a predictable, repeatable runtime profile that is useful for perf tooling and microbenchmarking. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))

Linux `perf` is a standard profiler for CPU usage and can measure cycles, instructions, and call graphs. A stable baseline like dot product makes it easier to verify that `perf` is configured correctly. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))

Example (not your solution): minimal dot product with comments.
```cpp
int dot_product(const std::vector<int>& a, const std::vector<int>& b) {
    int sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        // Multiply each pair and accumulate.
        sum += a[i] * b[i];
    }
    return sum;
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
sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb perf
```

Verify perf:
```
perf --version
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
1) Read `learner/src/main.cpp` and define the dot-product contract.
   The function must take two vectors of equal length and return the sum of element-wise products. This is a deterministic workload: the same inputs must always produce the same output. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   - **Expected result:** you can write the dot-product formula in one line.

2) Implement `dot_product(const std::vector<int>&, const std::vector<int>&)`.
   Use a for-loop over indices and accumulate `a[i] * b[i]` into a local sum. Keep it simple and avoid extra allocations. This is the baseline you will profile. (Source: [cppreference: std::vector::operator[]](https://en.cppreference.com/w/cpp/container/vector/operator_at))
   - **Expected result:** dot_product({1,2,3},{4,5,6}) returns 32.

3) Implement `exercise()` to validate correctness.
   Create two small vectors with known values, call `dot_product`, and compare against the expected result. Return 0 for success and non-zero for failure. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   - **Expected result:** `exercise()` returns 0 when dot_product is correct.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check for off-by-one errors and confirm you used `a.size()` as the loop bound. (Source: [cppreference: std::vector::size](https://en.cppreference.com/w/cpp/container/vector/size))
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Run a baseline perf measurement (optional).
   Build with `-O2` if desired, then run `perf stat ./build_learner/ex01_perf_baseline`. Record the output so you can compare later. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))
   - **Expected result:** perf prints cycles/instructions without errors.

6) Capture artifacts.
   Save build output to `learner/artifacts/build.log`, test output to `learner/artifacts/ctest.log`, and perf output to `learner/artifacts/perf_stat.txt` if you ran perf. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))
   - **Expected result:** all expected log files exist.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log`, `ctest.log`.
- `perf_stat.txt` if you ran perf.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/07_perf/exercises/ex01_perf_baseline`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/07_perf/exercises/ex01_perf_baseline --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: ensure `<vector>` is included.
- Test fails: check the expected value and loop bounds.

## 13) Stretch goals
- Add input length validation and return 0 for mismatched sizes.
- Compare perf for debug vs release builds and save both outputs.
