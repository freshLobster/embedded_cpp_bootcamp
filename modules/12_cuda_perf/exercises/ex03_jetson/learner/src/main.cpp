// Exercise: Jetson bottleneck classifier
// Implement a deterministic list of bottlenecks from boolean flags.
// The output order must be stable for CI and logging.

#include <cassert> // For assert() in main.
#include <string>  // For std::string labels.
#include <vector>  // For output list.

// TODO: return a vector of bottleneck labels in order cpu, gpu, io.
// HOW: push back "cpu" if cpu==true, then "gpu", then "io".
std::vector<std::string> bottlenecks(bool cpu, bool gpu, bool io) {
    // TODO: push labels in deterministic order.
    // Suggested outline:
    //   std::vector<std::string> out;
    //   if (cpu) out.push_back("cpu");
    //   if (gpu) out.push_back("gpu");
    //   if (io)  out.push_back("io");
    //   return out;
    (void)cpu;
    (void)gpu;
    (void)io;
    return {};
}

int exercise() {
    // Keep this error until bottlenecks() is implemented.
    #error TODO_implement_exercise
    auto b = bottlenecks(true, false, true);
    if (b.size() != 2) return 1;
    if (b[0] != "cpu" || b[1] != "io") return 2;
    return 0;
}

int main() {
    // The classifier must return the expected ordered labels.
    assert(exercise() == 0);
    return 0;
}
