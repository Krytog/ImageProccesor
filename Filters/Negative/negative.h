#pragma once

#include "../Filter/filter.h"

class Negative : public Filter {
public:
    void ApplyFilter(Image* image) override;
};
