#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <optional>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

NLOHMANN_JSON_NAMESPACE_BEGIN
        template <typename T>
        struct adl_serializer<std::optional<T>> {
        static void to_json(json& j, const std::optional<T>& opt) {
            if (opt.has_value()) {
                j = *opt;
            } else {
                j = nullptr;
            }
        }

        static void from_json(const json& j, std::optional<T>& opt) {
            if (j.is_null()) {
                opt.reset();
            } else {
                opt = j.template get<T>();
            }
        }
    };
NLOHMANN_JSON_NAMESPACE_END

namespace YandexSchedule {
    struct Pagination {
        uint16_t total;
        uint16_t limit;
        uint16_t offset;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Pagination, total, limit, offset)


    struct Station {
        std::string code;
        std::string title;
        std::string station_type;
        std::string station_type_name;
        std::optional<std::string> popular_title;
        std::optional<std::string> short_title;
        std::string transport_type;
        std::string type;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Station, 
        code, title, station_type, station_type_name,
        popular_title, short_title, transport_type, type
    )

    struct Interval {
        std::string density;
        std::string end_time;
        std::string begin_time;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Interval, density, end_time, begin_time)

    struct CarrierCode {
        std::optional<std::string> icao;
        std::optional<std::string> sirena;
        std::optional<std::string> iata;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(CarrierCode, icao, sirena, iata)

    struct Carrier {
        int64_t code;
        std::string contracts;
        std::string url;
        std::optional<std::string> logo_svg;
        std::string title;
        std::string phone;
        CarrierCode codes;
        std::optional<std::string> address;
        std::optional<std::string> logo;
        std::optional<std::string> email;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Carrier,
        code, contracts, url, logo_svg, title, phone,
        codes, address, logo, email
    )

    struct TransportSubtype {
        std::optional<std::string> color;
        std::optional<std::string> code;
        std::optional<std::string> title;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(TransportSubtype, color, code, title)

    struct Thread {
        std::string uid;
        std::string title;
        Interval interval;
        std::string number;
        std::optional<std::string> short_title;
        std::string thread_method_link;
        std::optional<Carrier> carrier;
        std::string transport_type;
        std::optional<std::string> vehicle;
        TransportSubtype transport_subtype;
        std::optional<std::string> express_type;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Thread,
        uid, title, interval, number, short_title,
        thread_method_link, carrier, transport_type, vehicle,
        transport_subtype, express_type
    )

    struct Price {
        uint16_t cents;
        uint16_t whole;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Price, cents, whole)

    struct Place {
        std::string currency;
        Price price;
        std::string name;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Place, currency, price, name)

    struct Tickets {
        bool et_marker;
        std::vector<Place> places;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Tickets, et_marker, places)

    struct Segment {
        Station from;
        Thread thread;
        std::string departure_platform;
        std::string stops;
        std::optional<std::string> departure_terminal;
        Station to;
        bool has_transfers;
        Tickets tickets_info;
        uint32_t duration;
        std::optional<std::string> arrival_terminal;
        std::string start_date;
        std::optional<std::string> arrival_platform;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Segment,
        from, thread, departure_platform, stops,
        departure_terminal, to, has_transfers,
        tickets_info, duration, arrival_terminal,
        start_date, arrival_platform
    )

    struct SearchPlace {
        std::string code;
        std::string type;
        std::string popular_title;
        std::optional<std::string> short_title;
        std::string title;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SearchPlace,
        code, type, popular_title, short_title, title
    )

    struct Search {
        std::optional<std::string> date;
        SearchPlace from;
        SearchPlace to;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Search, date, from, to)

    struct SearchResponse {
        Pagination pagination;
        std::vector<Segment> interval_segments;
        std::vector<Segment> segments;
        Search search;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SearchResponse,
        pagination, interval_segments, segments, search
    )

    struct Schedule {
        std::optional<std::string> except_days;
        std::optional<std::string> arrival;
        Thread thread;
        bool is_fuzzy;
        std::string days;
        std::string stops;
        std::string departure;
        std::string terminal;
        std::string platform;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Schedule,
        except_days, arrival, thread, is_fuzzy, days, stops,
        departure, terminal, platform
    )

    struct Direction {
        std::string code;
        std::string title;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Direction, code, title)

    struct ScheduleResponse {
        std::optional<std::string> date;
        Pagination pagination;
        Station station;
        std::vector<Schedule> schedule;
        std::vector<Schedule> interval_schedule;
        Direction schedule_direction;
        std::vector<Direction> directions;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(ScheduleResponse,
        date, pagination, station, schedule, interval_schedule,
        schedule_direction, directions
    )

    struct Stop {
        std::optional<std::string> arrival;
        std::optional<std::string> departure;
        uint32_t duration;
        std::optional<uint32_t> stop_time;
        Station station;
        std::optional<std::string> terminal;
        std::string platform;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Stop,
        arrival, departure, duration, stop_time, station,
        terminal, platform
    )
    
    struct ThreadResponse {
        std::optional<std::string> except_days;
        std::optional<std::string> arrival_date;
        std::optional<std::string> from;
        std::string uid;
        std::string title;
        Interval interval;
        std::optional<std::string> departure_date;
        std::string start_time;
        std::string number;
        std::optional<std::string> short_title;
        std::string days;
        std::optional<std::string> to;
        std::optional<Carrier> carrier;
        std::string transport_type;
        std::vector<Stop> stops;
        std::optional<std::string> vehicle;
        std::string start_date;
        TransportSubtype transport_subtype;
        std::optional<std::string> express_type;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(ThreadResponse,
        except_days, arrival_date, from, uid, title, interval,
        departure_date, start_time, number, short_title, days,
        to, carrier, transport_type, stops, vehicle, start_date,
        transport_subtype, express_type
    )

    struct TypeChoiceSchedule {
        std::string desktop_url;
        std::string touch_url;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(TypeChoiceSchedule,
        desktop_url, touch_url
    )

    struct TypeChoice {
        TypeChoiceSchedule schedule;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(TypeChoice, schedule)

    struct Geo {
        double lat;
        double lng;
    };

    struct NearestStation : public Station {
        double distance;
        TypeChoice type_choices;
        std::optional<uint16_t> majority;
        double lat;
        double lng;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(NearestStation,
        distance, type_choices, majority, lat, lng
    )

    struct NearestStationsResponse {
        Pagination pagination;
        std::vector<NearestStation> stations;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(NearestStationsResponse,
        pagination, stations
    )

    struct NearestSettlementResponse {
        double distance;
        std::string code;
        std::string title;
        std::string popular_title;
        std::string short_title;
        double lat;
        double lng;
        std::string type;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(NearestSettlementResponse,
        distance, code, title, popular_title, short_title,
        lat, lng, type
    )

    struct CarrierResponse {
        std::vector<Carrier> carriers;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(CarrierResponse,
        carriers
    )

    struct Codes {
        std::string esr_code;
        std::string yandex_code;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Codes,
        esr_code, yandex_code
    )

    struct SettlementStation {
        std::string direction;
        Codes codes;
        std::string station_type;
        std::string title;
        double longitude;
        std::string transport_type;
        double latitude;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SettlementStation,
        direction, codes, station_type, title, longitude,
        transport_type, latitude
    )

    struct Settlement {
        std::string title;
        Codes codes;
        std::vector<SettlementStation> stations;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Settlement,
        title, codes, stations
    )

    struct Region {
        std::vector<Settlement> settlements;
        Codes codes;
        std::string title;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Region,
        settlements, codes, title
    )

    struct Country {
        std::vector<Region> regions;
        Codes codes;
        std::string title;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Country,
        regions, codes, title
    )

    struct AllStationsReponse {
        std::vector<Country> countries;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(AllStationsReponse, countries)

    struct Copyright {
        std::string logo_vm;
        std::string url;
        std::string logo_vd;
        std::string logo_hy;
        std::string logo_hd;
        std::string logo_vy;
        std::string text;
        std::string logo_hm;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Copyright,
        logo_vm, url, logo_vd, logo_hy, logo_hd,
        logo_vy, text, logo_hm
    )

    struct CopyrightResponse {
        Copyright copyright;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(CopyrightResponse,
        copyright
    )

    struct BaseRequestParams {
        std::string format = "json";
        std::string lang = "ru_RU";
    };

    struct PaginatedRequestParams {
        uint16_t offset = 0;
        uint16_t limit = 100;
    };

    struct SearchRequestParams
    : BaseRequestParams, PaginatedRequestParams {
        std::string date;
        std::string transport_types;
        std::string system = "yandex";
        std::string show_systems = "yandex";
       
        bool add_days_mask = false;
        std::string result_timezone;
        bool transfers = false;
    };

    struct ScheduleRequestParams : BaseRequestParams {
        std::string date;
        std::string transport_types;
        std::string direction;
        std::string event = "departure";
        std::string system = "yandex";
        std::string show_systems = "yandex";
        std::string result_timezone;
    };

    struct ThreadRequestParams : BaseRequestParams {
        std::string from;
        std::string to;
        std::string date;
        std::string show_systems = "yandex";
    };
    
    struct NearestStationsRequestParams
     : BaseRequestParams, PaginatedRequestParams {
        std::string station_types;
        std::string transport_types;
    };

    struct NearestSettlementRequestParams : BaseRequestParams {
        double distance;
    };

    struct CarrierRequestParams : BaseRequestParams {
        std::string system = "yandex";
    };
};