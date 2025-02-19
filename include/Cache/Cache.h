#pragma once
#include <string>
#include <optional>

namespace YandexSchedule {

class Cache {
public:
    virtual ~Cache() = default;
    virtual std::optional<std::string> get(const std::string& key) const = 0;
    virtual void set(const std::string& key, const std::string& value) = 0;
};

};