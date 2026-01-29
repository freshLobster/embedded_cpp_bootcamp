#include <cassert>
#include <string>

std::string target_arch() {
#if defined(__aarch64__)
    return "aarch64";
#elif defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#else
    return "unknown";
#endif
}

int exercise() {
    auto arch = target_arch();
    if (arch == "unknown") {
        return 1;
    }
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
