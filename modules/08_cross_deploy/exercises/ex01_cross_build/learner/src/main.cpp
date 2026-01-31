// Exercise: Cross-build target probe
// Implement a compile-time architecture detection helper.
// The function should use preprocessor macros so it works in cross-builds.

#include <cassert> // For assert() in main.
#include <string>  // For std::string return type.

// TODO: return a string representing the target architecture.
// Use preprocessor macros to detect __aarch64__ and __x86_64__/ _M_X64.
// HOW: use #if defined(...) blocks and return a literal string.
std::string target_arch() {
    // TODO: add #if / #elif / #else blocks and return one of:
    // "aarch64", "x86_64", or "unknown".
    // Suggested pattern:
    // #if defined(__aarch64__) || defined(_M_ARM64)
    //   return "aarch64";
    // #elif defined(__x86_64__) || defined(_M_X64)
    //   return "x86_64";
    // #else
    //   return "unknown";
    // #endif
    return "unknown";
}

int exercise() {
    // Keep this error until target_arch() is implemented.
    #error TODO_implement_exercise
    // The probe must not return "unknown" on a supported architecture.
    auto arch = target_arch();
    if (arch == "unknown") return 1;
    return 0;
}

int main() {
    // The architecture probe must report a known target.
    assert(exercise() == 0);
    return 0;
}
