#pragma once

#include "../Filter/filter.h"

class Sharpening : public Filter {
public:
    void ApplyFilter(Image* image) override;
};
