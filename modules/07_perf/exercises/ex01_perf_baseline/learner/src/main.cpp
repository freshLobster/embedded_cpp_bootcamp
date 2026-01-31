// Exercise: Performance baseline (dot product)
// Implement a simple dot-product to use as a profiling baseline.
// The function should be small, deterministic, and easy to benchmark.

#include <cassert> // For assert() in main and for checks in exercise().
#include <vector>  // For std::vector inputs.

// TODO: compute sum of element-wise products.
// Contract: a and b are the same length for this exercise.
// HOW: initialize a local accumulator, loop over indices, add a[i] * b[i].
int dot_product(const std::vector<int>& a, const std::vector<int>& b) {
    // TODO: iterate over indices and accumulate a[i] * b[i].
    // Hint: use size_t for the index and a local int sum accumulator.
    // Suggested outline:
    //   int sum = 0;
    //   for (size_t i = 0; i < a.size(); ++i) { sum += a[i] * b[i]; }
    //   return sum;
    (void)a;
    (void)b;
    return 0;
}

int exercise() {
    // Keep this error until you implement dot_product().
    #error TODO_implement_exercise
    // Known inputs for deterministic output.
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{4, 5, 6};

    // Expected: 1*4 + 2*5 + 3*6 = 32.
    if (dot_product(a, b) != 32) return 1;
    return 0;
}

int main() {
    // The baseline must produce the expected dot-product result.
    // Keeping the check local makes profiling output less noisy.
    assert(exercise() == 0);
    return 0;
}
