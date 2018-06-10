//
// Created by Chris Schick on 2018-06-06.
//

#include "Maze.h"

namespace Wumpus {

    Room::Room(Room_id number, std::initializer_list<Room_id> adj)
        : room_number{number}
    {
        adjacent_rooms.resize(adj.size());

        std::copy(std::begin(adj), std::end(adj), std::begin(adjacent_rooms));
    }

    bool Room::is_adjacent_to(Room_id room_num) const
    {
        auto it = std::find(std::begin(adjacent_rooms),
                            std::end(adjacent_rooms),
                            room_num);

        return it == std::end(adjacent_rooms) ? false : true;
    }

    const std::vector<Room_id>& Room::get_adjacent_rooms() const
    {
        return adjacent_rooms;
    }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    void Maze::add_room(Room r)
    {
        rooms.emplace(r.get_room_id(), std::move(r));
    }

    const Room& Maze::get_room(Room_id room_num) const
    {
        return rooms.at(room_num);
    }

    Room& Maze::edit_room(Room_id room_num)
    {
        return rooms.at(room_num);
    }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    std::unique_ptr<Maze> Original_layout::create_maze() const
    {
        std::unique_ptr<Maze> pm = std::make_unique<Maze>();

        pm->add_room(Room{ 1, { 2, 5, 8 } });
        pm->add_room(Room{ 2, { 1, 3, 10 } });
        pm->add_room(Room{ 3, { 2, 4, 12 } });
        pm->add_room(Room{ 4, { 3, 5, 14 } });
        pm->add_room(Room{ 5, { 1, 4, 6 } });
        pm->add_room(Room{ 6, { 5, 7, 15 } });
        pm->add_room(Room{ 7, { 6, 8, 17 } });
        pm->add_room(Room{ 8, { 1, 7, 9 } });
        pm->add_room(Room{ 9, { 8, 10, 18 } });
        pm->add_room(Room{ 10, { 2, 9, 11 } });
        pm->add_room(Room{ 11, { 10, 12, 19 } });
        pm->add_room(Room{ 12, { 3, 11, 13 } });
        pm->add_room(Room{ 13, { 12, 14, 20 } });
        pm->add_room(Room{ 14, { 4, 13, 15 } });
        pm->add_room(Room{ 15, { 6, 14, 16 } });
        pm->add_room(Room{ 16, { 15, 17, 20 } });
        pm->add_room(Room{ 17, { 7, 16, 18 } });
        pm->add_room(Room{ 18, { 9, 17, 19 } });
        pm->add_room(Room{ 19, { 11, 18, 20 } });
        pm->add_room(Room{ 20, { 13, 16, 19 } });

        return pm;
    }
}