#include "Utils.h"

std::string YandexSchedule::Utils::today() {
    char buffer[11];
    std::time_t t = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&t));

    return buffer;
}

template <>
std::string YandexSchedule::Utils::toString<bool>(bool value) {
    return value ? "true" : "false";
}