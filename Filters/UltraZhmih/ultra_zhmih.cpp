#include "ultra_zhmih.h"

#include <random>
#include "../Zhmih/zhmih.h"

UltraZhmih::UltraZhmih(const int32_t count, const double scale) {
    count_ = count;
    scale_ = scale;
}

void UltraZhmih::ApplyFilter(Image *image) {
    std::random_device rd;
    std::mt19937 rnd(rd());
    for (int32_t index = 0; index < count_; ++index) {
        int32_t center_x = rnd() % image->GetWidth();
        int32_t center_y = rnd() % image->GetHeight();
        int32_t radius = rnd() % std::min(image->GetHeight(), image->GetWidth()) / 4;
        double scale = static_cast<double>(rnd()) / (1LL << 31);
        Zhmih zhmih(center_x, center_y, radius, scale * scale_);
        zhmih.ApplyFilter(image);
    }
}