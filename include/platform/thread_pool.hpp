// thread_pool.hpp - Minimal RAII thread pool with bounded work queue.
#pragma once

#include <atomic>
#include <functional>
#include <thread>
#include <vector>

#include "platform/bounded_queue.hpp"

namespace platform {

class ThreadPool {
public:
    explicit ThreadPool(std::size_t thread_count, std::size_t queue_capacity = 1024);
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    bool enqueue(std::function<void()> job);
    void shutdown();

private:
    void worker(std::stop_token st);

    std::vector<std::jthread> workers_;
    BoundedQueue<std::function<void()>> queue_;
    std::atomic<bool> shutting_down_{false};
};

}  // namespace platform

