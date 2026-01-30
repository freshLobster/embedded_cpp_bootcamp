// Exercise: Atomic counter
// Implement a thread-safe counter using std::atomic to eliminate data races.

#include <atomic>  // For std::atomic.
#include <cassert> // For assert() in main.
#include <thread>  // For std::jthread.
#include <vector>  // For std::vector of threads.

// Counter uses atomic operations to safely increment from multiple threads.
class Counter {
public:
    // Increment must be atomic to avoid lost updates.
    void increment();

    // Read the current counter value in a thread-safe way.
    int value() const;

private:
    std::atomic<int> value_{0};
};

void Counter::increment() {
    // TODO: use fetch_add(1) to perform an atomic increment.
}

int Counter::value() const {
    // TODO: use load() to read the atomic value.
    return 0;
}

int exercise() {
    #error TODO_implement_exercise
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

    // jthread joins on destruction, but we join explicitly for clarity.
    for (auto& th : threads) {
        if (th.joinable()) th.join();
    }

    if (c.value() != kThreads * kIters) return 1;
    return 0;
}

int main() {
    // The exercise returns 0 only when atomic increments are correct.
    assert(exercise() == 0);
    return 0;
}
