#include "sharpening.h"

void Sharpening::ApplyFilter(Image* image) {
    const std::vector<int32_t> matrix = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    ApplyMatrix(image, matrix);
}
