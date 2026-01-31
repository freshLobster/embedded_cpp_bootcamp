// Solution: Deterministic checksum for debugging practice
// This provides a predictable function to step through in gdb/gdbserver.
// The call chain is intentionally shallow but includes a second layer.

#include <cassert>     // assert() provides a minimal self-check.
#include <string_view> // std::string_view for read-only input.

int checksum(std::string_view s) {
    int sum = 0;
    for (unsigned char c : s) {
        // Add each byte value to the running total.
        sum += static_cast<int>(c);
    }
    return sum;
}

int checksum_layer2(std::string_view s) {
    // Extra layer to deepen the call stack during debugging.
    return checksum(s);
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    int c = checksum_layer2("GDB");
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
