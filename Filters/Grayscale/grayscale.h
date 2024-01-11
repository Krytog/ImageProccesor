#pragma once

#include "../Filter/filter.h"

class Grayscale : public Filter {
public:
    void ApplyFilter(Image* image) override;
};
