// Exercise: Latency jitter stats
// Compute min, max, and span from a set of latency samples.
// These numbers are a basic proxy for jitter on embedded targets.

#include <cassert> // For assert() in main.
#include <limits>  // For numeric_limits in min/max initialization.
#include <vector>  // For sample storage.

struct JitterStats {
    int min{0};
    int max{0};
    int span{0};
};

// TODO: compute min, max, and span from samples.
// HOW: initialize min to +inf, max to -inf, then update in a loop.
JitterStats compute_jitter(const std::vector<int>& samples) {
    // TODO: initialize min/max using numeric_limits.
    // TODO: iterate over samples and update min/max.
    // TODO: compute span = max - min.
    // Suggested outline:
    //   int min_v = std::numeric_limits<int>::max();
    //   int max_v = std::numeric_limits<int>::min();
    //   for (int v : samples) { min_v = std::min(min_v, v); max_v = std::max(max_v, v); }
    //   return {min_v, max_v, max_v - min_v};
    (void)samples;
    return {};
}

int exercise() {
    // Keep this error until compute_jitter() is implemented.
    #error TODO_implement_exercise
    auto s = compute_jitter({10, 12, 11, 15});
    if (s.min != 10) return 1;
    if (s.max != 15) return 2;
    if (s.span != 5) return 3;
    return 0;
}

int main() {
    // The jitter stats must match expected values.
    assert(exercise() == 0);
    return 0;
}
