#include <cassert>
#include <cstdint>
#include <vector>

int popcount32(uint32_t v) {
    int c = 0;
    while (v) {
        v &= v - 1;
        ++c;
    }
    return c;
}

double average_active_lanes(const std::vector<uint32_t>& masks) {
    if (masks.empty()) return 0.0;
    double total = 0.0;
    for (auto m : masks) {
        total += static_cast<double>(popcount32(m)) / 32.0;
    }
    return total / masks.size();
}

int exercise() {
    std::vector<uint32_t> masks{0xFFFFFFFFu, 0x0u};
    auto avg = average_active_lanes(masks);
    if (avg <= 0.49 || avg >= 0.51) return 1;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
