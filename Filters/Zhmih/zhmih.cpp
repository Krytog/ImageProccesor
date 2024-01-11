#include "zhmih.h"

#include <cmath>

namespace {
double Distance(const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2) {
    return std::sqrt(std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2));
}
}  // namespace

Zhmih::Zhmih(const int32_t center_x, const int32_t center_y, const int32_t radius, const double scale) {
    center_x_ = center_x;
    center_y_ = center_y;
    radius_ = radius;
    scale_ = scale;
}

void Zhmih::ApplyFilter(Image *image) {
    std::vector<std::vector<Pixel>> new_canvas = image->Canvas();
    for (int32_t row = 0; row < image->GetHeight(); ++row) {
        for (int32_t column = 0; column < image->GetWidth(); ++column) {
            double dist = Distance(row, column, center_y_, center_x_);
            if (dist < radius_) {
                int32_t new_row = row - center_y_;
                int32_t new_column = column - center_x_;
                double coef = 1.0 - ((radius_ - dist) / radius_) * scale_;
                coef *= coef;
                new_row *= coef;
                new_column *= coef;
                new_row += center_y_;
                new_column += center_x_;
                if (0 <= new_row && new_row < image->GetHeight() && 0 <= new_column && new_column < image->GetWidth()) {
                    image->Canvas()[row][column] = new_canvas[new_row][new_column];
                }
            }
        }
    }
}
