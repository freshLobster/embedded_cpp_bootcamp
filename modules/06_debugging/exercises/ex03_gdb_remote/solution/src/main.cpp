#include <cassert>
#include <string_view>

int checksum(std::string_view s) {
    int sum = 0;
    for (unsigned char c : s) {
        sum += static_cast<int>(c);
    }
    return sum;
}

int exercise() {
    int c = checksum("GDB");
    if (c <= 0) {
        return 1;
    }
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
