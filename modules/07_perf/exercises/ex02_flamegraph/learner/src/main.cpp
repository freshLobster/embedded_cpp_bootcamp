// Exercise: Flamegraph call chain
// Build a multi-level call chain to generate a useful stack profile.
// The chain should be deterministic so the flamegraph is stable.

#include <cassert> // For assert() in main.

// TODO: Implement the lowest-level work function.
// Keep it simple and deterministic (e.g., return x * 2).
// This function should do a small amount of math so perf samples have work.
int work(int x);

// TODO: Implement a call chain with at least three levels.
// Each level should call the next to create a deep stack for profiling.
int level3(int x);
int level2(int x);
int level1(int x);

int work(int x) {
    // TODO: return a deterministic computation based on x.
    // Suggested: return x * 2 so the expected output is easy to compute.
    (void)x;
    return 0;
}

int level3(int x) {
    // TODO: call work(x + 1) or similar.
    // Use a small transformation so each level contributes a visible frame.
    (void)x;
    return 0;
}

int level2(int x) {
    // TODO: call level3(x + 1) to deepen the stack.
    // Keep the arithmetic simple so you can predict the final value.
    (void)x;
    return 0;
}

int level1(int x) {
    // TODO: call level2(x + 1) as the top of the chain.
    // This is the entry point used by the test.
    (void)x;
    return 0;
}

int exercise() {
    // Keep this error until you have implemented the call chain.
    #error TODO_implement_exercise
    // Verify the call chain returns a known value.
    // With a +1 at each level and work(x)=x*2, level1(1) should yield 8.
    int v = level1(1);
    if (v != 8) return 1;
    return 0;
}

int main() {
    // The call chain must produce the expected deterministic output.
    assert(exercise() == 0);
    return 0;
}
