#pragma once
#include <string>
#include <optional>
#include <memory>
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "ScheduleTypes.h"

using json = nlohmann::json;

std::string today();

class YandexScheduleAPI {
private:
    std::string baseUrl_ = "https://api.rasp.yandex.net/v3.0/";
};
