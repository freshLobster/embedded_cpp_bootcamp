# ex03_perf_regression – Fix intentional perf bug

What you are building: Removal of extra copy in BoundedQueue when PLATFORM_FAILURE_PERF is on.
Why it matters: Avoid hidden allocations/copies.

Prerequisites check
- Configure with perf bug: `cmake --preset release -DPLATFORM_FAILURE_PERF=ON`

Files you will touch
- `include/platform/bounded_queue.hpp`
- `modules/07_perf/artifacts/ex03_before.txt`
- `modules/07_perf/artifacts/ex03_after.txt`

Steps
1. Run benchmark with bug:
```
./build/release/platform_core_bench --benchmark_filter=BoundedQueue > modules/07_perf/artifacts/ex03_before.txt
```
Expected: slower throughput.
2. Remove extra copy inside `#ifdef PLATFORM_FAILURE_PERF` (use move/emplace).
3. Rebuild without flag and rerun benchmark saving to after.txt.

Verification
- Throughput improved (>50% drop in time or >50% fewer allocations if measured).
- `ctest --preset release` passes.

Stop here and commit
- Message: "Module07: remove perf regression"

If it fails
- Benchmark not rebuilding: run with `--benchmark_min_time=0.1` to reduce noise.
