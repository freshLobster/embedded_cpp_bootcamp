// Solution: Peripheral count from log
// Counts how many times a token appears in a log string.
// This mirrors parsing a Renode console log for device lines.

#include <cassert>     // assert() provides a minimal self-check.
#include <string_view> // std::string_view for scanning.

int count_peripherals(std::string_view log) {
    int count = 0;
    std::string_view token = "peripheral";
    size_t pos = 0;
    while ((pos = log.find(token, pos)) != std::string_view::npos) {
        // Found one occurrence; advance past it.
        ++count;
        pos += token.size();
    }
    return count;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    int c = count_peripherals("peripheral uart\nperipheral spi\n");
    if (c != 2) return 1;
    return 0;
}

int main(){
    // The solution must count all occurrences correctly.
    assert(exercise()==0);
    return 0;
}
