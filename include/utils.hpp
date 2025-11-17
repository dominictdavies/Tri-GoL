#ifndef UTILS_HPP
#define UTILS_HPP

#include "constants.hpp"
#include <bitset>
#include <cstdint>

constexpr uint8_t neighbour_count_index(uint8_t x) {
    switch (x) {
    case 3:
        return 4;
    case 4:
        return 3;
    case 11:
        return 12;
    case 12:
        return 11;
    default:
        return x;
    }
}

std::string get_neighbourhood_name(uint8_t neighbourhood);

uint8_t get_neighbourhood(const std::bitset<CELL_COUNT> &is_alive, unsigned row,
                          unsigned col);

std::bitset<CELL_COUNT> execute_rule(const std::bitset<CELL_COUNT> &is_alive,
                                     uint16_t rule = 32368);

#endif
