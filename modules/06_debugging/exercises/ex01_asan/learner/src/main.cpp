// Exercise: AddressSanitizer-safe buffer
// This learner stub is intentionally incomplete. Your job is to implement
// a bounds-checked buffer and a small self-test that proves it works.
// Keep the buffer small and deterministic so ASan reports are easy to read.

#include <cassert> // For assert() and explicit precondition checks.
#include <vector>  // For std::vector storage backing the buffer.

// SafeBuffer owns a fixed-size array of ints and provides safe read/write.
// Contract: any access must validate that idx < size().
// Design intent:
//  - construction makes the buffer valid immediately (size is n)
//  - write/read enforce bounds so invalid indices fail fast in debug builds
class SafeBuffer {
public:
    // TODO: construct a buffer with n elements initialized to zero.
    // HOW: use the vector "fill" constructor or assign(), not reserve().
    // Reserve only changes capacity; size() would still be 0, which would
    // break your bounds checks and the exercise() self-test.
    explicit SafeBuffer(size_t n);

    // TODO: write value at idx with bounds check.
    // HOW: assert(idx < data_.size()) then store into data_[idx].
    // Keep this simple and deterministic; do not throw or log here.
    void write(size_t idx, int value);

    // TODO: read value at idx with bounds check.
    // HOW: assert(idx < data_.size()) then return data_[idx].
    int read(size_t idx) const;

    // Optional helper: expose size for debugging.
    size_t size() const { return data_.size(); }

private:
    std::vector<int> data_;
};

SafeBuffer::SafeBuffer(size_t n) {
    // TODO: allocate n elements and initialize to zero.
    // Suggested pattern:
    //   data_(n, 0)
    // or inside the body:
    //   data_.assign(n, 0);
    (void)n;
}

void SafeBuffer::write(size_t idx, int value) {
    // TODO: assert idx < data_.size(), then write to data_.
    // This makes an out-of-range access obvious in debug builds.
    (void)idx;
    (void)value;
}

int SafeBuffer::read(size_t idx) const {
    // TODO: assert idx < data_.size(), then return data_[idx].
    // Keep the return path simple so the test can reason about values.
    (void)idx;
    return 0;
}

int exercise() {
    // NOTE: keep this error until you finish the TODOs above.
    // Remove it only after SafeBuffer is complete and you are ready to test.
    #error TODO_implement_exercise
    // Minimal self-test: write and read within bounds.
    // HOW: construct a small buffer, write known values, then read them back.
    SafeBuffer buf(3);
    buf.write(0, 1);
    buf.write(1, 2);
    buf.write(2, 3);

    // Verify each read returns the expected value.
    // Return a unique non-zero code so failures are easy to spot.
    if (buf.read(0) != 1) return 1;
    if (buf.read(2) != 3) return 2;

    return 0;
}

int main() {
    // The test must pass; any non-zero indicates a contract violation.
    // assert() keeps the signal local and makes ASan output easy to read.
    assert(exercise() == 0);
    return 0;
}
