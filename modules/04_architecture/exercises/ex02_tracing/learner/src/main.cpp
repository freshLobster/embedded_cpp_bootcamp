#include <cassert>
#include <chrono>
#include <string>
#include <vector>
#include <thread>
#include <utility>

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
    : tracer_(tracer), name_(std::move(name)), start_(std::chrono::steady_clock::now()) {}

SpanGuard::~SpanGuard() {
    // TODO: compute elapsed time and record span.
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
    }
    if (t.spans().size() != 1) return 1;
    if (t.spans()[0].name != "io") return 2;
    if (t.spans()[0].micros <= 0) return 3;
    return 0;
}

int main() {
    assert(exercise() == 0);
    return 0;
}
