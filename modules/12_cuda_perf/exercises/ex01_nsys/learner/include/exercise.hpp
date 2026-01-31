#pragma once

// Runs the Nsight marker exercise self-check.
// Return 0 on success; non-zero codes map to specific failures.
// CPU-only path must always compile; GPU path is optional.
int exercise();
int exercise_cpu();
#ifdef ENABLE_CUDA
int exercise_gpu();
#endif
