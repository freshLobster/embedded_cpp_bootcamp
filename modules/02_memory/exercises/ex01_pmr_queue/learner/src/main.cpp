#include <cassert>
#include <cstddef>
#include <memory_resource>
#include <vector>

class PmrQueue {
public:
    explicit PmrQueue(std::pmr::memory_resource* res);
    std::pmr::memory_resource* resource() const;
    void push(int v);
    bool pop(int& out);
    size_t size() const;
private:
    std::pmr::vector<int> storage_;
    size_t head_{0};
};

PmrQueue::PmrQueue(std::pmr::memory_resource* res) : storage_(res) {}
std::pmr::memory_resource* PmrQueue::resource() const {
    // TODO: return allocator resource.
    return nullptr;
}
void PmrQueue::push(int v) {
    // TODO: push value into storage_.
    (void)v;
}
bool PmrQueue::pop(int& out) {
    // TODO: return false if empty; otherwise set out and advance head_.
    (void)out;
    return false;
}
size_t PmrQueue::size() const {
    // TODO: return number of remaining elements.
    return 0;
}

int exercise() {
    #error TODO_implement_exercise
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
    assert(exercise() == 0);
    return 0;
}
