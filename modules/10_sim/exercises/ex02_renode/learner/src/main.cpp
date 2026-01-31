// Exercise: Renode peripheral counting
// Implement a token counter for "peripheral" occurrences in a log.
// This simulates parsing a Renode log for attached devices.

#include <cassert>     // For assert() in main.
#include <string_view> // For scanning without copies.

// TODO: count how many times the token appears in the log.
// HOW: repeatedly call find() and advance the search position.
int count_peripherals(std::string_view log) {
    // TODO: implement a loop using find(token, pos).
    // Suggested outline:
    //   const std::string_view token = "peripheral";
    //   size_t pos = 0; int count = 0;
    //   while ((pos = log.find(token, pos)) != npos) { ++count; pos += token.size(); }
    //   return count;
    (void)log;
    return 0;
}

int exercise() {
    // Keep this error until count_peripherals() is implemented.
    #error TODO_implement_exercise
    int c = count_peripherals("peripheral uart\nperipheral spi\n");
    if (c != 2) return 1;
    return 0;
}

int main() {
    // The counter must detect each token occurrence.
    assert(exercise() == 0);
    return 0;
}
