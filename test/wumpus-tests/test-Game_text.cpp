//
// Created by Chris Schick on 2018-06-15.
//

#include "../lib/catch.hpp"
#include "../../src/Game_text.h"

using namespace Wumpus;

TEST_CASE("Game_text object can be created and text added", "[Game_text]") {

    auto gt = Game_text{};
    gt.add("alpha", "Never gonna give you up");

    REQUIRE(gt["alpha"] == "Never gonna give you up");
}

SCENARIO("Game_text object can be filled from a file", "[Game_text]") {

    GIVEN("A Game_text object and a file name") {

        auto gt = Game_text{};
        auto file = "../src/wumpus-text.txt";

        WHEN("The fill operation is called") {

            gt.fill(file);

            THEN("The Game_text object has text from the file") {

                REQUIRE(gt["splash-title"] == "Hunt the Wumpus");
            }
        }
    }
}
