#include <cassert>
#include <memory>
#include <vector>

struct Payload {
    std::vector<int> data;
    int sum() const;
};

int Payload::sum() const {
    // TODO: sum all values in data.
    return 0;
}

std::unique_ptr<Payload> make_payload(int n) {
    // TODO: allocate Payload on the heap and return ownership.
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
    assert(exercise() == 0);
    return 0;
}
