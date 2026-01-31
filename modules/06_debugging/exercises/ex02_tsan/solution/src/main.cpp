// Solution: Thread-safe log aggregator
// This implementation protects a shared vector with a mutex to avoid data races.
// The focus is correctness and race freedom rather than throughput.

#include <cassert> // assert() provides a minimal self-check.
#include <mutex>   // std::mutex and std::lock_guard for synchronization.
#include <thread>  // std::jthread for scoped thread lifetime.
#include <vector>  // std::vector stores the log entries.

class ThreadSafeLog {
public:
    void log(int v) {
        // Serialize writers so the vector is never modified concurrently.
        // lock_guard handles lock/unlock even if an exception is thrown.
        std::lock_guard<std::mutex> lock(m_);
        entries_.push_back(v);
    }
    int sum() const {
        // Protect reads with the same mutex to avoid races with writers.
        std::lock_guard<std::mutex> lock(m_);
        int s = 0;
        for (int v : entries_) s += v;
        return s;
    }
    size_t size() const {
        // Size is also a read of shared state; it needs the same lock.
        std::lock_guard<std::mutex> lock(m_);
        return entries_.size();
    }
private:
    // Mutable so sum() (const) can still take the lock safely.
    mutable std::mutex m_;
    std::vector<int> entries_; // Shared state guarded by m_.
};

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    ThreadSafeLog log;
    std::vector<std::jthread> threads;
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([&]() {
            for (int i = 0; i < 100; ++i) {
                log.log(1);
            }
        });
    }
    for (auto& th : threads) th.join();
    // Expect 4 * 100 = 400 writes and a sum of 400.
    if (log.size() != 400) return 1;
    if (log.sum() != 400) {
        return 2;
    }
    return 0;
}

int main() {
    // The solution must be race-free and produce correct results.
    assert(exercise() == 0);
    return 0;
}
