// Solution: Boot log marker check
// Scans a log string for a "Boot OK" marker.

#include <cassert>
#include <string_view>

bool boot_ok(std::string_view log) {
    // Return true only if the marker substring appears.
    return log.find("Boot OK") != std::string_view::npos;
}

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    if (!boot_ok("[    0.1] Boot OK")) return 1;
    if (boot_ok("[    0.1] Boot FAIL")) return 2;
    return 0;
}

int main(){
    // The solution must detect only the success marker.
    assert(exercise()==0);
    return 0;
}
