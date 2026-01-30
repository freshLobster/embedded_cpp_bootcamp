// Solution: Deterministic checksum for debugging practice
// This provides a predictable function to step through in gdb/gdbserver.

#include <cassert>
#include <string_view>

int checksum(std::string_view s) {
    int sum = 0;
    for (unsigned char c : s) {
        // Add each byte value to the running total.
        sum += static_cast<int>(c);
    }
    return sum;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    int c = checksum("GDB");
    // The checksum should be positive for a non-empty ASCII string.
    if (c <= 0) {
        return 1;
    }
    return 0;
}

int main() {
    // The solution must pass the checksum self-check.
    assert(exercise() == 0);
    return 0;
}
