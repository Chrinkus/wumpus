//
// Created by Chris Schick on 2018-06-08.
//
// Have changed move_to() to take a Room_id instead of an actual Room reference
// because it is a validated object as used in the Game::move_cmd() function.
// Have kept the Actor() ctor as is, requiring a full Room object to ensure a
// Room actually exists since Actors are created using an Assignment_table.
//
// Have altered the tests accordingly.
//

#ifndef WUMPUS_ACTOR_H
#define WUMPUS_ACTOR_H

#include "Room.h"

namespace Wumpus {

    class Actor {
    public:
        void move_to(Room_id rid) { current_room = rid; }
        Room_id get_current_room() const { return current_room; }

        virtual ~Actor() = default;

    protected:
        explicit Actor(const Room& r)
            : current_room{r.get_room_id()} { }

    private:
        Room_id current_room;
    };

    class Player : public Actor {
    public:
        explicit Player(const Room& r, int arrows = 5)
            : Actor{r}, number_of_arrows{arrows} { }

        bool has_arrow() const { return number_of_arrows > 0; }
        void shoot_arrow() { --number_of_arrows; }

    private:
        int number_of_arrows;
    };

    struct Wumpus : public Actor {
    public:
        explicit Wumpus(const Room& r) : Actor{r} { }

        // No extra functionality beyond base class for now.
    };
}

#endif //WUMPUS_ACTOR_H
