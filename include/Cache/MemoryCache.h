#pragma once
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include "Cache.h"

using json = nlohmann::json;

namespace YandexSchedule {

class MemoryCache : public Cache {
public:
    virtual std::optional<std::string> get(const std::string& key) const override; 
    virtual void set(const std::string& key, const std::string& value) override;

    operator json() const;
private:
    std::unordered_map<std::string, std::string> cache_;
};

}