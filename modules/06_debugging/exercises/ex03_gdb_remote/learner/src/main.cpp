// Exercise: GDB remote checksum practice
// Implement a deterministic checksum with a clear call chain for debugging.
// The implementation should be small enough to single-step in a debugger.

#include <cassert>     // For assert() in main.
#include <string_view> // For checksum input.

// TODO: implement a checksum that sums all bytes in the input string.
// HOW: iterate over the string, cast each char to unsigned char, and add
// the value to a running total. Return the total as an int.
int checksum(std::string_view s);

// Optional helper: wrap checksum in a second layer to deepen the call chain.
// This makes the debugger exercise more realistic.
int checksum_layer2(std::string_view s) {
    // TODO: call checksum(s) and return the result.
    // Keep this function small so you can step into checksum() easily.
    (void)s;
    return 0;
}

int checksum(std::string_view s) {
    // TODO: iterate over s and accumulate byte values into sum.
    // Use unsigned char to avoid sign extension.
    // Suggested outline:
    //   int sum = 0;
    //   for (unsigned char c : s) { sum += static_cast<int>(c); }
    //   return sum;
    (void)s;
    return 0;
}

int exercise() {
    // Keep this error until you have implemented checksum() and checksum_layer2().
    #error TODO_implement_exercise
    int c = checksum_layer2("GDB");
    // "GDB" should produce a non-zero checksum if your loop works.
    if (c <= 0) return 1;
    return 0;
}

int main() {
    // The test must pass and provide a stable debug target.
    // assert() keeps failures local and easy to inspect in GDB.
    assert(exercise() == 0);
    return 0;
}
