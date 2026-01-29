# ex01_race_repro – Trigger data race

What you are building: Reproduction of intentional race and proof of fix.
Why it matters: Determinism and safety depend on race-free code.

Prerequisites check
- Configure with race flag: `cmake --preset dev -DPLATFORM_FAILURE_RACE=ON`
- Ensure TSAN tool availability (WSL/Clang): `clang++ --version`.

Files you will touch
- `include/platform/bounded_queue.hpp`

Steps
1. Build tests with TSan:
```
cmake --build --preset dev --target platform_core_tests
TSAN_OPTIONS="halt_on_error=1" ctest --preset dev -R BoundedQueue --output-on-failure | tee modules/03_concurrency/artifacts/ex01_tsan.txt
```
Expected: TSan reports a data race in bounded_queue.
2. Fix by ensuring lock guards use real mutex even under failure flag (remove race path or guard it for test fix).
3. Reconfigure without flag: `cmake --preset dev -DPLATFORM_FAILURE_RACE=OFF`
4. Rerun tests: `ctest --preset dev -R BoundedQueue` → PASS.

Verification
- TSan log saved; clean run after fix.

Stop here and commit
- Message: "Module03: fix intentional race in BoundedQueue"

If it fails
- TSan not supported: run on WSL/Clang; do not use MSVC.
- No race reported: ensure flag ON and TSan enabled.

Stretch goals
- Add unit test that stresses queue with multiple producers/consumers.
