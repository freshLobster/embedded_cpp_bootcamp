// Solution: PMR-backed queue
// This reference implementation uses std::pmr::vector with a supplied allocator.
// The key behavior is that all allocations are routed through the memory_resource.

#include <cassert>         // For assert() in main.
#include <cstddef>         // For size_t.
#include <memory_resource> // For std::pmr types and resources.
#include <vector>          // For std::pmr::vector storage.

class PmrQueue {
public:
    explicit PmrQueue(std::pmr::memory_resource* res)
        : storage_(res) {}

    std::pmr::memory_resource* resource() const {
        // The allocator exposes its underlying resource via resource().
        // This lets callers verify which resource is actually in use.
        return storage_.get_allocator().resource();
    }

    void push(int v) {
        // Append at the tail. This may allocate via the pmr resource.
        // Using pmr::vector ensures the allocator is respected.
        storage_.push_back(v);
    }

    bool pop(int& out) {
        if (head_ >= storage_.size()) {
            return false;
        }
        // FIFO: read the next unread element and advance the head index.
        out = storage_[head_++];
        return true;
    }

    size_t size() const {
        // Remaining elements are total minus consumed head.
        // This makes size() reflect what is still in the queue.
        return storage_.size() - head_;
    }

private:
    std::pmr::vector<int> storage_;
    size_t head_{0};
};

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    std::byte buffer[1024];
    std::pmr::monotonic_buffer_resource res(buffer, sizeof(buffer));
    PmrQueue q(&res);
    if (q.resource() != &res) return 1;

    q.push(1);
    q.push(2);
    q.push(3);

    int out = 0;
    q.pop(out);
    if (out != 1) return 2;

    q.pop(out);
    if (out != 2) return 3;

    if (q.size() != 1) return 4;
    return 0;
}

int main() {
    // The solution must satisfy allocator and queue invariants.
    assert(exercise() == 0);
    return 0;
}
