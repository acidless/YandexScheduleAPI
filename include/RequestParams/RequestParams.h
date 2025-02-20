#pragma once
#include <string>
#include "GenericRequestParams.h"

namespace YandexSchedule {

struct BaseRequestParams {
    std::string format = "json";
    std::string lang = "ru_RU";
};

template <typename Derived, typename Params>
class RequestParamsBuilder {
    static_assert(std::is_base_of_v<BaseRequestParams, Params>, 
                  "Params must inherit from BaseRequestParams");
public:
    Derived& setFormat(const std::string& format) {
        params_.format = format;
        return static_cast<Derived&>(*this);
    }

    Derived& setLang(const std::string& lang) {
        params_.lang = lang;
        return static_cast<Derived&>(*this);
    }

    const Params& build() const {
        return params_;
    }

protected:
    Params params_{};

    template <typename D> 
    friend class DateParamBuilder;

    template <typename D> 
    friend class TransportParamBuilder;

    template <typename D> 
    friend class SystemParamBuilder;

    template <typename D> 
    friend class ShowSystemsParamBuilder;

    template <typename D> 
    friend class ResultTimezoneParamBuilder;
};

}