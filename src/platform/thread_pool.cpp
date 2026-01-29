#include "platform/thread_pool.hpp"

namespace platform {

    ThreadPool::ThreadPool(std::size_t thread_count, std::size_t queue_capacity) : queue_(queue_capacity) {
        workers_.reserve(thread_count);
        for (std::size_t i = 0; i < thread_count; ++i) {
            workers_.emplace_back([this](std::stop_token st) { worker(st); });
        }
    }

    ThreadPool::~ThreadPool() {
        shutdown();
    }

    bool ThreadPool::enqueue(std::function<void()> job) {
        if (shutting_down_.load(std::memory_order_relaxed)) {
            return false;
        }
        return queue_.push(std::move(job));
    }

    void ThreadPool::shutdown() {
        bool expected = false;
        if (!shutting_down_.compare_exchange_strong(expected, true)) {
            return;
        }
        queue_.close();
        for (auto &t : workers_) {
            if (t.joinable()) {
                t.request_stop();
                t.join();
            }
        }
    }

    void ThreadPool::worker(std::stop_token st) {
        while (!st.stop_requested()) {
            auto job = queue_.pop(st);
            if (!job.has_value()) {
                break;
            }
            (*job)();
        }
    }

} // namespace platform
