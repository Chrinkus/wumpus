//
// Created by Chris Schick on 2018-06-19.
//

#include "../lib/catch.hpp"
#include "../../src/Text_tree.h"

SCENARIO("Text_components implement a composite pattern", "[Text-tree]") {

    GIVEN("A text primitive") {
        Text_primitive tp1{"This is a line of game text"};

        WHEN("A text composite is created") {

            Text_composite tc1 {"b1"};

            THEN("A primitive can be added to the composite") {

                tc1.add(Text_primitive{"Another line of text!"});
            }
        }
    }
}
