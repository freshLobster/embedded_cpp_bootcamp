#include <cassert>
#include <queue>
#include <vector>

struct Item {
    int prio{0};
    int value{0};
};

struct ByPriority {
    bool operator()(const Item& a, const Item& b) const {
        // TODO: return true if a should come after b.
        (void)a; (void)b;
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
    // TODO: return and remove highest-priority item.
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
    assert(exercise() == 0);
    return 0;
}
