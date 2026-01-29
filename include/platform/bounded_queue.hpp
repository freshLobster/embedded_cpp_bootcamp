// bounded_queue.hpp - Bounded MPMC queue with optional stop_token support.
#pragma once

#include <condition_variable>
#include <deque>
#include <mutex>
#include <optional>
#include <stop_token>
#include <utility>

namespace platform {

    template <typename T> class BoundedQueue {
      public:
        explicit BoundedQueue(std::size_t capacity) : capacity_(capacity) {}

        bool push(const T &value, std::stop_token st = {}) {
            return emplace_impl(value, st);
        }
        bool push(T &&value, std::stop_token st = {}) {
            return emplace_impl(std::move(value), st);
        }

        template <class... Args> bool emplace(std::stop_token st, Args &&...args) {
            return emplace_impl(T(std::forward<Args>(args)...), st);
        }

        std::optional<T> pop(std::stop_token st = {}) {
#ifndef PLATFORM_FAILURE_RACE
            std::unique_lock lock(mutex_);
#else
            // Intentional: skip locking to create a race.
            std::unique_lock lock(dummy_mutex_);
#endif
            auto wait_pred = [this]() { return closed_ || !queue_.empty(); };
            if (st.stop_possible()) {
                if (!cv_not_empty_.wait(lock, st, wait_pred)) {
                    return std::nullopt;
                }
            } else {
                cv_not_empty_.wait(lock, wait_pred);
            }
            if (queue_.empty()) {
                return std::nullopt;
            }
            T value = std::move(queue_.front());
            queue_.pop_front();
            cv_not_full_.notify_one();
            return value;
        }

        void close() {
#ifndef PLATFORM_FAILURE_RACE
            std::lock_guard lock(mutex_);
#else
            std::lock_guard lock(dummy_mutex_);
#endif
            closed_ = true;
            cv_not_full_.notify_all();
            cv_not_empty_.notify_all();
        }

        std::size_t size() const {
#ifndef PLATFORM_FAILURE_RACE
            std::lock_guard lock(mutex_);
#else
            std::lock_guard lock(dummy_mutex_);
#endif
            return queue_.size();
        }

      private:
        template <typename U> bool emplace_impl(U &&value, std::stop_token st) {
#ifndef PLATFORM_FAILURE_RACE
            std::unique_lock lock(mutex_);
#else
            std::unique_lock lock(dummy_mutex_);
#endif
            auto full_pred = [this]() { return closed_ || queue_.size() < capacity_; };
            if (st.stop_possible()) {
                if (!cv_not_full_.wait(lock, st, full_pred)) {
                    return false;
                }
            } else {
                cv_not_full_.wait(lock, full_pred);
            }
            if (closed_) {
                return false;
            }

#ifdef PLATFORM_FAILURE_PERF
            // Intentional perf regression: force an extra copy and heap allocation.
            queue_.push_back(T(value));
#else
            queue_.push_back(std::forward<U>(value));
#endif
            cv_not_empty_.notify_one();
            return true;
        }

        const std::size_t capacity_;
        mutable std::mutex mutex_;
        std::condition_variable_any cv_not_full_;
        std::condition_variable_any cv_not_empty_;
        std::deque<T> queue_;
        bool closed_{false};

        // Used only when race injection is enabled to satisfy lock_guard types.
        mutable std::mutex dummy_mutex_;
    };

} // namespace platform
