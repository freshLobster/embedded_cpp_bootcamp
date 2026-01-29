#include <cassert>
#include <string>
#include <string_view>

struct TopicContract {
    std::string name;
    std::string type;
    int rate_hz{0};
};

bool parse_contract(std::string_view text, TopicContract& out) {
    auto first = text.find(':');
    auto second = text.find(':', first + 1);
    if (first == std::string_view::npos || second == std::string_view::npos) {
        return false;
    }
    out.name = std::string(text.substr(0, first));
    out.type = std::string(text.substr(first + 1, second - first - 1));
    out.rate_hz = std::stoi(std::string(text.substr(second + 1)));
    return !out.name.empty() && !out.type.empty() && out.rate_hz > 0;
}

int exercise() {
    TopicContract tc;
    if (!parse_contract("sensor.raw:float:50", tc)) {
        return 1;
    }
    if (tc.name != "sensor.raw" || tc.type != "float" || tc.rate_hz != 50) {
        return 2;
    }
    TopicContract bad;
    if (parse_contract("invalid", bad)) {
        return 3;
    }
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
