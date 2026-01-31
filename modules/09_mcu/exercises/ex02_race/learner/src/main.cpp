// Exercise: MCU-style shared counter (race-free)
// Implement a shared counter updated by multiple threads using atomics.
// This models ISR/task contention on a shared variable.

#include <cassert> // For assert() in main.
#include <atomic>  // For std::atomic counter.
#include <thread>  // For std::jthread.
#include <vector>  // For thread container.

// SharedCounter models a counter updated by multiple tasks/ISRs.
// The goal is to remove races with atomic operations.
class SharedCounter {
public:
    // TODO: increment counter atomically.
    // HOW: use value_.fetch_add(1, std::memory_order_relaxed).
    void increment();

    // TODO: read counter atomically.
    // HOW: use value_.load(std::memory_order_relaxed).
    int value() const;

private:
    std::atomic<int> value_{0};
};

void SharedCounter::increment() {
    // TODO: use fetch_add with relaxed ordering.
    // Using relaxed ordering is sufficient for a pure counter.
}

int SharedCounter::value() const {
    // TODO: return value_.load with relaxed ordering.
    return 0;
}

int exercise() {
    // Keep this error until SharedCounter is implemented.
    #error TODO_implement_exercise
    SharedCounter c;
    std::vector<std::jthread> threads;
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([&]() {
            for (int i = 0; i < 1000; ++i) {
                c.increment();
            }
        });
    }
    for (auto& th : threads) {
        if (th.joinable()) th.join();
    }
    if (c.value() != 4000) return 1;
    return 0;
}

int main() {
    // The counter must match the expected total increments.
    assert(exercise() == 0);
    return 0;
}
