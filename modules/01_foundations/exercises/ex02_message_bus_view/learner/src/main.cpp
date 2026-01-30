// Exercise: Message bus view (non-owning, const-correct)
// This learner stub asks you to expose a read-only view of a subscriber list
// without copying or allowing mutation. The tests describe the requirements.

#include <cassert>      // For assert() in main.
#include <string>       // For std::string storage.
#include <string_view>  // For non-owning string view return type.
#include <utility>      // For std::move.
#include <vector>       // For subscriber storage container.

// BusView is a non-owning "lens" over the MessageBus subscribers.
// It must not allow modification of the underlying vector.
class BusView {
public:
    // Store a raw pointer to the subscriber list; the view does not own it.
    explicit BusView(const std::vector<std::string>* subs) : subs_(subs) {}

    // TODO: return number of subscribers, handling nullptr safely.
    size_t size() const;

    // TODO: return a read-only view of the subscriber at index `idx`.
    // This must not return std::string by value or a mutable reference.
    std::string_view at(size_t idx) const;

private:
    const std::vector<std::string>* subs_{nullptr}; // Non-owning pointer.
};

// MessageBus stores subscribers and can produce a read-only view.
class MessageBus {
public:
    // TODO: store subscriber name in the internal container.
    void subscribe(std::string name);

    // TODO: return a BusView that refers to the internal subscriber vector.
    BusView view() const;

private:
    std::vector<std::string> subscribers_;
};

size_t BusView::size() const {
    // TODO: return 0 if subs_ is null; otherwise return subs_->size().
    return 0;
}

std::string_view BusView::at(size_t idx) const {
    // TODO: return a string_view that references the stored string.
    // Do not copy the string; do not return a mutable reference.
    (void)idx;
    return {};
}

void MessageBus::subscribe(std::string name) {
    // TODO: store the name. Prefer move to avoid a second allocation.
    (void)name;
}

BusView MessageBus::view() const {
    // TODO: return a BusView over subscribers_ (non-owning).
    return BusView(nullptr);
}

int exercise() {
    #error TODO_implement_exercise
    MessageBus bus;
    bus.subscribe("imu");
    bus.subscribe("gps");

    // View must expose current contents without copying.
    auto view = bus.view();
    if (view.size() != 2) return 1;
    if (view.at(0) != "imu") return 2;
    if (view.at(1) != "gps") return 3;

    // The view must observe updates to the underlying bus.
    bus.subscribe("lidar");
    if (view.size() != 3) return 4;
    if (view.at(2) != "lidar") return 5;

    return 0;
}

int main() {
    // The exercise returns 0 only if all view invariants hold.
    assert(exercise() == 0);
    return 0;
}
