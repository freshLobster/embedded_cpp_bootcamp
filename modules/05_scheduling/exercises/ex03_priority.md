# ex03_priority – Compare scheduler priority

What you are building: Jitter comparison between normal and FIFO high priority runs.
Why it matters: Shows impact of thread priority on real-time-ish behavior.

Prerequisites check
- Tool: `perf` installed (`perf --version`).

Files you will touch
- None (optional log parsing script).
- `modules/05_scheduling/artifacts/ex03_default.timehist`
- `modules/05_scheduling/artifacts/ex03_fifo.timehist`

Steps
1. Run app normally and capture:
```
sudo perf sched timehist -p $(./build/release/platform_core_app & echo $!) > modules/05_scheduling/artifacts/ex03_default.timehist
sleep 10; pkill platform_core_app
```
2. Run with chrt FIFO 50:
```
sudo chrt -f 50 ./build/release/platform_core_app & pid=$!
sudo perf sched timehist -p $pid > modules/05_scheduling/artifacts/ex03_fifo.timehist
sleep 10; pkill platform_core_app
```
3. Compare jitter by counting max latency lines.

Verification
- FIFO run shows reduced max latency (expect noticeable decrease).

Stop here and commit
- Message: "Module05: priority jitter experiment"

If it fails
- Permission denied: need sudo for perf and chrt.

Stretch goals
- Automate diff in small python script.
