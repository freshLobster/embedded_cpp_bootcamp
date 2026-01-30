#include <cassert>
#include <vector>

int allocate_and_free(int n) {
    // TODO: build a deterministic allocation workload and return a sum.
    (void)n;
    return 0;
}

int exercise() {
    #error TODO_implement_exercise
    int sum = allocate_and_free(4);
    if (sum != 10) return 1;
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
