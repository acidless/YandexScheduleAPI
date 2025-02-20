#pragma once
#include "PaginatedRequestParams.h"
#include "GenericRequestParams.h"

namespace YandexSchedule {

struct ThreadRequestParams
: BaseRequestParams, DateParam, ShowSystemsParam {
    std::string from;
    std::string to;
};

class ThreadRequestParamsBuilder
    : public RequestParamsBuilder<ThreadRequestParamsBuilder, ThreadRequestParams>,
    public DateParamBuilder<ThreadRequestParamsBuilder>,
    public SystemParamBuilder<ThreadRequestParamsBuilder> {
public:
    ThreadRequestParamsBuilder& setFrom(const std::string& from) {
        params_.from = from;
        return *this;
    }

    ThreadRequestParamsBuilder& setTo(const std::string& to) {
        params_.to = to;
        return *this;
    }
};

}