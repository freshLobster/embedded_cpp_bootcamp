#include <cassert>
#include <functional>
#include <utility>

namespace {
class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> fn) : fn_(std::move(fn)), active_(true) {}
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard(ScopeGuard&& other) noexcept : fn_(std::move(other.fn_)), active_(other.active_) { other.dismiss(); }
    ScopeGuard& operator=(ScopeGuard&& other) noexcept {
        if (this != &other) {
            if (active_ && fn_) {
                fn_();
            }
            fn_ = std::move(other.fn_);
            active_ = other.active_;
            other.dismiss();
        }
        return *this;
    }
    ~ScopeGuard() {
        if (active_ && fn_) {
            fn_();
        }
    }
    void dismiss() noexcept { active_ = false; }
private:
    std::function<void()> fn_;
    bool active_;
};
}

int exercise() {
    bool called = false;
    {
        ScopeGuard g([&]() { called = true; });
    }
    if (!called) {
        return 1;
    }

    called = false;
    {
        ScopeGuard g([&]() { called = true; });
        g.dismiss();
    }
    if (called) {
        return 2;
    }

    called = false;
    {
        ScopeGuard g([&]() { called = true; });
        ScopeGuard g2(std::move(g));
    }
    if (!called) {
        return 3;
    }

    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
