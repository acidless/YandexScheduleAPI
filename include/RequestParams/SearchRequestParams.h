#pragma once
#include "PaginatedRequestParams.h"
#include "GenericRequestParams.h"

namespace YandexSchedule {

struct SearchRequestParams
    : BaseRequestParams, PaginatedRequestParams, DateParam, 
    TransportTypesParam, SystemParam, ShowSystemsParam,
    ResultTimezoneParam {
    bool add_days_mask = false;
    bool transfers = false;
};

class SearchRequestParamsBuilder
    : public PaginatedRequestParamsBuilder<SearchRequestParamsBuilder, SearchRequestParams>,
    public DateParamBuilder<SearchRequestParamsBuilder>,
    public TransportTypesParamBuilder<SearchRequestParamsBuilder>,
    public SystemParamBuilder<SearchRequestParamsBuilder>,
    public ShowSystemsParamBuilder<SearchRequestParamsBuilder>,
    public ResultTimezoneParamBuilder<SearchRequestParamsBuilder> {
public:
    SearchRequestParamsBuilder& setAddDaysMask(bool value) {
        params_.add_days_mask = value;
        return *this;
    }

    SearchRequestParamsBuilder& setShowTransfers(bool show_transfers) {
        params_.transfers = show_transfers;
        return *this;
    }
};

}