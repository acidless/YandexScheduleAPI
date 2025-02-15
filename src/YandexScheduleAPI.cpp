#include "YandexScheduleAPI.h"

std::string today() {
    char buffer[11];
    std::time_t t = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&t));

    return buffer;
}