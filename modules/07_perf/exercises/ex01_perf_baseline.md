# ex01_perf_baseline – perf stat baseline

What you are building: Baseline perf stat for queue benchmark.
Why it matters: Quantifies performance before changes.

Prerequisites check
- `perf --version`

Files you will touch
- `modules/07_perf/artifacts/ex01_perf.txt`

Steps
1. Build release bench: `cmake --build --preset release --target platform_core_bench`
2. Run perf stat:
```
sudo perf stat -r 5 ./build/release/platform_core_bench --benchmark_filter=BoundedQueue > modules/07_perf/artifacts/ex01_perf.txt 2>&1
```
Expected: IPC/branch-miss stats recorded.

Verification
- File contains perf counters.

Stop here and commit
- Message: "Module07: perf baseline"

If it fails
- perf permission: adjust `kernel.perf_event_paranoid` or use sudo.
