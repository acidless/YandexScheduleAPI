#pragma once
#include "RequestParams.h"
#include "GenericRequestParams.h"

namespace YandexSchedule {
    
struct ScheduleRequestParams
    : BaseRequestParams, DateParam, TransportTypesParam,
    SystemParam, ShowSystemsParam, ResultTimezoneParam {
    std::string direction;
    std::string event = "departure";
};

class ScheduleRequestParamsBuilder
    : public RequestParamsBuilder<ScheduleRequestParamsBuilder, ScheduleRequestParams>,
    public DateParamBuilder<ScheduleRequestParamsBuilder>,
    public TransportTypesParamBuilder<ScheduleRequestParamsBuilder>,
    public SystemParamBuilder<ScheduleRequestParamsBuilder>,
    public ShowSystemsParamBuilder<ScheduleRequestParamsBuilder>,
    public ResultTimezoneParamBuilder<ScheduleRequestParamsBuilder> {
public:
    ScheduleRequestParamsBuilder& setDirection(const std::string& direction) {
        params_.direction = direction;
        return *this;
    }

    ScheduleRequestParamsBuilder& setEvent(const std::string& event) {
        params_.event = event;
        return *this;
    }
};

}