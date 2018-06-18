//
// Created by Chris Schick on 2018-06-14.
//

#include "Game_text.h"

namespace Wumpus {

    void Game_text::fill(const std::string& fname)
    {
        std::ifstream ifs {fname};
        if (!ifs)
            throw std::runtime_error("could not read from file");

        std::regex entry {R"(^([\w\-]+): (.+)$)"};

        std::string line;
        while (std::getline(ifs, line)) {
            std::smatch matches;
            if (std::regex_match(line, matches, entry))
                add(matches[1], matches[2]);
        }
    }
}