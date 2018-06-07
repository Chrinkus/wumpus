#include "Game.h"

int main() {
    auto game = Wumpus::Game{std::cin, std::cout};
    game.run();
}