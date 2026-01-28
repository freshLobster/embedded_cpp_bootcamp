#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>

#include "platform/scheduler.hpp"

TEST(Scheduler, PeriodicTicks) {
    platform::Scheduler sched;
    std::atomic<int> ticks{0};
    sched.start(std::chrono::milliseconds(10), [&ticks]() { ticks.fetch_add(1); });
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    sched.stop();
    EXPECT_GE(ticks.load(), 4);
}

