#pragma once
#include <stdexcept>
#include <string>

namespace YandexSchedule {

class HTTPException : public std::runtime_error {
public:
    explicit HTTPException(const std::string& message, long statusCode);

    long getStatusCode() const;
private:
    long statusCode_;
};

}