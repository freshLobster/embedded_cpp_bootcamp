#pragma once

// Runs the CPU/GPU parity exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// CPU path must always compile; GPU path is optional.
int exercise();
int exercise_cpu();
#ifdef ENABLE_CUDA
int exercise_gpu();
#endif
