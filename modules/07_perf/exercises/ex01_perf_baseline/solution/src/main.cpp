// Solution: Dot product baseline
// This provides a deterministic workload for perf measurements.

#include <cassert>
#include <vector>

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
