# ex01_env – CUDA environment capture

What you are building: Text file with CUDA driver/runtime versions (Windows + WSL if available).
Why it matters: Baseline for GPU work.

Prerequisites check
- `nvidia-smi`

Files you will touch
- `modules/11_cuda_basics/artifacts/ex01_env.txt`

Steps
1. Capture info:
```
{ nvidia-smi; nvcc --version; } > modules/11_cuda_basics/artifacts/ex01_env.txt 2>&1
```
2. If WSL and Windows differ, run both and append.

Verification
- File contains driver version and CUDA version lines.

Stop here and commit
- Message: "Module11: CUDA env log"

If it fails
- Commands missing: install CUDA toolkit/driver.
