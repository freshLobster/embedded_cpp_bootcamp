// Solution: RAII buffer with move-only semantics
// Models safe ownership transfer similar to CUDA buffer wrappers.
// The buffer uses new[]/delete[] for simplicity in a CPU-only build.

#include <cassert> // assert() provides a minimal self-check.
#include <cstddef> // size_t for buffer sizes.
#include <utility> // std::move for move operations.

class CudaBuffer {
public:
    // Allocate n elements (zero-initialized if n > 0).
    explicit CudaBuffer(size_t n) : size_(n), data_(n ? new int[n]() : nullptr) {}
    // Release owned memory on destruction.
    ~CudaBuffer() { delete[] data_; }
    CudaBuffer(const CudaBuffer&) = delete;
    CudaBuffer& operator=(const CudaBuffer&) = delete;
    // Move transfers ownership and clears the source.
    CudaBuffer(CudaBuffer&& other) noexcept : size_(other.size_), data_(other.data_) { other.size_ = 0; other.data_ = nullptr; }
    CudaBuffer& operator=(CudaBuffer&& other) noexcept {
        if (this != &other) {
            // Release current buffer before taking ownership of the new one.
            delete[] data_;
            size_ = other.size_;
            data_ = other.data_;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }
    size_t size() const { return size_; }
    int* data() { return data_; }
private:
    size_t size_{0};
    int* data_{nullptr};
};

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    CudaBuffer buf(4);
    if (buf.size() != 4) return 1;
    CudaBuffer moved = std::move(buf);
    if (moved.size() != 4) return 2;
    return 0;
}

int main(){
    // The solution must transfer ownership safely.
    assert(exercise()==0);
    return 0;
}
