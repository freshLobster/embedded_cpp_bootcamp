// Exercise: CPU/GPU parity baseline
// Implement CPU vector addition as the reference result.
// This CPU path is the correctness oracle for later GPU work.

#include <cassert> // For assert() in main.
#include <vector>  // For std::vector inputs/outputs.

// TODO: return element-wise sum of vectors a and b.
// HOW: allocate an output vector of a.size() and fill each element.
std::vector<int> add_cpu(const std::vector<int>& a, const std::vector<int>& b) {
    // TODO: reserve output size and push_back a[i] + b[i].
    // Suggested outline:
    //   std::vector<int> out;
    //   out.reserve(a.size());
    //   for (size_t i = 0; i < a.size(); ++i) out.push_back(a[i] + b[i]);
    //   return out;
    (void)a;
    (void)b;
    return {};
}

int exercise() {
    // Keep this error until add_cpu() is implemented.
    #error TODO_implement_exercise
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{4, 5, 6};
    auto out = add_cpu(a, b);
    if (out.size() != 3) return 1;
    if (out[0] != 5 || out[2] != 9) return 2;
    return 0;
}

int main() {
    // The CPU reference must match expected results.
    assert(exercise() == 0);
    return 0;
}
