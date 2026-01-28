#include "platform/logging.hpp"

#include <iomanip>

namespace platform {

namespace {
std::mutex log_mutex;
LogLevel current_level = LogLevel::kInfo;

const char* level_to_string(LogLevel level) {
    switch (level) {
        case LogLevel::kInfo:
            return "INFO";
        case LogLevel::kWarn:
            return "WARN";
        case LogLevel::kError:
            return "ERROR";
        case LogLevel::kDebug:
            return "DEBUG";
    }
    return "UNK";
}
}  // namespace

void set_log_level(LogLevel level) { current_level = level; }

void log(LogLevel level, const std::string& msg) {
    if (level < current_level) {
        return;
    }
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::lock_guard lock(log_mutex);
    std::cerr << "[" << level_to_string(level) << "] " << std::put_time(std::localtime(&now_c), "%F %T")
              << " [" << std::this_thread::get_id() << "] " << msg << std::endl;
}

}  // namespace platform
