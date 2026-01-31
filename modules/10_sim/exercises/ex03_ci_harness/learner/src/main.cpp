// Exercise: CI artifact manifest
// Implement a JSON-like manifest string for simulation artifacts.
// The output is plain text to keep the exercise dependency-free.

#include <cassert> // For assert() in main.
#include <string>  // For string building.
#include <vector>  // For artifact list input.

// TODO: build a JSON-like string: {"artifacts":["a.log","b.csv"]}.
// HOW: build the string piece-by-piece to control commas and quotes.
std::string make_manifest(const std::vector<std::string>& artifacts) {
    // TODO: start with {"artifacts":[
    // TODO: append each artifact in quotes, separated by commas.
    // TODO: close with ]}
    // Suggested outline:
    //   std::string out = "{\"artifacts\":[";
    //   for (size_t i = 0; i < artifacts.size(); ++i) {
    //       out += "\"";
    //       out += artifacts[i];
    //       out += "\"";
    //       if (i + 1 < artifacts.size()) out += ",";
    //   }
    //   out += "]}";
    //   return out;
    (void)artifacts;
    return {};
}

int exercise() {
    // Keep this error until make_manifest() is implemented.
    #error TODO_implement_exercise
    auto m = make_manifest({"a.log", "b.csv"});
    if (m.find("a.log") == std::string::npos) return 1;
    if (m.find("b.csv") == std::string::npos) return 2;
    return 0;
}

int main() {
    // The manifest must include all artifact names.
    assert(exercise() == 0);
    return 0;
}
