//
// Created by Chris Schick on 2018-06-06.
//

#ifndef WUMPUS_MAZE_H
#define WUMPUS_MAZE_H

#include "Room.h"
#include <unordered_map>

namespace Wumpus {

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
        std::unordered_map<Room_id,std::unique_ptr<Room>> rooms;

        /* Used vector by default here but have realized that I do not ever
         * traverse the Rooms of a Maze. The only time I do is when I want to
         * grab a Room by id with std::find_if(). These two reasons suggest I
         * would be better served using a hash table.
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
