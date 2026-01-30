// Exercise: Scope guard (RAII)
// This learner stub is intentionally incomplete. Your job is to implement
// a move-only scope guard that calls its cleanup callback exactly once.
// The comments below explain *what* each piece must do and *why* it matters.

#include <cassert>    // For assert() in main.
#include <functional> // For std::function as a type-erased callable holder.
#include <utility>    // For std::move in move operations.

// ScopeGuard owns a cleanup action and runs it when the guard leaves scope.
// The cleanup must run exactly once unless the guard is explicitly dismissed.
class ScopeGuard {
public:
    // Construct a guard that owns the cleanup callback.
    // The callable is stored by value so it can outlive the original lambda.
    explicit ScopeGuard(std::function<void()> fn);

    // Scope guards are move-only: copying would duplicate ownership and cause
    // double-cleanup. Disable copy operations explicitly.
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

    // Move operations transfer ownership of the cleanup callback.
    // The moved-from guard must be dismissed so it cannot run the cleanup.
    ScopeGuard(ScopeGuard&& other) noexcept;
    ScopeGuard& operator=(ScopeGuard&& other) noexcept;

    // Destructor runs the cleanup if the guard is still active.
    ~ScopeGuard();

    // Dismiss disables the cleanup permanently. This is used when the caller
    // successfully transfers or completes the work and no cleanup is needed.
    void dismiss() noexcept;

private:
    std::function<void()> fn_; // The cleanup callback (may be empty).
    bool active_{true};        // Tracks whether cleanup should still run.
};

// TODO: Implement all methods. Use the README for exact behavior.
ScopeGuard::ScopeGuard(std::function<void()> fn)
    : fn_(std::move(fn)), active_(true) {
    // TODO: nothing else needed here, but keep the guard active.
}

ScopeGuard::ScopeGuard(ScopeGuard&& other) noexcept
    : fn_(std::move(other.fn_)), active_(other.active_) {
    // TODO: ensure moved-from guard is dismissed so only one guard can fire.
}

ScopeGuard& ScopeGuard::operator=(ScopeGuard&& other) noexcept {
    if (this != &other) {
        // TODO: if this guard is still active, run its cleanup *before*
        // overwriting the callback to avoid leaks or missed cleanup.
        fn_ = std::move(other.fn_);
        active_ = other.active_;
        // TODO: dismiss the source guard to avoid double execution.
    }
    return *this;
}

ScopeGuard::~ScopeGuard() {
    // TODO: run cleanup exactly once if active_ is true and fn_ is non-empty.
}

void ScopeGuard::dismiss() noexcept {
    // TODO: disable cleanup permanently without calling it.
    active_ = false;
}

int exercise() {
    #error TODO_implement_exercise
    // After you remove the error above, keep these checks intact.

    // 1) Basic scope exit: cleanup must run when guard is destroyed.
    bool called = false;
    {
        ScopeGuard g([&]() { called = true; });
    }
    if (!called) return 1;

    // 2) Dismiss: cleanup must *not* run if dismissed.
    called = false;
    {
        ScopeGuard g([&]() { called = true; });
        g.dismiss();
    }
    if (called) return 2;

    // 3) Move: cleanup must run exactly once after ownership transfer.
    called = false;
    {
        ScopeGuard g([&]() { called = true; });
        ScopeGuard g2(std::move(g));
        (void)g2; // Silence unused warning; destructor drives behavior.
    }
    if (!called) return 3;

    return 0;
}

int main() {
    // The exercise returns 0 only if all invariants are satisfied.
    assert(exercise() == 0);
    return 0;
}
