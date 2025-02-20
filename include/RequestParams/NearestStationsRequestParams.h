#pragma once
#include "PaginatedRequestParams.h"
#include "GenericRequestParams.h"

namespace YandexSchedule {

struct NearestStationsRequestParams
: BaseRequestParams, PaginatedRequestParams, TransportTypesParam {
    std::string station_types;
};

class NearestStationsRequestParamsBuilder
    : public PaginatedRequestParamsBuilder<NearestStationsRequestParamsBuilder, NearestStationsRequestParams>,
    public TransportTypesParamBuilder<NearestStationsRequestParamsBuilder> {
public:
    NearestStationsRequestParamsBuilder& setStationTypes(
        const std::string& station_types
    ) {
        params_.station_types = station_types;
        return *this;
    }
};

}