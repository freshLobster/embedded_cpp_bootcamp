# CUDA Track

## Environment setup
- Windows: install NVIDIA driver + CUDA Toolkit 12.x; verify `nvidia-smi` and `nvcc --version`.
- WSL2: ensure driver supports WSL; install CUDA Toolkit for Ubuntu, verify `nvidia-smi` inside WSL.
- Build: `cmake --preset cuda && cmake --build --preset cuda`

## Labs
1) **Vector add correctness**
   - Files: `include/platform/cuda_stage.hpp`, `src/cuda/cuda_stage.cu`
   - Task: run `ctest --preset cuda` or `ctest --preset release` after `-DPLATFORM_ENABLE_CUDA=ON`.
   - Verify CPU vs GPU buffers are equal; capture timing (`nvprof --print-gpu-trace` or `nsys profile`).

2) **Error-handling discipline**
   - Introduce an invalid launch (set grid to 0) and observe `cudaErrorInvalidConfiguration`.
   - Fix by clamping blocks >0 and assert every CUDA call via `check_cuda`.

3) **Performance + occupancy**
   - Modify kernel launch parameters, compare runtime via `nvprof`/`nsys stats`.
   - Measure H2D/D2H transfer time vs kernel; report roofline-style summary.

4) **Async/streams**
   - Add stream parameter to `vector_add_cuda`, overlap copy+compute for large buffers.
   - Validate with `nsys` timeline; ensure `cudaStreamSynchronize` only at end.

5) **Debugging failure**
   - Configure: `cmake --preset cuda -DPLATFORM_FAILURE_UAF=ON`.
   - Run `compute-sanitizer --tool=memcheck ./build/cuda/platform_core_tests`.
   - Capture log; fix by removing UAF block in `pipeline.cpp`; re-run to confirm clean.

## Jetson awareness (simulated)
- Cross-compile with `./scripts/cross_compile_aarch64.sh -DPLATFORM_ENABLE_CUDA=ON` (requires aarch64 CUDA toolkit in sysroot).
- Emulate memory limits: set `CUDA_MEMPOOL_DEFAULT_OPS=1` and reduce batch sizes.
- Metrics to watch: latency per frame, GPU util, copy throughput, CPU-GPU sync points.

## Artifacts to save
- `nsys-reports/` trace files
- `compute-sanitizer` logs
- `benchmarks/cuda_vector_add.txt` with throughput numbers
