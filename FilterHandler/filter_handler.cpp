#include "filter_handler.h"
#include "../Filters/Crop/crop.h"
#include "../Filters/Grayscale/grayscale.h"
#include "../Filters/Negative/negative.h"
#include "../Filters/Sharpening/sharpening.h"
#include "../Filters/EdgeDetection/edge_detection.h"
#include "../Filters/GaussianBlur/gaussian_blur.h"
#include "../Filters/Zhmih/zhmih.h"
#include "../Filters/UltraZhmih/ultra_zhmih.h"
#include "../Filters/Minecraft/minecraft.h"

#include <stdexcept>

std::shared_ptr<Filter> FilterHandler::CreateFilter(const FilterData& filter_data) {
    if (filter_data.filter_name == "crop") {
        int64_t width = 0;
        int64_t height = 0;
        if (filter_data.filter_args.size() == 2) {
            try {
                width = std::stoll(filter_data.filter_args[0]);
                height = std::stoll(filter_data.filter_args[1]);
            } catch (std::exception& exc) {
                throw std::runtime_error("Crop: invalid arguments");
            }
        } else {
            throw std::runtime_error("Crop: invalid arguments");
        }
        return std::make_shared<Crop>(width, height);
    } else if (filter_data.filter_name == "gs") {
        if (filter_data.filter_args.empty()) {
            return std::make_shared<Grayscale>();
        } else {
            throw std::runtime_error("Grayscale: invalid arguments");
        }
    } else if (filter_data.filter_name == "neg") {
        if (filter_data.filter_args.empty()) {
            return std::make_shared<Negative>();
        } else {
            throw std::runtime_error("Negative: invalid arguments");
        }
    } else if (filter_data.filter_name == "sharp") {
        if (filter_data.filter_args.empty()) {
            return std::make_shared<Sharpening>();
        } else {
            throw std::runtime_error("Sharpening: invalid arguments");
        }
    } else if (filter_data.filter_name == "edge") {
        if (filter_data.filter_args.size() == 1) {
            double threshold = 0;
            try {
                threshold = std::stod(filter_data.filter_args[0]);
            } catch (std::exception& exc) {
                throw std::runtime_error("Edge detection: invalid arguments");
            }
            return std::make_shared<EdgeDetection>(threshold);
        } else {
            throw std::runtime_error("Edge detection: invalid arguments");
        }
    } else if (filter_data.filter_name == "blur") {
        if (filter_data.filter_args.size() == 1) {
            double sigma = 0;
            try {
                sigma = std::stod(filter_data.filter_args[0]);
            } catch (std::exception& exc) {
                throw std::runtime_error("Gaussian blur: invalid arguments");
            }
            return std::make_shared<GaussianBlur>(sigma);
        } else {
            throw std::runtime_error("Gaussian blur: invalid arguments");
        }
    } else if (filter_data.filter_name == "zhmih") {
        if (filter_data.filter_args.size() == 4) {
            int32_t center_x = 0;
            int32_t center_y = 0;
            int32_t radius = 0;
            double scale = 0;
            try {
                center_x = std::stoll(filter_data.filter_args[0]);
                center_y = std::stoll(filter_data.filter_args[1]);
                radius = std::stoll(filter_data.filter_args[2]);
                scale = std::stod(filter_data.filter_args[3]);
            } catch (std::exception& exc) {
                throw std::runtime_error("Zhmih: invalid arguments");
            }
            return std::make_shared<Zhmih>(center_x, center_y, radius, scale);
        } else {
            throw std::runtime_error("Zhmih: invalid arguments");
        }
    } else if (filter_data.filter_name == "ultzhmih") {
        if (filter_data.filter_args.size() == 2) {
            int32_t count = 0;
            double scale = 0;
            try {
                count = std::stoll(filter_data.filter_args[0]);
                scale = std::stod(filter_data.filter_args[1]);
            } catch (std::exception& exc) {
                throw std::runtime_error("Ultra zhmih: invalid arguments");
            }
            return std::make_shared<UltraZhmih>(count, scale);
        } else {
            throw std::runtime_error("Ultra zhmih: invalid arguments");
        }
    } else if (filter_data.filter_name == "minecraft") {
        if (filter_data.filter_args.size() == 1) {
            int32_t count = 0;
            try {
                count = std::stoll(filter_data.filter_args[0]);
            } catch (std::exception& exc) {
                throw std::runtime_error("Minecraft: invalid arguments");
            }
            return std::make_shared<Minecraft>(count);
        } else {
            throw std::runtime_error("Minecraft: invalid arguments");
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<Filter>> FilterHandler::CreateFilters(const Parser& parsed) {
    std::vector<std::shared_ptr<Filter>> output;
    output.reserve(parsed.FiltersDataSize());
    for (const auto& filter_data : parsed.GetData()) {
        std::shared_ptr<Filter> filter = CreateFilter(filter_data);
        if (filter == nullptr) {
            throw std::runtime_error("Unknown filter: " + filter_data.filter_name);
        }
        output.push_back(filter);
    }
    return output;
}
