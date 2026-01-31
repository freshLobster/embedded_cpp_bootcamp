// Solution: Nsight Systems marker string
// Provides a deterministic range label for profiling exercises.
// The string is human-readable so it is easy to spot in timelines.

#include <cassert> // assert() provides a minimal self-check.
#include <string>  // std::string for the marker label.

std::string profile_markers() {
    // In real code this could correspond to a profiling range name.
    return "nsys:range=compute";
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    auto s = profile_markers();
    if (s.find("nsys") == std::string::npos) return 1;
    return 0;
}

int main(){
    // The solution must emit a marker containing "nsys".
    assert(exercise()==0);
    return 0;
}
