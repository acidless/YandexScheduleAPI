#pragma once
#include "RequestParams.h"
#include "GenericRequestParams.h"

namespace YandexSchedule {

struct NearestSettlementRequestParams : BaseRequestParams {
    double distance;
};

class NearestSettlementRequestParamsBuilder
    : public RequestParamsBuilder<NearestSettlementRequestParamsBuilder, NearestSettlementRequestParams> {
public:
    NearestSettlementRequestParamsBuilder& setDistance(double distance) {
        params_.distance = distance;
        return *this;
    }
};

}