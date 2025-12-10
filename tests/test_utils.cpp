#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("modulo functions correctly", "[modulo]") {
    // Regular
    CHECK(modulo(0, 120) == 0);
    CHECK(modulo(1, 120) == 1);
    CHECK(modulo(60, 120) == 60);

    // Overflow
    CHECK(modulo(120, 120) == 0);
    CHECK(modulo(121, 120) == 1);
    CHECK(modulo(180, 120) == 60);
    CHECK(modulo(241, 120) == 1);

    // Underflow
    CHECK(modulo(-1, 120) == 119);
    CHECK(modulo(-60, 120) == 60);
    CHECK(modulo(-121, 120) == 119);
}

TEST_CASE("neighbour count index functions correctly",
          "[neighbourhood_index]") {
    std::array<unsigned, 16> expected = {0, 1, 2,  4,  3,  5,  6,  7,
                                         8, 9, 10, 12, 11, 13, 14, 15};
    for (uint8_t neighbourhood = 0; neighbourhood < 16; neighbourhood++) {
        CHECK(static_cast<unsigned>(neighbourhood_index(neighbourhood)) ==
              expected[neighbourhood]);
    }
}

TEST_CASE("gets whether every triangle is up correctly",
          "[get_is_up_triangle]") {
    bool expected = false;
    for (unsigned row = 0; row < ROW_COUNT; row++) {
        for (unsigned col = 0; col < COL_COUNT; col++) {
            CAPTURE(row);
            CAPTURE(col);
            REQUIRE(get_is_up_triangle(row, col) == expected);
            expected = !expected;
        }
        // Rows alternate is_up_triangle order
        expected = !expected;
    }
}

void test_get_cell_index_in_quadrant(int quadrant_x, int quadrant_y) {
    unsigned index = 0;
    int y = quadrant_y * ROW_COUNT;
    for (; y < (quadrant_y + 1) * ROW_COUNT; y++) {
        int x = quadrant_x * COL_COUNT;
        for (; x < (quadrant_x + 1) * COL_COUNT; x++) {
            CAPTURE(x);
            CAPTURE(y);
            REQUIRE(get_cell_index(x, y) == index);
            index += 1;
        }
    }
}

TEST_CASE("gets inside cell indexes correctly", "[get_cell_index]") {
    test_get_cell_index_in_quadrant(0, 0);
}

TEST_CASE("gets outside cell indexes correctly", "[get_cell_index]") {
    for (int quadrant_y = -2; quadrant_y <= 2; quadrant_y++) {
        for (int quadrant_x = -2; quadrant_x <= 2; quadrant_x++) {
            if (quadrant_x == 0 && quadrant_y == 0) {
                continue;
            }

            test_get_cell_index_in_quadrant(quadrant_x, quadrant_y);
        }
    }
}

void test_get_neighbourhood(unsigned row, unsigned col) {
    bool is_up_triangle = get_is_up_triangle(row, col);

    unsigned left_col = is_up_triangle ? col - 1 : col + 1;
    left_col = modulo(left_col, COL_COUNT);

    unsigned right_col = is_up_triangle ? col + 1 : col - 1;
    right_col = modulo(right_col, COL_COUNT);

    unsigned down_row = is_up_triangle ? row + 1 : row - 1;
    down_row = modulo(down_row, ROW_COUNT);

    for (uint8_t neighbourhood = 0; neighbourhood < 16; neighbourhood++) {
        uint8_t is_alive_neighbourhood = neighbourhood_index(neighbourhood);
        std::bitset<CELL_COUNT> is_alive;
        for (unsigned cell_index = 0; cell_index < 4; cell_index++) {
            bool is_cell_alive = is_alive_neighbourhood & 1;
            is_alive_neighbourhood >>= 1;

            if (!is_cell_alive) {
                continue;
            }

            switch (cell_index) {
            case 0:
                is_alive.set(get_cell_index(left_col, row));
                break;
            case 1:
                is_alive.set(get_cell_index(right_col, row));
                break;
            case 2:
                is_alive.set(get_cell_index(col, down_row));
                break;
            case 3:
                is_alive.set(get_cell_index(col, row));
                break;
            }
        }

        CHECK(static_cast<unsigned>(get_neighbourhood(is_alive, row, col)) ==
              static_cast<unsigned>(neighbourhood));
    }
}

TEST_CASE("gets central neighbourhoods correctly", "[get_neighbourhood]") {
    test_get_neighbourhood(1, 1);
    test_get_neighbourhood(1, 2);
    test_get_neighbourhood(2, 1);
    test_get_neighbourhood(2, 2);
}

TEST_CASE("gets horizontal edge neighbourhoods correctly",
          "[get_neighbourhood]") {
    test_get_neighbourhood(0, 1);
    test_get_neighbourhood(0, 2);
    test_get_neighbourhood(ROW_COUNT - 1, 1);
    test_get_neighbourhood(ROW_COUNT - 1, 2);
}

TEST_CASE("gets vertical edge neighbourhoods correctly",
          "[get_neighbourhood]") {
    test_get_neighbourhood(1, 0);
    test_get_neighbourhood(2, 0);
    test_get_neighbourhood(1, COL_COUNT - 1);
    test_get_neighbourhood(2, COL_COUNT - 1);
}

TEST_CASE("gets corner neighbourhoods correctly", "[get_neighbourhood]") {
    test_get_neighbourhood(0, 0);
    test_get_neighbourhood(0, COL_COUNT - 1);
    test_get_neighbourhood(ROW_COUNT - 1, 0);
    test_get_neighbourhood(ROW_COUNT - 1, COL_COUNT - 1);
}
