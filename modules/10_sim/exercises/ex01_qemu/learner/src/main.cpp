// Exercise: QEMU boot log parsing
// Implement a simple marker search for "Boot OK".
// This models checking a simulator log for a known-good boot marker.

#include <cassert>     // For assert() in main.
#include <string_view> // For log scanning without copies.

// TODO: return true if the log contains the substring "Boot OK".
// HOW: use std::string_view::find and compare against npos.
bool boot_ok(std::string_view log) {
    // TODO: use log.find("Boot OK") and compare with npos.
    // Suggested: return log.find("Boot OK") != std::string_view::npos;
    (void)log;
    return false;
}

int exercise() {
    // Keep this error until boot_ok() is implemented.
    #error TODO_implement_exercise
    if (!boot_ok("[    0.1] Boot OK")) return 1;
    if (boot_ok("[    0.1] Boot FAIL")) return 2;
    return 0;
}

int main() {
    // The parser must detect success and reject failure.
    assert(exercise() == 0);
    return 0;
}
