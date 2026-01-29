#include <cassert>
#include <string_view>

bool boot_ok(std::string_view log) {
    return log.find("Boot OK") != std::string_view::npos;
}

int exercise() {
    if (!boot_ok("[    0.1] Boot OK")) return 1;
    if (boot_ok("[    0.1] Boot FAIL")) return 2;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
