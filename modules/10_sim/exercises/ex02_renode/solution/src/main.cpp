#include <cassert>
#include <string_view>

int count_peripherals(std::string_view log) {
    int count = 0;
    std::string_view token = "peripheral";
    size_t pos = 0;
    while ((pos = log.find(token, pos)) != std::string_view::npos) {
        ++count;
        pos += token.size();
    }
    return count;
}

int exercise() {
    int c = count_peripherals("peripheral uart\nperipheral spi\n");
    if (c != 2) return 1;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
