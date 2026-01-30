// Solution: Fix use-after-free by enforcing ownership
// The factory returns a std::unique_ptr, ensuring the payload outlives the caller.

#include <cassert> // For assert() in main.
#include <memory>  // For std::unique_ptr.
#include <vector>  // For std::vector.

struct Payload {
    std::vector<int> data;

    // Sum values in the payload; used to validate correctness.
    int sum() const {
        int s = 0;
        for (int v : data) {
            s += v;
        }
        return s;
    }
};

// Allocate on the heap and return exclusive ownership.
std::unique_ptr<Payload> make_payload(int n) {
    auto p = std::make_unique<Payload>();
    p->data.reserve(static_cast<size_t>(n));
    for (int i = 1; i <= n; ++i) {
        p->data.push_back(i);
    }
    return p;
}

int exercise() {
    auto p = make_payload(5);
    if (!p) return 1;
    if (p->sum() != 15) return 2;
    return 0;
}

int main() {
    // The solution must satisfy lifetime and correctness requirements.
    assert(exercise() == 0);
    return 0;
}
