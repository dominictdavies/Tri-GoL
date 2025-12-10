#include "utils.hpp"
#include <cstddef>

uint8_t get_neighbourhood(const std::bitset<CELL_COUNT> &is_alive, unsigned row,
                          unsigned col) {
    bool is_up_triangle = get_is_up_triangle(row, col);
    uint8_t neighbourhood = 0;

    bool is_next_col_alive = is_alive[get_cell_index(row, col + 1)];
    bool is_prev_col_alive = is_alive[get_cell_index(row, col - 1)];
    bool is_next_row_alive = is_alive[get_cell_index(row + 1, col)];
    bool is_prev_row_alive = is_alive[get_cell_index(row - 1, col)];

    // Left
    if (is_up_triangle ? is_prev_col_alive : is_next_col_alive) {
        neighbourhood += 1;
    }

    // Right
    if (is_up_triangle ? is_next_col_alive : is_prev_col_alive) {
        neighbourhood += 2;
    }

    // Down
    if (is_up_triangle ? is_next_row_alive : is_prev_row_alive) {
        neighbourhood += 4;
    }

    // Origin
    if (is_alive[get_cell_index(row, col)]) {
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
