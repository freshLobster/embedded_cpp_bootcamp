# ex02_uaf_fix – Remove intentional UAF

What you are building: Clean fix for the deliberate use-after-free in `pipeline.cpp`.
Why it matters: Memory safety is mandatory for defense/autonomy deployments.

Prerequisites check
- Enable fault: `cmake --preset asan -DPLATFORM_FAILURE_UAF=ON`
- Run: `ctest --preset asan -R pipeline` (expect ASan failure pointing to pipeline.cpp)

Files you will touch
- `src/platform/pipeline.cpp`

Steps
1. Open file and remove the `#ifdef PLATFORM_FAILURE_UAF` block, replacing with safe math only.
2. Reconfigure without fault flag: `cmake --preset asan -DPLATFORM_FAILURE_UAF=OFF`
3. Rebuild + rerun tests:
```
cmake --build --preset asan --target platform_core_tests
ctest --preset asan -R pipeline --output-on-failure
```
Expected: tests pass, ASan clean.

Verification
- `ctest --preset asan` all pass
- No ASan errors in log saved to `modules/02_memory/artifacts/ex02_asan.txt`

Stop here and commit
- Message: "Module02: remove UAF injection"

If it fails
- Still seeing UAF: ensure cache cleared (`cmake --build --preset asan --clean-first`).
- Build uses old cache: delete `build/asan` and reconfigure.

Stretch goals
- Add GoogleTest covering the fixed path (construct ControlCommand and ensure no crash).
