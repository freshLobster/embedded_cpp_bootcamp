// Exercise: Tracing spans
// Implement a span guard that records elapsed time using a steady clock.

#include <cassert>  // For assert() in main.
#include <chrono>   // For steady_clock and durations.
#include <string>   // For span names.
#include <thread>   // For sleep_for in the test.
#include <utility>  // For std::move.
#include <vector>   // For span storage.

struct Span {
    std::string name;
    long long micros{0};
};

class Tracer;

// SpanGuard starts timing on construction and records on destruction.
class SpanGuard {
public:
    SpanGuard(Tracer& tracer, std::string name);
    ~SpanGuard();

private:
    Tracer& tracer_;
    std::string name_;
    std::chrono::steady_clock::time_point start_;
};

// Tracer collects spans.
class Tracer {
public:
    SpanGuard span(std::string name);
    void record(std::string name, long long micros);
    const std::vector<Span>& spans() const;

private:
    std::vector<Span> spans_;
    friend class SpanGuard;
};

SpanGuard::SpanGuard(Tracer& tracer, std::string name)
    : tracer_(tracer),
      name_(std::move(name)),
      start_(std::chrono::steady_clock::now()) {}

SpanGuard::~SpanGuard() {
    // TODO: compute elapsed microseconds and call tracer_.record(name_, micros).
    // Use steady_clock so the duration never goes backwards.
}

SpanGuard Tracer::span(std::string name) { return SpanGuard(*this, std::move(name)); }
void Tracer::record(std::string name, long long micros) { spans_.push_back({std::move(name), micros}); }
const std::vector<Span>& Tracer::spans() const { return spans_; }

int exercise() {
    #error TODO_implement_exercise
    Tracer t;
    {
        auto g = t.span("io");
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        (void)g;
    }
    if (t.spans().size() != 1) return 1;
    if (t.spans()[0].name != "io") return 2;
    if (t.spans()[0].micros <= 0) return 3;
    return 0;
}

int main() {
    // The exercise returns 0 only if a positive duration is recorded.
    assert(exercise() == 0);
    return 0;
}
