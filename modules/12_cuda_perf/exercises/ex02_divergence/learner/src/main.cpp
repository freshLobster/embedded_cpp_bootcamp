// Exercise: Warp divergence metric
// Implement popcount and average active lanes for 32-bit masks.
// This models how many lanes in a warp are active on average.

#include <cassert>  // For assert() in main.
#include <cstdint>  // For uint32_t.
#include <vector>   // For list of masks.

// TODO: count set bits in a 32-bit value.
// HOW: use the classic v &= (v - 1) loop to clear one bit per iteration.
int popcount32(uint32_t v) {
    // TODO: use v &= v - 1 loop to count bits.
    // Suggested outline:
    //   int count = 0;
    //   while (v != 0) { v &= (v - 1); ++count; }
    //   return count;
    (void)v;
    return 0;
}

// TODO: compute average active lanes for a list of masks.
// HOW: compute popcount(mask) / 32.0 for each, then average.
double average_active_lanes(const std::vector<uint32_t>& masks) {
    // TODO: handle empty input by returning 0.0.
    // TODO: sum popcount/32.0 for each mask and divide by count.
    // Suggested outline:
    //   if (masks.empty()) return 0.0;
    //   double sum = 0.0;
    //   for (auto m : masks) sum += popcount32(m) / 32.0;
    //   return sum / masks.size();
    (void)masks;
    return 0.0;
}

int exercise() {
    // Keep this error until popcount32 and average_active_lanes are implemented.
    #error TODO_implement_exercise
    std::vector<uint32_t> masks{0xFFFFFFFFu, 0x0u};
    auto avg = average_active_lanes(masks);
    if (avg <= 0.49 || avg >= 0.51) return 1;
    return 0;
}

int main() {
    // The average active lanes must be about 0.5 for one full and one empty mask.
    assert(exercise() == 0);
    return 0;
}
