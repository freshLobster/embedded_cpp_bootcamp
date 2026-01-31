// Exercise: Nsight Systems marker
// Implement a deterministic marker string for profiling ranges.
// The goal is to produce a recognizable label for profiler timelines.

#include <cassert> // For assert() in main.
#include <string>  // For std::string.

// TODO: return a marker string that includes "nsys".
// HOW: build a short, human-readable label that a profiler can display.
std::string profile_markers() {
    // TODO: return something like "nsys:range=compute".
    // Keep it short so it is readable in timeline views.
    return {};
}

int exercise() {
    // Keep this error until profile_markers() is implemented.
    #error TODO_implement_exercise
    auto s = profile_markers();
    if (s.find("nsys") == std::string::npos) return 1;
    return 0;
}

int main() {
    // The marker must include the substring "nsys".
    assert(exercise() == 0);
    return 0;
}
