// Solution: UART sample framing
// Encodes and decodes a simple "S:<value>\n" frame format.
// This mirrors typical MCU telemetry framing conventions.

#include <cassert>     // assert() provides a minimal self-check.
#include <string>      // std::string for encoding.
#include <string_view> // std::string_view for parsing.

std::string encode_sample(int value) {
    // Prefix with "S:" and terminate with newline for easy framing.
    return "S:" + std::to_string(value) + "\n";
}

int decode_sample(std::string_view text) {
    // Validate prefix.
    if (text.rfind("S:", 0) != 0) return -1;
    // Parse the remainder as an integer (stoi stops at newline).
    return std::stoi(std::string(text.substr(2)));
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    auto frame = encode_sample(42);
    if (frame != "S:42\n") return 1;
    if (decode_sample(frame) != 42) return 2;
    return 0;
}

int main(){
    // The solution must encode and decode the sample consistently.
    assert(exercise()==0);
    return 0;
}
