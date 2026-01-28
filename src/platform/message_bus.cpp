#include "platform/message_bus.hpp"

#include <algorithm>
#include <iostream>

namespace platform {

SubscriptionId MessageBus::subscribe(const std::string& topic, Subscriber cb) {
    const SubscriptionId id = next_id_++;
#ifndef PLATFORM_FAILURE_DEADLOCK
    std::unique_lock lock(mutex_);
#else
    // Intentional lock inversion when paired with publish().
    std::unique_lock inner_lock(deadlock_mutex_);
    std::unique_lock lock(mutex_);
#endif
    subscribers_[topic].push_back({id, std::move(cb)});
    return id;
}

void MessageBus::unsubscribe(SubscriptionId id) {
#ifndef PLATFORM_FAILURE_DEADLOCK
    std::unique_lock lock(mutex_);
#else
    std::unique_lock inner_lock(deadlock_mutex_);
    std::unique_lock lock(mutex_);
#endif
    for (auto& [topic, entries] : subscribers_) {
        entries.erase(std::remove_if(entries.begin(), entries.end(),
                                     [id](const Entry& e) { return e.id == id; }),
                      entries.end());
    }
}

void MessageBus::publish(const Message& msg) const {
#ifndef PLATFORM_FAILURE_DEADLOCK
    std::shared_lock lock(mutex_);
#else
    // Inverted lock order relative to subscribe/unsubscribe.
    std::unique_lock inner_lock(deadlock_mutex_);
    std::shared_lock lock(mutex_);
#endif
    auto it = subscribers_.find(msg.topic);
    if (it == subscribers_.end()) {
        return;
    }

    for (const auto& entry : it->second) {
        entry.cb(msg);
    }
}

std::size_t MessageBus::subscriber_count(const std::string& topic) const {
    std::shared_lock lock(mutex_);
    auto it = subscribers_.find(topic);
    if (it == subscribers_.end()) {
        return 0;
    }
    return it->second.size();
}

// NOLINTNEXTLINE cppcoreguidelines-avoid-non-const-global-variables
std::mutex MessageBus::deadlock_mutex_;

}  // namespace platform

