#include "image.h"

int64_t Image::GetHeight() const {
    return height_;
}

void Image::SetHeight(size_t height) {
    height_ = height;
}

int64_t Image::GetWidth() const {
    return width_;
}

void Image::SetWidth(size_t width) {
    width_ = width;
}

std::vector<std::vector<Pixel>>& Image::Canvas() {
    return canvas_;
}

Pixel Image::At(int64_t height, int64_t width) const {
    return canvas_[height][width];
}
