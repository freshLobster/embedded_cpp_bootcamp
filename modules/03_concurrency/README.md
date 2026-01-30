# Module 03_concurrency - Concurrency

**Mission:** Queues, deadlocks, races, clean shutdown.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.

## Lecture

### Threads as owned execution resources
`std::thread` is a handle that represents a single thread of execution, and constructing it starts the work immediately. That means ownership is explicit: a thread must be joined or detached, and the handle itself is move-only, which forces you to think about who is responsible for completion. In embedded or autonomy systems, that ownership model maps directly to watchdog and lifecycle logic: if a thread outlives the subsystem that spawned it, you have an availability or safety bug. Treat the thread handle as a resource that must be cleanly released just like a file descriptor or DMA buffer. ([cppreference: std::thread](https://en.cppreference.com/w/cpp/thread/thread))

`std::jthread` is a safer default when you want scoped execution because it automatically joins on destruction, preventing the "forgot to join" shutdown trap. It also integrates cooperative cancellation using `std::stop_token`, so your worker functions can check whether a stop has been requested and exit cleanly without races. This is the C++20 tool you want for deterministic shutdown in flight-control or perception pipelines where teardown order is safety-critical. The exercises in this module reinforce that cooperative stop is a design choice you build into the thread entry point, not an afterthought. ([cppreference: std::jthread](https://en.cppreference.com/w/cpp/thread/jthread), [cppreference: std::stop_token](https://en.cppreference.com/w/cpp/thread/stop_token))

### Coordination with mutexes and condition variables
Condition variables let a thread sleep until a condition is satisfied, but the API makes it explicit that waits can wake spuriously. The `wait` call atomically releases the mutex and blocks; on wake it re-locks and returns, which means you must re-check the predicate in a loop or use the predicated overload. In robotics pipelines this is the difference between sleeping until data arrives and waking on noise, which can turn a timing bug into a CPU spike. Building a correct waiting protocol is the baseline skill for any bounded queue or scheduler. ([cppreference: std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable))

Concurrency correctness relies on disciplined lock management. The C++ Core Guidelines explicitly warn to use RAII for locks and to avoid manual `lock()`/`unlock()` to prevent missed unlocks and exception paths. They also call out the standard approach to avoid deadlock when multiple mutexes are involved: acquire them with `std::lock` or `std::scoped_lock` so the ordering is managed for you. In practice, that means designing lock scopes to be small and obvious, and isolating lock ownership in helper types rather than scattered calls. ([C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

### Data races and atomics in pipelines
The Core Guidelines define a data race as concurrent access to the same object without synchronization where at least one access is a write, and the guidance is blunt: if you have a data race, nothing is guaranteed to work. In embedded autonomy software, races show up as rare, non-reproducible faults that become flight-test failures and safety incidents. The practical takeaway is to treat every shared variable as either protected by a mutex or as a carefully designed atomic, and to be explicit about which it is. This module's race-repro exercise is meant to make that failure mode concrete. ([C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

Atomics are not "lock-free magic"; they are tools with explicit memory-ordering semantics. The standard defines a range from `memory_order_relaxed` (atomicity only) to acquire/release, where a release store makes prior writes visible to a thread that performs a corresponding acquire load. Those ordering guarantees are what make single-producer/single-consumer queues safe without locks, but only if you apply them consistently. If you cannot explain which writes must be visible and when, default to higher-level synchronization and come back to atomics after you can measure the win. ([cppreference: memory_order](https://en.cppreference.com/w/cpp/atomic/memory_order))

## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_race_repro | [ex01_race_repro](exercises/ex01_race_repro/README.md) |
| ex02_deadlock | [ex02_deadlock](exercises/ex02_deadlock/README.md) |
| ex03_clean_shutdown | [ex03_clean_shutdown](exercises/ex03_clean_shutdown/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/03_concurrency/artifacts/`.

## Checklists and evidence
Use these files in `modules/03_concurrency/checklists/`:
- `mastery.md`: confirm you can explain the module goal, list failure modes you found, and map skills to autonomy/defense use cases.
- `validation.md`: run the validation commands and record results. At minimum:
  - `cmake --preset dev`
  - `ctest --preset dev -R Module03_concurrency` (if the module test filter exists)
- `review.md`: perform a quick self-review against `STYLE.md` and confirm no warnings or unsafe patterns remain.

Save any required artifacts in `modules/03_concurrency/artifacts/` and in each exercise’s `learner/artifacts/` folder.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/03_concurrency`
- JSON: `python3 tools/grader/grade.py --module 03 --json`
- Per-exercise grading is done inside each exercise folder README.
