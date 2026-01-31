// Exercise: CUDA environment detection
// Implement a compile-time probe for CUDA compilation.
// This helps select CPU vs GPU code paths at build time.

#include <cassert> // For assert() in main.

// TODO: return true if compiled with NVCC, false otherwise.
// HOW: use #if defined(__CUDACC__) to switch the return value.
constexpr bool cuda_available() {
    // TODO: use #if defined(__CUDACC__) to detect CUDA compilation.
    // Suggested pattern:
    // #if defined(__CUDACC__)
    //   return true;
    // #else
    //   return false;
    // #endif
    return false;
}

int exercise() {
    // Keep this error until cuda_available() is implemented.
    #error TODO_implement_exercise
    constexpr bool expected = cuda_available();
    if (cuda_available() != expected) return 1;
    return 0;
}

int main() {
    // The environment probe must be consistent.
    assert(exercise() == 0);
    return 0;
}
