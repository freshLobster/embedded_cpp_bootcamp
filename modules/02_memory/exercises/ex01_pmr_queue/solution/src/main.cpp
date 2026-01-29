#include <cassert>
#include <cstddef>
#include <memory_resource>
#include <vector>

class PmrQueue {
public:
    explicit PmrQueue(std::pmr::memory_resource* res) : storage_(res) {}
    std::pmr::memory_resource* resource() const { return storage_.get_allocator().resource(); }
    void push(int v) { storage_.push_back(v); }
    bool pop(int& out) {
        if (head_ >= storage_.size()) {
            return false;
        }
        out = storage_[head_++];
        return true;
    }
    size_t size() const { return storage_.size() - head_; }
private:
    std::pmr::vector<int> storage_;
    size_t head_{0};
};

int exercise() {
    std::byte buffer[1024];
    std::pmr::monotonic_buffer_resource res(buffer, sizeof(buffer));
    PmrQueue q(&res);
    if (q.resource() != &res) {
        return 1;
    }
    q.push(1);
    q.push(2);
    q.push(3);
    int out = 0;
    q.pop(out);
    if (out != 1) {
        return 2;
    }
    q.pop(out);
    if (out != 2) {
        return 3;
    }
    if (q.size() != 1) {
        return 4;
    }
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
