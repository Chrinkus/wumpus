//
// Created by Chris Schick on 2018-06-12.
//

#include "../lib/catch.hpp"
#include "../../src/Room.h"

TEST_CASE("Rooms can be created and queried", "[Room]") {

    auto r1 = Wumpus::Room{37, {5, 8, 13}};

    REQUIRE(r1.get_room_id() == 37);
    REQUIRE(r1.is_adjacent_to(8));
    REQUIRE(!r1.is_adjacent_to(2));
    REQUIRE(!r1.has_hazard());

    SECTION("Adjacent rooms can be queried") {
        const auto& ar = r1.get_adjacent_rooms();

        REQUIRE(ar.size() == 3);

        for (const auto& r : ar)
            REQUIRE(r1.is_adjacent_to(r));
    }

    SECTION("Hazards can be changed and queried") {

        r1.set_hazard(Wumpus::Room::Hazard::bat);
        REQUIRE(r1.has_hazard());
        REQUIRE(r1.get_hazard() == Wumpus::Room::Hazard::bat);

        r1.set_hazard(Wumpus::Room::Hazard::none);
        REQUIRE(!r1.has_hazard());
        REQUIRE(r1.get_hazard() == Wumpus::Room::Hazard::none);

        r1.set_hazard(Wumpus::Room::Hazard::pit);
        REQUIRE(r1.has_hazard());
        REQUIRE(r1.get_hazard() == Wumpus::Room::Hazard::pit);
    }
}
