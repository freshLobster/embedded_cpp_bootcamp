#pragma once

// Reference solution entry points for Jetson bottleneck exercise.
int exercise();
int exercise_cpu();
#ifdef ENABLE_CUDA
int exercise_gpu();
#endif
