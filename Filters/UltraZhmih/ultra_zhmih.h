#pragma once

#include "../Filter/filter.h"

class UltraZhmih : public Filter {
public:
    UltraZhmih(const int32_t count, const double scale);
    void ApplyFilter(Image* image) override;

private:
    int32_t count_;
    double scale_;
};
