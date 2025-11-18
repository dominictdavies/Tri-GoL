#include "utils.hpp"
#include <cstddef>

std::string get_neighbourhood_name(uint8_t neighbourhood) {
    const bool is_alive = neighbourhood >= 8;
    const uint8_t pattern = neighbourhood & 0b0111;

    std::string result = is_alive ? "live-" : "dead-";

    switch (pattern) {
    case 0b000:
        result += "empty";
        break;
    case 0b001:
        result += "left";
        break;
    case 0b010:
        result += "right";
        break;
    case 0b011:
        result += "down";
        break;
    case 0b100:
        result += "left-right";
        break;
    case 0b101:
        result += "left-down";
        break;
    case 0b110:
        result += "right-down";
        break;
    case 0b111:
        result += "full";
        break;
    }

    return result;
}

uint8_t get_neighbourhood(const std::bitset<CELL_COUNT> &is_alive, unsigned row,
                          unsigned col) {
    size_t index = row * COL_COUNT + col;

    bool is_up_triangle = (row + col) & 1;
    bool am_alive = is_alive[index];
    bool down_alive =
        is_alive[(is_up_triangle ? (row + 1) : (row - 1)) * COL_COUNT + col];
    bool left_alive = is_alive[is_up_triangle ? index - 1 : index + 1];
    bool right_alive = is_alive[is_up_triangle ? index + 1 : index - 1];

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
