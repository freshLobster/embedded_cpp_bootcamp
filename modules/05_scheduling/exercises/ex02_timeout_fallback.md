# ex02_timeout_fallback – Sensor timeout safe command

What you are building: Watchdog that sends effort=0 if no sensor data for 200 ms.
Why it matters: Actuators must fail safe when inputs stall.

Prerequisites check
- `grep -n "sensor.raw" src/platform/pipeline.cpp`

Files you will touch
- `src/platform/pipeline.cpp`
- `tests/test_pipeline_timeout.cpp` (create)

Steps
1. Track last sensor timestamp; if stale >200ms, publish control.cmd with 0 and log warning.
2. Add unit/integration test simulating stall by invoking pipeline functions directly or mocking bus.
3. Build + run filtered tests:
```
cmake --build --preset dev --target platform_core_tests
ctest --preset dev -R Module05
```
Expected: new test passes.

Verification
- Warning log appears when stall simulated.
- Tests pass.

Stop here and commit
- Message: "Module05: watchdog fallback"

If it fails
- Time math wrong: use steady_clock durations.

Stretch goals
- Expose timeout duration via config constant.
