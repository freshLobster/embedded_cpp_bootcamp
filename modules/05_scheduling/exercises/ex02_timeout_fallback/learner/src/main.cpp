#include <cassert>
#include <chrono>
#include <functional>
#include <future>
#include <thread>
#include <utility>

int run_with_timeout(std::function<int()> fn, std::chrono::milliseconds timeout, int fallback) {
    // TODO: launch async, wait_for, return fallback on timeout.
    (void)fn; (void)timeout; (void)fallback;
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
    assert(exercise() == 0);
    return 0;
}
