// Exercise: PMR-backed queue
// Implement a small queue that uses std::pmr allocators so allocations are
// controlled by a caller-provided memory_resource.

#include <cassert>         // For assert() in main.
#include <cstddef>         // For size_t.
#include <memory_resource> // For std::pmr types and resources.
#include <vector>          // For std::pmr::vector storage.

// PmrQueue stores integers in a std::pmr::vector so allocations are controlled
// by a caller-provided memory_resource (e.g., monotonic_buffer_resource).
class PmrQueue {
public:
    // Construct the queue with a memory resource for its allocator.
    explicit PmrQueue(std::pmr::memory_resource* res);

    // Return the memory resource used by the internal allocator.
    std::pmr::memory_resource* resource() const;

    // Push a value into the queue.
    void push(int v);

    // Pop a value from the queue into `out`. Return false if empty.
    bool pop(int& out);

    // Return number of elements remaining in the queue.
    size_t size() const;

private:
    std::pmr::vector<int> storage_;
    size_t head_{0}; // Index of the next element to pop.
};

PmrQueue::PmrQueue(std::pmr::memory_resource* res) : storage_(res) {}

std::pmr::memory_resource* PmrQueue::resource() const {
    // TODO: return allocator resource for storage_.
    return nullptr;
}

void PmrQueue::push(int v) {
    // TODO: push value into storage_. This may allocate from the resource.
    (void)v;
}

bool PmrQueue::pop(int& out) {
    // TODO: return false if empty; otherwise set out and advance head_.
    (void)out;
    return false;
}

size_t PmrQueue::size() const {
    // TODO: return number of remaining elements (storage_.size() - head_).
    return 0;
}

int exercise() {
    #error TODO_implement_exercise
    // Provide a fixed buffer and a monotonic resource so we can verify
    // that our container is actually using the supplied allocator.
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
    // The exercise returns 0 only if allocator and queue semantics are correct.
    assert(exercise() == 0);
    return 0;
}
