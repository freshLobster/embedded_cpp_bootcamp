// Exercise: Timeout fallback
// Implement a wrapper that returns a fallback result if a task exceeds a deadline.

#include <cassert>    // For assert() in main.
#include <chrono>     // For std::chrono::milliseconds.
#include <functional> // For std::function.
#include <future>     // For std::future and std::async.
#include <thread>     // For sleep_for in tests.
#include <utility>    // For std::move.

// Run a function asynchronously and return its result if it finishes
// before the timeout. Otherwise return the fallback.
int run_with_timeout(std::function<int()> fn,
                     std::chrono::milliseconds timeout,
                     int fallback) {
    // TODO: launch async task, wait_for(timeout), and return fallback on timeout.
    (void)fn;
    (void)timeout;
    (void)fallback;
    return 0;
}

int exercise() {
    #error TODO_implement_exercise
    int fast = run_with_timeout([]() { return 7; }, std::chrono::milliseconds(10), -1);
    if (fast != 7) return 1;

    int slow = run_with_timeout([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        return 9;
    }, std::chrono::milliseconds(5), -1);
    if (slow != -1) return 2;

    return 0;
}

int main() {
    // The exercise returns 0 only if timeout behavior is correct.
    assert(exercise() == 0);
    return 0;
}
