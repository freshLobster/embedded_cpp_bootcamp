# ex01_scope_guard – RAII Scope Guard

What you are building: A move-only `ScopeGuard` helper to ensure deterministic cleanup.
Why it matters: Embedded/robotics code must not leak resources or leave hardware in unsafe states.

Prerequisites check
- `cmake --preset dev` (should succeed)
- `ctest --preset dev -N | grep platform_core_tests` → should list tests

Files you will touch
- `include/platform/scope_guard.hpp` (create)
- `tests/test_scope_guard.cpp` (create)

Steps
1. Create header:
```
cat > include/platform/scope_guard.hpp <<'EOF'
#pragma once
#include <functional>
namespace platform {
class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> fn) : fn_(std::move(fn)), active_(true) {}
    ScopeGuard(ScopeGuard&& other) noexcept : fn_(std::move(other.fn_)), active_(other.active_) { other.active_=false; }
    ScopeGuard& operator=(ScopeGuard&& other) noexcept {
        if(this!=&other){ if(active_ && fn_) fn_(); fn_=std::move(other.fn_); active_=other.active_; other.active_=false; }
        return *this;
    }
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ~ScopeGuard(){ if(active_ && fn_) fn_(); }
    void release(){ active_=false; }
private:
    std::function<void()> fn_{};
    bool active_{false};
};
}
EOF
```
Expected result: file created with move-only RAII helper.

2. Add test:
```
cat > tests/test_scope_guard.cpp <<'EOF'
#include <gtest/gtest.h>
#include <atomic>
#include "platform/scope_guard.hpp"
TEST(Module01, ScopeGuardRuns){ std::atomic<int> c{0}; { platform::ScopeGuard g([&]{c++;}); EXPECT_EQ(c.load(),0); } EXPECT_EQ(c.load(),1); }
TEST(Module01, ScopeGuardRelease){ std::atomic<int> c{0}; { platform::ScopeGuard g([&]{c++;}); g.release(); } EXPECT_EQ(c.load(),0); }
EOF
```

3. Build + run:
```
cmake --build --preset dev --target platform_core_tests
ctest --preset dev -R Module01
```
Expected results: tests pass (2/2).

Verification
- `ctest --preset dev -R Module01` PASS
- No new warnings in build output.

Stop here and commit
- Suggested message: "Module01: add ScopeGuard"

If it fails
- Missing header include: ensure path `include/platform` is in target includes.
- Link errors: rerun `cmake --build --preset dev --clean-first`.
- Test not discovered: check test name prefix `Module01` matches filter.

Stretch goals
- Add noexcept to destructor; add constexpr if desired.
- Add `make_scope_guard` helper.
