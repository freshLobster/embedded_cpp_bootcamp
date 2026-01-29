#include <cassert>
#include <string>
#include <vector>

std::vector<std::string> bottlenecks(bool cpu, bool gpu, bool io) {
    std::vector<std::string> out;
    if (cpu) out.push_back("cpu");
    if (gpu) out.push_back("gpu");
    if (io) out.push_back("io");
    return out;
}

int exercise() {
    auto b = bottlenecks(true, false, true);
    if (b.size() != 2) return 1;
    if (b[0] != "cpu" || b[1] != "io") return 2;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
