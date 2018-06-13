//
// Created by Chris Schick on 2018-06-05.
//

#ifndef WUMPUS_GAME_H
#define WUMPUS_GAME_H

#include <iostream>
#include <vector>
#include <string>
#include "Maze.h"
#include "Actor.h"
#include "Random_utils.h"

namespace Wumpus {

    struct Command {
    public:
        enum class Type { error, move, shoot, help, quit };
        explicit Command(const std::string& line);
        Type type = Type::error;
        std::vector<int> params;
    };

    class Game {
    public:
        Game(std::istream& istr, std::ostream& ostr);

        void run();                     // main loop

        void debug() const;

    private:
        bool validate_adjacent(Room_id source, Room_id destination) const;
        std::vector<bool> room_trace(Room_id source,
                                     const std::vector<Room_id>& path) const;

        bool check_wumpus() const { return player->get_current_room() ==
                                           wumpus->get_current_room(); }
        void hit_wumpus();              // victory condition
        void miss_wumpus();             // moves wumpus
        void trigger_hazard(Room_id);   // move or kill player
        void wumpus_room();             // player enters wumpus room

        void print_status() const;

        void route_command(Command&);
        void move_cmd(Room_id);
        void shoot_cmd(std::vector<Room_id>&);
        void no_arrows() const;
        void help_cmd() const;
        void error_cmd() const;
        void quit_cmd();

        bool game_over = false;
        Random_int randint;             // Game-owned random generator

        const size_t max_shoot_rooms = 3;

        std::istream& is;
        std::ostream& os;

        std::unique_ptr<Maze> maze;
        std::unique_ptr<Player> player;
        std::unique_ptr<Wumpus> wumpus;
    };
}

#endif //WUMPUS_GAME_H
