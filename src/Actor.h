//
// Created by Chris Schick on 2018-06-08.
//

#ifndef WUMPUS_ACTOR_H
#define WUMPUS_ACTOR_H

#include "Maze.h"           // Room only (consider separating to own header)

namespace Wumpus {

    class Actor {
    public:
        void move_to(const Room& r) { current_room = r.get_room_id(); }
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
        Wumpus(const Room& r) : Actor{r} { }

        // No extra functionality beyond base class for now.
    };
}

#endif //WUMPUS_ACTOR_H
