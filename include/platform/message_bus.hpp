// message_bus.hpp - lightweight in-process pub/sub bus.
#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <shared_mutex>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace platform {

struct Message {
    std::string topic;
    std::string payload;
    std::chrono::steady_clock::time_point timestamp{std::chrono::steady_clock::now()};
};

using SubscriptionId = std::uint64_t;
using Subscriber = std::function<void(const Message&)>;

class MessageBus {
public:
    SubscriptionId subscribe(const std::string& topic, Subscriber cb);
    void unsubscribe(SubscriptionId id);
    void publish(const Message& msg) const;
    void publish(std::string_view topic, std::string_view payload) const;

    std::size_t subscriber_count(const std::string& topic) const;

private:
    struct Entry {
        SubscriptionId id;
        Subscriber cb;
    };

    SubscriptionId next_id_{1};
    mutable std::shared_mutex mutex_;
    std::unordered_map<std::string, std::vector<Entry>> subscribers_;
    static std::mutex deadlock_mutex_;
};

}  // namespace platform
