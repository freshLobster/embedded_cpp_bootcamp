#include "platform/pipeline.hpp"

#include <random>

#include "platform/logging.hpp"

namespace platform {

namespace {
double noisy_read() {
    static thread_local std::mt19937 rng{std::random_device{}()};
    static thread_local std::normal_distribution<double> dist{0.0, 0.05};
    return 1.0 + dist(rng);
}
}  // namespace

Pipeline::Pipeline() : worker_pool_(std::thread::hardware_concurrency(), 256) {}

Pipeline::~Pipeline() { stop(); }

void Pipeline::start() {
    if (running_.exchange(true)) {
        return;
    }
    start_perception();
    start_control();
    start_io();
    start_sensor();
}

void Pipeline::stop() {
    if (!running_.exchange(false)) {
        return;
    }
    sensor_scheduler_.stop();
    worker_pool_.shutdown();
}

void Pipeline::start_sensor() {
    sensor_scheduler_.start(std::chrono::milliseconds(50), [this]() {
        SensorSample sample{
            .name = "imu",
            .value = noisy_read(),
            .timestamp = std::chrono::steady_clock::now(),
        };
        Message msg{.topic = "sensor.raw",
                    .payload = sample.name + ":" + std::to_string(sample.value),
                    .timestamp = sample.timestamp};
        bus_.publish(msg);
    });
}

void Pipeline::start_perception() {
    bus_.subscribe("sensor.raw", [this](const Message& msg) {
        worker_pool_.enqueue([this, msg]() {
            // Parse payload and create processed value.
            ControlCommand cmd{
                .effort = std::stod(msg.payload.substr(msg.payload.find(':') + 1)) * 0.5,
                .timestamp = std::chrono::steady_clock::now(),
            };
#ifdef PLATFORM_FAILURE_UAF
            double* scratch = new double(cmd.effort);
            delete scratch;  // Intentional UAF: cmd.effort still references freed memory in trace below.
            cmd.effort += *scratch;  // NOLINT
#endif

            Message out{.topic = "control.cmd",
                        .payload = std::to_string(cmd.effort),
                        .timestamp = cmd.timestamp};
            bus_.publish(out);
            processed_samples_.fetch_add(1, std::memory_order_relaxed);
        });
    });
}

void Pipeline::start_control() {
    bus_.subscribe("control.cmd", [this](const Message& msg) {
        worker_pool_.enqueue([msg]() {
            double effort = std::stod(msg.payload);
            // Simulated actuator write.
            (void)effort;
        });
    });
}

void Pipeline::start_io() {
    bus_.subscribe("control.cmd", [](const Message& msg) {
        LOG_INFO("Actuator command: " + msg.payload);
    });
}

}  // namespace platform

