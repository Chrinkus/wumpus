//
// Created by Chris Schick on 2018-06-05.
//

#ifndef WUMPUS_RANDOM_UTILS_H
#define WUMPUS_RANDOM_UTILS_H

#include <random>
#include <chrono>
#include <vector>

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

class Assignment_table {
    // A sorted vector of integer values to randomly grab from
public:
    explicit Assignment_table(size_t sz, int start = 0);

    int get_value(int min = INT_MIN, int max = INT_MAX);

    const auto& view_table() const { return table; }        // aids debugging

private:
    std::vector<int> table;
    Random_int rint;
};

#endif //WUMPUS_RANDOM_UTILS_H
