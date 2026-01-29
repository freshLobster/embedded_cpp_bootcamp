#include <cassert>
#include <atomic>
#include <thread>
#include <vector>

class SharedCounter {
public:
    void increment() { value_.fetch_add(1, std::memory_order_relaxed); }
    int value() const { return value_.load(std::memory_order_relaxed); }
private:
    std::atomic<int> value_{0};
};

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
    assert(exercise()==0);
    return 0;
}
