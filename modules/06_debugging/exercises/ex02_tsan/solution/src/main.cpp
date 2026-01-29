#include <cassert>
#include <mutex>
#include <thread>
#include <vector>

class ThreadSafeLog {
public:
    void log(int v) {
        std::lock_guard<std::mutex> lock(m_);
        entries_.push_back(v);
    }
    int sum() const {
        int s = 0;
        for (int v : entries_) s += v;
        return s;
    }
private:
    mutable std::mutex m_;
    std::vector<int> entries_;
};

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
    assert(exercise() == 0);
    return 0;
}
