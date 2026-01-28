// logging.hpp - lightweight logging with timestamps.
#pragma once

#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

namespace platform {

enum class LogLevel { kInfo, kWarn, kError, kDebug };

void set_log_level(LogLevel level);
void log(LogLevel level, const std::string& msg);

}  // namespace platform

#define LOG_INFO(msg) ::platform::log(::platform::LogLevel::kInfo, msg)
#define LOG_WARN(msg) ::platform::log(::platform::LogLevel::kWarn, msg)
#define LOG_ERROR(msg) ::platform::log(::platform::LogLevel::kError, msg)
#define LOG_DEBUG(msg) ::platform::log(::platform::LogLevel::kDebug, msg)

