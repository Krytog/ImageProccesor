#pragma once

#include "../Filter/filter.h"

class EdgeDetection : public Filter {
public:
    EdgeDetection(const double threshold);
    void ApplyFilter(Image* image) override;

private:
    double threshold_;
};
