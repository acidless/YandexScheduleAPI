#include "YandexScheduleAPI.h"

YandexSchedule::YandexScheduleAPI::YandexScheduleAPI(const std::string& apiKey) 
: apiKey_(apiKey), pCache_(new MemoryCache()) {
}

YandexSchedule::YandexScheduleAPI::YandexScheduleAPI(const std::string& apiKey, Cache* cache)
: apiKey_(apiKey), pCache_(cache) {

}

YandexSchedule::SearchResponse YandexSchedule::YandexScheduleAPI::search(
    const std::string& from, 
    const std::string& to, 
    const SearchRequestParams&& params
) {
    auto url = cpr::Url{baseUrl_ + "search/"};
    auto cprParams = cpr::Parameters{
        {"apikey", apiKey_}, {"from", from},
        {"to", to}, {"format", params.format},
        {"lang", params.lang}, {"date", params.date},
        {"transport_types", params.transport_types}, {"system", params.system},
        {"show_systems", params.show_systems}, {"offset", Utils::toString(params.offset)},
        {"limit", Utils::toString(params.limit)}, {"add_days_mask", Utils::toString(params.add_days_mask)},
        {"result_timezone", params.result_timezone}, {"transfers", Utils::toString(params.transfers)},
    };

    return getWithCache(url, cprParams).template get<SearchResponse>();
}

YandexSchedule::ScheduleResponse YandexSchedule::YandexScheduleAPI::schedule(
    const std::string& station, 
    const ScheduleRequestParams&& params
) {
    auto url = cpr::Url{baseUrl_ + "schedule/"};
    auto cprParams = cpr::Parameters{
        {"apikey", apiKey_}, {"station", station},
        {"format", params.format}, {"lang", params.lang}, 
        {"date", params.date}, {"transport_types", params.transport_types},
        {"system", params.system}, {"show_systems", params.show_systems}, 
        {"result_timezone", params.result_timezone}, {"direction", params.direction},
        {"event", params.event}
    };

    return getWithCache(url, cprParams).template get<ScheduleResponse>();
}

YandexSchedule::ThreadResponse YandexSchedule::YandexScheduleAPI::thread(
    const std::string& uid, 
    const ThreadRequestParams&& params
) {
    auto url = cpr::Url{baseUrl_ + "thread/"};
    auto cprParams = cpr::Parameters{
        {"apikey", apiKey_}, {"from", params.from},
        {"format", params.format}, {"lang", params.lang}, 
        {"to", params.to}, {"uid", uid},{"show_systems", params.show_systems}
    };

    return getWithCache(url, cprParams).template get<ThreadResponse>();
}

YandexSchedule::NearestStationsResponse YandexSchedule::YandexScheduleAPI::nearestStations(
    const Geo&& geo,
    double distance, 
    const NearestStationsRequestParams&& params
) {
    auto url = cpr::Url{baseUrl_ + "nearest_stations/"};
    auto cprParams = cpr::Parameters{
        {"apikey", apiKey_}, {"station_types", params.station_types},
        {"format", params.format}, {"lang", params.lang}, 
        {"transport_types", params.transport_types}, {"offset", Utils::toString(params.offset)},
        {"limit", Utils::toString(params.limit)}, {"lat",  Utils::toString(geo.lat)},
        {"lng", Utils::toString(geo.lng)}, {"distance", Utils::toString(distance)}
    };

    return getWithCache(url, cprParams).template get<NearestStationsResponse>();
}


YandexSchedule::NearestSettlementResponse YandexSchedule::YandexScheduleAPI::nearestSettlement(
    const Geo&& geo,
    double distance,
    const NearestSettlementRequestParams&& params
) {
    auto url = cpr::Url{baseUrl_ + "nearest_settlement/"};
    auto cprParams = cpr::Parameters{
        {"apikey", apiKey_}, {"format", params.format}, 
        {"lang", params.lang}, {"lat",  Utils::toString(geo.lat)},
        {"lng", Utils::toString(geo.lng)}, {"distance", Utils::toString(distance)}
    };

    return getWithCache(url, cprParams).template get<NearestSettlementResponse>();
}

YandexSchedule::CarrierResponse YandexSchedule::YandexScheduleAPI::carrier(
    const std::string& carrierCode,
    const CarrierRequestParams&& params
) {
    auto url = cpr::Url{baseUrl_ + "carrier/"};
    auto cprParams = cpr::Parameters{
        {"apikey", apiKey_}, {"format", params.format}, 
        {"lang", params.lang}, {"system", params.system},
        {"code", carrierCode}
    };

    return getWithCache(url, cprParams).template get<CarrierResponse>();
}

YandexSchedule::AllStationsReponse YandexSchedule::YandexScheduleAPI::allStations(
    const BaseRequestParams&& params
) {
    auto url = cpr::Url{baseUrl_ + "stations_list/"};
    auto cprParams = cpr::Parameters{
        {"apikey", apiKey_}, {"format", params.format}, 
        {"lang", params.lang}
    };

    cpr::Response r = cpr::Get(url, cprParams);
    return processResponse(r).template get<AllStationsReponse>();
}

YandexSchedule::CopyrightResponse YandexSchedule::YandexScheduleAPI::copyright(
    const std::string& format
) {
    auto url = cpr::Url{baseUrl_ + "copyright/"};
    auto cprParams = cpr::Parameters{
        {"apikey", apiKey_}, {"format", format}
    };

    cpr::Response r = cpr::Get(url, cprParams);
    return processResponse(r).template get<CopyrightResponse>();
}

json YandexSchedule::YandexScheduleAPI::getWithCache(
    const cpr::Url& url, 
    const cpr::Parameters& params
    ) {
    if(auto cachedRes = tryGetFromCache(makeFullUrl(url, params))) {
        return cachedRes.value();
    }
    
    cpr::Response r = cpr::Get(url, params);
    return processResponse(r);
}

std::optional<json> YandexSchedule::YandexScheduleAPI::tryGetFromCache(const std::string& key) {
    if(auto response = pCache_->get(key)) {
        return json::parse(response.value());
    }

    return {};
}

std::string YandexSchedule::YandexScheduleAPI::makeFullUrl(
    const cpr::Url& url, 
    const cpr::Parameters& params
) const {
    return url.str() + "?" + params.GetContent({}).c_str();
}

json YandexSchedule::YandexScheduleAPI::processResponse(const cpr::Response& response) {
    if(response.status_code == 0) {
        throw std::runtime_error(response.error.message);
    }
    
    if(response.status_code >= 400) {
        throw HTTPException("HTTP error: ", response.status_code);
    }
    
    pCache_->set(response.url.c_str(), response.text);
    return json::parse(response.text);
}