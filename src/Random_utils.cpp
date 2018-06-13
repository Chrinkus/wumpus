//
// Created by Chris Schick on 2018-06-10.
//

#include "Random_utils.h"

template<typename T>
Assignment_table::Assignment_table(size_t sz, T start)
        : table{std::vector<T>(sz)}
{
    for (auto& val : table)
        val = start++;
}

template<typename T>
T Assignment_table::get_value(T low, T high)
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
T Assignment_table::get_value()
    // grab a random value from the table, remove and return it
{
    auto offset = random_index(0, table.size() - 1);
    auto it_val = std::begin(table) + offset;
    auto value = *it_val;

    table.erase(it_val);
    return value;
}
