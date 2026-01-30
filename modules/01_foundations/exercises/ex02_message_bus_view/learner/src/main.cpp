#include <cassert>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class BusView {
public:
    explicit BusView(const std::vector<std::string>* subs) : subs_(subs) {}
    size_t size() const;                // TODO: return number of subscribers.
    std::string_view at(size_t idx) const; // TODO: return read-only view.
private:
    const std::vector<std::string>* subs_{nullptr};
};

class MessageBus {
public:
    void subscribe(std::string name);   // TODO: store subscriber name.
    BusView view() const;               // TODO: return read-only view.
private:
    std::vector<std::string> subscribers_;
};

size_t BusView::size() const {
    // TODO: handle null pointer safely.
    return 0;
}

std::string_view BusView::at(size_t idx) const {
    // TODO: return a string_view into the stored subscriber list.
    (void)idx;
    return {};
}

void MessageBus::subscribe(std::string name) {
    // TODO: store name without extra copies if possible.
    (void)name;
}

BusView MessageBus::view() const {
    // TODO: return BusView over subscribers_.
    return BusView(nullptr);
}

int exercise() {
    #error TODO_implement_exercise
    MessageBus bus;
    bus.subscribe("imu");
    bus.subscribe("gps");

    auto view = bus.view();
    if (view.size() != 2) return 1;
    if (view.at(0) != "imu") return 2;
    if (view.at(1) != "gps") return 3;

    bus.subscribe("lidar");
    if (view.size() != 3) return 4;
    if (view.at(2) != "lidar") return 5;

    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
