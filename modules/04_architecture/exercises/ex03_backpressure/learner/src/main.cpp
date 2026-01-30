#include <cassert>
#include <deque>

class BoundedQueue {
public:
    explicit BoundedQueue(size_t cap) : cap_(cap) {}
    bool try_push(int v);
    bool try_pop(int& out);
    size_t drops() const;
    size_t size() const;
private:
    size_t cap_;
    size_t drops_{0};
    std::deque<int> q_;
};

bool BoundedQueue::try_push(int v) {
    // TODO: drop when full and increment drops_.
    (void)v;
    return false;
}

bool BoundedQueue::try_pop(int& out) {
    // TODO: pop if available.
    (void)out;
    return false;
}

size_t BoundedQueue::drops() const { return drops_; }
size_t BoundedQueue::size() const { return q_.size(); }

int exercise() {
    #error TODO_implement_exercise
    BoundedQueue q(2);
    q.try_push(1);
    q.try_push(2);
    if (q.try_push(3)) return 1;
    if (q.drops() != 1) return 2;
    int out = 0;
    q.try_pop(out);
    if (out != 1) return 3;
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
