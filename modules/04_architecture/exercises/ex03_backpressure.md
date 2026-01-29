# ex03_backpressure – Demonstrate bounded queue behavior

What you are building: Backpressure experiment with tiny queue size and high publish rate.
Why it matters: Prevents unbounded memory in real systems.

Prerequisites check
- Editable scheduler period in `pipeline.cpp` (sensor scheduler 50 ms currently).

Files you will touch
- `src/platform/pipeline.cpp`
- `modules/04_architecture/artifacts/ex03_backpressure.log`

Steps
1. Temporarily set bounded queue capacity to 8 in ThreadPool ctor usage or BoundedQueue initialization.
2. Increase sensor scheduler rate to 5 ms.
3. Add log when enqueue fails or blocks indicating backpressure.
4. Build/run debug app for 15s capturing logs:
```
cmake --build --preset dev --target platform_core_app
./build/dev/platform_core_app > modules/04_architecture/artifacts/ex03_backpressure.log 2>&1 & sleep 15; pkill platform_core_app
```
Expected: log contains backpressure markers, but process stays alive.

Verification
- Count markers: `grep -c backpressure modules/04_architecture/artifacts/ex03_backpressure.log` > 0
- Memory stable: `ps -o rss= -C platform_core_app` roughly steady (<10% drift).

Stop here and commit
- Message: "Module04: backpressure experiment"

If it fails
- App exits early: ensure shutdown not triggered by unhandled exception; check logs.

Stretch goals
- Convert backpressure event to metrics counter.
