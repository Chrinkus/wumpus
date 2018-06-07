//
// Created by Chris Schick on 2018-06-05.
//

#include "Game.h"

namespace Wumpus {

    void Game::run()
    {
        os << "Hunt the Wumpus\n"
           << "===============\n";

        while (!game_over) {
            os << "> ";
            std::string command;
            std::getline(is, command);

            if (command == "end game") {
                game_over = true;
            } else {
                os << "Unknown command\n";
            }
        }

        os << "Thank you for playing!\n";
    }
}
