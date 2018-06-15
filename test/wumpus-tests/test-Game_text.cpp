//
// Created by Chris Schick on 2018-06-15.
//

#include "../lib/catch.hpp"
#include "../../src/Game_text.h"

using namespace Wumpus;

TEST_CASE("Nodes can be created and compared", "[Node]") {
    auto n1 = Node{"alpha", "Hey I'm the alpha node"};
    auto n2 = Node{"beta", "Don't mind me, a beta node"};
    auto n3 = Node{"alpha", "Uh oh.. another alpha.."};

    REQUIRE(n1 != n2);
    REQUIRE(n1 == n3);
}

/*
SCENARIO("Nodes can have children", "[Node]") {

    GIVEN("A node object") {
        auto n1 = Node{"Days of Week"};

        REQUIRE(!n1.get_children());        // empty unique_ptr's are false

        WHEN("A child is added") {

            n1.add_child(Node{"mon", "Monday"});

            THEN("That child can be accessed") {

                const auto& kids = n1.get_children();

                REQUIRE(!kids->empty());
            }
        }
    }
}
*/
