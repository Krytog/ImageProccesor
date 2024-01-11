#include "bmp_handler.h"

#include <fstream>

void BmpHandler::Read(const std::string &input, Image *image) {
    std::ifstream in_file(input, std::ios_base::in | std::ios_base::binary);

    if (in_file) {
        in_file.read(reinterpret_cast<char *>(&bmp_header_), BmpHandler::HEADER_SIZE);
        if (bmp_header_.id != 0x4D42) {
            throw std::runtime_error("Incorrect format of bmp");
        }

        in_file.read(reinterpret_cast<char *>(&dib_header_), BmpHandler::DIB_HEADER_SIZE);
        if (dib_header_.bits_per_pixel != 24) {
            throw std::runtime_error("Wrong number of bits in bmp");
        }
        if (bmp_header_.offset - dib_header_.size != 14) {
            throw std::runtime_error("Corrupted header");
        }
        if (dib_header_.size != 40) {
            throw std::runtime_error("Corrupted dib header");
        }
        if (dib_header_.bi_rgb != 0) {
            throw std::runtime_error("Bmp has compression");
        }

        image->SetHeight(dib_header_.height);
        image->SetWidth(dib_header_.width);

        uint8_t coefficient = dib_header_.bits_per_pixel / 8;

        image->Canvas().resize(dib_header_.height);
        for (int32_t index = 0; index < dib_header_.height; ++index) {
            image->Canvas()[index].resize(dib_header_.width);
        }

        if (dib_header_.width % 4 == 0) {
            for (int32_t index = 0; index < dib_header_.height; ++index) {
                in_file.read(reinterpret_cast<char *>(image->Canvas()[index].data()), dib_header_.width * coefficient);
            }
        } else {
            uint64_t row_size = dib_header_.width * coefficient;
            uint64_t new_row_size = dib_header_.width * coefficient + 4 - (row_size) % 4;

            std::vector<uint8_t> additional_row(new_row_size - row_size);

            for (size_t index = 0; index < dib_header_.height; ++index) {
                in_file.read(reinterpret_cast<char *>(image->Canvas()[index].data()), row_size);
                in_file.read(reinterpret_cast<char *>(additional_row.data()), additional_row.size());
            }
        }
    } else {
        throw std::runtime_error("Cannot open this file");
    }
}

void BmpHandler::Write(const std::string &output, Image *image) {
    std::ofstream out_file(output, std::ios_base::out | std::ios_base::binary);

    if (out_file) {
        uint8_t coefficient = dib_header_.bits_per_pixel / 8;

        dib_header_.width = image->GetWidth();
        dib_header_.height = image->GetHeight();
        dib_header_.data_size = coefficient * dib_header_.width * dib_header_.height;
        dib_header_.data_size += bmp_header_.offset;

        out_file.write(reinterpret_cast<char *>(&bmp_header_), BmpHandler::HEADER_SIZE);
        out_file.write(reinterpret_cast<char *>(&dib_header_), BmpHandler::DIB_HEADER_SIZE);

        if (dib_header_.width % 4 == 0) {
            for (int32_t index = 0; index < dib_header_.height; ++index) {
                out_file.write(reinterpret_cast<char *>(image->Canvas()[index].data()),
                               dib_header_.width * coefficient);
            }
        } else {
            uint64_t row_size = dib_header_.width * coefficient;
            uint64_t new_row_size = row_size + 4 - row_size % 4;

            std::vector<uint8_t> additional_row(new_row_size - row_size);

            for (int32_t index = 0; index < dib_header_.height; ++index) {
                out_file.write(reinterpret_cast<char *>(image->Canvas()[index].data()), row_size);
                out_file.write(reinterpret_cast<char *>(&additional_row), new_row_size - row_size);
            }
        }
    } else {
        throw std::runtime_error("Cannot write in this file");
    }
}
