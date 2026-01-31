// Solution: Dot product baseline
// This provides a deterministic workload for perf measurements.
// The goal is correctness and repeatability, not extreme optimization.

#include <cassert> // assert() provides a simple correctness check.
#include <vector>  // std::vector holds the inputs.

int dot_product(const std::vector<int>& a, const std::vector<int>& b) {
    int sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        // Multiply corresponding elements and accumulate.
        sum += a[i] * b[i];
    }
    return sum;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    std::vector<int> a{1,2,3};
    std::vector<int> b{4,5,6};
    // Known result: 1*4 + 2*5 + 3*6 = 32.
    if (dot_product(a,b) != 32) {
        return 1;
    }
    return 0;
}

int main(){
    // The solution must compute the known dot-product result.
    assert(exercise()==0);
    return 0;
}
