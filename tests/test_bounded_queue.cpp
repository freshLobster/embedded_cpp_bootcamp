#include <gtest/gtest.h>

#include <thread>
#include <vector>

#include "platform/bounded_queue.hpp"

TEST(BoundedQueue, PushPopRoundTrip) {
    platform::BoundedQueue<int> q(4);
    EXPECT_TRUE(q.push(1));
    auto v = q.pop();
    ASSERT_TRUE(v.has_value());
    EXPECT_EQ(*v, 1);
}

TEST(BoundedQueue, ClosesGracefully) {
    platform::BoundedQueue<int> q(1);
    q.close();
    EXPECT_FALSE(q.push(3));
    auto v = q.pop();
    EXPECT_FALSE(v.has_value());
}

TEST(BoundedQueue, MultiThreaded) {
    platform::BoundedQueue<int> q(8);
    std::jthread producer([&q](std::stop_token) {
        for (int i = 0; i < 100; ++i) {
            ASSERT_TRUE(q.push(i));
        }
    });
    int total = 0;
    std::jthread consumer([&q, &total](std::stop_token st) {
        while (!st.stop_requested()) {
            auto v = q.pop(st);
            if (!v) break;
            total += *v;
        }
    });
    producer.join();
    q.close();
    consumer.request_stop();
    consumer.join();
    EXPECT_GT(total, 0);
}

