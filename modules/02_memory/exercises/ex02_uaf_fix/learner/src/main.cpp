// Exercise: Fix use-after-free by enforcing ownership
// This stub asks you to allocate a payload on the heap and return
// exclusive ownership via std::unique_ptr. The tests validate lifetime safety.

#include <cassert> // For assert() in main.
#include <memory>  // For std::unique_ptr.
#include <vector>  // For std::vector payload storage.

// Payload represents a small data block with a summation helper.
struct Payload {
    std::vector<int> data;

    // Sum all values in data (used by the test to validate correctness).
    int sum() const;
};

int Payload::sum() const {
    // TODO: sum all values in data without modifying the vector.
    return 0;
}

// Factory returns a heap-allocated Payload so the caller owns its lifetime.
std::unique_ptr<Payload> make_payload(int n) {
    // TODO: allocate a Payload, fill it with 1..n, and return unique_ptr.
    // This prevents returning a pointer to a local (stack) object.
    (void)n;
    return nullptr;
}

int exercise() {
    #error TODO_implement_exercise
    auto p = make_payload(5);
    if (!p) return 1;
    if (p->sum() != 15) return 2;
    return 0;
}

int main() {
    // The exercise returns 0 only if ownership and lifetime are correct.
    assert(exercise() == 0);
    return 0;
}
