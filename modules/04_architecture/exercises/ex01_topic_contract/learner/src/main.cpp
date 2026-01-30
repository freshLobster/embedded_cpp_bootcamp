// Exercise: Topic contract parser (non-owning views)
// Implement a parser that reads "name:type:rate" without unnecessary copies.

#include <cassert>      // For assert() in main.
#include <string>       // For std::string in the output contract.
#include <string_view>  // For non-owning input text.

struct TopicContract {
    std::string name;
    std::string type;
    int rate_hz{0};
};

// Parse format "name:type:rate" into `out`.
// Return true on success, false on any validation error.
bool parse_contract(std::string_view text, TopicContract& out) {
    // TODO: split by ':' into exactly three parts.
    // TODO: validate that name and type are non-empty.
    // TODO: parse rate to integer and require > 0.
    (void)text;
    (void)out;
    return false;
}

int exercise() {
    #error TODO_implement_exercise
    TopicContract tc;
    if (!parse_contract("sensor.raw:float:50", tc)) return 1;
    if (tc.name != "sensor.raw" || tc.type != "float" || tc.rate_hz != 50) return 2;

    TopicContract bad;
    if (parse_contract("invalid", bad)) return 3;
    return 0;
}

int main() {
    // The exercise returns 0 only when parsing and validation are correct.
    assert(exercise() == 0);
    return 0;
}
