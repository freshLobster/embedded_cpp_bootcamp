// Solution: Cross-build target probe
// Uses compile-time macros to identify the target architecture.
// This is a compile-time decision so it works in cross-build pipelines.

#include <cassert> // assert() provides a minimal self-check.
#include <string>  // std::string for the return value.

std::string target_arch() {
#if defined(__aarch64__) || defined(_M_ARM64)
    // GCC/Clang define __aarch64__ for 64-bit ARM targets.
    // MSVC uses _M_ARM64 for the same target.
    return "aarch64";
#elif defined(__x86_64__) || defined(_M_X64)
    // __x86_64__ is used by GCC/Clang; _M_X64 is used by MSVC.
    return "x86_64";
#else
    // Fall back to unknown if no expected macro is defined.
    return "unknown";
#endif
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    auto arch = target_arch();
    if (arch == "unknown") {
        return 1;
    }
    return 0;
}

int main(){
    // The solution must identify a known architecture.
    assert(exercise()==0);
    return 0;
}
