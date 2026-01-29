# Debugging & Profiling Labs

## Lab A - gdb local
- Build: `./scripts/build_debug.sh`
- Run: `gdb --args ./build/dev/platform_core_app`
- Steps: `b platform::Pipeline::start_control`, `run`, `info threads`, `thread apply all bt`, `finish`, `continue`.
- Artifact: save session to `artifacts/gdb_local.txt` (`set logging on`).

## Lab B - gdbserver remote (SBC)
- On SBC: `gdbserver :2345 /home/pi/bin/platform_core_app`
- Host: `gdb build/aarch64/platform_core_app -ex "target remote pi@raspberrypi.local:2345" -ex "set sysroot /"`
- Steps: breakpoint on `bus_.publish`; inspect `info mutex` (GDB python pretty printer optional).
- Artifact: `artifacts/gdb_remote.log`.

## Lab C - Sanitizers
- ASan/UBSan: `./scripts/run_sanitizers.sh`
- TSan: `cmake --preset dev -DPLATFORM_ENABLE_TSAN=ON && cmake --build --preset dev && ctest --preset dev`
- Artifact: `artifacts/asan.txt`, `artifacts/tsan.txt`.

## Lab D - perf + flamegraph (WSL)
- Record: `perf record -g -- ./build/release/platform_core_app --duration 30`
- Convert: `perf script | stackcollapse-perf.pl | flamegraph.pl > artifacts/flame.svg`
- Artifact: `artifacts/perf.data`, `artifacts/flame.svg`, summary text.

## Lab E - Heap profiling
- Run: `heaptrack ./build/release/platform_core_app`
- Artifact: `artifacts/heaptrack.platform_core_app.gz`; open with `heaptrack_gui` for inspection.

## Lab F - Tracing
- Add NVTX or custom timestamp spans around pipeline stages.
- Collect: `trace.log` with start/end timestamps; compute latency in `notebooks/trace_analysis.ipynb` (TODO).
- Artifact: `artifacts/trace.log`, processed CSV.
