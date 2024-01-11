#include "../../../contrib/catch/catch.hpp"

#include "../FilterHandler/filter_handler.h"

TEST_CASE("Unknown filter") {
    FilterHandler filter_handler;
    FilterData filt{"DOESNOTEXIST", {}};
    REQUIRE(filter_handler.CreateFilter(filt) == nullptr);
}

TEST_CASE("Invalid args") {
    FilterHandler filter_handler;
    FilterData filt{"sharp", {"123"}};
    bool works = false;
    try {
        auto it = filter_handler.CreateFilter(filt);
    } catch (std::exception& exc) {
        works = true;
    }
    REQUIRE(works == true);
}

TEST_CASE("Valid filter with no args") {
    FilterHandler filter_handler;
    FilterData filt{"sharp", {}};
    bool works = true;
    try {
        auto it = filter_handler.CreateFilter(filt);
    } catch (std::exception& exc) {
        works = true;
    }
    REQUIRE(works == true);
}

TEST_CASE("Valid filter with args") {
    FilterHandler filter_handler;
    FilterData filt{"edge", {"0.039"}};
    bool works = true;
    try {
        auto it = filter_handler.CreateFilter(filt);
    } catch (std::exception& exc) {
        works = true;
    }
    REQUIRE(works == true);
}

TEST_CASE("Valid filter with invalid args") {
    FilterHandler filter_handler;
    FilterData filt{"edge", {"rzhaka"}};
    bool works = false;
    try {
        auto it = filter_handler.CreateFilter(filt);
    } catch (std::exception& exc) {
        works = true;
    }
    REQUIRE(works == true);
}

TEST_CASE("Valid filter with invalid args #2 (too many)") {
    FilterHandler filter_handler;
    FilterData filt{"edge", {"0.039", "11", "198"}};
    bool works = false;
    try {
        auto it = filter_handler.CreateFilter(filt);
    } catch (std::exception& exc) {
        works = true;
    }
    REQUIRE(works == true);
}

TEST_CASE("Valid filter with invalid args #3 (not enough)") {
    FilterHandler filter_handler;
    FilterData filt{"zhmih", {"0.039", "11"}};
    bool works = false;
    try {
        auto it = filter_handler.CreateFilter(filt);
    } catch (std::exception& exc) {
        works = true;
    }
    REQUIRE(works == true);
}

TEST_CASE("Invalid filter with args") {
    FilterHandler filter_handler;
    FilterData filt{"DOESNOTEXIST", {"0.039", "11", "198"}};
    auto it = filter_handler.CreateFilter(filt);
    REQUIRE(it == nullptr);
}
