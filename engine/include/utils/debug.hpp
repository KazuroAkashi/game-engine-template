#pragma once

namespace Engine {

enum class LogLevel {
    INFO, WARN, ERROR
};

void log_raw(const std::string& message);

void log(LogLevel level, const std::string& message);
inline void log(const std::string& message) { log(LogLevel::INFO, message); }

}