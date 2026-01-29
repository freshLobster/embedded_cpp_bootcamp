#include <cassert>
#include <cstddef>
#include <utility>

class CudaBuffer {
public:
    explicit CudaBuffer(size_t n) : size_(n), data_(n ? new int[n]() : nullptr) {}
    ~CudaBuffer() { delete[] data_; }
    CudaBuffer(const CudaBuffer&) = delete;
    CudaBuffer& operator=(const CudaBuffer&) = delete;
    CudaBuffer(CudaBuffer&& other) noexcept : size_(other.size_), data_(other.data_) { other.size_ = 0; other.data_ = nullptr; }
    CudaBuffer& operator=(CudaBuffer&& other) noexcept {
        if (this != &other) {
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

int exercise() {
    CudaBuffer buf(4);
    if (buf.size() != 4) return 1;
    CudaBuffer moved = std::move(buf);
    if (moved.size() != 4) return 2;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
