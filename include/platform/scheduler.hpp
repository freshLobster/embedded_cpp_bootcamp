// scheduler.hpp - periodic scheduler built atop std::jthread.
#pragma once

#include <chrono>
#include <functional>
#include <stop_token>
#include <thread>

namespace platform {

class Scheduler {
public:
    Scheduler() = default;
    ~Scheduler();

    Scheduler(const Scheduler&) = delete;
    Scheduler& operator=(const Scheduler&) = delete;

    void start(std::chrono::milliseconds period, std::function<void()> task);
    void stop();

private:
    void run(std::chrono::milliseconds period, std::function<void()> task, std::stop_token st);

    std::jthread thread_;
};

}  // namespace platform

