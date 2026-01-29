#include <cassert>
#include <algorithm>
#include <cmath>
#include <vector>

struct LatencyStats {
    int p50{0};
    int p95{0};
};

LatencyStats compute_stats(std::vector<int> samples) {
    std::sort(samples.begin(), samples.end());
    auto idx = [&](double p) {
        size_t i = static_cast<size_t>(std::ceil(p * samples.size())) - 1;
        if (i >= samples.size()) {
            i = samples.size() - 1;
        }
        return samples[i];
    };
    return { idx(0.50), idx(0.95) };
}

int exercise() {
    std::vector<int> samples{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    auto s = compute_stats(samples);
    if (s.p50 != 50) {
        return 1;
    }
    if (s.p95 != 100) {
        return 2;
    }
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
