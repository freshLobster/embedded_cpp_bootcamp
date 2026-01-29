# ex02_tracing – Add lightweight tracing

What you are building: Timestamped span tracing around pipeline stages writing to log file.
Why it matters: Needed to debug latency and ordering in autonomy stacks.

Prerequisites check
- Confirm logging available: `grep -n "log(LogLevel" src/platform/logging.cpp`

Files you will touch
- `src/platform/pipeline.cpp`
- `modules/04_architecture/artifacts/ex02_trace.log`

Steps
1. Add trace log lines around perception and control publish paths using `LOG_DEBUG` with start/end timestamps.
2. Build and run release app for 10s:
```
cmake --build --preset release --target platform_core_app
./build/release/platform_core_app > modules/04_architecture/artifacts/ex02_trace.log 2>&1 & sleep 10; pkill platform_core_app
```
Expected: log file contains start/end markers with timestamps.

Verification
- Parse log: `grep -c "TRACE" modules/04_architecture/artifacts/ex02_trace.log` > 0
- `ctest --preset release` still passes.

Stop here and commit
- Message: "Module04: add pipeline tracing"

If it fails
- No debug logs: ensure log level set to Debug at app start.

Stretch goals
- Emit JSON lines for ingestion by trace tools.
