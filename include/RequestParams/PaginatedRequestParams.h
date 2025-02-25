#pragma once
#include "RequestParams.h"

namespace YandexSchedule {

struct PaginatedRequestParams {
    uint16_t offset = 0;
    uint16_t limit = 100;
};

template <typename Derived, typename Params>
class PaginatedRequestParamsBuilder : public RequestParamsBuilder<Derived, Params> {
public:
    Derived& setOffset(uint16_t offset) {
        this->params_.offset = offset;
        return static_cast<Derived&>(*this);
    }

    Derived& setLimit(uint16_t limit) {
        this->params_.limit = limit;
        return static_cast<Derived&>(*this);
    }
};

}