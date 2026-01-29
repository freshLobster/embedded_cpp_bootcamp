#include <cassert>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

class Buffer {
public:
    explicit Buffer(size_t size) : size_(size), data_(size ? std::make_unique<int[]>(size) : nullptr) {}
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&& other) noexcept : size_(other.size_), data_(std::move(other.data_)) { other.size_ = 0; }
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
    size_t size() const { return size_; }
    int& operator[](size_t idx) { return data_[idx]; }
    const int& operator[](size_t idx) const { return data_[idx]; }
    int sum() const {
        int s = 0;
        for (size_t i = 0; i < size_; ++i) {
            s += data_[i];
        }
        return s;
    }
private:
    size_t size_{0};
    std::unique_ptr<int[]> data_;
};

int exercise() {
    static_assert(!std::is_copy_constructible_v<Buffer>);
    static_assert(std::is_move_constructible_v<Buffer>);

    Buffer a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    Buffer b = std::move(a);
    if (a.size() != 0) {
        return 1;
    }
    if (b.sum() != 6) {
        return 2;
    }
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
