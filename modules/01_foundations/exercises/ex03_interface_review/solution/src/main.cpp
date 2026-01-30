// Solution: Interface review (Rule of Five and safe moves)
// This reference implementation demonstrates correct move-only ownership
// and a safe, predictable moved-from state.

#include <cassert>     // For assert() in main.
#include <cstddef>     // For size_t.
#include <memory>      // For std::unique_ptr.
#include <type_traits> // For static_assert on type traits.
#include <utility>     // For std::move.

// Buffer owns a heap-allocated array and is move-only.
// Invariants:
//   1) Copy is disabled to prevent double free.
//   2) Move transfers ownership.
//   3) Moved-from objects report size 0 and are safe to destroy.
class Buffer {
public:
    explicit Buffer(size_t size)
        : size_(size), data_(size ? std::make_unique<int[]>(size) : nullptr) {}

    // Copy disabled to prevent double free.
    // This enforces unique ownership.
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    // Move transfers ownership and leaves the source in a safe empty state.
    Buffer(Buffer&& other) noexcept
        : size_(other.size_), data_(std::move(other.data_)) {
        other.size_ = 0;
    }

    // Move assignment transfers ownership safely and clears the source size.
    // std::unique_ptr handles releasing the old buffer automatically.
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

    // Sum values for verification.
    // This uses size_ so moved-from objects behave as empty.
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

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    // Verify type properties at compile time.
    static_assert(!std::is_copy_constructible_v<Buffer>);
    static_assert(std::is_move_constructible_v<Buffer>);

    Buffer a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    // Move ownership to b.
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
    // The solution must satisfy all invariants.
    assert(exercise() == 0);
    return 0;
}
