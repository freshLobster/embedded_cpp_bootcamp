#include <cassert>
#include <functional>
#include <utility>

class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> fn);
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard(ScopeGuard&& other) noexcept;
    ScopeGuard& operator=(ScopeGuard&& other) noexcept;
    ~ScopeGuard();

    void dismiss() noexcept;
private:
    std::function<void()> fn_;
    bool active_{true};
};

// TODO: Implement all methods. Use the README for exact behavior.
ScopeGuard::ScopeGuard(std::function<void()> fn) : fn_(std::move(fn)), active_(true) {}
ScopeGuard::ScopeGuard(ScopeGuard&& other) noexcept : fn_(std::move(other.fn_)), active_(other.active_) {
    // TODO: ensure moved-from guard is dismissed.
}
ScopeGuard& ScopeGuard::operator=(ScopeGuard&& other) noexcept {
    if (this != &other) {
        // TODO: if currently active, run cleanup before overwriting.
        fn_ = std::move(other.fn_);
        active_ = other.active_;
        // TODO: dismiss other.
    }
    return *this;
}
ScopeGuard::~ScopeGuard() {
    // TODO: run cleanup exactly once if active.
}
void ScopeGuard::dismiss() noexcept {
    // TODO: disable cleanup permanently.
    active_ = false;
}

int exercise() {
    #error TODO_implement_exercise
    // After you remove the error above, keep these checks:
    bool called = false;
    {
        ScopeGuard g([&]() { called = true; });
    }
    if (!called) return 1;

    called = false;
    {
        ScopeGuard g([&]() { called = true; });
        g.dismiss();
    }
    if (called) return 2;

    called = false;
    {
        ScopeGuard g([&]() { called = true; });
        ScopeGuard g2(std::move(g));
    }
    if (!called) return 3;

    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
