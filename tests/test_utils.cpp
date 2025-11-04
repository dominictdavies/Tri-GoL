#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("all neighbourhoods are accurate", "[neighbourhood]") {
    std::bitset<CELL_COUNT> is_alive;

    bool is_up_triangle = (MIDDLE_ROW + MIDDLE_COL) & 1;
    unsigned left_col = is_up_triangle ? MIDDLE_COL + 1 : MIDDLE_COL - 1;
    unsigned right_col = is_up_triangle ? MIDDLE_COL - 1 : MIDDLE_COL + 1;
    unsigned vertical_row = is_up_triangle ? MIDDLE_ROW + 1 : MIDDLE_ROW - 1;

    SECTION("dead-empty neighbourhood is 0") {
        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 0);
    }

    SECTION("dead-left neighbourhood is 1") {
        is_alive[MIDDLE_ROW * COL_COUNT + left_col] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 1);
    }

    SECTION("dead-right neighbourhood is 2") {
        is_alive[MIDDLE_ROW * COL_COUNT + right_col] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 2);
    }

    SECTION("dead-vertical neighbourhood is 3") {
        is_alive[vertical_row * COL_COUNT + MIDDLE_COL] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 3);
    }

    SECTION("dead-left-right neighbourhood is 4") {
        is_alive[MIDDLE_ROW * COL_COUNT + left_col] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + right_col] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 4);
    }

    SECTION("dead-left-vertical neighbourhood is 5") {
        is_alive[MIDDLE_ROW * COL_COUNT + left_col] = true;
        is_alive[vertical_row * COL_COUNT + MIDDLE_COL] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 5);
    }

    SECTION("dead-right-vertical neighbourhood is 6") {
        is_alive[MIDDLE_ROW * COL_COUNT + right_col] = true;
        is_alive[vertical_row * COL_COUNT + MIDDLE_COL] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 6);
    }

    SECTION("dead-full neighbourhood is 7") {
        is_alive[MIDDLE_ROW * COL_COUNT + left_col] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + right_col] = true;
        is_alive[vertical_row * COL_COUNT + MIDDLE_COL] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 7);
    }

    SECTION("live-empty neighbourhood is 8") {
        is_alive[MIDDLE_ROW * COL_COUNT + MIDDLE_COL] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 8);
    }

    SECTION("live-left neighbourhood is 9") {
        is_alive[MIDDLE_ROW * COL_COUNT + MIDDLE_COL] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + left_col] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 9);
    }

    SECTION("live-right neighbourhood is 10") {
        is_alive[MIDDLE_ROW * COL_COUNT + MIDDLE_COL] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + right_col] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 10);
    }

    SECTION("live-vertical neighbourhood is 11") {
        is_alive[MIDDLE_ROW * COL_COUNT + MIDDLE_COL] = true;
        is_alive[vertical_row * COL_COUNT + MIDDLE_COL] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 11);
    }

    SECTION("live-left-right neighbourhood is 12") {
        is_alive[MIDDLE_ROW * COL_COUNT + MIDDLE_COL] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + left_col] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + right_col] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 12);
    }

    SECTION("live-left-vertical neighbourhood is 13") {
        is_alive[MIDDLE_ROW * COL_COUNT + MIDDLE_COL] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + left_col] = true;
        is_alive[vertical_row * COL_COUNT + MIDDLE_COL] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 13);
    }

    SECTION("live-right-vertical neighbourhood is 14") {
        is_alive[MIDDLE_ROW * COL_COUNT + MIDDLE_COL] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + right_col] = true;
        is_alive[vertical_row * COL_COUNT + MIDDLE_COL] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 14);
    }

    SECTION("live-full neighbourhood is 15") {
        is_alive[MIDDLE_ROW * COL_COUNT + MIDDLE_COL] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + left_col] = true;
        is_alive[MIDDLE_ROW * COL_COUNT + right_col] = true;
        is_alive[vertical_row * COL_COUNT + MIDDLE_COL] = true;

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 15);
    }
}
