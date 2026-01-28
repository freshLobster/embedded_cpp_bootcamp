# Intentional Failure Modes

Use one option at a time when configuring CMake.

## Data race
- Enable: `-DPLATFORM_FAILURE_RACE=ON`
- Trigger: run `ctest --preset dev` or stress with `./build/dev/platform_core_app`.
- Diagnose: `TSAN_OPTIONS="halt_on_error=1" ctest`; look at `BoundedQueue` lock elision in `bounded_queue.hpp`.
- Fix: restore locking path; remove `#ifdef PLATFORM_FAILURE_RACE` block.
- Prove: `TSan` clean run + `perf stat` shows no stalls; latency logs stable.

## Deadlock
- Enable: `-DPLATFORM_FAILURE_DEADLOCK=ON`
- Trigger: run app; threads hang after startup.
- Diagnose: `gdb -p <pid>` -> `thread apply all bt`; see lock inversion between `MessageBus::subscribe` and `publish`.
- Fix: enforce single mutex or consistent order; remove `deadlock_mutex_` usage.
- Prove: 5-minute run without hang; `perf sched timehist` shows runnable threads.

## Use-after-free
- Enable: `-DPLATFORM_FAILURE_UAF=ON`
- Trigger: run `./scripts/run_sanitizers.sh`.
- Diagnose: ASan reports in `pipeline.cpp` control stage scratch pointer.
- Fix: delete fault block; keep ownership within scope; optional `std::unique_ptr`.
- Prove: ASan clean; long soak test with `valgrind` (WSL) shows 0 errors.

## Performance regression
- Enable: `-DPLATFORM_FAILURE_PERF=ON`
- Trigger: run `./build/release/platform_core_bench`; throughput collapses.
- Diagnose: flamegraph/`perf` shows extra copies in `BoundedQueue` push path.
- Fix: remove duplicate copy; prefer `emplace`/move.
- Prove: benchmark throughput returns to baseline; allocation count drops >50%.
