// Solution: Backpressure queue
// Implements a bounded queue with drop tracking.

#include <cassert> // For assert() in main.
#include <deque>   // For std::deque.

class BoundedQueue {
public:
    explicit BoundedQueue(size_t cap) : cap_(cap) {}

    bool try_push(int v) {
        if (q_.size() >= cap_) {
            ++drops_;
            return false;
        }
        q_.push_back(v);
        return true;
    }

    bool try_pop(int& out) {
        if (q_.empty()) {
            return false;
        }
        out = q_.front();
        q_.pop_front();
        return true;
    }

    size_t drops() const { return drops_; }
    size_t size() const { return q_.size(); }

private:
    size_t cap_;
    size_t drops_{0};
    std::deque<int> q_;
};

int exercise() {
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
    // The solution must implement correct drop/backpressure behavior.
    assert(exercise() == 0);
    return 0;
}
