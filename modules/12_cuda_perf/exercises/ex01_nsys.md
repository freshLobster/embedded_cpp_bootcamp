# ex01_nsys – Nsight Systems capture

What you are building: Nsight Systems report for vector add benchmark.
Why it matters: Visualize copy/compute overlap and bottlenecks.

Prerequisites check
- `nsys --version` (or `which nsys`)

Files you will touch
- `modules/12_cuda_perf/artifacts/ex01_nsys.qdrep`
- `modules/12_cuda_perf/artifacts/ex01_nsys.txt`

Steps
1. Build CUDA bench (add simple bench if missing) or reuse app; profile:
```
nsys profile -o modules/12_cuda_perf/artifacts/ex01_nsys ./build/cuda/platform_core_bench --benchmark_filter=vector_add
```
2. Generate summary:
```
nsys stats modules/12_cuda_perf/artifacts/ex01_nsys.qdrep > modules/12_cuda_perf/artifacts/ex01_nsys.txt
```
Expected: report with kernel and memcpy times.

Verification
- Summary file exists; shows GPU activity.

Stop here and commit
- Message: "Module12: nsys profile"

If it fails
- Tool missing: note in summary and skip.
