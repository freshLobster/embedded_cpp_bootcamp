// Solution: Message bus view (non-owning, const-correct)
// This implementation returns read-only views of internal storage with no copies.
// Key idea: MessageBus owns strings; BusView only borrows them.

#include <cassert>     // For assert() in main.
#include <string>      // For std::string storage.
#include <string_view> // For non-owning views.
#include <vector>      // For subscriber container.

// BusView is a non-owning view over the subscriber vector.
// It must never allocate or mutate the underlying data.
class BusView {
public:
    explicit BusView(const std::vector<std::string>* subs) : subs_(subs) {}

    // Size returns 0 if the view is empty/null.
    // This makes the view safe even if it was default-constructed.
    size_t size() const { return subs_ ? subs_->size() : 0; }

    // at() returns a read-only view of the subscriber string.
    // Returning std::string_view avoids copies and prevents mutation.
    std::string_view at(size_t idx) const { return (*subs_)[idx]; }

private:
    const std::vector<std::string>* subs_; // Non-owning pointer.
};

// MessageBus owns the subscriber list and can produce a view.
class MessageBus {
public:
    // Store the subscriber name; move to avoid an extra allocation.
    // Ownership transfers to the bus here.
    void subscribe(std::string name) { subscribers_.push_back(std::move(name)); }

    // Expose a view that refers to the internal subscriber vector.
    // The view is only valid while the bus is alive.
    BusView view() const { return BusView(&subscribers_); }

private:
    std::vector<std::string> subscribers_;
};

// exercise() runs a minimal self-check for this solution.
// Return 0 on success; non-zero indicates which invariant failed.
int exercise() {
    MessageBus bus;
    bus.subscribe("imu");
    bus.subscribe("gps");

    // View should see existing subscribers.
    auto view = bus.view();
    if (view.size() != 2) {
        return 1;
    }
    if (view.at(0) != "imu" || view.at(1) != "gps") {
        return 2;
    }

    // View should reflect later additions.
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
    // The solution must satisfy all invariants.
    assert(exercise() == 0);
    return 0;
}
