// Solution: Clean shutdown worker
// This implementation drains tasks and exits only after a stop is requested.

#include <atomic>              // For std::atomic.
#include <cassert>             // For assert() in main.
#include <condition_variable>  // For std::condition_variable.
#include <functional>          // For std::function.
#include <mutex>               // For std::mutex.
#include <queue>               // For std::queue.
#include <thread>              // For std::jthread.

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
    {
        std::lock_guard<std::mutex> lock(m_);
        tasks_.push(std::move(task));
    }
    cv_.notify_one();
}

void Worker::stop() {
    {
        std::lock_guard<std::mutex> lock(m_);
        stopped_ = true;
    }
    thread_.request_stop();
    cv_.notify_one();
}

void Worker::run(std::stop_token st) {
    for (;;) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(m_);
            cv_.wait(lock, [&]() { return stopped_ || !tasks_.empty() || st.stop_requested(); });

            if (tasks_.empty()) {
                if (stopped_ || st.stop_requested()) {
                    break;
                }
                continue;
            }

            task = std::move(tasks_.front());
            tasks_.pop();
        }

        if (task) {
            task();
        }
    }
}

int exercise() {
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
    // The solution must drain all tasks and shut down cleanly.
    assert(exercise() == 0);
    return 0;
}
