//
// Created by Chris Schick on 2018-06-06.
//

#include "../lib/catch.hpp"
#include "../../src/Random_utils.h"

class Less_than {
public:
    explicit Less_than(int c) : cmp{c} { }

    bool operator()(int val) { return val < cmp; }

private:
    int cmp;
};

class More_than {
public:
    explicit More_than(int c) : cmp{c} { }

    bool operator()(int val) { return val > cmp; }

private:
    int cmp;
};

SCENARIO("Random_int produces values in a range", "[Random_int]") {

    GIVEN("A Random_utils object") {
        auto ri = Random_int{};

        WHEN("1-10 is passed") {
            const auto min = 1;
            const auto max = 10;

            auto val = ri(min, max);

            THEN("A value in the range is returned") {
                REQUIRE(val >= min);
                REQUIRE(val <= max);
            }
        }

        WHEN("Many values are produced in a range") {
            auto vi = std::vector<int>(10000);

            const auto min = 1234;
            const auto max = 5678;

            for (auto& val : vi)
                val = ri(min, max);

            THEN("All of the values are within the range") {
                REQUIRE(std::find_if(std::begin(vi), std::end(vi),
                                     Less_than(min)) == vi.end());
                REQUIRE(std::find_if(std::begin(vi), std::end(vi),
                                     More_than(max)) == vi.end());
            }
        }
    }
}

SCENARIO("Assignment table allows random selection", "[Assignment_table]") {

    GIVEN("A default assignment table") {
        const auto initial_size = size_t{10};
        const auto initial_value = int{0};
        auto ass_tab = Assignment_table<int>{initial_size, initial_value};

        const auto& view = ass_tab.view_table();

        REQUIRE(view.size() == initial_size);

        WHEN("A value is requested") {
            auto val1 = ass_tab.get_value();

            THEN("That value is in the expected range") {
                REQUIRE(val1 < initial_size);   // expected max based on size
                REQUIRE(val1 >= 0);             // expected min based on default
            }

            THEN("The table's size shrinks by one") {
                REQUIRE(view.size() == initial_size - 1);
            }

            THEN("That value is no longer in the table") {
                auto it = std::find(std::begin(view), std::end(view), val1);
                REQUIRE(it == view.end());
            }

        }
    }
}