# Module 05_scheduling - Scheduling

**Mission:** Latency/jitter budgets, watchdogs, safe defaults.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.
## Lecture

### Latency budgets and scheduler behavior
On Linux, real-time scheduling policies like SCHED_FIFO and SCHED_RR are priority-based, and a runnable thread with higher priority will preempt lower-priority work. This is the mechanical reason latency budgets are not just math: if a control thread runs at a higher real-time priority, it can take CPU immediately, but if you misconfigure priority you can starve critical work. Understanding the scheduler's rules is the first step to writing repeatable timing tests. In this module you will measure latency under load to see these effects directly. ([sched(7)](https://man7.org/linux/man-pages/man7/sched.7.html))

SCHED_RR differs from SCHED_FIFO by adding round-robin time slices among threads at the same priority, while SCHED_FIFO lets a runnable thread keep the CPU until it blocks or a higher-priority thread arrives. That means your choice of policy affects jitter: SCHED_RR can be fairer under equal priority, but SCHED_FIFO can reduce context-switch noise if your critical loop yields explicitly. When you build periodic tasks, you must align your time budget with the policy you choose so your measured jitter makes sense. The exercise on latency budgets is designed to force that alignment. ([sched(7)](https://man7.org/linux/man-pages/man7/sched.7.html))

### Timeouts and watchdogs as safety rails
The Linux watchdog API exposes a /dev/watchdog device that expects periodic keep-alive activity; if the system stops responding, the hardware or kernel watchdog can reset the system. This is the canonical safety rail for embedded systems that must fail fast rather than hang silently. In practice, you integrate a watchdog ping into your health monitor and treat missed deadlines as actionable faults. That is why your code must be able to detect "no progress" instead of waiting forever. ([Linux Watchdog API](https://www.kernel.org/doc/html/latest/watchdog/watchdog-api.html))

Because the watchdog acts on a timer, your software must express timeouts clearly and consistently. Using explicit timeouts on blocking operations gives the watchdog a chance to observe a stalled subsystem rather than letting a single deadlock freeze the process. When you combine watchdogs with structured logging and metrics, you can prove that your fallback logic triggers under load. This module's timeout and fallback exercise is effectively a rehearsal for that failure mode. ([Linux Watchdog API](https://www.kernel.org/doc/html/latest/watchdog/watchdog-api.html))

### Priority inversion awareness and safe defaults
Priority inversion happens when a high-priority thread is blocked behind a lock held by a lower-priority thread. POSIX mutexes can be configured with priority inheritance (PRIO_INHERIT), which temporarily boosts the lower-priority thread so it can release the lock and unblock the high-priority one. That mechanism is essential when you have mixed-priority pipelines and cannot afford long priority inversions. The goal is not to eliminate locks, but to make their worst-case impact bounded and explainable. ([pthread_mutexattr_setprotocol](https://man7.org/linux/man-pages/man3/pthread_mutexattr_setprotocol.3.html))

Real-time policies like SCHED_FIFO let a runnable thread continue until it blocks, so unbounded critical sections are especially dangerous because they can starve unrelated work. Safe defaults therefore include short lock scopes, explicit timeouts, and thread priorities that match the system's timing contracts. The same scheduler behavior that gives you low latency can also hide starvation bugs until late testing, which is why you will measure and budget latency explicitly in this module. The emphasis here is on making scheduler behavior visible and testable rather than magical. ([sched(7)](https://man7.org/linux/man-pages/man7/sched.7.html))



## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_latency_budget | [ex01_latency_budget](exercises/ex01_latency_budget/README.md) |
| ex02_timeout_fallback | [ex02_timeout_fallback](exercises/ex02_timeout_fallback/README.md) |
| ex03_priority | [ex03_priority](exercises/ex03_priority/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/05_scheduling/artifacts/`.

## Checklists and evidence
Use these files in `modules/05_scheduling/checklists/`:
- `mastery.md`: confirm you can explain the module goal, list failure modes you found, and map skills to autonomy/defense use cases.
- `validation.md`: run the validation commands and record results. At minimum:
  - `cmake --preset dev`
  - `ctest --preset dev -R Module05_scheduling` (if the module test filter exists)
- `review.md`: perform a quick self-review against `STYLE.md` and confirm no warnings or unsafe patterns remain.

Save any required artifacts in `modules/05_scheduling/artifacts/` and in each exercise’s `learner/artifacts/` folder.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/05_scheduling`
- JSON: `python3 tools/grader/grade.py --module 05 --json`
- Per-exercise grading is done inside each exercise folder README.
