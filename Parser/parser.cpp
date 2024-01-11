#include "parser.h"

#include <cctype>
#include <stdexcept>

namespace {
bool IsNumber(const std::string& str) {
    if (str[0] != '-' && !isdigit(str[0])) {
        return false;
    }
    for (size_t i = 1; i < str.size(); ++i) {
        if (!isdigit(str[i])) {
            if (i != 2 && str[i] != '.') {
                return false;
            }
        }
    }
    return true;
}
}  // namespace

Parser::Parser(const int args, char* argv[]) {
    if (args == 2) {
        throw std::runtime_error("Not enough arguments");
    }
    input_name_ = argv[1];
    output_name_ = argv[2];
    if (args > 3 && argv[3][0] != '-') {
        throw std::runtime_error("Invalid arguments");
    }
    if (args > 3) {
        std::vector<FilterData> filter_data;
        std::vector<std::string> filter_args;
        std::string current_filter_name = argv[3];
        current_filter_name.erase(0, 1);
        for (int index = 4; index < args; ++index) {
            if (argv[index][0] == '-') {
                if (!IsNumber(argv[index])) {
                    filter_data.push_back(FilterData{current_filter_name, filter_args});
                    filter_args.clear();
                    current_filter_name = argv[index];
                    current_filter_name.erase(0, 1);
                } else {
                    filter_args.push_back(argv[index]);
                }
            } else {
                filter_args.push_back(argv[index]);
            }
        }
        filter_data.push_back(FilterData{current_filter_name, filter_args});
        filters_data_ = filter_data;
    }
}

std::string Parser::GetInputName() {
    return input_name_;
}

std::string Parser::GetOutputName() {
    return output_name_;
}

int64_t Parser::FiltersDataSize() const {
    return filters_data_.size();
}

const std::vector<FilterData>& Parser::GetData() const {
    return filters_data_;
}

const std::string Parser::HELP =
    "Image processor for 24bit BMP without compression. Available filters: crop (-crop width height),\n"
    "grayscale (-gs), negative (-neg), sharpening (-sharp), edge detection (-edge threshold), gaussian blur (-blur "
    "sigma),\n"
    "zhmih (-zhmih x y radius scale), ultra zhmih (-ultzhmih count scale), minecraft (-minecraft pixels)";
