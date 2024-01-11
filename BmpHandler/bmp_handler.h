#pragma once

#include <string>

#include "../Image/image.h"

#pragma pack(push, 1)

struct BmpHeader {
    uint16_t id{0x4D42};
    uint32_t size{};
    uint16_t specific1{};
    uint16_t specific2{};
    uint32_t offset{};
};

struct DibHeader {
    uint32_t size{};
    int32_t width{};
    int32_t height{};
    uint16_t planes{};
    uint16_t bits_per_pixel{};
    uint32_t bi_rgb{};
    uint32_t data_size{};
    uint32_t pxl_mtr_hor{};
    uint32_t plx_mtr_ver{};
    uint32_t colors{};
    uint32_t colors_important{};
};

#pragma pack(pop)

class BmpHandler {
public:
    BmpHandler() : bmp_header_(), dib_header_(){};

    static const uint8_t HEADER_SIZE = 14;

    static const uint8_t DIB_HEADER_SIZE = 40;

    void Read(const std::string& input, Image* image);
    void Write(const std::string& output, Image* image);

private:
    BmpHeader bmp_header_;
    DibHeader dib_header_;
};
