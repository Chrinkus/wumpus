//
// Created by Chris Schick on 2018-06-06.
//

/* Omitted for now as Game is not even minimally set
#include "../lib/catch.hpp"
#include "../../src/Game.h"
#include <fstream>
#include <sstream>

SCENARIO("Game command loop handles unrecognized commands", "[Game]") {
    const auto unknown = "Unknown command";
    const auto eog = "Thank you for playing!";

    GIVEN("A game is initialized with streams") {
        auto istr = std::stringstream{};
        auto ostr = std::stringstream{};

        istr << "game over\n"
             << "quit already\n"
             << "home screen\n"
             << "end game\n";

        auto game = Wumpus::Game{istr, ostr};

        WHEN("The game loop runs through the bad input") {
            game.run();

            std::vector<std::string> vs;
            for (std::string line; std::getline(ostr, line); )
                vs.push_back(line);

            THEN("The loop runs until 'end game' is input") {
                REQUIRE(vs.back() == eog);
            }
        }
    }
}
*/
