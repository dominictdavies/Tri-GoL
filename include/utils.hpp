#ifndef UTILS_HPP
#define UTILS_HPP

#include "constants.hpp"
#include <bitset>
#include <cstdint>

constexpr uint8_t neighbourhood_index(uint8_t neighbourhood) {
    switch (neighbourhood) {
    case 3:
        return 4;
    case 4:
        return 3;
    case 11:
        return 12;
    case 12:
        return 11;
    default:
        return neighbourhood;
    }
}

constexpr bool check_is_up_triangle(unsigned row, unsigned col) {
    return (row + col) & 1;
}

uint8_t get_neighbourhood(const std::bitset<CELL_COUNT> &is_alive, unsigned row,
                          unsigned col);

std::bitset<CELL_COUNT> execute_rule(const std::bitset<CELL_COUNT> &is_alive,
                                     uint16_t rule = 32368);

#endif
