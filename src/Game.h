//
// Created by Chris Schick on 2018-06-05.
//

#ifndef WUMPUS_GAME_H
#define WUMPUS_GAME_H

namespace Wumpus {

    class Game {
    public:
        Game() = default;

        void run();                     // main loop

    private:
        bool game_over = false;
    };
}

#endif //WUMPUS_GAME_H
