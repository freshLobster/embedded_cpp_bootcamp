#include <gtest/gtest.h>

#include <atomic>

#include "platform/message_bus.hpp"

TEST(MessageBus, PublishReceives) {
    platform::MessageBus bus;
    std::atomic<int> count{0};
    bus.subscribe("topic", [&count](const platform::Message&) { count.fetch_add(1); });
    platform::Message msg{.topic = "topic", .payload = "data"};
    bus.publish(msg);
    EXPECT_EQ(count.load(), 1);
}

TEST(MessageBus, Unsubscribe) {
    platform::MessageBus bus;
    std::atomic<int> count{0};
    auto id = bus.subscribe("topic", [&count](const platform::Message&) { count.fetch_add(1); });
    bus.unsubscribe(id);
    platform::Message msg{.topic = "topic", .payload = "data"};
    bus.publish(msg);
    EXPECT_EQ(count.load(), 0);
}

