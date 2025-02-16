#pragma once
#include <string>
#include <optional>
#include <memory>
#include <iostream>
#include <optional>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "ScheduleTypes.h"
#include "Utils.h"

using json = nlohmann::json;

namespace YandexSchedule {
    class YandexScheduleAPI {
    public:
        YandexScheduleAPI(const std::string& apiKey);

        SearchResponse search(
            const std::string& from, 
            const std::string& to, 
            const SearchRequestAdditional&& params = {}
        );

        ScheduleResponse schedule(
            const std::string& station, 
            const ScheduleRequestAdditional&& params = {}
        );

        ThreadResponse thread(
            const std::string& uid, 
            const ThreadRequestAdditional&& params = {}
        );

    private:
        json processResponse(const cpr::Response& response);

        std::string baseUrl_ = "https://api.rasp.yandex.net/v3.0/";
        std::string apiKey_;
    };
};
