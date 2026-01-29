# ex03_raii_buffer – Strengthen CudaBuffer RAII

What you are building: Add stream ownership and move-only semantics to CudaBuffer (or new class) with tests.
Why it matters: Prevent leaks and enforce deterministic release.

Prerequisites check
- `grep -n "CudaBuffer" include/platform/cuda_stage.hpp`

Files you will touch
- `include/platform/cuda_stage.hpp`
- `src/cuda/cuda_stage.cu`
- `tests/test_cuda_stage.cpp`

Steps
1. Add optional `cudaStream_t` wrapper class (move-only) inside header.
2. Ensure CudaBuffer reset handles stream sync if associated.
3. Add test that alloc/free under compute-sanitizer is clean (may skip if tool absent).
4. Rebuild CUDA target and run tests.

Verification
- `ctest --preset cuda -R CudaStage` passes.
- No leaks in `compute-sanitizer --tool=memcheck ./build/cuda/platform_core_tests` (if available).

Stop here and commit
- Message: "Module11: RAII stream/buffer"

If it fails
- compile errors: include <cuda_runtime_api.h> and guard under PLATFORM_ENABLE_CUDA.
