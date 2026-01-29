#include <cassert>
#include <vector>

int allocate_and_free(int n) {
    std::vector<int> v;
    for (int i = 1; i <= n; ++i) {
        v.push_back(i);
    }
    int sum = 0;
    for (int x : v) {
        sum += x;
    }
    return sum;
}

int exercise() {
    int sum = allocate_and_free(4);
    if (sum != 10) {
        return 1;
    }
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
