#include "filter.h"

#include <algorithm>

void Filter::ApplyMatrix(Image* image, const std::vector<int32_t>& matrix) {
    if (matrix.size() != 9) {
        return;
    }
    std::vector<std::vector<Pixel>> extended_canvas;
    std::vector<Pixel> bound_row;
    bound_row.push_back(image->At(0, 0));
    for (int32_t index = 0; index < image->GetWidth(); ++index) {
        bound_row.push_back(image->At(0, index));
    }
    bound_row.push_back(image->At(0, image->GetWidth() - 1));
    extended_canvas.push_back(bound_row);
    for (int32_t index = 0; index < image->GetHeight(); ++index) {
        std::vector<Pixel> row;
        row.push_back(image->At(index, 0));
        row.insert(row.end(), image->Canvas()[index].begin(), image->Canvas()[index].end());
        row.push_back(image->At(index, image->GetWidth() - 1));
        extended_canvas.push_back(row);
    }
    bound_row.clear();
    bound_row.push_back(image->At(image->GetHeight() - 1, 0));
    for (int32_t index = 0; index < image->GetWidth(); ++index) {
        bound_row.push_back(image->At(image->GetHeight() - 1, index));
    }
    bound_row.push_back(image->At(image->GetHeight() - 1, image->GetWidth() - 1));
    extended_canvas.push_back(bound_row);
    int16_t r = 0;
    int16_t g = 0;
    int16_t b = 0;
    for (int32_t row = 1; row < image->GetHeight() + 1; ++row) {
        for (int32_t column = 1; column < image->GetWidth() + 1; ++column) {
            r = extended_canvas[row - 1][column - 1].r * matrix[0];
            r += extended_canvas[row - 1][column].r * matrix[1];
            r += extended_canvas[row - 1][column + 1].r * matrix[2];
            r += extended_canvas[row][column - 1].r * matrix[3];
            r += extended_canvas[row][column].r * matrix[4];
            r += extended_canvas[row][column + 1].r * matrix[5];
            r += extended_canvas[row + 1][column - 1].r * matrix[6];
            r += extended_canvas[row + 1][column].r * matrix[7];
            r += extended_canvas[row + 1][column + 1].r * matrix[8];
            image->Canvas()[row - 1][column - 1].r =
                std::max(static_cast<int16_t>(0), std::min(static_cast<int16_t>(255), r));

            g = extended_canvas[row - 1][column - 1].g * matrix[0];
            g += extended_canvas[row - 1][column].g * matrix[1];
            g += extended_canvas[row - 1][column + 1].g * matrix[2];
            g += extended_canvas[row][column - 1].g * matrix[3];
            g += extended_canvas[row][column].g * matrix[4];
            g += extended_canvas[row][column + 1].g * matrix[5];
            g += extended_canvas[row + 1][column - 1].g * matrix[6];
            g += extended_canvas[row + 1][column].g * matrix[7];
            g += extended_canvas[row + 1][column + 1].g * matrix[8];
            image->Canvas()[row - 1][column - 1].g =
                std::max(static_cast<int16_t>(0), std::min(static_cast<int16_t>(255), g));

            b = extended_canvas[row - 1][column - 1].b * matrix[0];
            b += extended_canvas[row - 1][column].b * matrix[1];
            b += extended_canvas[row - 1][column + 1].b * matrix[2];
            b += extended_canvas[row][column - 1].b * matrix[3];
            b += extended_canvas[row][column].b * matrix[4];
            b += extended_canvas[row][column + 1].b * matrix[5];
            b += extended_canvas[row + 1][column - 1].b * matrix[6];
            b += extended_canvas[row + 1][column].b * matrix[7];
            b += extended_canvas[row + 1][column + 1].b * matrix[8];
            image->Canvas()[row - 1][column - 1].b =
                std::max(static_cast<int16_t>(0), std::min(static_cast<int16_t>(255), b));
        }
    }
}