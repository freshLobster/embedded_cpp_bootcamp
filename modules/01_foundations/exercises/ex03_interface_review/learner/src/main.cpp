#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

class Buffer {
public:
    explicit Buffer(size_t size);
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;
    size_t size() const;
    int& operator[](size_t idx);
    const int& operator[](size_t idx) const;
    int sum() const;
private:
    size_t size_{0};
    std::unique_ptr<int[]> data_;
};

Buffer::Buffer(size_t size) : size_(size), data_(size ? std::make_unique<int[]>(size) : nullptr) {}
Buffer::Buffer(Buffer&& other) noexcept : size_(other.size_), data_(std::move(other.data_)) {
    // TODO: reset other.size_.
}
Buffer& Buffer::operator=(Buffer&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        size_ = other.size_;
        // TODO: reset other.size_.
    }
    return *this;
}
size_t Buffer::size() const { return size_; }
int& Buffer::operator[](size_t idx) { return data_[idx]; }
const int& Buffer::operator[](size_t idx) const { return data_[idx]; }
int Buffer::sum() const {
    // TODO: compute sum of elements.
    return 0;
}

int exercise() {
    #error TODO_implement_exercise
    Buffer a(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    Buffer b = std::move(a);
    if (a.size() != 0) return 1;
    if (b.sum() != 6) return 2;
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
