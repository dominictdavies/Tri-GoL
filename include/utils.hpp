#ifndef UTILS_HPP
#define UTILS_HPP

#include "constants.hpp"
#include <bitset>
#include <cstdint>

constexpr unsigned modulo(int dividend, int modulus) {
    int remainder = dividend % modulus;
    return remainder < 0 ? modulus + remainder : remainder;
}

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

constexpr bool get_neighbour(const std::bitset<CELL_COUNT> &is_alive,
                             unsigned row, unsigned col, int distance,
                             bool is_vertical = false) {
    if (is_vertical) {
        row = modulo(row + distance, ROW_COUNT);
    } else {
        col = modulo(col + distance, COL_COUNT);
    }

    return is_alive[row * COL_COUNT + col];
}

uint8_t get_neighbourhood(const std::bitset<CELL_COUNT> &is_alive, unsigned row,
                          unsigned col);

std::bitset<CELL_COUNT> execute_rule(const std::bitset<CELL_COUNT> &is_alive,
                                     uint16_t rule = 32368);

#endif
