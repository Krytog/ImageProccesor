#include "negative.h"

void Negative::ApplyFilter(Image* image) {
    for (int32_t row = 0; row < image->GetHeight(); ++row) {
        for (int32_t column = 0; column < image->GetWidth(); ++column) {
            image->Canvas()[row][column].r = 255 - image->At(row, column).r;
            image->Canvas()[row][column].g = 255 - image->At(row, column).g;
            image->Canvas()[row][column].b = 255 - image->At(row, column).b;
        }
    }
}
