#include <cassert>
#include <string>
#include <vector>

std::string join_with_commas(const std::vector<std::string>& parts) {
    if (parts.empty()) return {};
    size_t total = 0;
    for (const auto& p : parts) total += p.size();
    total += parts.size() - 1;
    std::string out;
    out.reserve(total);
    for (size_t i = 0; i < parts.size(); ++i) {
        out += parts[i];
        if (i + 1 < parts.size()) out += ',';
    }
    return out;
}

int exercise() {
    std::vector<std::string> v{"a","b","c"};
    if (join_with_commas(v) != "a,b,c") {
        return 1;
    }
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
