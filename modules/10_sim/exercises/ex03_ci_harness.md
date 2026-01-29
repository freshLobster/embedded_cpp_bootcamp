# ex03_ci_harness – Simulation add_test

What you are building: CTest entry to run QEMU smoke test.
Why it matters: Deterministic CI guardrail.

Prerequisites check
- `ctest -N` currently lists existing tests.

Files you will touch
- `CMakeLists.txt` (add test)
- `modules/10_sim/artifacts/ex03_ctest.txt`

Steps
1. Add in CMakeLists near tests:
```
add_test(NAME sim_qemu COMMAND qemu-aarch64 -L /usr/aarch64-linux-gnu ${PROJECT_SOURCE_DIR}/build/aarch64/platform_core_app)
```
2. Reconfigure: `cmake --preset dev`
3. List tests: `ctest --preset dev -N | grep sim_qemu > modules/10_sim/artifacts/ex03_ctest.txt`

Verification
- Test shows up; optionally run if qemu available.

Stop here and commit
- Message: "Module10: add sim test"

If it fails
- QEMU path wrong: adjust to your install location.
