// Solution: Timeout fallback
// Wraps a task with a timeout using std::async and future::wait_for.
// Returns a fallback result if the task is too slow.

#include <cassert>    // For assert() in main.
#include <chrono>     // For std::chrono::milliseconds.
#include <functional> // For std::function.
#include <future>     // For std::future and std::async.
#include <thread>     // For sleep_for in tests.
#include <utility>    // For std::move.

int run_with_timeout(std::function<int()> fn,
                     std::chrono::milliseconds timeout,
                     int fallback) {
    // Launch the task asynchronously so it can run in parallel.
    auto fut = std::async(std::launch::async, std::move(fn));

    // Wait for the result or timeout.
    if (fut.wait_for(timeout) == std::future_status::ready) {
        // Ready: return the actual result.
        return fut.get();
    }
    // Timeout: return fallback without blocking for completion.
    return fallback;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
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
    // The solution must respect timeouts and return fallback when needed.
    assert(exercise() == 0);
    return 0;
}
