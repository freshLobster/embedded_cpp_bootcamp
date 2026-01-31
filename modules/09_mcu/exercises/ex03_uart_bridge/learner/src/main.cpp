// Exercise: UART bridge framing with checksum
// Implement encode/decode with a simple checksum to detect corruption.
// This models a lightweight serial protocol for MCU-to-host links.

#include <cassert>     // For assert() in main.
#include <string>      // For std::string operations.
#include <string_view> // For parsing without copies.

// TODO: compute a simple checksum over the payload bytes.
// HOW: sum bytes modulo 256 using unsigned char to avoid sign issues.
unsigned checksum(std::string_view payload) {
    // TODO: sum bytes modulo 256 (use unsigned char).
    // Suggested outline:
    //   unsigned sum = 0;
    //   for (unsigned char c : payload) sum = (sum + c) & 0xFFu;
    //   return sum;
    (void)payload;
    return 0;
}

// TODO: encode payload with checksum as "<payload>|CS=<checksum>".
// HOW: compute checksum(payload), then build a string with a separator.
std::string encode_frame(std::string_view payload) {
    // Suggested outline:
    //   unsigned cs = checksum(payload);
    //   return std::string(payload) + "|CS=" + std::to_string(cs);
    (void)payload;
    return {};
}

// TODO: decode frame, validate checksum, and return payload via payload_out.
// HOW: split on "|CS=", parse checksum, recompute, compare.
bool decode_frame(std::string_view frame, std::string& payload_out) {
    // Suggested outline:
    //   auto pos = frame.find("|CS=");
    //   if (pos == npos) return false;
    //   payload = frame.substr(0, pos)
    //   checksum_text = frame.substr(pos + 4)
    //   if (parsed != checksum(payload)) return false;
    //   payload_out = payload; return true;
    (void)frame;
    (void)payload_out;
    return false;
}

int exercise() {
    // Keep this error until checksum/encode/decode are implemented.
    #error TODO_implement_exercise
    auto frame = encode_frame("HELLO");
    std::string payload;
    if (!decode_frame(frame, payload)) return 1;
    if (payload != "HELLO") return 2;
    return 0;
}

int main() {
    // The encoder/decoder must round-trip a valid payload.
    assert(exercise() == 0);
    return 0;
}
