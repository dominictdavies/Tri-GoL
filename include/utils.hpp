#ifndef UTILS_HPP
#define UTILS_HPP

#include "constants.hpp"
#include <bitset>
#include <cstdint>

uint8_t get_neighbourhood(const std::bitset<CELL_COUNT> &is_alive, unsigned row,
                          unsigned col);

std::bitset<CELL_COUNT> execute_rule(const std::bitset<CELL_COUNT> &is_alive,
                                     uint16_t rule = 32368);

#endif
