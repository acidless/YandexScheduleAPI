#pragma once
#include <string>

namespace YandexSchedule {

struct DateParam {
    std::string date;
};

template <typename Derived>
class DateParamBuilder {
public:
    Derived& setDate(const std::string& date) {
        static_cast<Derived&>(*this).params_.date = date;
        return static_cast<Derived&>(*this);
    }
};


struct TransportTypesParam {
    std::string transport_types;
};

template <typename Derived>
class TransportTypesParamBuilder {
public:
    Derived& setTransportTypes(const std::string& types) {
        static_cast<Derived&>(*this).params_.transport_types = types;
        return static_cast<Derived&>(*this);
    }
};

struct SystemParam {
    std::string system = "yandex";
};

template <typename Derived>
class SystemParamBuilder {
public:
    Derived& setSystem(const std::string& system) {
        static_cast<Derived&>(*this).params_.system = system;
        return static_cast<Derived&>(*this);
    }
};

struct ShowSystemsParam {
    std::string show_systems = "yandex";
};

template <typename Derived>
class ShowSystemsParamBuilder {
public:
    Derived& setShowSystems(const std::string& show_systems) {
        static_cast<Derived&>(*this).params_.show_systems = show_systems;
        return static_cast<Derived&>(*this);
    }
};

struct ResultTimezoneParam {
    std::string result_timezone;
};

template <typename Derived>
class ResultTimezoneParamBuilder {
public:
    Derived& setResultTimezone(const std::string& result_timezone) {
        static_cast<Derived&>(*this).params_.result_timezone = result_timezone;
        return static_cast<Derived&>(*this);
    }
};

}