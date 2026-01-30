// Exercise: Interface review (Rule of Five and safe moves)
// This stub asks you to correct an interface so it is move-only, safe,
// and self-consistent when ownership is transferred.

#include <cassert> // For assert() in main.
#include <cstddef> // For size_t.
#include <memory>  // For std::unique_ptr.
#include <utility> // For std::move.

// Buffer owns a heap-allocated array of ints.
// Ownership must be unique and transferable (move-only).
class Buffer {
public:
    // Allocate an array of the requested size (may be zero).
    explicit Buffer(size_t size);

    // Buffer owns memory, so copy is disabled to avoid double free.
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    // Move transfers ownership of the array.
    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;

    // Introspection and element access.
    size_t size() const;
    int& operator[](size_t idx);
    const int& operator[](size_t idx) const;

    // Compute sum of stored elements.
    int sum() const;

private:
    size_t size_{0};
    std::unique_ptr<int[]> data_;
};

Buffer::Buffer(size_t size)
    : size_(size), data_(size ? std::make_unique<int[]>(size) : nullptr) {}

Buffer::Buffer(Buffer&& other) noexcept
    : size_(other.size_), data_(std::move(other.data_)) {
    // TODO: reset other.size_ to 0 so moved-from state is safe and consistent.
}

Buffer& Buffer::operator=(Buffer&& other) noexcept {
    if (this != &other) {
        // TODO: move the data first, then copy size, then reset other.size_.
        data_ = std::move(other.data_);
        size_ = other.size_;
        // TODO: reset other.size_ to 0 so moved-from objects are inert.
    }
    return *this;
}

size_t Buffer::size() const { return size_; }
int& Buffer::operator[](size_t idx) { return data_[idx]; }
const int& Buffer::operator[](size_t idx) const { return data_[idx]; }

int Buffer::sum() const {
    // TODO: compute sum of elements 0..size_-1.
    return 0;
}

int exercise() {
    #error TODO_implement_exercise
    Buffer a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    // Move should leave 'a' empty and transfer ownership to 'b'.
    Buffer b = std::move(a);
    if (a.size() != 0) return 1;
    if (b.sum() != 6) return 2;
    return 0;
}

int main() {
    // The exercise returns 0 only when move semantics are correct.
    assert(exercise() == 0);
    return 0;
}
