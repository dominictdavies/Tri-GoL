#include "utils.hpp"
#include <cstddef>

uint8_t get_neighbourhood(const std::bitset<CELL_COUNT> &is_alive, unsigned row,
                          unsigned col) {
    // size_t index = row * COL_COUNT + col;
    // bool am_alive = is_alive[index];
    // bool is_up_triangle = (row + col) & 1;
    // index = (is_up_triangle ? (row + 1) : (row - 1)) * COL_COUNT + col;
    // bool close_alive = is_alive[index];
    // index = row * COL_COUNT + 0;

    return (uint8_t)0;
}

std::bitset<CELL_COUNT> execute_rule(const std::bitset<CELL_COUNT> &is_alive,
                                     uint16_t rule) {
    // std::bitset<CELL_COUNT> new_is_alive;
    // for (unsigned row = 0; row < ROW_COUNT; row++) {
    //     for (unsigned col = 0; col < COL_COUNT; col++) {
    //         uint8_t neighbourhood = get_neighbourhood(is_alive, row, col);
    //     }
    // }

    return is_alive;
}
