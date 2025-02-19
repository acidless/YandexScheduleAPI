#include "Exceptions/HTTPException.h"

YandexSchedule::HTTPException::HTTPException(const std::string& message, long statusCode)
 : statusCode_(statusCode), std::runtime_error(message) {

}

long YandexSchedule::HTTPException::getStatusCode() const {
    return statusCode_;
}