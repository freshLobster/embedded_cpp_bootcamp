
# Validation checklist – Cross & Deploy
- [ ] `cmake --preset dev` succeeds.
- [ ] `ctest --preset dev -R Module08_cross_deploy` passes (or noted skip if not added).
- [ ] Artifacts present in `artifacts/` and named correctly.
- [ ] Any benchmarks/sanitizers requested in exercises executed with logs saved.
