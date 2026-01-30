// Solution: Clean shutdown worker
// This implementation drains tasks and exits only after a stop is requested.
// It uses a condition variable for efficient waiting and a stop token for cancellation.

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
        // Publish the task while holding the mutex so the queue stays consistent.
        tasks_.push(std::move(task));
    }
    // Notify after pushing so the worker wakes to see the new task.
    cv_.notify_one();
}

void Worker::stop() {
    {
        std::lock_guard<std::mutex> lock(m_);
        // Mark stopped_ so the worker can exit once the queue is empty.
        stopped_ = true;
    }
    // Request cooperative stop and wake the worker if it is waiting.
    thread_.request_stop();
    cv_.notify_one();
}

void Worker::run(std::stop_token st) {
    for (;;) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(m_);
            // Sleep until there is work or a stop is requested.
            cv_.wait(lock, [&]() { return stopped_ || !tasks_.empty() || st.stop_requested(); });

            if (tasks_.empty()) {
                if (stopped_ || st.stop_requested()) {
                    // No work left and stop requested: exit cleanly.
                    break;
                }
                continue;
            }

            // Pop one task while holding the lock.
            task = std::move(tasks_.front());
            tasks_.pop();
        }

        // Execute outside the lock to avoid blocking producers.
        if (task) {
            task();
        }
    }
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
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
