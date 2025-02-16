#include "YandexScheduleAPI.h"

YandexSchedule::YandexScheduleAPI::YandexScheduleAPI(const std::string& apiKey) 
: apiKey_(apiKey) {

}

YandexSchedule::SearchResponse YandexSchedule::YandexScheduleAPI::search(
    const std::string& from, 
    const std::string& to, 
    const SearchRequestAdditional&& params
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
    const ScheduleRequestAdditional&& params
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

json YandexSchedule::YandexScheduleAPI::processResponse(const cpr::Response& response) {
    if(response.status_code != 200) {
        throw std::exception("Request error with status code: " + response.status_code);
    }
    
    return json::parse(response.text);
}