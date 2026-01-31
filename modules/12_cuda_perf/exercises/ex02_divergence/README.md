# 12_cuda_perf - ex02_divergence

## 1) Title + Mission
Mission: compute average active lanes from warp masks to reason about branch divergence. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

## 2) What you are building (plain English)
You are building a helper that takes a list of 32-bit masks (one per warp) and computes the average fraction of active lanes. This is a proxy for divergence efficiency. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

## 3) Why it matters (embedded/robotics/defense relevance)
Divergence reduces GPU efficiency. In autonomy pipelines, branch-heavy kernels can underperform and cause latency spikes. Measuring active lanes helps diagnose this. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

## 4) Concepts (short lecture)
NVIDIA GPUs execute threads in warps of 32 lanes. If threads in a warp diverge, some lanes become inactive, reducing effective throughput. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

A warp mask is a 32-bit bitset indicating which lanes are active. Counting set bits and dividing by 32 gives the active fraction. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))

Example (not your solution): popcount and active fraction.
```cpp
int popcount32(uint32_t v) {
    int c = 0;
    // Clear one set bit per iteration.
    while (v) { v &= v - 1; ++c; }
    return c;
}
// Convert active lanes to a fraction of 32.
double active = static_cast<double>(popcount32(mask)) / 32.0;
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
1) Read `learner/src/main.cpp` and identify the required outputs.
   You must compute the average active lanes for a set of 32-bit masks. The test uses two masks: all lanes active and none active, so the average should be ~0.5. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))
   How: compute the average by hand: (32/32 + 0/32) / 2 = 0.5. This is the expected target.
   - **Expected result:** you can compute the expected average by hand.

2) Implement `popcount32(uint32_t v)`.
   Use the classic `v &= v - 1` loop to count set bits. This counts active lanes efficiently and deterministically. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))
   How: initialize `count = 0`, then loop while `v != 0`, clear the lowest set bit, increment `count`, and return it.
   - **Expected result:** popcount32(0xFFFFFFFF) returns 32, popcount32(0x0) returns 0.

3) Implement `average_active_lanes`.
   Sum the active fraction for each mask (popcount / 32.0) and divide by the number of masks. Return 0.0 for empty input. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))
   How: if `masks.empty()`, return 0.0. Otherwise compute `sum += popcount32(m) / 32.0` and finally return `sum / masks.size()`.
   - **Expected result:** two masks (all active, none active) yield ~0.5.

4) Remove `#error TODO_implement_exercise`, rebuild, and run tests.
   If tests fail, check that you used floating-point division and not integer division. (Source: [cppreference: floating point arithmetic](https://en.cppreference.com/w/cpp/language/expressions))
   How: remove the `#error`, rebuild, and run `ctest`. If you see 0.0 or 1.0, you likely used integer division.
   - **Expected result:** `ctest` reports `100% tests passed`.

5) Capture artifacts.
   Save build output to `learner/artifacts/build.log` and test output to `learner/artifacts/ctest.log`. (Source: [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html))
   How: redirect outputs with `> file 2>&1` to capture errors.
   - **Expected result:** artifacts exist and contain your outputs.

## 9) Verification
- `ctest --test-dir build_learner --output-on-failure` must report `100% tests passed`.

## 10) Artifacts to save
- `build.log` and `ctest.log` in `learner/artifacts/`.

## 11) Grade this exercise
- Learner attempt: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/12_cuda_perf/exercises/ex02_divergence`
- Solution check: `python3 ../../../../tools/grader/grade.py --exercise ../../../../modules/12_cuda_perf/exercises/ex02_divergence --use-solution`

## 12) If it fails (quick triage)
See `troubleshooting.md`. Quick triage:
- Build fails: include `<cstdint>` and `<vector>`.
- Test fails: check for integer division or incorrect popcount.

## 13) Stretch goals
- Add masks with partial activity and compare expected averages.
- Compute min/max active fraction across masks.
