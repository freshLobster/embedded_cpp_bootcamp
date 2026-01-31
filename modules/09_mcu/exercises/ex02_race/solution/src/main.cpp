// Solution: Shared counter with atomic operations
// Demonstrates a race-free update pattern for shared state.
// This mirrors ISR/task updates on an MCU.

#include <cassert> // assert() provides a minimal self-check.
#include <atomic>  // std::atomic for race-free updates.
#include <thread>  // std::jthread for scoped lifetime threads.
#include <vector>  // std::vector for thread container.

class SharedCounter {
public:
    // Atomic increment; relaxed ordering is sufficient for a simple counter.
    void increment() { value_.fetch_add(1, std::memory_order_relaxed); }
    // Atomic read of the current value.
    int value() const { return value_.load(std::memory_order_relaxed); }
private:
    // Shared state protected by atomic operations.
    std::atomic<int> value_{0};
};

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    SharedCounter c;
    std::vector<std::jthread> threads;
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([&]() {
            for (int i = 0; i < 1000; ++i) c.increment();
        });
    }
    for (auto& th : threads) th.join();
    if (c.value() != 4000) return 1;
    return 0;
}

int main(){
    // The solution must produce the expected final count.
    assert(exercise()==0);
    return 0;
}
