// Solution: Backpressure queue
// Implements a bounded queue with drop tracking.
// The queue drops new items when full to bound latency and memory.

#include <cassert> // For assert() in main.
#include <deque>   // For std::deque.

class BoundedQueue {
public:
    explicit BoundedQueue(size_t cap) : cap_(cap) {}

    bool try_push(int v) {
        if (q_.size() >= cap_) {
            // Queue full: drop the new item and record the drop.
            ++drops_;
            return false;
        }
        // Queue has capacity: accept the item.
        q_.push_back(v);
        return true;
    }

    bool try_pop(int& out) {
        if (q_.empty()) {
            return false;
        }
        // FIFO: return oldest item first.
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

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
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
