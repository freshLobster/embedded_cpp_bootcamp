// Solution: Topic contract parser (non-owning views)
// Parses "name:type:rate" using std::string_view for input.

#include <cassert>      // For assert() in main.
#include <string>       // For std::string.
#include <string_view>  // For std::string_view.

struct TopicContract {
    std::string name;
    std::string type;
    int rate_hz{0};
};

bool parse_contract(std::string_view text, TopicContract& out) {
    const size_t first = text.find(':');
    if (first == std::string_view::npos) return false;
    const size_t second = text.find(':', first + 1);
    if (second == std::string_view::npos) return false;

    std::string_view name = text.substr(0, first);
    std::string_view type = text.substr(first + 1, second - first - 1);
    std::string_view rate = text.substr(second + 1);

    if (name.empty() || type.empty() || rate.empty()) return false;

    int value = 0;
    for (char c : rate) {
        if (c < '0' || c > '9') return false;
        value = value * 10 + (c - '0');
    }
    if (value <= 0) return false;

    out.name.assign(name);
    out.type.assign(type);
    out.rate_hz = value;
    return true;
}

int exercise() {
    TopicContract tc;
    if (!parse_contract("sensor.raw:float:50", tc)) return 1;
    if (tc.name != "sensor.raw" || tc.type != "float" || tc.rate_hz != 50) return 2;
    TopicContract bad;
    if (parse_contract("invalid", bad)) return 3;
    return 0;
}

int main() {
    // The solution must parse valid contracts and reject invalid ones.
    assert(exercise() == 0);
    return 0;
}
