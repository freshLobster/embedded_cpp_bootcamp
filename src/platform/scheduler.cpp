#include "platform/scheduler.hpp"

#include <thread>

namespace platform {

Scheduler::~Scheduler() { stop(); }

void Scheduler::start(std::chrono::milliseconds period, std::function<void()> task) {
    stop();
    thread_ = std::jthread([this, period, task = std::move(task)](std::stop_token st) {
        run(period, task, st);
    });
}

void Scheduler::stop() {
    if (thread_.joinable()) {
        thread_.request_stop();
        thread_.join();
    }
}

void Scheduler::run(std::chrono::milliseconds period, std::function<void()> task, std::stop_token st) {
    auto next = std::chrono::steady_clock::now();
    while (!st.stop_requested()) {
        next += period;
        task();
        std::this_thread::sleep_until(next);
    }
}

}  // namespace platform

