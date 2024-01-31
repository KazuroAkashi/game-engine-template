#pragma once

namespace Engine {

enum class LogLevel {
    INFO, WARN, ERROR
};

void log_raw(const std::string& message);

void log(const std::string& message, LogLevel level = LogLevel::INFO);

}