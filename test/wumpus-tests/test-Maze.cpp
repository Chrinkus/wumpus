//
// Created by Chris Schick on 2018-06-06.
//

#include <iostream>
#include "../lib/catch.hpp"
#include "../../src/Maze.h"

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

SCENARIO("Mazes can be created and rooms added", "[Maze]") {

    GIVEN("An empty maze is created") {
        auto maze = Wumpus::Maze{};

        REQUIRE(maze.number_of_rooms() == 0);

        WHEN("Rooms are added") {
            maze.add_room(Wumpus::Room{1, {2, 3}});
            maze.add_room(Wumpus::Room{2, {1, 4}});
            maze.add_room(Wumpus::Room{3, {1, 4}});
            maze.add_room(Wumpus::Room{4, {2, 3}});

            THEN("The size of the maze changes") {

                REQUIRE(maze.number_of_rooms() == 4);
            }

            AND_WHEN("A Room is queried") {
                const auto& room = maze.get_room(2);

                THEN("That room can be examined") {
                    REQUIRE(room.get_room_id() == 2);
                    REQUIRE(room.get_hazard() == Wumpus::Room::Hazard::none);
                    REQUIRE(room.is_adjacent_to(1));
                    REQUIRE(!room.is_adjacent_to(3));

                    const auto& adj_rooms = room.get_adjacent_rooms();

                    for (const auto& r : adj_rooms)
                        REQUIRE(room.is_adjacent_to(r));
                }
            }

            AND_WHEN("A Room is queried for editing") {
                auto& room = maze.edit_room(4);
                REQUIRE(!room.has_hazard());

                THEN("That room can be altered") {
                    room.set_hazard(Wumpus::Room::Hazard::bat);
                    REQUIRE(room.has_hazard());
                }
            }
        }
    }
}

SCENARIO("Mazes can be created by factories", "[Layout_factory]") {

    GIVEN("A derived layout factory") {
        auto factory = Wumpus::Original_layout{};

        WHEN("The factory creates a maze") {
            auto maze = factory.create_maze();

            THEN("That maze is filled with Rooms") {
                REQUIRE(maze->number_of_rooms() == 20);
            }

            AND_WHEN("A room is queried") {
                // Room{ 5, { 1, 4, 6 } }
                const auto& room = maze->get_room(5);

                THEN("That room can be examined") {
                    REQUIRE(room.get_room_id() == 5);
                    REQUIRE(room.get_hazard() == Wumpus::Room::Hazard::none);
                    REQUIRE(room.is_adjacent_to(6));
                    REQUIRE(!room.is_adjacent_to(13));
                }

                AND_THEN("The adjacent rooms can be cross-referenced") {
                    const auto& adj_rooms = room.get_adjacent_rooms();

                    for (const auto& r : adj_rooms)
                        REQUIRE(maze->get_room(r)
                                .is_adjacent_to(room.get_room_id()));
                }
            }

            AND_WHEN("A room is queried for editing") {
                // Room{ 15, { 6, 14, 16 } }
                auto& room = maze->edit_room(15);
                REQUIRE(!room.has_hazard());

                THEN("That room can be edited") {
                    room.set_hazard(Wumpus::Room::Hazard::pit);
                    REQUIRE(room.has_hazard());
                }
            }
        }
    }
}

