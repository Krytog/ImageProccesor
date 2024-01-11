#include "crop.h"

void Crop::ApplyFilter(Image* image) {
    if (height_ < image->GetHeight()) {
        image->SetHeight(height_);
        std::reverse(image->Canvas().begin(), image->Canvas().end());
        image->Canvas().resize(image->GetHeight());
        if (width_ < image->GetWidth()) {
            image->SetWidth(width_);
            for (int64_t index = 0; index < height_; ++index) {
                image->Canvas()[index].resize(image->GetWidth());
            }
        }
        std::reverse(image->Canvas().begin(), image->Canvas().end());
    } else {
        if (width_ < image->GetWidth()) {
            image->SetWidth(width_);
            for (int64_t index = 0; index < height_; ++index) {
                image->Canvas()[index].resize(image->GetWidth());
            }
        }
    }
}

Crop::Crop(int64_t width, int64_t height) {
    width_ = width;
    height_ = height;
}