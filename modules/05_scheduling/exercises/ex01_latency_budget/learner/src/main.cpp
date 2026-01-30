// Exercise: Latency budget statistics
// Compute p50 and p95 latency percentiles from sample data.

#include <algorithm> // For std::sort.
#include <cassert>   // For assert() in main.
#include <vector>    // For sample storage.

struct LatencyStats {
    int p50{0};
    int p95{0};
};

LatencyStats compute_stats(std::vector<int> samples) {
    // TODO: sort samples and compute p50/p95 deterministically.
    // Use an index-based percentile (e.g., p50 = element at 50th percentile).
    (void)samples;
    return {};
}

int exercise() {
    #error TODO_implement_exercise
    std::vector<int> samples{10,20,30,40,50,60,70,80,90,100};
    auto s = compute_stats(samples);
    if (s.p50 != 50) return 1;
    if (s.p95 != 100) return 2;
    return 0;
}

int main() {
    // The exercise returns 0 only when percentile math is correct.
    assert(exercise() == 0);
    return 0;
}
