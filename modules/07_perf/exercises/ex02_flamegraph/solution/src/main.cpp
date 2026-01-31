// Solution: Call-chain for flamegraph practice
// This creates a predictable stack trace for profilers.
// The arithmetic is intentionally simple to keep profiling deterministic.

#include <cassert> // assert() provides a minimal self-check.

// Lowest-level work function: deterministic arithmetic.
int work(int x) { return x * 2; }
// Each level adds 1 and calls the next level to build stack depth.
int level3(int x) { return work(x + 1); }
int level2(int x) { return level3(x + 1); }
int level1(int x) { return level2(x + 1); }

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    int v = level1(1);
    // With three +1 layers and work(x)=x*2, level1(1) == 8.
    if (v != 8) {
        return 1;
    }
    return 0;
}

int main(){
    // The solution must produce the expected chain result.
    assert(exercise()==0);
    return 0;
}
