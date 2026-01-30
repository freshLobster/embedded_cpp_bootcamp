// Solution: Heap profiling workload
// This implementation builds a predictable allocation pattern for profiling.
// The goal is repeatable allocations so tools like Massif can compare runs.

#include <cassert> // For assert() in main.
#include <vector>  // For allocation workload.

int allocate_and_free(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        // Allocate a vector with predictable size.
        // The allocation size grows with i, creating a clear pattern.
        std::vector<int> v(static_cast<size_t>(i));
        for (int j = 0; j < i; ++j) {
            v[static_cast<size_t>(j)] = j + 1;
            sum += j + 1;
        }
        // v is freed at end of loop iteration, creating a clear allocation pattern.
    }
    return sum;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    int sum = allocate_and_free(4);
    if (sum != 10) return 1; // 1+2+3+4 = 10
    return 0;
}

int main() {
    // The solution must satisfy the deterministic workload check.
    assert(exercise() == 0);
    return 0;
}
