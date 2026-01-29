#include <cassert>
#include <string>
#include <string_view>

std::string encode_sample(int value) {
    return "S:" + std::to_string(value) + "\n";
}

int decode_sample(std::string_view text) {
    if (text.rfind("S:", 0) != 0) return -1;
    return std::stoi(std::string(text.substr(2)));
}

int exercise() {
    auto frame = encode_sample(42);
    if (frame != "S:42\n") return 1;
    if (decode_sample(frame) != 42) return 2;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
