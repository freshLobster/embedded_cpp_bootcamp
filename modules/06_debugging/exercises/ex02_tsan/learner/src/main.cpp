// Exercise: ThreadSanitizer race removal
// Implement a thread-safe log aggregator that can be updated concurrently.
// The focus is on correct locking, not on performance optimization.

#include <cassert> // For assert() in main.
#include <mutex>   // For std::mutex and std::lock_guard.
#include <thread>  // For std::jthread in the test.
#include <vector>  // For log storage.

// ThreadSafeLog stores integer entries from multiple threads.
// All access to entries_ must be protected by m_.
// Design intent:
//  - Only one thread touches entries_ at a time.
//  - lock_guard keeps lock/unlock exception-safe.
class ThreadSafeLog {
public:
    // TODO: append a value to the log in a thread-safe way.
    // HOW: lock m_ with std::lock_guard, then push_back on entries_.
    void log(int v);

    // TODO: return the sum of all logged values safely.
    // HOW: lock m_, iterate entries_, accumulate into a local int.
    int sum() const;

    // Optional helper: current entry count.
    // HOW: lock m_, then return entries_.size().
    size_t size() const;

private:
    mutable std::mutex m_;
    std::vector<int> entries_;
};

void ThreadSafeLog::log(int v) {
    // TODO: lock m_ and push_back v into entries_.
    // Hint: std::lock_guard<std::mutex> guard(m_);
    (void)v;
}

int ThreadSafeLog::sum() const {
    // TODO: lock m_ and sum entries_.
    // Keep the sum deterministic; avoid modifying entries_.
    return 0;
}

size_t ThreadSafeLog::size() const {
    // TODO: lock m_ and return entries_.size().
    // Use size_t to match vector::size() return type.
    return 0;
}

int exercise() {
    // Keep this error until you have implemented the methods above.
    #error TODO_implement_exercise
    ThreadSafeLog log;
    std::vector<std::jthread> threads;

    // Start several threads that log values concurrently.
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([&]() {
            for (int i = 0; i < 100; ++i) {
                log.log(1);
            }
        });
    }

    for (auto& th : threads) {
        if (th.joinable()) th.join();
    }

    // Expect exactly 400 entries and sum 400.
    // These are strong invariants for the thread-safe log.
    if (log.size() != 400) return 1;
    if (log.sum() != 400) return 2;
    return 0;
}

int main() {
    // The test must pass without data races.
    // When running with TSan, any race should be reported.
    assert(exercise() == 0);
    return 0;
}
