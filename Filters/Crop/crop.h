#pragma once

#include <cstdint>
#include "../Filter/filter.h"

class Crop : public Filter {
public:
    Crop(int64_t width, int64_t height);
    void ApplyFilter(Image* image) override;

private:
    int64_t width_;
    int64_t height_;
};
