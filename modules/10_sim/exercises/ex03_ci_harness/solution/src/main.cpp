#include <cassert>
#include <string>
#include <vector>

std::string make_manifest(const std::vector<std::string>& artifacts) {
    std::string out = "{\"artifacts\":[";
    for (size_t i = 0; i < artifacts.size(); ++i) {
        out += "\"" + artifacts[i] + "\"";
        if (i + 1 < artifacts.size()) out += ",";
    }
    out += "]}";
    return out;
}

int exercise() {
    auto m = make_manifest({"a.log", "b.csv"});
    if (m.find("a.log") == std::string::npos) return 1;
    if (m.find("b.csv") == std::string::npos) return 2;
    return 0;
}

int main(){
    assert(exercise()==0);
    return 0;
}
