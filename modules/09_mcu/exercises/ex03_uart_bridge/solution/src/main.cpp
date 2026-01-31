// Solution: UART frame encoder/decoder with checksum
// The checksum detects corruption in a simple payload frame.
// This mirrors lightweight MCU serial protocols.

#include <cassert>     // assert() provides a minimal self-check.
#include <string>      // std::string for building frames.
#include <string_view> // std::string_view for parsing.

unsigned checksum(std::string_view payload) {
    unsigned sum = 0;
    // Add each byte modulo 256 to get a simple checksum.
    for (unsigned char c : payload) sum = (sum + c) & 0xFFu;
    return sum;
}

std::string encode_frame(std::string_view payload) {
    // Format: <payload>|CS=<checksum>
    return std::string(payload) + "|CS=" + std::to_string(checksum(payload));
}

bool decode_frame(std::string_view frame, std::string& payload_out) {
    // Find the checksum delimiter from the right.
    auto pos = frame.rfind("|CS=");
    if (pos == std::string_view::npos) return false;
    auto payload = frame.substr(0, pos);
    auto cs_str = frame.substr(pos + 4);
    unsigned cs = static_cast<unsigned>(std::stoul(std::string(cs_str)));
    // Verify checksum matches.
    if (checksum(payload) != cs) return false;
    // Output the payload if valid.
    payload_out = std::string(payload);
    return true;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    auto frame = encode_frame("HELLO");
    std::string payload;
    if (!decode_frame(frame, payload)) return 1;
    if (payload != "HELLO") return 2;
    return 0;
}

int main(){
    // The solution must encode/decode with checksum validation.
    assert(exercise()==0);
    return 0;
}
