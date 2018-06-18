//
// Created by Chris Schick on 2018-06-14.
//

#ifndef WUMPUS_GAME_TEXT_H
#define WUMPUS_GAME_TEXT_H

#include <string>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <regex>

namespace Wumpus {

    class Game_text {
    public:
        Game_text() = default;

        void add(const std::string& key, std::string line)
        {
            text[key] = std::move(line);
        }

        const std::string& operator[](const std::string& key) const
        {
            return text.at(key);
        }

        void fill(const std::string&);

    private:
        std::unordered_map<std::string,std::string> text;
    };
}

#endif //WUMPUS_GAME_TEXT_H
