// Exercise: Priority dispatcher
// Implement a priority-based dispatcher using std::priority_queue.

#include <cassert> // For assert() in main.
#include <queue>   // For std::priority_queue.
#include <vector>  // For underlying container.

struct Item {
    int prio{0};
    int value{0};
};

// Comparator: return true if 'a' has lower priority than 'b'.
struct ByPriority {
    bool operator()(const Item& a, const Item& b) const {
        // TODO: return true if a should come after b (lower priority).
        (void)a;
        (void)b;
        return false;
    }
};

class Dispatcher {
public:
    void push(Item item) { pq_.push(item); }
    Item dispatch_next();

private:
    std::priority_queue<Item, std::vector<Item>, ByPriority> pq_;
};

Item Dispatcher::dispatch_next() {
    // TODO: return and remove the highest-priority item from pq_.
    return {};
}

int exercise() {
    #error TODO_implement_exercise
    Dispatcher d;
    d.push({1, 10});
    d.push({3, 30});
    d.push({2, 20});

    Item first = d.dispatch_next();
    if (first.prio != 3) return 1;
    Item second = d.dispatch_next();
    if (second.prio != 2) return 2;
    return 0;
}

int main() {
    // The exercise returns 0 only if priority ordering is correct.
    assert(exercise() == 0);
    return 0;
}
