// Solution: Bottleneck classifier
// Returns a deterministic list of CPU/GPU/IO bottlenecks.
// This mirrors how a Jetson pipeline might report constraints.

#include <cassert> // assert() provides a minimal self-check.
#include <string>  // std::string for labels.
#include <vector>  // std::vector for ordered output.

std::vector<std::string> bottlenecks(bool cpu, bool gpu, bool io) {
    std::vector<std::string> out;
    // Preserve order: cpu, gpu, io.
    if (cpu) out.push_back("cpu");
    if (gpu) out.push_back("gpu");
    if (io) out.push_back("io");
    return out;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    auto b = bottlenecks(true, false, true);
    if (b.size() != 2) return 1;
    if (b[0] != "cpu" || b[1] != "io") return 2;
    return 0;
}

int main(){
    // The solution must return the correct ordered labels.
    assert(exercise()==0);
    return 0;
}
