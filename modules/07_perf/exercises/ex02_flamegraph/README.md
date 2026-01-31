# 07_perf - ex02_flamegraph

## 1) Title + Mission
Mission: implement a multi-level call chain that produces a clear stack profile suitable for flamegraph practice. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))

## 2) What you are building (plain English)
You are building a small stack of functions that call each other in sequence. The goal is to create a call graph with distinct frames so profiling tools show a meaningful stack trace. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))

## 3) Why it matters (embedded/robotics/defense relevance)
Profilers are only useful if your code produces meaningful call stacks. In robotics, flamegraphs are used to find hot paths in perception or control pipelines; you must first know how to generate and interpret stack traces. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))

## 4) Concepts (short lecture)
Sampling profilers like `perf` collect call stacks periodically and aggregate them. A clean, layered call chain makes it easy to verify that the profiler is working and that symbols are resolved correctly. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))

Flamegraphs visualize stack traces by collapsing identical call paths. Even a small program can produce a meaningful flamegraph if it has a structured call chain. (Source: [FlameGraph tools](https://github.com/brendangregg/FlameGraph))

Example (not your solution): a call chain with comments.
```cpp
// Lowest-level work: deterministic arithmetic.
int work(int x) { return x * 2; }
// Each level adds depth for profiling stacks.
int level3(int x) { return work(x + 1); }
int level2(int x) { return level3(x + 1); }
int level1(int x) { return level2(x + 1); }
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
1) Read `learner/src/main.cpp` and identify the required call chain.
   The TODO asks for a multi-level call chain. This means at least three nested function calls that are easy to see in a backtrace. Your goal is to build a predictable stack shape, not a complex algorithm. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))
   How: list the functions in order (`level1` -> `level2` -> `level3` -> `work`) and decide how each function modifies the input so you can predict the final value.
   - **Expected result:** you can name each function and the order they are called.

2) Implement the lowest-level `work(int)` function first.
   Keep it simple: return `x * 2` or another deterministic computation. This makes it easy to reason about the expected result when called from higher levels. (Source: [cppreference: expressions](https://en.cppreference.com/w/cpp/language/expressions))
   How: write the arithmetic in one line and avoid loops. The goal is to make the cost predictable, not to optimize.
   - **Expected result:** `work(3)` returns 6.

3) Build the call chain with `level1`, `level2`, `level3`.
   Each level should increment the input and call the next level, eventually calling `work`. This creates a predictable call stack for profiling tools. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))
   How: implement `level3(x)` as `return work(x + 1);`, then `level2(x)` as `return level3(x + 1);`, and `level1(x)` as `return level2(x + 1);`. This creates three frames plus the work function.
   - **Expected result:** `level1(1)` returns the expected final value.

4) Implement `exercise()` to validate the chain.
   Call `level1(1)` and verify the output matches the expected value. Return 0 on success and non-zero on failure. (Source: [cppreference: assert](https://en.cppreference.com/w/cpp/error/assert))
   How: compute the expected value by hand (for the suggested chain, `level1(1)` should evaluate to 8) and compare against that constant.
   - **Expected result:** `exercise()` returns 0.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If the test fails, check each function's arithmetic and the order of calls. (Source: [cppreference: expressions](https://en.cppreference.com/w/cpp/language/expressions))
   How: remove `#error`, rebuild, and run `ctest`. If the value is off by 1 or 2, a single level likely failed to add `+1`.
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Generate a perf profile (optional).
   Run `perf record -g ./build_learner/ex02_flamegraph` and then `perf report` to view the call stack. If you have FlameGraph tools, you can convert the stack data into a flamegraph. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))
   How: confirm the stack shows `level1`, `level2`, `level3`, and `work` frames. This is the primary evidence the call chain is working as intended.
   - **Expected result:** the call chain appears in the report.

7) Capture artifacts.
   Save build output to `learner/artifacts/build.log`, test output to `learner/artifacts/ctest.log`, and perf output to `learner/artifacts/perf_report.txt` if you ran perf. (Source: [perf wiki](https://perf.wiki.kernel.org/index.php/Main_Page))
   How: redirect command output with `> file 2>&1` so the logs include errors as well as normal output.
   - **Expected result:** artifacts exist and contain your command outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log`, `ctest.log`.
- `perf_report.txt` if you generated a report.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/07_perf/exercises/ex02_flamegraph`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/07_perf/exercises/ex02_flamegraph --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: ensure all functions are declared before use.
- Test fails: re-check the arithmetic in each level.

## 13) Stretch goals
- Add one more level to the call chain and observe it in perf.
- Add a second call path to compare stack profiles.
