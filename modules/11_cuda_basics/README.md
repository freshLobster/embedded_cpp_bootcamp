# Module 11_cuda_basics - CUDA Basics

**Mission:** Environment, CPU/GPU parity, RAII CUDA buffer.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Optional (CUDA toolkit): `sudo apt-get install -y nvidia-cuda-toolkit`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.
## Lecture

### Kernel execution model and launch geometry
The CUDA programming model organizes parallel work into a grid of thread blocks, and a kernel is executed by that grid. Threads are grouped into blocks, and the grid/block dimensions are part of the kernel launch configuration. This abstraction is central to how you think about mapping data to computation in GPU code. In this module, you will explicitly choose grid and block sizes to match the data size and verify correctness against a CPU reference. ([CUDA Programming Model](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#programming-model))

Because the grid and block layout are part of the kernel launch, performance and correctness depend on those choices. A wrong launch geometry can silently leave data unprocessed or overrun buffers. The exercises here are designed to make those failure modes visible, so you learn to reason about indexing and boundaries. This is the foundational skill behind every CUDA kernel you will write. ([CUDA Programming Model](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#programming-model))

### Memory spaces and explicit transfers
CUDA exposes a memory hierarchy that includes global, shared, and local memory, and the programming guide makes those spaces explicit. Understanding which data lives where is critical because it defines visibility, lifetime, and access cost. Even in a basic kernel, you must know which arrays are in global memory and which data should be staged in shared memory for reuse. The exercises emphasize this by asking you to compare CPU and GPU results with identical inputs. ([CUDA Memory Hierarchy](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#memory-hierarchy))

The programming model also distinguishes host and device memory spaces, which means data must be transferred explicitly between them. That separation is why CPU/GPU parity tests are essential: you must confirm that the data you copied is the data you compute on. It also means you should minimize unnecessary transfers because they are part of the execution cost. This module teaches you to make those transfers explicit and verifiable. ([CUDA Memory Management](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#memory-management))

### Error handling and CUDA resource ownership
The CUDA Runtime API returns `cudaError_t` values from its functions, and you are expected to check those return codes. Error handling discipline is not optional: a kernel launch that fails silently will corrupt downstream results, and you may not notice until integration testing. In safety-critical pipelines, that is unacceptable. This module makes you capture and report errors as part of every CUDA call. ([cudaError_t](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__TYPES.html))

CUDA memory allocation is explicit, with functions like `cudaMalloc` returning a `cudaError_t` status (inference). In C++, that is a strong signal to wrap allocations in RAII so that `cudaFree` happens even on exceptions or early returns. The module's RAII buffer exercise forces you to encode ownership and lifetime as types, not comments. That approach is the only reliable way to manage GPU resources at scale. ([cudaMalloc](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__MEMORY.html))



## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_env | [ex01_env](exercises/ex01_env/README.md) |
| ex02_cpu_gpu_parity | [ex02_cpu_gpu_parity](exercises/ex02_cpu_gpu_parity/README.md) |
| ex03_raii_buffer | [ex03_raii_buffer](exercises/ex03_raii_buffer/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/11_cuda_basics/artifacts/`.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/11_cuda_basics`
- JSON: `python3 tools/grader/grade.py --module 11 --json`
- Per-exercise grading is done inside each exercise folder README.
- CUDA checks require `--enable-cuda` to score full points.
