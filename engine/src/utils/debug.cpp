#include "utils/debug.hpp"

#ifdef DEBUG
#include <iostream>
#include <fmt/core.h>
#include <chrono>

#ifdef __gnu_linux__
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLD   "\033[1m"      /* Bold */
#else
#define RESET   ""
#define BLACK   ""      
#define RED     ""      
#define GREEN   ""      
#define YELLOW  ""      
#define BLUE    ""      
#define MAGENTA ""      
#define CYAN    ""      
#define WHITE   ""      
#define BOLD   ""
#endif

#endif

namespace Engine {

#ifdef DEBUG
static std::string log_level_name(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

static std::string log_level_color(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:
            return BLUE;
        case LogLevel::WARN:
            return YELLOW;
        case LogLevel::ERROR:
            return RED;
        default:
            return "";
    }
}

static std::string time_of_day() {
    using namespace std::chrono;
    auto const time = system_clock::to_time_t(system_clock::now());
    auto const local = std::localtime(&time);
    std::string clock(10, '\0');
    std::strftime(&clock[0], clock.size(), "%H:%M:%S", local);
    return clock;
}
#endif

void log_raw(const std::string& message [[maybe_unused]] ) {
#ifdef DEBUG
    std::cout << message << std::endl;
#endif
}

void log(LogLevel level [[maybe_unused]], const std::string& message [[maybe_unused]] ) {
#ifdef DEBUG
    const auto color = log_level_color(level);
    log_raw(fmt::format("{}{}[{} {}]{}{} {}{}", BOLD, color, time_of_day(), log_level_name(level), RESET, color, message, RESET));
#endif
}
}