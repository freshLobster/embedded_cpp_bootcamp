
# Validation checklist - CUDA Basics
- [ ] `cmake --preset dev` succeeds.
- [ ] `ctest --preset dev -R Module11_cuda_basics` passes (or noted skip if not added).
- [ ] Artifacts present in `artifacts/` and named correctly.
- [ ] Any benchmarks/sanitizers requested in exercises executed with logs saved.
