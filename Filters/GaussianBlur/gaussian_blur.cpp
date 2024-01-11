#include "gaussian_blur.h"

#include <cmath>

GaussianBlur::GaussianBlur(const double sigma) {
    sigma_ = sigma;
}

void GaussianBlur::ApplyFilter(Image *image) {
    if (sigma_ < 1e-6) {
        return;
    }
    std::vector<std::vector<Pixel>> new_canvas = image->Canvas();
    std::vector<double> linear_matrix;
    double matrix_sum = 0;
    for (int32_t index = 0; index < 6 * sigma_ + 1; ++index) {
        double pow = std::pow((index - 3 * sigma_), 2) / (2 * std::pow(sigma_, 2));
        double coef = std::exp(-pow);
        matrix_sum += coef;
        linear_matrix.push_back(coef);
    }
    for (int32_t row = 0; row < image->GetHeight(); ++row) {
        for (int32_t column = 0; column < image->GetWidth(); ++column) {
            int64_t r = 0;
            int64_t g = 0;
            int64_t b = 0;
            for (int32_t row_blur = row - 3 * sigma_; row_blur < row + 3 * sigma_; ++row_blur) {
                if (row_blur >= 0 && row_blur < image->GetHeight()) {
                    r += image->At(row_blur, column).r * linear_matrix[row_blur - row + 3 * sigma_];
                    g += image->At(row_blur, column).g * linear_matrix[row_blur - row + 3 * sigma_];
                    b += image->At(row_blur, column).b * linear_matrix[row_blur - row + 3 * sigma_];
                }
            }
            r /= matrix_sum;
            g /= matrix_sum;
            b /= matrix_sum;
            new_canvas[row][column].r = std::max(static_cast<int64_t>(0), std::min(static_cast<int64_t>(255), r));
            new_canvas[row][column].g = std::max(static_cast<int64_t>(0), std::min(static_cast<int64_t>(255), g));
            new_canvas[row][column].b = std::max(static_cast<int64_t>(0), std::min(static_cast<int64_t>(255), b));
        }
    }
    image->Canvas() = new_canvas;
    for (int32_t row = 0; row < image->GetHeight(); ++row) {
        for (int32_t column = 0; column < image->GetWidth(); ++column) {
            int64_t r = 0;
            int64_t g = 0;
            int64_t b = 0;
            for (int32_t column_blur = column - 3 * sigma_; column_blur < column + 3 * sigma_; ++column_blur) {
                if (column_blur >= 0 && column_blur < image->GetWidth()) {
                    r += image->At(row, column_blur).r * linear_matrix[column_blur - column + 3 * sigma_];
                    g += image->At(row, column_blur).g * linear_matrix[column_blur - column + 3 * sigma_];
                    b += image->At(row, column_blur).b * linear_matrix[column_blur - column + 3 * sigma_];
                }
            }
            r /= matrix_sum;
            g /= matrix_sum;
            b /= matrix_sum;
            new_canvas[row][column].r = std::max(static_cast<int64_t>(0), std::min(static_cast<int64_t>(255), r));
            new_canvas[row][column].g = std::max(static_cast<int64_t>(0), std::min(static_cast<int64_t>(255), g));
            new_canvas[row][column].b = std::max(static_cast<int64_t>(0), std::min(static_cast<int64_t>(255), b));
        }
    }
    image->Canvas() = new_canvas;
}
