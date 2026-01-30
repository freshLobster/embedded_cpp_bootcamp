// Solution: Tracing spans
// Records span durations using std::chrono::steady_clock.

#include <cassert>  // For assert() in main.
#include <chrono>   // For steady_clock and durations.
#include <string>   // For span names.
#include <thread>   // For sleep_for.
#include <utility>  // For std::move.
#include <vector>   // For span storage.

struct Span {
    std::string name;
    long long micros{0};
};

class Tracer;

class SpanGuard {
public:
    SpanGuard(Tracer& tracer, std::string name);
    ~SpanGuard();

private:
    Tracer& tracer_;
    std::string name_;
    std::chrono::steady_clock::time_point start_;
};

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
    const auto end = std::chrono::steady_clock::now();
    const auto micros =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
    tracer_.record(std::move(name_), micros);
}

SpanGuard Tracer::span(std::string name) { return SpanGuard(*this, std::move(name)); }
void Tracer::record(std::string name, long long micros) { spans_.push_back({std::move(name), micros}); }
const std::vector<Span>& Tracer::spans() const { return spans_; }

int exercise() {
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
    // The solution must record a positive duration for the span.
    assert(exercise() == 0);
    return 0;
}
