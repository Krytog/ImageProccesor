#pragma once

#include <unordered_map>
#include <vector>
#include <string>

struct FilterData {
    std::string filter_name;
    std::vector<std::string> filter_args;
};

class Parser {
public:
    Parser(const int args, char* argv[]);
    std::string GetInputName();
    std::string GetOutputName();
    int64_t FiltersDataSize() const;
    const std::vector<FilterData>& GetData() const;

    static const std::string HELP;

private:
    std::string input_name_;
    std::string output_name_;
    std::vector<FilterData> filters_data_ = {};
};
