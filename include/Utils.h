#include <string>
#include <ctime>

namespace YandexSchedule {
    namespace Utils {
        std::string today();

        template<typename T>
        std::string toString(T value) {
            return std::to_string(value);
        }
    };
};