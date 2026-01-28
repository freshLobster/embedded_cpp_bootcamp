# platform_core_training – Hands-on Curriculum

Audience: strong C developer, rusty in C++, targeting senior robotics/autonomy/defense roles. All work is done in this repo unless stated. Windows host with WSL2 Ubuntu is the primary path; hardware and CUDA tracks are mandatory where specified.

## Module 1 – Modern C++ Foundations (C++17/20 refresh)
- **Objectives**
  - Use RAII for every resource.
  - Understand value vs reference vs pointer ownership.
  - Prefer move over copy; design APIs that express ownership.
- **Lecture bullets**
  - RAII patterns; destructors as safety rails.
  - `std::unique_ptr`, `std::shared_ptr`, `std::optional`, `std::variant`.
  - Rule of 0/3/5; move-only types.
  - Interface hygiene: minimal headers, PIMPL only when needed.
- **Exercises**
  1. *RAII wrapper*: Implement a `ScopeGuard` in `include/platform/scope_guard.hpp`.  
     Constraints: no exceptions thrown; must be move-only.  
     Hints: store `std::function<void()>`; cancel flag.  
     Verify: `ctest --preset dev --tests-regex ScopeGuard`.
  2. *Move cost audit*: Instrument copies/moves in `Message` (add counters under `#ifdef UNIT_TEST`).  
     Constraints: zero heap allocations added.  
     Hints: use `static std::atomic<int>` counters.  
     Verify: `ctest --preset dev --tests-regex MessageMove`.
  3. *API redesign*: Refactor `MessageBus::publish` to accept `std::string_view` payload overload.  
     Constraints: no additional allocations on hot path.  
     Hints: forward to existing overload; guard lifetime.  
     Verify: `perf stat -r 5 ./build/release/platform_core_bench`.
- **Mastery checklist**
  - Explains RAII and rule-of-0/3/5.
  - Chooses value vs reference intentionally.
  - Removes accidental copies after profiling.

## Module 2 – Memory Management & Allocators
- **Objectives**
  - Design bounded-memory systems; avoid hidden allocations.
  - Implement arena/custom allocator for hot path objects.
  - Detect and fix UAF/dangling references.
- **Lecture bullets**
  - `new`/`delete` bans; `std::pmr` basics.
  - Small-buffer optimization, `std::array` vs `std::vector`.
  - Ownership diagrams; aliasing hazards.
  - Sanitizers for memory safety.
- **Exercises**
  1. *Arena queue*: Add optional `std::pmr::polymorphic_allocator` to `BoundedQueue<T>`.  
     Constraints: no regressions in `BenchQueue`; bounded capacity only.  
     Hints: use `std::pmr::deque`.  
     Verify: `./build/release/platform_core_bench --benchmark_filter=BoundedQueue`.
  2. *UAF bug hunt*: Enable `-DPLATFORM_FAILURE_UAF=ON`, reproduce crash.  
     Constraints: use `ASan` output to identify exact line.  
     Hints: look at `pipeline.cpp`.  
     Verify: `./scripts/run_sanitizers.sh` fails, then fix and rerun to pass.
  3. *Heap audit*: Use `heaptrack ./build/release/platform_core_app`.  
     Constraints: reduce top allocator to <2 allocations/s in steady state.  
     Hints: preallocate strings or use `std::string::reserve`.  
     Verify: compare `heaptrack` before/after.
- **Mastery checklist**
  - Can explain allocator choice and lifetime.
  - Demonstrates bounded memory in profiles.
  - Shows UAF fix validated by sanitizer.

## Module 3 – Concurrency Primitives
- **Objectives**
  - Use `std::jthread`, mutexes, condvars correctly.
  - Avoid deadlocks via lock ordering; diagnose races.
  - Apply stop tokens for clean shutdown.
- **Lecture bullets**
  - `std::mutex` vs `std::shared_mutex`; lock ordering.
  - `std::condition_variable_any` with `std::stop_token`.
  - Atomics: acquire/release vs seq_cst (practical view).
  - Bounded queues and backpressure.
- **Exercises**
  1. *Race repro*: Configure `-DPLATFORM_FAILURE_RACE=ON`; run `ctest`.  
     Constraints: capture failing test log.  
     Hints: `bounded_queue.hpp` guards.  
     Verify: `tsan` (`cmake --preset dev -DPLATFORM_ENABLE_TSAN=ON && ctest --preset dev`).
  2. *Deadlock repro*: `-DPLATFORM_FAILURE_DEADLOCK=ON` then `./build/dev/platform_core_app` under `gdb` attach.  
     Constraints: obtain two-thread backtrace showing lock inversion.  
     Hints: `thread apply all bt`.  
     Verify: after fix, `perf stat` shows no hang for 60s.
  3. *Stop token integration*: Extend `ThreadPool::enqueue` to reject when stop requested.  
     Constraints: no blocking on enqueue during shutdown.  
     Hints: check `shutting_down_`.  
     Verify: new unit test `tests/test_thread_pool.cpp` you add.
- **Mastery checklist**
  - Always pairs lock/unlock via RAII.
  - Proves deadlock prevention with documented lock order.
  - Explains memory order used in atomics.

## Module 4 – Platform Core Architecture
- **Objectives**
  - Understand provided pub/sub bus and pipeline skeleton.
  - Enforce API boundaries and modular decomposition.
  - Add logging/metrics/tracing hooks without coupling.
- **Lecture bullets**
  - Domain layout: `message_bus`, `bounded_queue`, `scheduler`, `thread_pool`, `pipeline`.
  - API stability: headers vs impl, dependency directions.
  - Logging discipline; trace IDs; minimal globals.
- **Exercises**
  1. *Topic contract*: Document bus topics in `docs/topic_contract.md`.  
     Constraints: include payload schema + rate.  
     Hints: start with `sensor.raw`, `control.cmd`.  
     Verify: peer review checklist in `STYLE.md`.
  2. *Metrics hook*: Add lightweight timing spans to pipeline stages.  
     Constraints: <1 µs overhead per message (measure with `std::chrono`).  
     Hints: wrap in `#ifndef NDEBUG` or sampling.  
     Verify: `ctest` still passes; add `trace.log` sample.
  3. *Backpressure demo*: Force queue capacity to 8; publish at 500 Hz; show drops or blocking.  
     Constraints: no unbounded allocations.  
     Hints: adjust scheduler period.  
     Verify: log contains "backpressure" marker you add.
- **Mastery checklist**
  - Can draw module dependency graph.
  - Explains message flow and backpressure points.
  - Produces trace showing latency budget.

## Module 5 – Scheduling & Real-Time-ish Behavior
- **Objectives**
  - Budget latency/jitter; design timeouts and fault handling.
  - Understand priority inversion risks.
  - Implement bounded queues with backpressure signaling.
- **Lecture bullets**
  - Periodic scheduling vs event-driven.
  - Timeouts, watchdogs, exponential backoff.
  - Measuring p50/p95/p99 latency; logging schema.
  - Priority inversion awareness; mitigation strategies.
- **Exercises**
  1. *Latency budget*: Instrument publish→actuator latency; log p50/p95/p99.  
     Constraints: run 2 minutes at 20 Hz.  
     Hints: use `std::chrono::steady_clock` timestamps in `Message`.  
     Verify: produce `logs/latency.csv`.
  2. *Fault handler*: Add timeout + fallback command when sensor data stops for >200 ms.  
     Constraints: no crashes; actuator must receive safe default.  
     Hints: track last-sample time; send `effort=0`.  
     Verify: integration test you add in `tests/test_pipeline_timeout.cpp`.
  3. *Priority experiment*: On Linux, run pipeline under `chrt -f 50` vs default.  
     Constraints: measure jitter difference with `perf sched timehist`.  
     Verify: screenshot or text summary in `docs/hardware/jitter.md`.
- **Mastery checklist**
  - Defines latency budget and meets it.
  - Implements timeouts that fail safe.
  - Explains observed jitter sources.

## Module 6 – Debugging & Sanitizers
- **Objectives**
  - Use gdb locally and via gdbserver.
  - Run ASan/UBSan/TSan; interpret reports; fix bugs.
  - Capture and preserve debug artifacts.
- **Lecture bullets**
  - gdb essentials: break/watch, `thread apply all bt`.
  - ASan/UBSan flags; symbolized output.
  - TSan caveats; suppressions.
  - Core dumps and `coredumpctl`.
- **Exercises**
  1. *ASan lab*: Enable `PLATFORM_FAILURE_UAF`; run `./scripts/run_sanitizers.sh`.  
     Constraints: store log at `artifacts/asan_uaf.txt`.  
     Hints: `pipeline.cpp` UAF path.  
     Verify: log contains "heap-use-after-free" before fix, clean after fix.
  2. *TSan lab*: Enable `PLATFORM_FAILURE_RACE`; run `TSAN_OPTIONS="halt_on_error=1" ctest`.  
     Constraints: capture minimized repro input.  
     Hints: `BoundedQueue` lock guard swap.  
     Verify: artifact `artifacts/tsan_race.txt`.
  3. *gdbserver remote*: On SBC, run `gdbserver :2345 platform_core_app`; connect from host, set breakpoint in `pipeline.cpp` control stage.  
     Constraints: collect `gdb_commands.txt` transcript.  
     Verify: saved to `artifacts/gdb_remote.log`.
- **Mastery checklist**
  - Reads sanitizer stacks and maps to source quickly.
  - Uses gdb to inspect threads/locks.
  - Archives artifacts with timestamps.

## Module 7 – Performance & Profiling
- **Objectives**
  - Benchmark hot paths; prove improvements.
  - Use `perf`, flamegraphs, and Google Benchmark.
  - Identify accidental allocations/copies in pipelines.
- **Lecture bullets**
  - `perf stat`, `perf record`, `perf script | stackcollapse | flamegraph`.
  - Benchmark design: warm-up, iterations, noise control.
  - Cache/NUMA considerations; false sharing avoidance.
- **Exercises**
  1. *Perf baseline*: `perf stat -r 5 ./build/release/platform_core_bench`.  
     Constraints: capture IPC, branch-misses.  
     Hints: use WSL `sudo sysctl kernel.perf_event_paranoid=1`.  
     Verify: store `artifacts/perf_baseline.txt`.
  2. *Flamegraph*: `perf record -g -- ./build/release/platform_core_app` for 30s; generate SVG.  
     Constraints: annotate dominant function.  
     Hints: use Brendan Gregg's `FlameGraph` scripts.  
     Verify: `artifacts/flame.svg`.
  3. *Allocation hunt*: Build with `-DPLATFORM_FAILURE_PERF=ON`; show extra allocations in flamegraph/heaptrack; fix by removing copy.  
     Constraints: after fix, total allocations reduced by >50%.  
     Verify: before/after comparison document.
- **Mastery checklist**
  - Reports perf gains with numbers.
  - Reads flamegraphs to pinpoint work.
  - Removes hidden allocations and proves it.

## Module 8 – Cross-Compilation & SBC Deployment
- **Objectives**
  - Cross-compile for aarch64 Linux.
  - Deploy and validate on Raspberry Pi/Orange Pi.
  - Measure latency/jitter on hardware.
- **Lecture bullets**
  - Toolchains and sysroots; CMake toolchain files.
  - scp/rsync deployment; systemd services.
  - Clock sync, power/thermal considerations.
- **Exercises**
  1. *Cross build*: `./scripts/cross_compile_aarch64.sh`.  
     Constraints: zero warnings; strip binary <2 MB.  
     Hints: `-DCMAKE_BUILD_TYPE=Release`.  
     Verify: `file build/aarch64/platform_core_app` shows aarch64.
  2. *Deploy + run*: `./scripts/deploy_to_sbc.sh pi@raspberrypi.local /home/pi/bin`.  
     Constraints: log output reachable via `journalctl -u platform_core`.  
     Hints: use provided systemd unit (docs/hardware/sbc.md).  
     Verify: latency log copied back to `artifacts/pi_latency.csv`.
  3. *Fault injection on hardware*: Unplug I2C mid-run.  
     Constraints: process stays alive; actuator set to safe value.  
     Hints: watchdog from Module 5.  
     Verify: capture log excerpt with timestamps.
- **Mastery checklist**
  - Builds and deploys reproducibly.
  - Demonstrates latency numbers on hardware.
  - Handles sensor faults gracefully.

## Module 9 – MCU Track (ESP32-C3)
- **Objectives**
  - Build and flash firmware with UART link.
  - Debug with OpenOCD/GDB; inspect registers/memory.
  - Demonstrate ISR/task race and fix.
- **Lecture bullets**
  - ESP-IDF tasks, timers, and ISRs.
  - UART protocol framing; flow control.
  - Critical sections vs atomics on RISC-V core.
- **Exercises**
  1. *Firmware bring-up*: Create `firmware/main/app.c` (or C++) to read sensor + drive LED PWM.  
     Constraints: 50 Hz loop; jitter <200 µs.  
     Hints: use `esp_timer_get_time()`.  
     Verify: scope/logic analyzer trace or UART timestamps saved to `artifacts/esp_jitter.csv`.
  2. *Race lab*: Intentionally share struct between ISR and task without protection; observe corrupt data.  
     Constraints: capture GDB watchpoint trigger.  
     Hints: `watch variable` in GDB.  
     Verify: fix with `portENTER_CRITICAL` or atomic; rerun to prove clean.
  3. *Host bridge*: Write host-side tool in `tools/uart_bridge.py` to log UART packets.  
     Constraints: handle reconnect; no dropped packets for 5 minutes.  
     Verify: checksum count == packet count.
- **Mastery checklist**
  - Flashes and debugs MCU confidently.
  - Explains ISR/task coordination.
  - Provides timing evidence meeting budget.

## Module 10 – Simulation Track (QEMU / Renode)
- **Objectives**
  - Use simulators for deterministic repro and CI.
  - Compare simulation vs hardware limitations.
  - Automate tests in simulation.
- **Lecture bullets**
  - QEMU aarch64 user/system modes.
  - Renode for MCU peripherals; scripting tests.
  - Determinism knobs; timing model caveats.
- **Exercises**
  1. *QEMU run*: `qemu-aarch64 -L /usr/aarch64-linux-gnu build/aarch64/platform_core_app`.  
     Constraints: ensure deterministic log ordering in 30s run.  
     Hints: use `taskset` to pin CPU.  
     Verify: compare log checksum vs reference.
  2. *Renode script*: Write `.resc` to boot ESP32-C3 equivalent and run minimal firmware stub.  
     Constraints: log I2C transactions; simulate disconnection.  
     Hints: use Renode Monitor `emulation CreateUartTerminal`.  
     Verify: captured Renode log matches expected sequence.
  3. *CI harness*: Add `scripts/run_sim.sh` to execute QEMU test and return non-zero on failure.  
     Constraints: runs <5 min; no root needed.  
     Verify: integrates with `ctest` via `add_test(NAME sim ...)`.
- **Mastery checklist**
  - Spins up simulation quickly.
  - Knows limitations vs real hardware.
  - Uses simulation for regression tests.

## Module 11 – CUDA Fundamentals & Integration
- **Objectives**
  - Build CUDA code on Windows and WSL.
  - Wrap CUDA resources in RAII; no raw `cudaMalloc` in app code.
  - Validate GPU output vs CPU reference.
- **Lecture bullets**
  - Kernel launch parameters; occupancy intuition.
  - Memory spaces; host<->device transfer costs.
  - Streams and async copies; event timing.
  - Error handling: every call checked.
- **Exercises**
  1. *Environment check*: `nvidia-smi`, `nvcc --version`, `cuda-memcheck --help`.  
     Constraints: capture versions into `artifacts/cuda_env.txt`.  
     Hints: run inside WSL and Windows to compare.  
     Verify: file contains driver + runtime versions.
  2. *CPU/GPU parity*: Use `vector_add_cuda` and compare vs CPU for 1M elements.  
     Constraints: max absolute error <1e-6.  
     Hints: reuse test harness in `tests/test_cuda_stage.cpp`.  
     Verify: add benchmark `bench_cuda_vector_add.cpp` (TODO) and record throughput.
  3. *RAII wrap*: Extend `CudaBuffer` to support move-only stream association.  
     Constraints: no leaks (checked by `cuda-memcheck`).  
     Hints: encapsulate `cudaStream_t` with unique handle.  
     Verify: `compute-sanitizer --tool=memcheck ./build/cuda/platform_core_tests`.
- **Mastery checklist**
  - Builds CUDA on both Windows and WSL.
  - Uses RAII for device memory/streams.
  - Proves GPU correctness vs CPU.

## Module 12 – CUDA Performance, Debugging, and Jetson Awareness
- **Objectives**
  - Profile kernels with Nsight Systems/Compute (or CLI).
  - Identify divergence, coalescing issues, and CPU/GPU sync points.
  - Understand Jetson-class constraints and deployment.
- **Lecture bullets**
  - Nsight CLI: `nsys profile`, `ncu --set full`. Fallback: `cudaEvent` timing.
  - Common bottlenecks: non-coalesced loads, small kernels, sync-heavy design.
  - Jetson specifics: shared memory limits, clocks, unified memory caveats.
- **Exercises**
  1. *Nsight timeline*: `nsys profile -o artifacts/nsys_report ./build/cuda/platform_core_bench`.  
     Constraints: annotate H2D/D2H vs kernel time.  
     Hints: add NVTX ranges around copy/compute.  
     Verify: screenshot or text summary.
  2. *Divergence lab*: Modify kernel to branch on `idx % 2`; measure slowdown.  
     Constraints: report occupancy change.  
     Hints: use `ncu --metrics sm__sass_branch_targets_threads_uniform.pct`.  
     Verify: results in `docs/cuda/divergence.md`.
  3. *Jetson simulation*: Build aarch64 CUDA binary (requires Jetson sysroot) and run under QEMU with `--cuda-trace` disabled (functional only).  
     Constraints: document missing HW acceleration.  
     Hints: note driver requirements.  
     Verify: ADR entry `docs/cuda/jetson_adr.md`.
- **Mastery checklist**
  - Produces Nsight/CLI profiles with conclusions.
  - Connects kernel design to performance metrics.
  - Articulates Jetson deployment constraints and workarounds.

---

## 4-Week Schedule (5–10 hrs/week)
- **Week 1:** Modules 1–3 (C++ refresh, memory, concurrency) + reproduce race/UAF failures.
- **Week 2:** Modules 4–6 (architecture, scheduling, debugging) + fix failure modes.
- **Week 3:** Modules 7–8 (profiling, SBC cross/deploy) + gather hardware latency data.
- **Week 4:** Modules 9–12 (MCU, simulation, CUDA fundamentals + performance) + finalize artifacts.

## 2-Week Cram Mode
- **Days 1–3:** Modules 1–3 condensed; run sanitizers and fix failures.
- **Days 4–6:** Modules 4–6; produce latency budget + timeout test.
- **Days 7–9:** Modules 7–8; cross-compile and deploy once to SBC.
- **Days 10–14:** Modules 11–12 focus; minimal MCU/sim exposure; capture CUDA parity + Nsight snapshot.

## Interview Mapping (topics → modules)
- C++ ownership/RAII: 1–2  
- Concurrency & deadlocks/races: 3  
- Systems design & APIs: 4–5  
- Debugging/sanitizers: 6  
- Performance/flamegraphs: 7  
- Cross-compilation/deployment: 8  
- Embedded/RTOS/ISR: 9  
- Simulation/determinism: 10  
- CUDA fundamentals/perf: 11–12  
- Fault tolerance/backpressure: 5,8

## Portfolio Checklist
- Architecture diagram of platform core.
- ADRs: topic contracts, allocator choice, CUDA vs CPU tradeoffs.
- Benchmarks: queue throughput, CUDA vs CPU throughput, latency CSVs.
- Debug artifacts: ASan/TSan logs, gdb transcripts, flamegraphs, Nsight reports.
- Hardware evidence: photos/wiring, oscilloscope/logic analyzer captures, systemd logs.
- Simulation scripts and CI logs.
- Bug writeups: race, deadlock, UAF, perf regression—cause, fix, proof.
