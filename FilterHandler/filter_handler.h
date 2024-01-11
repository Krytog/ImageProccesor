#pragma once

#include <memory>
#include <vector>
#include <string>
#include "../Image/image.h"
#include "../Filters/Filter/filter.h"
#include "../Parser/parser.h"

class FilterHandler {
public:
    std::shared_ptr<Filter> CreateFilter(const FilterData& filter_data);
    std::vector<std::shared_ptr<Filter>> CreateFilters(const Parser& parsed);
};
