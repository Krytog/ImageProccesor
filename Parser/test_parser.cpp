#include "../../../contrib/catch/catch.hpp"

#include "../Parser/parser.h"

TEST_CASE("Too low args") {
    const int args = 2;
    char* argv[] = {(char*)"aboba", (char*)"abiba"};
    bool works = false;
    try {
        Parser parsed(args, argv);
    } catch (std::exception& exc) {
        works = true;
    }
    REQUIRE(works == true);
}

TEST_CASE("Input/output") {
    const int args = 5;
    char* argv[] = {(char*)"./image_processor", (char*)"../examples/example.bmp", (char*)"../examples/output.bmp", (char*)"-edge", (char*)"0.039", };
    Parser parsed(args, argv);
    REQUIRE(parsed.GetInputName() == "../examples/example.bmp");
    REQUIRE(parsed.GetOutputName() == "../examples/output.bmp");
}

TEST_CASE("One filter") {
    const int args = 5;
    char* argv[] = {(char*)"./image_processor", (char*)"../examples/example.bmp", (char*)"../examples/output.bmp", (char*)"-edge", (char*)"0.039", };
    Parser parsed(args, argv);
    std::vector<FilterData> expected = {FilterData{"edge", {"0.039"}}};
    REQUIRE(parsed.GetData()[0].filter_name == expected[0].filter_name);
    REQUIRE(parsed.GetData()[0].filter_args[0] == expected[0].filter_args[0]);
}

TEST_CASE("Multiple filters") {
    const int args = 7;
    char* argv[] = {(char*)"./image_processor", (char*)"../examples/example.bmp", (char*)"../examples/output.bmp", (char*)"-edge", (char*)"0.039", (char*)"-sharp", (char*)"-neg"};
    Parser parsed(args, argv);
    std::vector<FilterData> expected = {FilterData{"edge", {"0.039"}}, FilterData{"sharp",{}}, FilterData{"neg", {}}};
    for (size_t i = 0; i < expected.size(); ++i) {
        REQUIRE(parsed.GetData()[i].filter_name == expected[i].filter_name);
        for (size_t j = 0; j < expected[i].filter_args.size(); ++j) {
            REQUIRE(parsed.GetData()[i].filter_args[j] == expected[i].filter_args[j]);
        }
    }
}

TEST_CASE("Negative arg") {
    const int args = 5;
    char* argv[] = {(char*)"./image_processor", (char*)"../examples/example.bmp", (char*)"../examples/output.bmp", (char*)"-edge", (char*)"-0.14", };
    Parser parsed(args, argv);
    std::vector<FilterData> expected = {FilterData{"edge", {"0.039"}}};
    REQUIRE(parsed.GetData().size() == 1);
}
