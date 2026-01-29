#include <cassert>
#include <string>
#include <string_view>
#include <vector>

class BusView {
public:
    explicit BusView(const std::vector<std::string>* subs) : subs_(subs) {}
    size_t size() const { return subs_ ? subs_->size() : 0; }
    std::string_view at(size_t idx) const { return (*subs_)[idx]; }
private:
    const std::vector<std::string>* subs_;
};

class MessageBus {
public:
    void subscribe(std::string name) { subscribers_.push_back(std::move(name)); }
    BusView view() const { return BusView(&subscribers_); }
private:
    std::vector<std::string> subscribers_;
};

int exercise() {
    MessageBus bus;
    bus.subscribe("imu");
    bus.subscribe("gps");

    auto view = bus.view();
    if (view.size() != 2) {
        return 1;
    }
    if (view.at(0) != "imu" || view.at(1) != "gps") {
        return 2;
    }

    bus.subscribe("lidar");
    if (view.size() != 3) {
        return 3;
    }
    if (view.at(2) != "lidar") {
        return 4;
    }

    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
