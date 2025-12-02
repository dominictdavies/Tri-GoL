#include "utils.hpp"
#include <cstddef>

uint8_t get_neighbourhood(const std::bitset<CELL_COUNT> &is_alive, unsigned row,
                          unsigned col) {
    bool am_alive = is_alive[row * COL_COUNT + col];

    unsigned next_col = modulo(col + 1, COL_COUNT);
    unsigned prev_col = modulo(col - 1, COL_COUNT);
    unsigned next_row = modulo(row + 1, ROW_COUNT);
    unsigned prev_row = modulo(row - 1, ROW_COUNT);

    bool is_up_triangle = check_is_up_triangle(row, col);
    bool left_alive =
        is_alive[(is_up_triangle ? prev_col : next_col) + (row * COL_COUNT)];
    bool right_alive =
        is_alive[(is_up_triangle ? next_col : prev_col) + (row * COL_COUNT)];
    bool down_alive =
        is_alive[(is_up_triangle ? next_row : prev_row) * COL_COUNT + col];

    uint8_t neighbourhood = 0;
    if (left_alive) {
        neighbourhood += 1;
    }
    if (right_alive) {
        neighbourhood += 2;
    }
    if (down_alive) {
        neighbourhood += 4;
    }
    if (am_alive) {
        neighbourhood += 8;
    }

    return neighbourhood_index(neighbourhood);
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
