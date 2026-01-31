// Solution: Warp divergence metric
// Computes average active lanes from warp masks.
// This is a CPU-side proxy for divergence analysis.

#include <cassert> // assert() provides a minimal self-check.
#include <cstdint> // uint32_t for masks.
#include <vector>  // std::vector for mask list.

int popcount32(uint32_t v) {
    int c = 0;
    while (v) {
        // Clear the lowest set bit each iteration.
        v &= v - 1;
        ++c;
    }
    return c;
}

double average_active_lanes(const std::vector<uint32_t>& masks) {
    if (masks.empty()) return 0.0;
    double total = 0.0;
    for (auto m : masks) {
        // Each mask represents a 32-lane warp.
        total += static_cast<double>(popcount32(m)) / 32.0;
    }
    // Average across all masks.
    return total / masks.size();
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    std::vector<uint32_t> masks{0xFFFFFFFFu, 0x0u};
    auto avg = average_active_lanes(masks);
    if (avg <= 0.49 || avg >= 0.51) return 1;
    return 0;
}

int main(){
    // The solution must compute the expected average active lanes.
    assert(exercise()==0);
    return 0;
}
