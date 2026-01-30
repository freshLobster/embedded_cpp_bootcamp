// Solution: Priority dispatcher
// Uses std::priority_queue with a custom comparator.
// Higher priority values are dispatched first.

#include <cassert> // For assert() in main.
#include <queue>   // For std::priority_queue.
#include <vector>  // For underlying container.

struct Item {
    int prio{0};
    int value{0};
};

// Higher priority should come first, so comparator returns true if a has
// lower priority than b.
struct ByPriority {
    bool operator()(const Item& a, const Item& b) const {
        // Return true if a should come after b in the queue ordering.
        // This makes higher priorities rise to the top.
        return a.prio < b.prio;
    }
};

class Dispatcher {
public:
    void push(Item item) { pq_.push(item); }
    Item dispatch_next() {
        // top() returns the highest-priority item by comparator.
        Item top = pq_.top();
        // pop() removes it so the next call returns the next highest.
        pq_.pop();
        return top;
    }

private:
    std::priority_queue<Item, std::vector<Item>, ByPriority> pq_;
};

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
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
    // The solution must dispatch highest-priority tasks first.
    assert(exercise() == 0);
    return 0;
}
