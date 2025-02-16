#include "Utils.h"

std::string YandexSchedule::Utils::today() {
    char buffer[11];
    std::time_t t = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&t));

    return buffer;
}

std::string YandexSchedule::Utils::toString(bool value) {
    return value ? "true" : "false";
}

std::string YandexSchedule::Utils::toString(uint16_t number) {
    return std::to_string(number);
}