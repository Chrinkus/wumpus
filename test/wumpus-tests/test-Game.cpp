//
// Created by Chris Schick on 2018-06-06.
//

/*
#include <sstream>
#include "../lib/catch.hpp"
#include "../../src/Game.h"

TEST_CASE("A Command parses expected input as expected", "[Command]") {

    std::istringstream is1 {"move 3"};
    auto cmd1 = Wumpus::Command{is1};
    CHECK(cmd1.type == Wumpus::Command::Type::move);
    REQUIRE(cmd1.params.size() == 1);

    std::istringstream is2 {"shoot 1 2 3"};
    auto cmd2 = Wumpus::Command{is2};
    CHECK(cmd2.type == Wumpus::Command::Type::shoot);
    REQUIRE(cmd2.params.size() == 3);

    std::istringstream is3 {"help"};
    auto cmd3 = Wumpus::Command{is3};
    CHECK(cmd3.type == Wumpus::Command::Type::help);
    REQUIRE(cmd3.params.empty());

    std::istringstream is4 {"quit"};
    auto cmd4 = Wumpus::Command{is4};
    CHECK(cmd4.type == Wumpus::Command::Type::quit);
    REQUIRE(cmd4.params.empty());
}

TEST_CASE("A Command parses unexpected input as errors", "[Command]") {

    std::istringstream is1 {""};
    auto cmd1 = Wumpus::Command{is1};
    CHECK(cmd1.type == Wumpus::Command::Type::error);

    std::istringstream is2 {"shoop 2 4 6"};
    auto cmd2 = Wumpus::Command{is2};
    CHECK(cmd2.type == Wumpus::Command::Type::error);

    std::istringstream is3 {"move move"};
    auto cmd3 = Wumpus::Command{is3};
    CHECK(cmd3.type == Wumpus::Command::Type::error);
}

TEST_CASE("A Command parses acceptable unexpected inputs correctly",
          "[Command]") {

    std::istringstream is1 {"move 1 2 3 5 8"};
    auto cmd1 = Wumpus::Command{is1};
    CHECK(cmd1.type == Wumpus::Command::Type::move);

    std::istringstream is2 {"shoot 1 2 3 5 8"};
    auto cmd2 = Wumpus::Command{is2};
    CHECK(cmd2.type == Wumpus::Command::Type::shoot);

    std::istringstream is3 {"help 1 2 3 5 8"};
    auto cmd3 = Wumpus::Command{is3};
    CHECK(cmd3.type == Wumpus::Command::Type::help);

    std::istringstream is4 {"quit 1 2 3 5 8"};
    auto cmd4 = Wumpus::Command{is4};
    CHECK(cmd4.type == Wumpus::Command::Type::quit);
}
 */
