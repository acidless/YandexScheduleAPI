#include "Cache/FileCache.h"

YandexSchedule::FileCache::FileCache(const char* filename) : filename_(filename) {
    loadCache();
}

YandexSchedule::FileCache::~FileCache() {
    saveCache();
}

std::optional<std::string> YandexSchedule::FileCache::get(const std::string& key) const {
    return memCache_.get(key);
}

void YandexSchedule::FileCache::set(const std::string& key, const std::string& value) {
    memCache_.set(key, value);
}

void YandexSchedule::FileCache::loadCache() {
    std::ifstream file(filename_);
    if (!file.is_open()) {
        return;
    }
    
    json j = memCache_;
    file >> j;
    for (auto& [key, value] : j.items()) {
        memCache_.set(key, value);
    }

    file.close();
}

void YandexSchedule::FileCache::saveCache() {
    std::ofstream file(filename_);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open cache file");
    }

    json j = memCache_;
    file << j.dump(4);
    file.close();
}