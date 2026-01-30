#include <cassert>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

class Worker {
public:
    Worker();
    ~Worker();
    void enqueue(std::function<void()> task);
    void stop();
private:
    void run(std::stop_token st);
    std::mutex m_;
    std::condition_variable cv_;
    std::queue<std::function<void()>> tasks_;
    std::jthread thread_;
    bool stopped_{false};
};

Worker::Worker() : thread_([this](std::stop_token st) { run(st); }) {}
Worker::~Worker() { stop(); }

void Worker::enqueue(std::function<void()> task) {
    // TODO: lock, push, notify.
    (void)task;
}

void Worker::stop() {
    // TODO: request stop and notify.
}

void Worker::run(std::stop_token st) {
    // TODO: wait on cv_, drain tasks, exit when stop requested and queue empty.
    (void)st;
}

int exercise() {
    #error TODO_implement_exercise
    Worker w;
    std::atomic<int> count{0};
    for (int i = 0; i < 10; ++i) w.enqueue([&]() { count.fetch_add(1); });
    while (count.load() < 10) std::this_thread::yield();
    w.stop();
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
