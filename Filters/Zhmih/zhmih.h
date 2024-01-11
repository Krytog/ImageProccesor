#pragma once

#include "../Filter/filter.h"

class Zhmih : public Filter {
public:
    Zhmih(const int32_t center_x, const int32_t center_y, const int32_t radius, const double scale);
    void ApplyFilter(Image* image) override;

private:
    int32_t center_x_;
    int32_t center_y_;
    int32_t radius_;
    double scale_;
};