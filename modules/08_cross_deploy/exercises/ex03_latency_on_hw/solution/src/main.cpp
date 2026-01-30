// Solution: Jitter statistics
// Computes min, max, and span from latency samples.

#include <cassert>
#include <vector>
#include <limits>

struct JitterStats {
    int min{0};
    int max{0};
    int span{0};
};

JitterStats compute_jitter(const std::vector<int>& samples) {
    int minv = std::numeric_limits<int>::max();
    int maxv = std::numeric_limits<int>::min();
    for (int v : samples) {
        // Update min and max trackers.
        if (v < minv) minv = v;
        if (v > maxv) maxv = v;
    }
    // Span is the jitter range.
    return {minv, maxv, maxv - minv};
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    auto s = compute_jitter({10,12,11,15});
    if (s.min != 10 || s.max != 15 || s.span != 5) {
        return 1;
    }
    return 0;
}

int main(){
    // The solution must compute correct min/max/span values.
    assert(exercise()==0);
    return 0;
}
