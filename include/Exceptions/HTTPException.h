#pragma once
#include <stdexcept>
#include <string>
#include <cpr/cpr.h>
#include "Export.h"

namespace YandexSchedule {

class YANDEX_SCHEDULE_API HTTPException : public std::runtime_error {
public:
    explicit HTTPException(const std::string& message, const cpr::Response& response);

    const char* what() const noexcept override;
private:
    std::string message_;
    const cpr::Response& response_;
};

}