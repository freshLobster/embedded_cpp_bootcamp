
# Validation checklist – Perf
- [ ] `cmake --preset dev` succeeds.
- [ ] `ctest --preset dev -R Module07_perf` passes (or noted skip if not added).
- [ ] Artifacts present in `artifacts/` and named correctly.
- [ ] Any benchmarks/sanitizers requested in exercises executed with logs saved.
