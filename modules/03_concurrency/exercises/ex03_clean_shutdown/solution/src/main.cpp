#include <cassert>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

class Worker {
public:
    Worker() : thread_([this](std::stop_token st) { run(st); }) {}
    ~Worker() { stop(); }

    void enqueue(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(m_);
            tasks_.push(std::move(task));
        }
        cv_.notify_one();
    }

    void stop() {
        if (stopped_) {
            return;
        }
        stopped_ = true;
        thread_.request_stop();
        cv_.notify_all();
    }

private:
    void run(std::stop_token st) {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(m_);
                cv_.wait(lock, [&]() { return st.stop_requested() || !tasks_.empty(); });
                if (st.stop_requested() && tasks_.empty()) {
                    break;
                }
                task = std::move(tasks_.front());
                tasks_.pop();
            }
            task();
        }
    }

    std::mutex m_;
    std::condition_variable cv_;
    std::queue<std::function<void()>> tasks_;
    std::jthread thread_;
    bool stopped_{false};
};

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
    assert(exercise() == 0);
    return 0;
}
