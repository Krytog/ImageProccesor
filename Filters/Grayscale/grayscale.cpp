#include "grayscale.h"

void Grayscale::ApplyFilter(Image* image) {
    uint8_t r_copy = 0;
    uint8_t g_copy = 0;
    uint8_t b_copy = 0;
    uint8_t result = 0;
    const double r_coef = 0.299;
    const double g_coef = 0.587;
    const double b_coef = 0.114;
    for (int32_t row = 0; row < image->GetHeight(); ++row) {
        for (int32_t column = 0; column < image->GetWidth(); ++column) {
            r_copy = image->At(row, column).r;
            g_copy = image->At(row, column).g;
            b_copy = image->At(row, column).b;
            result = r_coef * r_copy + g_coef * g_copy + b_coef * b_copy;
            image->Canvas()[row][column].r = result;
            image->Canvas()[row][column].g = result;
            image->Canvas()[row][column].b = result;
        }
    }
}