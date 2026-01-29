# ex02_cpu_gpu_parity – CPU vs GPU vector add

What you are building: Validation that GPU output matches CPU reference for 1M elements.
Why it matters: Correctness before optimization.

Prerequisites check
- Build with CUDA: `cmake --preset cuda && cmake --build --preset cuda`

Files you will touch
- `tests/test_cuda_stage.cpp` (optional update to allow large vector)
- `modules/11_cuda_basics/artifacts/ex02_parity.txt`

Steps
1. Run test (may already exist):
```
ctest --preset cuda -R CudaStage > modules/11_cuda_basics/artifacts/ex02_parity.txt
```
2. If GPU available, extend test to 1M elements; rerun and capture output.

Verification
- Test passes; log shows CUDA path executed or skipped with message.

Stop here and commit
- Message: "Module11: CPU/GPU parity"

If it fails
- No device: log skip as acceptable.
