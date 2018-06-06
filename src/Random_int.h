//
// Created by Chris Schick on 2018-06-05.
//

#ifndef WUMPUS_RANDOM_INT_H
#define WUMPUS_RANDOM_INT_H

#include <random>
#include <chrono>

class Random_int {
public:
    Random_int()
        : ran{static_cast<unsigned int>(std::chrono::system_clock::now()
            .time_since_epoch().count())} { }

    int operator()(int min, int max) {
        return std::uniform_int_distribution<>{min, max}(ran);
    }

private:
    std::minstd_rand ran;
};

#endif //WUMPUS_RANDOM_INT_H
