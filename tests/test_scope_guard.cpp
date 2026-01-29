// test_scope_guard.cpp - basic scope guard behavior checks.
#include "platform/scope_guard.hpp"

#include <gtest/gtest.h>

TEST(ScopeGuard, RunsOnScopeExit) {
    bool ran = false;
    {
        auto guard = platform::make_scope_guard([&ran]() { ran = true; });
        (void)guard;
    }
    EXPECT_TRUE(ran);
}

TEST(ScopeGuard, DismissPreventsRun) {
    bool ran = false;
    {
        auto guard = platform::make_scope_guard([&ran]() { ran = true; });
        guard.dismiss();
    }
    EXPECT_FALSE(ran);
}
