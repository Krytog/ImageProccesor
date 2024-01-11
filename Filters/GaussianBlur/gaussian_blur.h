#pragma once

#include "../Filter/filter.h"

class GaussianBlur : public Filter {
public:
    GaussianBlur(const double sigma);
    void ApplyFilter(Image* image) override;

private:
    double sigma_;
};
