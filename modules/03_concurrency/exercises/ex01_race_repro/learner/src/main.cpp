#include <cassert>
#include <atomic>
#include <thread>
#include <vector>

class Counter {
public:
    void increment();
    int value() const;
private:
    std::atomic<int> value_{0};
};

void Counter::increment() {
    // TODO: use atomic fetch_add.
}

int Counter::value() const {
    // TODO: use atomic load.
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
            for (int i = 0; i < kIters; ++i) c.increment();
        });
    }
    for (auto& th : threads) {
        if (th.joinable()) th.join();
    }
    if (c.value() != kThreads * kIters) return 1;
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
