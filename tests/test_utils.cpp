#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("neighbour count index functions correctly",
          "[neighbourhood_index]") {
    std::array<unsigned, 16> expected = {0, 1, 2,  4,  3,  5,  6,  7,
                                         8, 9, 10, 12, 11, 13, 14, 15};
    for (uint8_t neighbourhood = 0; neighbourhood < 16; neighbourhood++) {
        REQUIRE(static_cast<unsigned>(neighbourhood_index(neighbourhood)) ==
                expected[neighbourhood]);
    }
}

TEST_CASE("gets all neighbourhood names correctly",
          "[get_neighbourhood_name]") {
    std::array<std::string, 16> expected = {
        "dead-empty",      "dead-left",      "dead-right",      "dead-down",
        "dead-left-right", "dead-left-down", "dead-right-down", "dead-full",
        "live-empty",      "live-left",      "live-right",      "live-down",
        "live-left-right", "live-left-down", "live-right-down", "live-full"};
    for (uint8_t neighbourhood = 0; neighbourhood < 16; neighbourhood++) {
        REQUIRE(get_neighbourhood_name(neighbourhood) ==
                expected[neighbourhood]);
    }
}

void test_get_neighbourhood(unsigned row, unsigned col) {
    for (uint8_t neighbourhood = 0; neighbourhood < 16; neighbourhood++) {
        uint8_t rule_index = neighbourhood_index(neighbourhood);
        std::bitset<CELL_COUNT> is_alive;

        bool is_up_triangle = (row + col) & 1;
        unsigned left_col = is_up_triangle ? col - 1 : col + 1;
        unsigned right_col = is_up_triangle ? col + 1 : col - 1;
        unsigned down_row = is_up_triangle ? row + 1 : row - 1;

        for (unsigned cell_index = 0; cell_index < 4; cell_index++) {
            bool is_cell_alive = rule_index & 1;
            rule_index >>= 1;

            if (!is_cell_alive) {
                continue;
            }

            switch (cell_index) {
            case 0:
                is_alive.set(row * COL_COUNT + left_col);
                break;
            case 1:
                is_alive.set(row * COL_COUNT + right_col);
                break;
            case 2:
                is_alive.set(down_row * COL_COUNT + col);
                break;
            case 3:
                is_alive.set(row * COL_COUNT + col);
                break;
            }
        }

        REQUIRE(static_cast<unsigned>(get_neighbourhood(is_alive, row, col)) ==
                neighbourhood);
    }
}

TEST_CASE("gets all neighbourhoods correctly", "[get_neighbourhood]") {
    test_get_neighbourhood(MIDDLE_ROW, MIDDLE_COL);
    test_get_neighbourhood(MIDDLE_ROW + 1, MIDDLE_COL);
}
