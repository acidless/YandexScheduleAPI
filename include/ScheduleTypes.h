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
        int duration;
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
};