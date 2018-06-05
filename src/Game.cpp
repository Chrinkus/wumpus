//
// Created by Chris Schick on 2018-06-05.
//

#include <iostream>
#include "Game.h"

namespace Wumpus {

    void Game::run()
    {
        std::cout << "Hunt the Wumpus\n"
                  << "===============\n"
                  << "> ";

        while (!game_over) {
            std::string command;
            std::getline(std::cin, command);

            if (command == "end game") {
                game_over = true;
            } else {
                std::cout << "You wanted to: " << command << '\n'
                          << "but I don't know how to do that.\n";
            }
        }

        std::cout << "Thank you for playing!\n";
    }
}
