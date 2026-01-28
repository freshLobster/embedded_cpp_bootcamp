// pipeline.hpp - skeleton perception/control pipeline with pub/sub bus.
#pragma once

#include <atomic>
#include <functional>
#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include "platform/bounded_queue.hpp"
#include "platform/message_bus.hpp"
#include "platform/scheduler.hpp"
#include "platform/thread_pool.hpp"

namespace platform {

struct SensorSample {
    std::string name;
    double value;
    std::chrono::steady_clock::time_point timestamp{std::chrono::steady_clock::now()};
};

struct ControlCommand {
    double effort;
    std::chrono::steady_clock::time_point timestamp{std::chrono::steady_clock::now()};
};

class Pipeline {
public:
    Pipeline();
    ~Pipeline();

    void start();
    void stop();

    // Hooks for tests/benchmarks.
    std::size_t processed_samples() const { return processed_samples_.load(); }

    MessageBus& bus() { return bus_; }

private:
    void start_sensor();
    void start_perception();
    void start_control();
    void start_io();

    Scheduler sensor_scheduler_;
    ThreadPool worker_pool_;
    MessageBus bus_;
    std::atomic<bool> running_{false};
    std::atomic<std::size_t> processed_samples_{0};
};

}  // namespace platform
