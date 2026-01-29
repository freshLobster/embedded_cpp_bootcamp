#include <cassert>
#include <string>
#include <string_view>

unsigned checksum(std::string_view payload) {
    unsigned sum = 0;
    for (unsigned char c : payload) sum = (sum + c) & 0xFFu;
    return sum;
}

std::string encode_frame(std::string_view payload) {
    return std::string(payload) + "|CS=" + std::to_string(checksum(payload));
}

bool decode_frame(std::string_view frame, std::string& payload_out) {
    auto pos = frame.rfind("|CS=");
    if (pos == std::string_view::npos) return false;
    auto payload = frame.substr(0, pos);
    auto cs_str = frame.substr(pos + 4);
    unsigned cs = static_cast<unsigned>(std::stoul(std::string(cs_str)));
    if (checksum(payload) != cs) return false;
    payload_out = std::string(payload);
    return true;
}

int exercise() {
    auto frame = encode_frame("HELLO");
    std::string payload;
    if (!decode_frame(frame, payload)) return 1;
    if (payload != "HELLO") return 2;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
