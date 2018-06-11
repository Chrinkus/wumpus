//
// Created by Chris Schick on 2018-06-10.
//

#include "Random_utils.h"

Assignment_table::Assignment_table(size_t sz, int start)
        : table{std::vector<int>(sz)}
{
    for (auto& val : table)
        val = start++;
}

int Assignment_table::get_value(int min, int max)
{
    if (min == INT_MIN) min = 0;
    if (max == INT_MAX) max = table.size() - 1;

    auto value = table[rint(min, max)];
    table.erase(std::find(std::begin(table), std::end(table), value));
    return value;
}
