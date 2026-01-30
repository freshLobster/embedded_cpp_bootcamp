// Exercise: Clean shutdown worker
// Implement a worker thread that drains tasks and shuts down cleanly.

#include <atomic>              // For std::atomic counters.
#include <cassert>             // For assert() in main.
#include <condition_variable>  // For blocking wait.
#include <functional>          // For std::function tasks.
#include <mutex>               // For std::mutex.
#include <queue>               // For std::queue.
#include <thread>              // For std::jthread and std::this_thread::yield.

class Worker {
public:
    Worker();
    ~Worker();

    // Enqueue a task for the worker thread to execute.
    void enqueue(std::function<void()> task);

    // Request a clean shutdown and wake the worker.
    void stop();

private:
    // Worker thread loop; exits when stop requested and queue is empty.
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
    // TODO: lock the mutex, push task into queue, then notify the worker.
    (void)task;
}

void Worker::stop() {
    // TODO: set stopped_, request stop on thread_, and notify condition variable.
}

void Worker::run(std::stop_token st) {
    // TODO: wait on cv_ until work arrives or stop requested.
    // Drain tasks while holding minimal lock time.
    // Exit only when stop requested AND the queue is empty.
    (void)st;
}

int exercise() {
    #error TODO_implement_exercise
    Worker w;
    std::atomic<int> count{0};

    for (int i = 0; i < 10; ++i) {
        w.enqueue([&]() { count.fetch_add(1); });
    }

    while (count.load() < 10) {
        std::this_thread::yield();
    }

    w.stop();
    return 0;
}

int main() {
    // The exercise returns 0 only if the worker drains and shuts down correctly.
    assert(exercise() == 0);
    return 0;
}
