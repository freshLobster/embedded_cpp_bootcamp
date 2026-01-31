// Solution: Artifact manifest builder
// Builds a deterministic JSON-like manifest string.
// This simulates a CI summary file for simulation artifacts.

#include <cassert> // assert() provides a minimal self-check.
#include <string>  // std::string for building JSON-like output.
#include <vector>  // std::vector for artifact list.

std::string make_manifest(const std::vector<std::string>& artifacts) {
    std::string out = "{\"artifacts\":[";
    for (size_t i = 0; i < artifacts.size(); ++i) {
        // Quote each artifact name.
        out += "\"" + artifacts[i] + "\"";
        if (i + 1 < artifacts.size()) out += ",";
    }
    out += "]}";
    return out;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    auto m = make_manifest({"a.log", "b.csv"});
    if (m.find("a.log") == std::string::npos) return 1;
    if (m.find("b.csv") == std::string::npos) return 2;
    return 0;
}

int main(){
    // The solution must include all artifacts in the manifest.
    assert(exercise()==0);
    return 0;
}
