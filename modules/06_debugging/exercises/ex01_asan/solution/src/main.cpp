#include <cassert>
#include <vector>

class SafeBuffer {
public:
    explicit SafeBuffer(size_t n) : data_(n, 0) {}
    void write(size_t idx, int value) {
        assert(idx < data_.size());
        data_[idx] = value;
    }
    int read(size_t idx) const {
        assert(idx < data_.size());
        return data_[idx];
    }
private:
    std::vector<int> data_;
};

int exercise() {
    SafeBuffer buf(3);
    buf.write(0, 1);
    buf.write(1, 2);
    buf.write(2, 3);
    if (buf.read(0) != 1 || buf.read(2) != 3) {
        return 1;
    }
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
