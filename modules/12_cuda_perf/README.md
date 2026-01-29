# Module 12_cuda_perf - CUDA Perf

**Mission:** Nsight/CLI profiling, divergence, Jetson awareness.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional (CUDA toolkit): `sudo apt-get install -y nvidia-cuda-toolkit`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.
## Lecture

### Profiling with Nsight Systems and Nsight Compute
Nsight Systems is a system-wide performance analysis tool that provides a timeline view across CPU and GPU activity. That perspective matters because GPU kernels do not exist in isolation; their latency is shaped by CPU launches, synchronization, and data movement. For autonomy pipelines, system-level timelines are the only reliable way to explain end-to-end latency. This module uses Nsight Systems (or its CLI equivalents) to capture those timelines as artifacts. ([Nsight Systems](https://docs.nvidia.com/nsight-systems/))

Nsight Compute is a kernel profiler focused on detailed GPU metrics and per-kernel analysis. It is the tool you use when a specific kernel is too slow and you need to understand why. This module uses Nsight Compute to quantify kernel performance and validate the impact of optimizations. The key point is that kernel-level and system-level profiling are complementary, not interchangeable. ([Nsight Compute](https://docs.nvidia.com/nsight-compute/))

### Divergence and memory access efficiency
The CUDA Best Practices Guide explains that warp divergence occurs when threads in a warp take different execution paths, which reduces efficiency because warps execute one path at a time. In real workloads, divergence often comes from branch-heavy logic or data-dependent control flow. In autonomy pipelines, this shows up in conditional processing based on sensor content or classification thresholds. This module forces you to observe divergence and fix it deliberately. ([CUDA Best Practices: Divergence](https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/index.html#divergent-branches))

The same guide emphasizes that global memory access is most efficient when threads in a warp access consecutive addresses, enabling coalesced memory transactions. Uncoalesced access multiplies memory traffic and can dominate kernel time. That is why memory layout and indexing are performance-critical decisions, not just implementation details. In this module you will measure the impact of access patterns directly. ([CUDA Best Practices: Coalescing](https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/index.html#coalesced-memory-accesses))

### Jetson-class constraints and deployment awareness
Jetson platforms use power models that set CPU/GPU clock and power limits, and those limits are configured via a power mode model. The platform power management documentation makes it clear that different modes provide different performance levels by changing available power and frequency. This matters because a kernel that is fast on a desktop GPU can be limited by power or frequency on an embedded Jetson-class device. Your profiling artifacts must therefore include the power mode context. ([Jetson Power Management](https://docs.nvidia.com/jetson/archives/r35.3.1/DeveloperGuide/text/SD/PlatformPowerAndPerformance/JetsonXavierNxSeriesAndJetsonAgxXavierSeries.html))

Because the power mode constrains available CPU and GPU clocks, the balance between CPU work and GPU work becomes a deployment decision, not just a coding decision (inference). A pipeline that over-saturates the GPU can starve CPU-side stages if the system is in a lower power mode. This module explicitly connects profiling data to deployment constraints so you learn to reason about performance in realistic embedded conditions. ([Jetson Power Management](https://docs.nvidia.com/jetson/archives/r35.3.1/DeveloperGuide/text/SD/PlatformPowerAndPerformance/JetsonXavierNxSeriesAndJetsonAgxXavierSeries.html))



## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_nsys | [ex01_nsys](exercises/ex01_nsys/README.md) |
| ex02_divergence | [ex02_divergence](exercises/ex02_divergence/README.md) |
| ex03_jetson | [ex03_jetson](exercises/ex03_jetson/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/12_cuda_perf/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/12_cuda_perf`
- JSON: `python3 tools/grader/grade.py --module 12 --json`
- Per-exercise grading is done inside each exercise folder README.
- CUDA checks require `--enable-cuda` to score full points.
