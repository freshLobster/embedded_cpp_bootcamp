#pragma once

// Reference solution entry points for CPU/GPU parity.
int exercise();
int exercise_cpu();
#ifdef ENABLE_CUDA
int exercise_gpu();
#endif
