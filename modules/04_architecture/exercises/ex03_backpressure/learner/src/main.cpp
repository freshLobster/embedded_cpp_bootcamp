// Exercise: Backpressure queue
// Implement a bounded queue that drops items when full and tracks drop count.

#include <cassert> // For assert() in main.
#include <deque>   // For std::deque storage.

class BoundedQueue {
public:
    explicit BoundedQueue(size_t cap) : cap_(cap) {}

    // Try to push; return false if full and increment drop counter.
    bool try_push(int v);

    // Try to pop; return false if empty.
    bool try_pop(int& out);

    size_t drops() const;
    size_t size() const;

private:
    size_t cap_;
    size_t drops_{0};
    std::deque<int> q_;
};

bool BoundedQueue::try_push(int v) {
    // TODO: if queue is full, increment drops_ and return false.
    // Otherwise push value and return true.
    (void)v;
    return false;
}

bool BoundedQueue::try_pop(int& out) {
    // TODO: if queue is empty, return false.
    // Otherwise set out to front element, pop it, and return true.
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
    // The exercise returns 0 only if backpressure behavior is correct.
    assert(exercise() == 0);
    return 0;
}
