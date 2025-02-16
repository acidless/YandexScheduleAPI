#include "YandexScheduleAPI.h"

YandexSchedule::YandexScheduleAPI::YandexScheduleAPI(const std::string& apiKey) 
: apiKey_(apiKey) {

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

    cpr::Response r = cpr::Get(url, cprParams);
    return processResponse(r).template get<YandexSchedule::SearchResponse>();
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

    cpr::Response r = cpr::Get(url, cprParams);
    return processResponse(r).template get<YandexSchedule::ScheduleResponse>();
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

    cpr::Response r = cpr::Get(url, cprParams);
    return processResponse(r).template get<YandexSchedule::ThreadResponse>();
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

    cpr::Response r = cpr::Get(url, cprParams);
    return processResponse(r).template get<YandexSchedule::NearestStationsResponse>();
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

    cpr::Response r = cpr::Get(url, cprParams);
    return processResponse(r).template get<YandexSchedule::NearestSettlementResponse>();
}


json YandexSchedule::YandexScheduleAPI::processResponse(const cpr::Response& response) {
    if(response.status_code != 200) {
        throw std::exception("Request error with status code: " + response.status_code);
    }
    
    return json::parse(response.text);
}