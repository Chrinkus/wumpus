//
// Created by Chris Schick on 2018-06-14.
//

#ifndef WUMPUS_GAME_TEXT_H
#define WUMPUS_GAME_TEXT_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace Wumpus {

    class Node {
    public:
        using key_t = std::string;
        using value_t = std::string;

        explicit Node(key_t k, const value_t& v = "")
            : key{std::move(k)}, value{v} { }

        Node(Node&& n)
            : key{n.key}, value{n.value}, children{n.children.release()} { }

        void add_child(Node n) { children->emplace_back(std::move(n)); }

        const auto& get_key() const { return key; }
        const auto& get_value() const { return value; }
        const auto& get_children() const { return children; }

        const auto& operator[](const key_t& k)
        {
            return *(std::find_if(std::begin(*children), std::end(*children),
                    [&k](const Node& n) { return n.get_key() == k; }));
        }

    private:
        key_t key;
        value_t value;
        std::unique_ptr<std::vector<Node>> children;    // nullptr for leaves
    };

    bool operator==(const Node& a, const Node& b)
    {
        return a.get_key() == b.get_key();
    }

    bool operator!=(const Node& a, const Node& b) { return !(a == b); }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    /*
    class Game_text {
    public:
        Game_text() = default;

        void fetch(const std::string& file_name);
    private:
        std::vector<Node> table;
    };
    */
}

#endif //WUMPUS_GAME_TEXT_H
