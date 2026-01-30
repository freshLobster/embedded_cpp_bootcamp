// Solution: CPU reference vector addition
// This serves as the correctness baseline for GPU parity checks.

#include <cassert>
#include <vector>

std::vector<int> add_cpu(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> out;
    // Reserve once to avoid repeated reallocations.
    out.reserve(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        // Element-wise addition.
        out.push_back(a[i] + b[i]);
    }
    return out;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    std::vector<int> a{1,2,3};
    std::vector<int> b{4,5,6};
    auto out = add_cpu(a,b);
    if (out[0] != 5 || out[2] != 9) return 1;
    return 0;
}

int main(){
    // The solution must produce correct element-wise sums.
    assert(exercise()==0);
    return 0;
}
