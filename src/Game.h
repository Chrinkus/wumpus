//
// Created by Chris Schick on 2018-06-05.
//

#ifndef WUMPUS_GAME_H
#define WUMPUS_GAME_H

#include <iostream>

namespace Wumpus {

    class Game {
    public:
        explicit Game(std::istream& istr, std::ostream& ostr)
            : is{istr}, os{ostr} { }

        void run();                     // main loop

    private:
        bool game_over = false;
        std::istream& is;
        std::ostream& os;
    };
}

#endif //WUMPUS_GAME_H
