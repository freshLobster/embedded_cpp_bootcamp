#include "platform/logging.hpp"
#include "platform/pipeline.hpp"

#include <atomic>
#include <csignal>
#include <iostream>
#include <thread>

namespace {
    std::atomic<bool> running{true};

    void handle_signal(int) {
        running = false;
    }
} // namespace

int main() {
    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    platform::set_log_level(platform::LogLevel::kInfo);
    platform::Pipeline pipeline;
    pipeline.start();

    LOG_INFO("Platform core running. Press Ctrl+C to exit.");
    while (running.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    pipeline.stop();
    LOG_INFO("Shutdown complete.");
    return 0;
}
