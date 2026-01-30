#include <cassert>
#include <string>
#include <string_view>

struct TopicContract {
    std::string name;
    std::string type;
    int rate_hz{0};
};

bool parse_contract(std::string_view text, TopicContract& out) {
    // TODO: parse format "name:type:rate" and validate fields.
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
    assert(exercise() == 0);
    return 0;
}
