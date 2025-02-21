#include "Exceptions/HTTPException.h"

YandexSchedule::HTTPException::HTTPException(const std::string& message,  const cpr::Response& response)
 : std::runtime_error(message), response_(response) {
    message_ = (message_ + 
            " Status code: " + std::to_string(response_.status_code) + 
            " Response: " + response_.text);
}

const char* YandexSchedule::HTTPException::what() const noexcept {
    return message_.c_str();
}