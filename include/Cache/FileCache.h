#pragma once
#include <fstream>
#include <iostream>
#include "MemoryCache.h"

namespace YandexSchedule {

class FileCache : public Cache {
public:
    FileCache(const char* filename);
    FileCache(const FileCache& other);
    FileCache& operator=(const FileCache& other);
    ~FileCache() override;

    virtual std::optional<std::string> get(const std::string& key) const override;
    virtual void set(const std::string& key, const std::string& value) override;
private:
    void loadCache();
    void saveCache();

    const char* filename_;
    MemoryCache memCache_;
};

}