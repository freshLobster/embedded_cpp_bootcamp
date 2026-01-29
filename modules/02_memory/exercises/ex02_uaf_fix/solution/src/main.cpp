#include <cassert>
#include <memory>
#include <vector>

struct Payload {
    std::vector<int> data;
    int sum() const {
        int s = 0;
        for (int v : data) {
            s += v;
        }
        return s;
    }
};

std::unique_ptr<Payload> make_payload(int n) {
    auto p = std::make_unique<Payload>();
    for (int i = 1; i <= n; ++i) {
        p->data.push_back(i);
    }
    return p;
}

int exercise() {
    auto p = make_payload(5);
    if (!p) {
        return 1;
    }
    if (p->sum() != 15) {
        return 2;
    }
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
