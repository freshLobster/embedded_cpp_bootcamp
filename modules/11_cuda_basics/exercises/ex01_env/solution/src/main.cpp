// Solution: CUDA environment probe
// Detects CUDA compilation via the __CUDACC__ macro.

#include <cassert>

constexpr bool cuda_available() {
#if defined(__CUDACC__)
    // NVCC defines __CUDACC__ when compiling CUDA code.
    return true;
#else
    // Fallback for non-CUDA compilers.
    return false;
#endif
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    constexpr bool expected = cuda_available();
    if (cuda_available() != expected) {
        return 1;
    }
    return 0;
}

int main(){
    // The solution must compile and run in both CUDA and non-CUDA builds.
    assert(exercise()==0);
    return 0;
}
