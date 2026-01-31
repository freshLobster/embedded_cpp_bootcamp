#pragma once

// Reference solution entry points for divergence exercise.
int exercise();
int exercise_cpu();
#ifdef ENABLE_CUDA
int exercise_gpu();
#endif
