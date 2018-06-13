//
// Created by Chris Schick on 2018-06-12.
//

#include "Room.h"

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
}
