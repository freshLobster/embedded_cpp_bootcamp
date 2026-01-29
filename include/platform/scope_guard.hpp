// scope_guard.hpp - minimal RAII scope guard utility.
#pragma once

#include <utility>

namespace platform {

    template <typename F> class ScopeGuard {
      public:
        explicit ScopeGuard(F &&func) : func_(std::forward<F>(func)) {}
        ScopeGuard(const ScopeGuard &)            = delete;
        ScopeGuard &operator=(const ScopeGuard &) = delete;
        ScopeGuard(ScopeGuard &&other) noexcept : func_(std::move(other.func_)), active_(other.active_) {
            other.dismiss();
        }
        ~ScopeGuard() {
            if (active_) {
                func_();
            }
        }

        void dismiss() noexcept {
            active_ = false;
        }

      private:
        F func_;
        bool active_{true};
    };

    template <typename F> ScopeGuard<F> make_scope_guard(F &&func) {
        return ScopeGuard<F>(std::forward<F>(func));
    }

} // namespace platform
