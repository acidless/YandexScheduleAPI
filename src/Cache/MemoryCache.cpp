#include "Cache/MemoryCache.h"

std::optional<std::string> YandexSchedule::MemoryCache::get(const std::string& key) const {
    auto iter = cache_.find(key);
    if(iter != cache_.end()) {
        return iter->second;
    }

    return {};
}

void YandexSchedule::MemoryCache::set(const std::string& key, const std::string& value) {
    cache_[key] = value;
}

YandexSchedule::MemoryCache::operator json() const {
    return cache_;
}