# 05_scheduling - ex01_latency_budget

## 1) Title + Mission
Mission: compute latency percentiles (p50/p95) from samples and validate against a budget using deterministic math. (Source: [cppreference: std::chrono::duration](https://en.cppreference.com/w/cpp/chrono/duration))

## 2) What you are building (plain English)
You are building a small statistics helper that takes latency samples and returns p50 and p95 metrics. These metrics are then used to reason about timing budgets. (Source: [cppreference: std::chrono::duration](https://en.cppreference.com/w/cpp/chrono/duration))

## 3) Why it matters (embedded/robotics/defense relevance)
Latency budgets and jitter bounds are contractual requirements for safety-critical systems. Percentiles (p50, p95) summarize how a system behaves under load and help you detect tail latency issues. (Source: [cppreference: std::chrono::steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock))

## 4) Concepts (short lecture)
Percentiles summarize distributions. The p50 is the median; p95 indicates the tail where worst-case behavior hides. Using a deterministic percentile calculation makes results repeatable, which is important for validation. (Source: [cppreference: std::sort](https://en.cppreference.com/w/cpp/algorithm/sort))

If you store samples as integer microseconds or milliseconds, you can compute percentiles by sorting and selecting an index. This is a simple, deterministic method that is easy to explain in reviews. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))

Example (not your solution): compute a percentile index with comments.
```cpp
// Sort samples so percentile indices are meaningful.
std::sort(samples.begin(), samples.end());
// Compute the index for the 95th percentile.
size_t idx95 = static_cast<size_t>((samples.size() - 1) * 0.95);
// Read the value at that index.
int p95 = samples[idx95];
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
1) Read `compute_stats` in `learner/src/main.cpp` and restate the inputs/outputs.
   The function receives a copy of the samples, which means you are free to sort without mutating the caller's data. The expected outputs for the provided samples are p50=50 and p95=100. Understanding the expected values first helps validate your index math. (Source: [cppreference: std::sort](https://en.cppreference.com/w/cpp/algorithm/sort))
   How: write the sample list, sort it by hand, and locate the 50th and 95th percentile positions using the formula provided.
   - **Expected result:** you can explain why sorting a local copy is safe and why the expected p50/p95 are 50/100.

2) Sort the samples in ascending order.
   Use `std::sort(samples.begin(), samples.end())`. Percentile selection assumes the data is ordered; without sorting, the percentile indices are meaningless. (Source: [cppreference: std::sort](https://en.cppreference.com/w/cpp/algorithm/sort))
   How: call `std::sort` on the local copy and avoid any extra allocations or temporary vectors.
   - **Expected result:** samples are strictly ordered from smallest to largest.

3) Compute deterministic percentile indices.
   Use `(samples.size() - 1) * 0.50` for p50 (median in 0-based indexing). For p95, use `samples.size() * 0.95` and clamp to `size - 1` so the 95th percentile can select the last element for small datasets. This matches the expected result for the 10-element example. (Source: [cppreference: std::vector::size](https://en.cppreference.com/w/cpp/container/vector/size))
   How: compute `idx50` with `(size - 1) * 0.50`, compute `idx95` with `size * 0.95`, then if `idx95 >= size`, set it to `size - 1`.
   - **Expected result:** p50=50 and p95=100 for the provided dataset.

4) Return `LatencyStats` without side effects.
   Construct and return the struct directly. Do not print or log inside `compute_stats`; keep it pure so tests remain deterministic. (Source: [cppreference: aggregate initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization))
   How: return `{samples[idx50], samples[idx95]};` and avoid modifying any global state.
   - **Expected result:** the test observes the correct percentile values.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, verify you are using `(size - 1)` in index calculations and not `size`, which can produce out-of-range indices. (Source: [cppreference: std::vector::size](https://en.cppreference.com/w/cpp/container/vector/size))
   How: remove the `#error` line, rebuild, then run `ctest --test-dir build_learner --output-on-failure`.
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Redirect build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log` for grading. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   How: run `cmake --build build_learner > learner/artifacts/build.log 2>&1` and `ctest --test-dir build_learner --output-on-failure > learner/artifacts/ctest.log 2>&1`.
   - **Expected result:** both log files exist and contain the command output.

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
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/05_scheduling/exercises/ex01_latency_budget`
- Solution check:
  `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/05_scheduling/exercises/ex01_latency_budget --use-solution`
- High-level scoring:
  - Configure/build: 40 points
  - Tests: 40 points
  - Artifacts present: 20 points

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- If build fails: ensure you removed `#error` and included `<algorithm>`.
- If tests fail: double-check percentile index math and integer rounding.

## 13) Stretch goals
- Add a p99 percentile and compare it to a tighter budget.
- Add a CSV export of samples and computed statistics.
