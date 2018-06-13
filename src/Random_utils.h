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

template<typename T>
    // requires incrementable value
class Assignment_table {
    // A sorted vector of T values to randomly grab from
public:
    Assignment_table(size_t sz, T start);
    // could potentially provide a ctor that takes an init_list and predicate

    T get_value(T low, T high);
    T get_value();

    const auto& view_table() const { return table; }        // aids debugging

private:
    std::vector<int> table;
    Random_int random_index;
};

#endif //WUMPUS_RANDOM_UTILS_H
