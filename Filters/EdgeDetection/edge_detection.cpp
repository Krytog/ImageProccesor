#include "edge_detection.h"

#include "../Grayscale/grayscale.h"

EdgeDetection::EdgeDetection(const double threshold) {
    threshold_ = threshold;
}

void EdgeDetection::ApplyFilter(Image* image) {
    Grayscale grayscale;
    grayscale.ApplyFilter(image);
    std::vector<int32_t> matrix = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    ApplyMatrix(image, matrix);
    if (threshold_ < 0) {
        for (int32_t row = 0; row < image->GetHeight(); ++row) {
            for (int32_t column = 0; column < image->GetWidth(); ++column) {
                image->Canvas()[row][column] = Pixel{255, 255, 255};
            }
        }
    } else {
        for (int32_t row = 0; row < image->GetHeight(); ++row) {
            for (int32_t column = 0; column < image->GetWidth(); ++column) {
                if (image->At(row, column).r < threshold_ * 255) {
                    image->Canvas()[row][column] = Pixel{0, 0, 0};
                } else {
                    image->Canvas()[row][column] = Pixel{255, 255, 255};
                }
            }
        }
    }
}
