# ex02_deadlock – Diagnose lock inversion

What you are building: Deadlock repro and fix in MessageBus.
Why it matters: Deadlocks halt robots; must be prevented and diagnosed quickly.

Prerequisites check
- Configure with deadlock flag: `cmake --preset dev -DPLATFORM_FAILURE_DEADLOCK=ON`
- Ensure gdb available: `gdb --version`

Files you will touch
- `src/platform/message_bus.cpp`

Steps
1. Run app under gdb and hit deadlock:
```
cmake --build --preset dev --target platform_core_app
(gdb -ex "run" --args ./build/dev/platform_core_app) <<'EOF'
^C
thread apply all bt
quit
EOF
```
Expected: two threads blocked on mutexes.
2. Save backtrace to `modules/03_concurrency/artifacts/ex02_deadlock_bt.txt`.
3. Fix by removing `deadlock_mutex_` or enforcing consistent lock order.
4. Rebuild without flag: `cmake --preset dev -DPLATFORM_FAILURE_DEADLOCK=OFF && cmake --build --preset dev`
5. Run app 60s: `timeout 60 ./build/dev/platform_core_app` (expect no hang; stop with Ctrl+C).

Verification
- No deadlock; app responsive for 60s.
- Optional: `perf sched timehist` shows runnable threads.

Stop here and commit
- Message: "Module03: remove deadlock path"

If it fails
- gdb cannot attach: install gdb, ensure symbols built (Debug).
- Still hangs: ensure flag OFF and rebuild clean.

Stretch goals
- Add scoped_lock alternative covering shared_mutex.
