#pragma once

#include <cstdint>
#include <vector>

#pragma pack(push, 1)

struct Pixel {
    uint8_t r{};
    uint8_t g{};
    uint8_t b{};
};

#pragma pack(pop)

class Image {
public:
    int64_t GetHeight() const;
    void SetHeight(size_t height);

    int64_t GetWidth() const;
    void SetWidth(size_t width);

    std::vector<std::vector<Pixel>>& Canvas();
    Pixel At(int64_t height, int64_t width) const;

private:
    int64_t height_;
    int64_t width_;
    std::vector<std::vector<Pixel>> canvas_;
};
