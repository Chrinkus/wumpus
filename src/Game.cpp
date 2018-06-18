//
// Created by Chris Schick on 2018-06-05.
//

#include <sstream>
#include "Game.h"

namespace Wumpus {

    Command::Command(const std::string& line)
    {
        std::istringstream iss {line};
        std::string verb;
        iss >> verb;

        for (int val; iss >> val; )
            params.push_back(val);

        if (verb == "move" && !params.empty())          type = Type::move;
        else if (verb == "shoot" && !params.empty())    type = Type::shoot;
        else if (verb == "help")                        type = Type::help;
        else if (verb == "quit")                        type = Type::quit;
    }

    Game::Game(std::istream& istr, std::ostream& ostr)
        : is{istr}, os{ostr}
    {
        // Maze
        auto maze_factory = Original_layout{};
        maze = maze_factory.create_maze();

        // create vector of Room_id's to randomly assign
        auto room_assignment =
                Assignment_table<Room_id>(maze->number_of_rooms(), 1);

        // Player
        auto player_room = room_assignment.get_value(1, 5);
        player = std::make_unique<Player>(maze->get_room(player_room));

        // Wumpus
        auto wumpus_room = room_assignment.get_value(16, 20);
        wumpus = std::make_unique<Wumpus>(maze->get_room(wumpus_room));

        // Hazards
        const auto max_hazards = 5;
        const auto max_bats = 4;

        auto number_of_bats = randint(1, max_bats);
        auto number_of_pits = max_hazards - number_of_bats;

        for (auto i = 0; i < number_of_bats; ++i) {
            auto room = room_assignment.get_value();
            maze->edit_room(room).set_hazard(Room::Hazard::bat);
        }

        for (auto i = 0; i < number_of_pits; ++i) {
            auto room = room_assignment.get_value();
            maze->edit_room(room).set_hazard(Room::Hazard::pit);
        }

        // Game Text
        g_text.fill("../src/wumpus-text.txt");
    }

    bool Game::validate_adjacent(Room_id source, Room_id destination) const
    {
        return maze->get_room(source).is_adjacent_to(destination);
    }

    std::vector<bool> Game::room_trace(Room_id source,
                          const std::vector<Room_id>& path) const
    {
        std::vector<bool> vb;

        for (const auto next_room : path) {
            vb.push_back(validate_adjacent(source, next_room));
            source = next_room;
        }

        return vb;
    }

    void Game::print_status() const
    {
        auto player_room = maze->get_room(player->get_current_room());
        const auto& adjacents = player_room.get_adjacent_rooms();

        os << g_text["status-room"] << ' '
           << player_room.get_room_id() << ".\n"
           << g_text["status-doors"] << ' '
           << adjacents[0] << ", "
           << adjacents[1] << " & "
           << adjacents[2] << ".\n";

        // Check hazards
        bool bat = false;
        bool pit = false;

        for (const auto& room_id : adjacents) {
            switch (maze->get_room(room_id).get_hazard()) {
                case Room::Hazard::bat:
                    bat = true;
                    break;
                case Room::Hazard::pit:
                    pit = true;
                    break;
                case Room::Hazard::none:
                    break;
            }
        }

        if (bat)
            os << g_text["hint-bat"] << '\n';
        if (pit)
            os << g_text["hint-pit"] << '\n';

        // Check Wumpus
        auto it = std::find(std::begin(adjacents), std::end(adjacents),
                            wumpus->get_current_room());
        if (it != std::end(adjacents))
            os << g_text["hint-wumpus"] << '\n';

        os << g_text["prompt-command"] << '\n';
    }

    void Game::run()
    {
        auto title = g_text["splash-title"];

        auto underline = std::string{};
        for (const auto c : title)
            underline += '=';

        os << title << '\n'
           << underline << "\n\n"
           << g_text["splash-story"] << '\n';

        while (!game_over) {
            //debug();
            print_status();
            auto line = std::string{};
            std::getline(is, line);
            auto cmd = Command{line};

            route_command(cmd);
        }
    }

    void Game::route_command(Command& cmd)
        // validate command if necessary and pass pass to correct handler
    {
        switch (cmd.type) {
            case Command::Type::error:  return error_cmd();
            case Command::Type::quit:   return quit_cmd();
            case Command::Type::help:   return help_cmd();
            case Command::Type::move:   return move_cmd(cmd.params[0]);
            case Command::Type::shoot:  return player->has_arrow()
                                               ? shoot_cmd(cmd.params)
                                               : no_arrows();
        }
    }

    void Game::move_cmd(Room_id destination)
    {
        if (validate_adjacent(player->get_current_room(), destination)) {
            player->move_to(destination);

            if (check_wumpus())
                return wumpus_room();
            else if (maze->get_room(destination).has_hazard())
                return trigger_hazard(destination);
        }
        else
            os << g_text["fail-move"] << '\n';
    }

    void Game::trigger_hazard(Room_id room_id)
    {
        auto hazard = maze->get_room(room_id).get_hazard();

        switch (hazard) {
            case Room::Hazard::bat:
                os << g_text["result-move-bat"] << '\n';
                player->move_to(randint(1, 20));
                trigger_hazard(player->get_current_room());
                break;
            case Room::Hazard::pit:
                os << g_text["result-move-pit"] << '\n';
                game_over = true;
                break;
            case Room::Hazard::none:
                // get here after bat drops you
                if (check_wumpus())
                    os << g_text["result-move-wumpus"] << '\n';
                    return wumpus_room();
                break;
        }
    }

    void Game::no_arrows() const
    {
        os << g_text["fail-shoot"] << '\n';
    }

    void Game::shoot_cmd(std::vector<Room_id>& target_rooms)
    {
        if (target_rooms.size() > max_shoot_rooms)
            target_rooms.resize(max_shoot_rooms);

        player->shoot_arrow();

        auto trace = room_trace(player->get_current_room(), target_rooms);

        // STL-style algorithm
        auto it_trace = std::begin(trace);
        auto it_rooms = std::begin(target_rooms);

        while (it_trace != std::end(trace) && *it_trace) {
            if (wumpus->get_current_room() == *it_rooms)
                return hit_wumpus();
            ++it_rooms;
            ++it_trace;
        }

        return miss_wumpus();
    }

    void Game::hit_wumpus()
    {
        os << g_text["result-hit-wumpus"] << '\n'
           << g_text["victory"] << '\n';
        game_over = true;
    }

    void Game::miss_wumpus()
    {
        // move wumpus randomly
        os << g_text["result-miss-wake"] << '\n';

        auto adj_rooms = maze->get_room(wumpus->get_current_room())
                .get_adjacent_rooms();
        wumpus->move_to(adj_rooms[randint(0, adj_rooms.size() - 1)]);

        if (check_wumpus()) {
            os << g_text["result-miss-enter"] << '\n';
            return wumpus_room();
        }
        else {
            os << g_text["result-miss-sleep"] << '\n';
        }

    }

    void Game::wumpus_room()
    {
        os << g_text["death-wumpus"] << '\n';
        game_over = true;
    }

    void Game::quit_cmd()
    {
        os << g_text["quit"] << '\n';
        game_over = true;
    }

    void Game::help_cmd() const
    {
        os << g_text["help"] << '\n';
    }

    void Game::error_cmd() const
    {
        os << g_text["fail-command"] << '\n';
    }

    void Game::debug() const
    {
        std::vector<Room_id> bats;
        std::vector<Room_id> pits;

        for (Room_id i = 1; i <= maze->number_of_rooms(); ++i) {
            switch (maze->get_room(i).get_hazard()) {
                case Room::Hazard::bat:
                    bats.push_back(i);
                    break;
                case Room::Hazard::pit:
                    pits.push_back(i);
                    break;
                default:
                    break;
            }
        }

        std::cout << "WUMPUS DEBUG\n"
                  << "Player: " << player->get_current_room() << '\n'
                  << "Wumpus: " << wumpus->get_current_room() << '\n'
                  << "Bats in: ";

        for (const auto rid : bats)
            std::cout << rid << ' ';
        std::cout << '\n';

        std::cout << "Pits in: ";

        for (const auto rid : pits)
            std::cout << rid << ' ';
        std::cout << '\n';
    }
}
