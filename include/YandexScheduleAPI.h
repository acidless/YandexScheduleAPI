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
#include "Cache/MemoryCache.h"
#include "Cache/FileCache.h"
#include "Exceptions/HTTPException.h"
#include "RequestParams/SearchRequestParams.h"
#include "RequestParams/ScheduleRequestParams.h"
#include "RequestParams/NearestStationsRequestParams.h"
#include "RequestParams/NearestSettlementRequestParams.h"
#include "RequestParams/ThreadRequestParams.h"
#include "RequestParams/CarrierRequestParams.h"

#ifdef _WIN32
    #ifdef YANDEX_SCHEDULE_EXPORTS
        #define YANDEX_SCHEDULE_API __declspec(dllexport)
    #else
        #define YANDEX_SCHEDULE_API __declspec(dllimport)
    #endif
#else
    #define YANDEX_SCHEDULE_API
#endif

using json = nlohmann::json;

namespace YandexSchedule {

class YANDEX_SCHEDULE_API YandexScheduleAPI {
public:
    YandexScheduleAPI(const std::string& apiKey);
    YandexScheduleAPI(const std::string& apiKey, Cache* cache);

    SearchResponse search(
        const std::string& from, 
        const std::string& to, 
        const SearchRequestParams& params = {}
    );

    ScheduleResponse schedule(
        const std::string& station, 
        const ScheduleRequestParams& params = {}
    );

    ThreadResponse thread(
        const std::string& uid, 
        const ThreadRequestParams& params = {}
    );

    NearestStationsResponse nearestStations(
        const Geo&& geo,
        double distance, 
        const NearestStationsRequestParams& params = {}
    );

    NearestSettlementResponse nearestSettlement(
        const Geo&& geo,
        double distance = 50,
        const NearestSettlementRequestParams& params = {}
    );

    CarrierResponse carrier(
        const std::string& carrierCode,
        const CarrierRequestParams& params = {}
    );

    AllStationsReponse allStations(
        const BaseRequestParams& params = {}
    );

    CopyrightResponse copyright(
        const std::string& format = "json"
    );

private:
    json getWithCache(const cpr::Url& url, const cpr::Parameters& params);
    std::optional<json> tryGetFromCache(const std::string& key);


    std::string makeFullUrl(const cpr::Url& url, const cpr::Parameters& params) const;
    json processResponse(const cpr::Response& response);

    std::string baseUrl_ = "https://api.rasp.yandex.net/v3.0/";
    std::string apiKey_;
    std::unique_ptr<Cache> pCache_;
};

};
