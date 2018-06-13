//
// Created by Chris Schick on 2018-06-12.
//
// A Room is a location in a maze. It may have a hazard within it.
//

#ifndef WUMPUS_ROOM_H
#define WUMPUS_ROOM_H

#include <vector>
#include <initializer_list>
#include <iostream>

namespace Wumpus {

    using Room_id = int;

    class Room {
    public:
        enum class Hazard { none, bat, pit };

        Room(int number, std::initializer_list<Room_id> adj);

        Room_id get_room_id() const { return room_number; }

        bool has_hazard() const { return hazard != Hazard::none; }
        Hazard get_hazard() const { return hazard; }
        void set_hazard(Hazard h) { hazard = h; }

        bool is_adjacent_to(Room_id room_num) const;
        const std::vector<Room_id>& get_adjacent_rooms() const;

    private:
        Room_id room_number;
        std::vector<Room_id> adjacent_rooms;
        Hazard hazard = Hazard::none;
    };
}

#endif //WUMPUS_ROOM_H
