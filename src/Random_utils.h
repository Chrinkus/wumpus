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

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
    // requires incrementable value
class Assignment_table {
    // A sorted vector of T values to randomly grab from
public:
    Assignment_table(size_t sz, T start)
            : table{std::vector<T>(sz)}
    {
        for (auto& val : table) val = start++;
    }

    T get_value(T low, T high);
    T get_value();

    const auto& view_table() const { return table; }        // aids debugging

private:
    std::vector<int> table;
    Random_int random_index;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
T Assignment_table<T>::get_value(T low, T high)
    // find iterators to values not lower than low and one higher than high
    // calculate a random offset based on their distance - 1
    // remove the value from the table and return it
{
    auto it_min = std::lower_bound(std::begin(table), std::end(table), low);
    auto it_max = std::upper_bound(std::begin(table), std::end(table), high);

    auto dist = std::distance(it_min, it_max);

    auto offset = random_index(0, dist - 1);
    auto it_val = it_min + offset;
    auto value = *it_val;

    table.erase(it_val);
    return value;
}

template<typename T>
T Assignment_table<T>::get_value()
    // grab a random value from the table, remove and return it
{
    auto offset = random_index(0, table.size() - 1);
    auto it_val = std::begin(table) + offset;
    auto value = *it_val;

    table.erase(it_val);
    return value;
}

#endif //WUMPUS_RANDOM_UTILS_H
