#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
        std::string popular_title;
        std::string short_title;
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
        std::string icao;
        std::string sirena;
        std::string iata;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(CarrierCode, icao, sirena, iata)

    struct Carrier {
        int64_t code;
        std::string contracts;
        std::string url;
        std::string logo_svg;
        std::string title;
        std::string phone;
        CarrierCode codes;
        std::string address;
        std::string logo;
        std::string email;  
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Carrier,
        code, contracts, url, logo_svg, title, phone,
        codes, address, logo, email
    )

    struct TransportSubtype {
        std::string color;
        std::string code;
        std::string title;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(TransportSubtype, color, code, title)

    struct Thread {
        std::string uid;
        std::string title;
        Interval interval;
        std::string number;
        std::string short_title;
        std::string thread_method_link;
        Carrier carrier;
        std::string transport_type;
        std::string vehicle;
        TransportSubtype transport_subtype;
        std::string express_type;
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
        std::string departure_terminal;
        Station to;
        bool has_transfers;
        Tickets tickets_info;
        uint32_t duration;
        std::string arrival_terminal;
        std::string start_date;
        std::string arrival_platform;
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
        std::string short_title;
        std::string title;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SearchPlace,
        code, type, popular_title, short_title, title
    )

    struct Search {
        std::string date;
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
        std::string except_days;
        std::string arrival;
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
        std::string date;
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
        std::string arrival;
        std::string departure;
        uint32_t duration;
        uint32_t stop_time;
        Station station;
        std::string terminal;
        std::string platform;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Stop,
        arrival, departure, duration, stop_time, station,
        terminal, platform
    )
    
    struct ThreadResponse {
        std::string except_days;
        std::string arrival_date;
        std::string from;
        std::string uid;
        std::string title;
        Interval interval;
        std::string departure_date;
        std::string start_time;
        std::string number;
        std::string short_title;
        std::string days;
        std::string to;
        Carrier carrier;
        std::string transport_type;
        std::vector<Stop> stops;
        std::string vehicle;
        std::string start_date;
        TransportSubtype transport_subtype;
        std::string express_type;
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

    struct NearestStation : public Station {
        double distance;
        TypeChoice type_choices;
        std::string majority;
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

    struct CarriersResponse {
        std::vector<Carrier> carriers;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(CarriersResponse,
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


};