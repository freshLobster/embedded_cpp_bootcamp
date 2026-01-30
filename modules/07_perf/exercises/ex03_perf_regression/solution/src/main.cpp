// Solution: Efficient join with reserved capacity
// This avoids repeated reallocations by reserving the final size once.

#include <cassert>
#include <string>
#include <vector>

std::string join_with_commas(const std::vector<std::string>& parts) {
    if (parts.empty()) return {};
    // Compute total output length: sum of part sizes + delimiters.
    size_t total = 0;
    for (const auto& p : parts) total += p.size();
    total += parts.size() - 1;
    std::string out;
    // Reserve once to avoid repeated reallocations.
    out.reserve(total);
    for (size_t i = 0; i < parts.size(); ++i) {
        out += parts[i];
        if (i + 1 < parts.size()) out += ',';
    }
    return out;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    std::vector<std::string> v{"a","b","c"};
    if (join_with_commas(v) != "a,b,c") {
        return 1;
    }
    return 0;
}

int main(){
    // The solution must produce the correct joined string.
    assert(exercise()==0);
    return 0;
}
