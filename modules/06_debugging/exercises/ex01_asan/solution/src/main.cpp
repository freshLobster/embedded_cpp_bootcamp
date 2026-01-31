// Solution: ASan-safe buffer
// This reference implementation adds explicit bounds checks using assert.
// The goal is a tiny, deterministic workload so ASan reports are short and
// easy to interpret during debugging labs.

#include <cassert> // assert() enforces the buffer's index contract in debug.
#include <vector>  // std::vector holds the buffer contents.

class SafeBuffer {
public:
    // Construct a buffer with n elements initialized to zero.
    // The size is set immediately so any read/write can rely on size().
    explicit SafeBuffer(size_t n) : data_(n, 0) {}
    void write(size_t idx, int value) {
        // Enforce the API contract: idx must be in range.
        // assert() is the most direct way to catch mistakes early.
        assert(idx < data_.size());
        data_[idx] = value;
    }
    int read(size_t idx) const {
        // Enforce the same bound check on reads to prevent OOB access.
        assert(idx < data_.size());
        return data_[idx];
    }
private:
    // Vector owns the storage; ASan will catch any out-of-bounds access.
    // Keeping this as the sole storage avoids confusing aliasing.
    std::vector<int> data_;
};

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    // A tiny buffer keeps the test deterministic and easy to reason about.
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
    // Any non-zero return indicates a contract or logic failure.
    assert(exercise() == 0);
    return 0;
}
