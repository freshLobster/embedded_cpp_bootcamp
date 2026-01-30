// Solution: Atomic counter
// Uses std::atomic operations to prevent data races and lost updates.

#include <atomic>  // For std::atomic.
#include <cassert> // For assert() in main.
#include <thread>  // For std::jthread.
#include <vector>  // For std::vector.

class Counter {
public:
    void increment() {
        // Atomic increment; relaxed ordering is sufficient for a simple counter
        // because we only need atomicity, not cross-thread ordering.
        value_.fetch_add(1);
    }

    int value() const {
        // Atomic read; returns the current value safely.
        return value_.load();
    }

private:
    std::atomic<int> value_{0};
};

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    Counter c;
    constexpr int kThreads = 4;
    constexpr int kIters = 10000;

    std::vector<std::jthread> threads;
    for (int t = 0; t < kThreads; ++t) {
        threads.emplace_back([&]() {
            for (int i = 0; i < kIters; ++i) {
                c.increment();
            }
        });
    }

    for (auto& th : threads) {
        if (th.joinable()) th.join();
    }

    if (c.value() != kThreads * kIters) return 1;
    return 0;
}

int main() {
    // The solution must satisfy the atomic counter invariant.
    assert(exercise() == 0);
    return 0;
}
