#pragma once
#include <string>
#include <ctime>
#include "Export.h"

namespace YandexSchedule {
    namespace Utils {
        std::string YANDEX_SCHEDULE_API today();

        template<typename T>
        std::string toString(T value) {
            return std::to_string(value);
        }

        template <>
        std::string toString<bool>(bool value);
    };
};