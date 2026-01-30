// Solution: Latency budget statistics
// Computes deterministic p50 and p95 percentiles from samples.
// Sorting and index selection produce a stable, repeatable metric.

#include <algorithm> // For std::sort.
#include <cassert>   // For assert() in main.
#include <vector>    // For sample storage.

struct LatencyStats {
    int p50{0};
    int p95{0};
};

LatencyStats compute_stats(std::vector<int> samples) {
    std::sort(samples.begin(), samples.end());
    if (samples.empty()) {
        return {};
    }
    // Use (size - 1) so the max index is valid for 0-based arrays.
    const auto idx50 = static_cast<size_t>((samples.size() - 1) * 0.50);
    const auto idx95 = static_cast<size_t>((samples.size() - 1) * 0.95);
    return {samples[idx50], samples[idx95]};
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    std::vector<int> samples{10,20,30,40,50,60,70,80,90,100};
    auto s = compute_stats(samples);
    if (s.p50 != 50) return 1;
    if (s.p95 != 100) return 2;
    return 0;
}

int main() {
    // The solution must compute correct percentiles for a known dataset.
    assert(exercise() == 0);
    return 0;
}
