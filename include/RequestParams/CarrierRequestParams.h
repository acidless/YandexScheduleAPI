#pragma once
#include "RequestParams.h"
#include "GenericRequestParams.h"

namespace YandexSchedule {

struct CarrierRequestParams
    : BaseRequestParams, SystemParam {};

class CarrierRequestParamsBuilder
    : public RequestParamsBuilder<CarrierRequestParamsBuilder, CarrierRequestParams>,
    public SystemParamBuilder<CarrierRequestParamsBuilder> {};

}