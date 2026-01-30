// Solution: Thread-safe log aggregator
// This implementation protects a shared vector with a mutex to avoid data races.

#include <cassert>
#include <mutex>
#include <thread>
#include <vector>

class ThreadSafeLog {
public:
    void log(int v) {
        // Serialize writers so the vector is never modified concurrently.
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
private:
    // Mutable so sum() (const) can still take the lock safely.
    mutable std::mutex m_;
    std::vector<int> entries_;
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
    if (log.sum() != 400) {
        return 1;
    }
    return 0;
}

int main() {
    // The solution must be race-free and produce a correct sum.
    assert(exercise() == 0);
    return 0;
}
