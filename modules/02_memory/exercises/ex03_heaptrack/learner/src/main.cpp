// Exercise: Heap profiling workload
// Build a deterministic allocation pattern so you can profile memory usage.

#include <cassert> // For assert() in main.
#include <vector>  // For allocation workload.

// Build a deterministic allocation workload and return a sum that proves
// the data was created and accessed. The profiling tools will observe the
// allocation behavior of this function.
int allocate_and_free(int n) {
    // TODO: create n vectors of increasing size and sum their contents.
    // Example idea: for i in [1..n], allocate vector<int> of size i,
    // fill with 1..i, and accumulate into a running sum.
    (void)n;
    return 0;
}

int exercise() {
    #error TODO_implement_exercise
    int sum = allocate_and_free(4);
    if (sum != 10) return 1;
    return 0;
}

int main() {
    // The exercise returns 0 only if the workload is correct.
    assert(exercise() == 0);
    return 0;
}
