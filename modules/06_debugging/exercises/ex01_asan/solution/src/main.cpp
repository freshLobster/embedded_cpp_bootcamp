// Solution: ASan-safe buffer
// This reference implementation adds explicit bounds checks using assert.

#include <cassert>
#include <vector>

class SafeBuffer {
public:
    // Construct a buffer with n elements initialized to zero.
    explicit SafeBuffer(size_t n) : data_(n, 0) {}
    void write(size_t idx, int value) {
        // Enforce the API contract: idx must be in range.
        assert(idx < data_.size());
        data_[idx] = value;
    }
    int read(size_t idx) const {
        // Enforce the same bound check on reads.
        assert(idx < data_.size());
        return data_[idx];
    }
private:
    // Vector owns the storage; ASan will catch any out-of-bounds access.
    std::vector<int> data_;
};

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    SafeBuffer buf(3);
    // Write known values inside bounds.
    buf.write(0, 1);
    buf.write(1, 2);
    buf.write(2, 3);
    // Verify reads return the expected values.
    if (buf.read(0) != 1 || buf.read(2) != 3) {
        return 1;
    }
    return 0;
}

int main() {
    // The solution must satisfy the bounds-checked contract.
    assert(exercise() == 0);
    return 0;
}
