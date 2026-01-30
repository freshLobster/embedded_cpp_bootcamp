// Solution: Scope guard (RAII)
// This reference implementation shows correct move-only semantics and
// deterministic cleanup behavior. The comments explicitly tie each line
// to the "exactly once" cleanup invariant.

#include <cassert>    // For assert() in main.
#include <functional> // For std::function callback storage.
#include <utility>    // For std::move.

namespace {
// ScopeGuard owns a cleanup action and runs it on scope exit if active.
// Invariants:
//   1) Cleanup runs exactly once if not dismissed.
//   2) Cleanup never runs if dismissed.
//   3) Move transfers ownership and disables the source.
class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> fn)
        : fn_(std::move(fn)), active_(true) {}

    // Copy is disabled to prevent duplicate ownership of cleanup.
    // If copying were allowed, two guards could attempt the same cleanup.
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

    // Move transfers ownership; the source guard is dismissed to avoid
    // double-invocation of the cleanup. This preserves "exactly once."
    ScopeGuard(ScopeGuard&& other) noexcept
        : fn_(std::move(other.fn_)), active_(other.active_) {
        other.dismiss();
    }

    // Move-assign must clean up any currently-owned resource before
    // overwriting, then take ownership from the source and dismiss it.
    // This prevents losing the old cleanup or running cleanup twice.
    ScopeGuard& operator=(ScopeGuard&& other) noexcept {
        if (this != &other) {
            if (active_ && fn_) {
                fn_(); // Run existing cleanup before overwriting.
            }
            fn_ = std::move(other.fn_);
            active_ = other.active_;
            other.dismiss();
        }
        return *this;
    }

    // Destructor executes the cleanup exactly once if still active.
    // It must not throw or allocate; it must be safe on any exit path.
    ~ScopeGuard() {
        if (active_ && fn_) {
            fn_();
        }
    }

    // Dismiss prevents the cleanup from running later.
    // This is used when the guarded action completed successfully.
    void dismiss() noexcept { active_ = false; }

private:
    std::function<void()> fn_; // Cleanup callback (may be empty).
    bool active_;              // True while cleanup should run.
};
} // namespace

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    // 1) Basic scope exit.
    bool called = false;
    {
        ScopeGuard g([&]() { called = true; });
    }
    if (!called) {
        return 1;
    }

    // 2) Dismiss suppresses cleanup.
    called = false;
    {
        ScopeGuard g([&]() { called = true; });
        g.dismiss();
    }
    if (called) {
        return 2;
    }

    // 3) Move semantics transfer ownership.
    called = false;
    {
        ScopeGuard g([&]() { called = true; });
        ScopeGuard g2(std::move(g));
        (void)g2;
    }
    if (!called) {
        return 3;
    }

    return 0;
}

int main() {
    // The solution must pass all exercise checks.
    assert(exercise() == 0);
    return 0;
}
