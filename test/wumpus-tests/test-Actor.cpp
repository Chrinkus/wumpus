//
// Created by Chris Schick on 2018-06-09.
//

#include "../lib/catch.hpp"
#include "../../src/Actor.h"

SCENARIO("A Player can be created and manipulated", "[Player]") {
    const auto arrows = 3;

    GIVEN("Some Rooms and a Player") {
        auto room1 = Wumpus::Room{ 1, { 2, 3 } };
        auto room2 = Wumpus::Room{ 2, { 1, 4 } };
        auto player = Wumpus::Player{ room1, arrows };

        REQUIRE(player.get_current_room() == 1);
        REQUIRE(player.has_arrow());

        WHEN("The player is moved") {
            player.move_to(room2.get_room_id());

            THEN("The player's current_room changes") {

                REQUIRE(player.get_current_room() == 2);
            }
        }

        WHEN("The player shoots all arrows") {
            for (auto i = 0; i < arrows; ++i)
                player.shoot_arrow();

            THEN("The player has no arrows") {

                REQUIRE(!player.has_arrow());
            }
        }
    }
}
