// Exercise: RAII buffer for CUDA-style ownership
// Implement a move-only buffer that manages dynamic memory safely.
// This mirrors how you would wrap cudaMalloc/cudaFree in real code.

#include <cassert> // For assert() in main.
#include <cstddef> // For size_t.
#include <utility> // For std::move.

class CudaBuffer {
public:
    // TODO: allocate n elements (zero-initialized if n > 0).
    // HOW: if n == 0, keep data_ = nullptr. Otherwise use new int[n]().
    explicit CudaBuffer(size_t n);
    // TODO: release any owned memory.
    // HOW: if data_ is non-null, delete[] it and reset size_/data_.
    ~CudaBuffer();

    // Copy is disallowed (single ownership).
    CudaBuffer(const CudaBuffer&) = delete;
    CudaBuffer& operator=(const CudaBuffer&) = delete;

    // TODO: implement move constructor and move assignment.
    // HOW: steal the pointer/size from other, then null out other.
    CudaBuffer(CudaBuffer&& other) noexcept;
    CudaBuffer& operator=(CudaBuffer&& other) noexcept;

    // Accessors used by the test.
    size_t size() const { return size_; }
    int* data() { return data_; }

private:
    size_t size_{0};
    int* data_{nullptr};
};

CudaBuffer::CudaBuffer(size_t n) {
    // TODO: allocate with new[] when n > 0, otherwise keep nullptr.
    // Suggested outline:
    //   if (n > 0) { data_ = new int[n](); size_ = n; }
    (void)n;
}

CudaBuffer::~CudaBuffer() {
    // TODO: delete[] data_ and set data_ to nullptr if desired.
    // Remember to set size_ to 0 so moved-from objects are empty.
}

CudaBuffer::CudaBuffer(CudaBuffer&& other) noexcept {
    // TODO: transfer ownership and clear other.
    // Suggested outline:
    //   data_ = other.data_; size_ = other.size_;
    //   other.data_ = nullptr; other.size_ = 0;
    (void)other;
}

CudaBuffer& CudaBuffer::operator=(CudaBuffer&& other) noexcept {
    if (this != &other) {
        // TODO: free current memory, then transfer ownership and clear other.
        // Suggested outline:
        //   delete[] data_;
        //   data_ = other.data_; size_ = other.size_;
        //   other.data_ = nullptr; other.size_ = 0;
    }
    return *this;
}

int exercise() {
    // Keep this error until the RAII buffer is implemented.
    #error TODO_implement_exercise
    CudaBuffer buf(4);
    if (buf.size() != 4) return 1;
    CudaBuffer moved = std::move(buf);
    if (moved.size() != 4) return 2;
    if (buf.size() != 0) return 3; // moved-from object should be empty
    return 0;
}

int main() {
    // The RAII buffer must move safely and clean up correctly.
    assert(exercise() == 0);
    return 0;
}
