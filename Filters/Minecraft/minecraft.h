#pragma once

#include "../Filter/filter.h"

class Minecraft : public Filter {
public:
    Minecraft(int32_t pixel_count);
    void ApplyFilter(Image* image) override;

private:
    int32_t pixel_count_;
};
