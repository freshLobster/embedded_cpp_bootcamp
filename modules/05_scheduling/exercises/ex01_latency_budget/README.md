# 05_scheduling - ex01_latency_budget

## 1) Title + Mission
Mission: Compute latency statistics from monotonic timestamp samples and validate them against a budget.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】【https://en.cppreference.com/w/cpp/chrono/duration†L450-L450】

## 2) What you are building (plain English)
You are building a small stats utility that turns duration samples into p50/p95 metrics for latency review.【https://en.cppreference.com/w/cpp/chrono/duration†L450-L450】

## 3) Why it matters (embedded/robotics/defense relevance)
Latency budgets and jitter bounds are contractual requirements in safety-critical software and require monotonic time sources.【https://en.cppreference.com/w/cpp/chrono/steady_clock†L377-L377】

## 4) Concepts (short lecture)
`std::chrono::duration` represents a time interval and is the correct type for expressing latency samples and budgets.【https://en.cppreference.com/w/cpp/chrono/duration†L450-L450】

A p50 is the median sample and p95 is a tail metric: 95% of samples are less than or equal to it. Computing these from sorted samples is a simple, deterministic way to reason about jitter.

Example (not your solution): compute percentile indices from a sorted vector.
```cpp
int percentile(std::vector<int> samples, double p) {
    std::sort(samples.begin(), samples.end());
    size_t idx = static_cast<size_t>(std::ceil(p * samples.size())) - 1;
    if (idx >= samples.size()) idx = samples.size() - 1;
    return samples[idx];
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

Run these in **this exercise folder**:
```
cmake --version
```
Expected output (example): `cmake version 3.22.1`.

```
c++ --version
```
Expected output (example): `g++ (Ubuntu 11.4.0)` or `clang version 14.x`.


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


## 8) Step-by-step implementation instructions
1) Open `learner/src/main.cpp` and review `LatencyStats` and `compute_stats`.
   - Identify how p50 and p95 should be computed.
   - **Expected result:** you can describe the index calculation for each percentile.
2) Implement `compute_stats`.
   - Sort the samples and compute percentile indices deterministically.
   - Guard against empty input (return zeros or handle as you decide in README).
   - **Expected result:** p50/p95 match expected values for a known sample set.
3) Remove `#error TODO_implement_exercise`, build, and run tests.
4) Save artifacts.

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
- If build fails: verify CMake + compiler version.
- If tests fail: re-check your logic against the required behavior.

## 13) Stretch goals
- Add p99 and max to the stats output.
- Record the sample count and add a guard for empty input.
