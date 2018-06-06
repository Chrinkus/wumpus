//
// Created by Chris Schick on 2018-06-06.
//

#include "../lib/catch.hpp"
#include "../../src/Random_int.h"

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

    GIVEN("A Random_int object") {
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