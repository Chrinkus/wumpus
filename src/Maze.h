//
// Created by Chris Schick on 2018-06-06.
//

#ifndef WUMPUS_MAZE_H
#define WUMPUS_MAZE_H

#include <vector>
#include <unordered_map>
#include <initializer_list>

namespace Wumpus {

    using Room_id = int;

    class Room {
        // A Room is a location in a maze. It may have a hazard within it.
    public:
        enum class Hazard {none, bat, pit};
        Room(int number, std::initializer_list<Room_id> adj);

        Room_id get_room_id() const { return room_number; }
        bool has_hazard() const { return hazard != Hazard::none; }

        void set_hazard(Hazard h) { hazard = h; }
        Hazard get_hazard() const { return hazard; }

        bool is_adjacent_to(Room_id room_num) const;
        const std::vector<Room_id>& get_adjacent_rooms() const;

    private:
        Room_id room_number;
        std::vector<Room_id> adjacent_rooms;
        Hazard hazard = Hazard::none;

        /* Thinking ahead to how I would draw a map on the fly from a Room
         * object I would like to know how the adjacent rooms relate to a
         * given room. Top, mid, bot? Right, left.. even?
         */
    };

    class Maze {
        // A Maze is a collection of Rooms. It provides facilities for adding
        // rooms, the number of rooms and a const query.
    public:
        Maze() = default;

        void add_room(Room r);

        const Room& get_room(Room_id room_num) const;
        Room& edit_room(Room_id room_num);

        size_t number_of_rooms() const { return rooms.size(); }

    private:
        std::unordered_map<Room_id,Room> rooms;

        /* Used vector by default here but have realized that I do not ever
         * traverse the Rooms of a Maze. The only time I do is when I want to
         * grab a Room by id with std::find_if(). These two reasons suggest I
         * would be better served using a hash table.
         *
         * sizeof(Room) == 40 bytes. Is this big? Would it be better to store
         * std::unique_ptr<Room>'s instead?
         */
    };

    class Layout_factory {
        // Base class for producing Room layouts in a Maze
    public:
        virtual std::unique_ptr<Maze> create_maze() const = 0;

        virtual ~Layout_factory() = default;

    protected:
        Layout_factory() = default;
    };

    struct Original_layout : public Layout_factory {
        // Creates a dodecahedron layout similar to the original Hunt the
        // Wumpus game.
    public:
        Original_layout() = default;

        std::unique_ptr<Maze> create_maze() const override;
    };
}

#endif //WUMPUS_MAZE_H
