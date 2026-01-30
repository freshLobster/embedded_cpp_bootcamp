# 08_cross_deploy - ex03_latency_on_hw

## 1) Title + Mission
Mission: compute jitter statistics (min, max, span) from latency samples to validate timing stability on hardware. (Source: [cppreference: std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits))

## 2) What you are building (plain English)
You are building a small function that takes latency samples and returns the minimum, maximum, and the span (max - min). This is a basic jitter metric for hardware validation. (Source: [cppreference: std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits))

## 3) Why it matters (embedded/robotics/defense relevance)
Latency jitter can destabilize control loops even when average latency looks good. Min/max span is a quick sanity check to identify unstable timing on SBCs and embedded targets. (Source: [cppreference: std::chrono::steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock))

## 4) Concepts (short lecture)
Jitter is variation in latency over time. A simple way to quantify it is to compute min and max latency and take the span as max - min. This is not a full statistical analysis but is useful as a first validation step. (Source: [cppreference: std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits))

Using `std::numeric_limits` is a standard pattern to initialize min/max trackers before scanning samples. It ensures your initial values do not bias the results. (Source: [cppreference: std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits))

Example (not your solution): min/max scan with comments.
```cpp
int minv = std::numeric_limits<int>::max();
int maxv = std::numeric_limits<int>::min();
for (int v : samples) {
    if (v < minv) minv = v;
    if (v > maxv) maxv = v;
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
1) Read `learner/src/main.cpp` and restate the expected output.
   The function `compute_jitter` must return min, max, and span for a vector of samples. The test uses {10,12,11,15} and expects min=10, max=15, span=5. (Source: [cppreference: std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits))
   - **Expected result:** you can calculate the expected values by hand.

2) Initialize min/max with numeric limits.
   Set `minv` to `numeric_limits<int>::max()` and `maxv` to `numeric_limits<int>::min()` so any real sample will replace them. This is the standard pattern for min/max scanning. (Source: [cppreference: std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits))
   - **Expected result:** the first sample always updates both min and max.

3) Scan the samples and update min/max.
   Loop over the input vector and update `minv` and `maxv` when a sample is smaller or larger than the current extrema. Keep this loop simple and deterministic. (Source: [cppreference: std::vector](https://en.cppreference.com/w/cpp/container/vector))
   - **Expected result:** after the loop, minv and maxv are correct.

4) Compute span and return the result struct.
   `span = maxv - minv`. Return a `JitterStats{minv, maxv, span}`. This is the simple jitter metric used in the test. (Source: [cppreference: aggregate initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization))
   - **Expected result:** span is 5 for the test sample set.

5) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, verify that you did not mix up min and max and that you computed span after scanning. (Source: [cppreference: std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits))
   - **Expected result:** `ctest` reports `100% tests passed`.

6) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [cppreference: std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits))
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex03_latency_on_hw`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/08_cross_deploy/exercises/ex03_latency_on_hw --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: include `<limits>` and `<vector>`.
- Test fails: verify min/max updates and span calculation.

## 13) Stretch goals
- Add mean and standard deviation for a richer jitter report.
- Add a CSV export of samples and computed stats.
