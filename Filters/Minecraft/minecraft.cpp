#include "minecraft.h"

namespace {
struct Triplet {
    int32_t sum_r = 0;
    int32_t sum_g = 0;
    int32_t sum_b = 0;
};
}  // namespace

Minecraft::Minecraft(int32_t pixel_count) {
    pixel_count_ = pixel_count;
}

void Minecraft::ApplyFilter(Image *image) {
    std::vector<std::vector<Triplet>> sums;
    for (int32_t row = 0; row < image->GetHeight(); ++row) {
        int32_t sum_r = 0;
        int32_t sum_g = 0;
        int32_t sum_b = 0;
        int32_t count = 0;
        std::vector<Triplet> line;
        for (int32_t column = 0; column < image->GetWidth(); ++column) {
            sum_r += image->At(row, column).r;
            sum_g += image->At(row, column).g;
            sum_b += image->At(row, column).b;
            ++count;
            if (column == image->GetWidth() - 1 && count != pixel_count_) {
                --column;
            }
            if (count == pixel_count_) {
                line.push_back(Triplet{sum_r, sum_g, sum_b});
                sum_r = 0;
                sum_g = 0;
                sum_b = 0;
                count = 0;
            }
        }
        sums.push_back(line);
    }
    std::vector<std::vector<Pixel>> new_pixels(image->GetHeight() / pixel_count_ + 1,
                                               std::vector<Pixel>(image->GetWidth() / pixel_count_ + 1));
    int32_t pixels_square = pixel_count_ * pixel_count_;
    for (int32_t column = 0; column < image->GetWidth() / pixel_count_ + 1; ++column) {
        int32_t sum_r = 0;
        int32_t sum_g = 0;
        int32_t sum_b = 0;
        int32_t count = 0;
        for (int32_t row = 0; row < image->GetHeight(); ++row) {
            sum_r += sums[row][column].sum_r;
            sum_g += sums[row][column].sum_g;
            sum_b += sums[row][column].sum_b;
            ++count;
            if (row == image->GetHeight() - 1 && count != pixel_count_) {
                --row;
            }
            if (count == pixel_count_) {
                uint8_t r = sum_r / pixels_square;
                uint8_t g = sum_g / pixels_square;
                uint8_t b = sum_b / pixels_square;
                new_pixels[row / pixel_count_][column] = Pixel{r, g, b};
                sum_r = 0;
                sum_g = 0;
                sum_b = 0;
                count = 0;
            }
        }
    }
    for (int32_t row = 0; row < image->GetHeight(); ++row) {
        for (int32_t column = 0; column < image->GetWidth(); ++column) {
            image->Canvas()[row][column] = new_pixels[row / pixel_count_][column / pixel_count_];
        }
    }
}
