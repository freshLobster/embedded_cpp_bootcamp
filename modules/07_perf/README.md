# Module 07_perf - Performance

**Mission:** perf, flamegraphs, allocation hunting.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional (perf tooling): `sudo apt-get install -y linux-tools-common linux-tools-generic`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.
## Lecture

### Sampling and profiling with perf
`perf` is the standard Linux profiling tool, and it is designed for profiling and tracing using performance counters and tracepoints. That scope matters: you are not guessing where time is spent, you are measuring it with the same hardware and kernel facilities the system uses to schedule and count work. For autonomy pipelines, this is the difference between "it feels slow" and a defensible latency budget. This module uses perf as the baseline evidence for regression analysis. ?cite?turn15view0?

Because perf is a system-level tool, it forces you to think in terms of workloads and repeatability. You will be running realistic input data, capturing a profile, and comparing the profile after a change to see whether a regression occurred. That workflow is the core of performance engineering in mission-critical software. The goal is to make performance a measurable artifact, not a subjective impression. ?cite?turn15view0?

### Flamegraphs as a visual map of time
FlameGraph is a visualization that takes sampled stack traces and displays where time is spent, with width proportional to sample count. This means you can see which call stacks dominate execution rather than focusing only on individual functions. For embedded robotics workloads with deep pipelines, that context is essential because overhead often hides in glue code, serialization, and logging. The flamegraph tells you where to look first. ?cite?turn15view1?

A flamegraph is most valuable when you can compare before and after changes under the same workload. The visualization encodes the structure of the program's call stacks, so a widened frame is a concrete signal that a new cost has been introduced. That makes flamegraphs a powerful review tool when you are tracking regressions across commits. In this module you will generate and save flamegraph artifacts for exactly that reason. ?cite?turn15view1?

### Allocation profiling and bounded memory
Heaptrack is a heap memory profiler that records and analyzes heap allocations, which makes it ideal for finding allocation hot spots and leaks. In embedded systems, every unexpected allocation is a potential jitter source and a potential failure under memory pressure. Heaptrack gives you concrete evidence about when and where allocations occur. That evidence lets you decide whether to redesign a hot path or switch to an arena. ?cite?turn15view2?

Allocation profiling is also part of making memory use deterministic. If the profiler shows growth over time or spikes during critical loops, you can tie those observations to queue sizes, message rates, or logging behavior. That lets you set explicit limits and verify them under load. The exercises in this module make you capture and interpret allocation data instead of hand-waving about "probably fine" memory use. ?cite?turn15view2?



## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_perf_baseline | [ex01_perf_baseline](exercises/ex01_perf_baseline/README.md) |
| ex02_flamegraph | [ex02_flamegraph](exercises/ex02_flamegraph/README.md) |
| ex03_perf_regression | [ex03_perf_regression](exercises/ex03_perf_regression/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/07_perf/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/07_perf`
- JSON: `python3 tools/grader/grade.py --module 07 --json`
- Per-exercise grading is done inside each exercise folder README.
