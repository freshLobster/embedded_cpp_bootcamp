// Exercise: UART sample framing
// Implement encode/decode helpers for a simple "S:<value>\n" frame.
// The format is intentionally tiny to mimic MCU serial telemetry.

#include <cassert>     // For assert() in main.
#include <string>      // For std::string outputs.
#include <string_view> // For parsing without copies.

// TODO: encode a sample value into a UART-friendly frame.
// HOW: prefix with "S:", append decimal digits, then '\n'.
std::string encode_sample(int value) {
    // TODO: return "S:" + value + "\n".
    // Suggested outline:
    //   return "S:" + std::to_string(value) + "\n";
    (void)value;
    return {};
}

// TODO: decode a UART frame into a sample value.
// Return -1 for invalid frames.
// HOW: check prefix and suffix, then parse the integer substring.
int decode_sample(std::string_view text) {
    // TODO: verify prefix "S:", then parse integer.
    // Suggested outline:
    //   if (!text.starts_with("S:")) return -1;
    //   if (text.back() != '\n') return -1;
    //   auto number = text.substr(2, text.size() - 3);
    //   return std::stoi(std::string(number));
    (void)text;
    return -1;
}

int exercise() {
    // Keep this error until encode/decode are implemented.
    #error TODO_implement_exercise
    auto frame = encode_sample(42);
    if (frame != "S:42\n") return 1;
    if (decode_sample(frame) != 42) return 2;
    return 0;
}

int main() {
    // The framing functions must round-trip correctly.
    assert(exercise() == 0);
    return 0;
}
