#pragma once

#include <vector>
#include "../../Image/image.h"

class Filter {
public:
    void ApplyMatrix(Image* image, const std::vector<int32_t>& matrix);
    virtual void ApplyFilter(Image* image) = 0;
};
