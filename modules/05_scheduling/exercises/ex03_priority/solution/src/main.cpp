#include <cassert>
#include <queue>
#include <vector>

struct Item {
    int prio;
    int value;
};

struct ItemCmp {
    bool operator()(const Item& a, const Item& b) const { return a.prio < b.prio; }
};

class PriorityQueue {
public:
    void push(int prio, int value) { q_.push({prio, value}); }
    bool pop(int& out) {
        if (q_.empty()) {
            return false;
        }
        out = q_.top().value;
        q_.pop();
        return true;
    }
private:
    std::priority_queue<Item, std::vector<Item>, ItemCmp> q_;
};

int exercise() {
    PriorityQueue q;
    q.push(1, 10);
    q.push(5, 50);
    q.push(3, 30);
    int out = 0;
    q.pop(out);
    if (out != 50) return 1;
    q.pop(out);
    if (out != 30) return 2;
    q.pop(out);
    if (out != 10) return 3;
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
