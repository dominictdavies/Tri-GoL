#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("gets all neighbourhoods correctly", "[get_neighbourhood]") {
    std::bitset<CELL_COUNT> is_alive;

    bool is_up_triangle = (MIDDLE_ROW + MIDDLE_COL) & 1;
    unsigned left_col = is_up_triangle ? MIDDLE_COL + 1 : MIDDLE_COL - 1;
    unsigned right_col = is_up_triangle ? MIDDLE_COL - 1 : MIDDLE_COL + 1;
    unsigned down_row = is_up_triangle ? MIDDLE_ROW + 1 : MIDDLE_ROW - 1;

    SECTION("dead-empty neighbourhood is 0") {
        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 0);
    }

    SECTION("dead-left neighbourhood is 1") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 1);
    }

    SECTION("dead-right neighbourhood is 2") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 2);
    }

    SECTION("dead-down neighbourhood is 3") {
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 3);
    }

    SECTION("dead-left-right neighbourhood is 4") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 4);
    }

    SECTION("dead-left-down neighbourhood is 5") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 5);
    }

    SECTION("dead-right-down neighbourhood is 6") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 6);
    }

    SECTION("dead-full neighbourhood is 7") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 7);
    }

    SECTION("live-empty neighbourhood is 8") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 8);
    }

    SECTION("live-left neighbourhood is 9") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 9);
    }

    SECTION("live-right neighbourhood is 10") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 10);
    }

    SECTION("live-down neighbourhood is 11") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 11);
    }

    SECTION("live-left-right neighbourhood is 12") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 12);
    }

    SECTION("live-left-down neighbourhood is 13") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 13);
    }

    SECTION("live-right-down neighbourhood is 14") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 14);
    }

    SECTION("live-full neighbourhood is 15") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL) == 15);
    }
}

void test_rule_execution(const std::bitset<CELL_COUNT> &initial, uint16_t rule,
                         const std::bitset<CELL_COUNT> &expected) {
    auto result = execute_rule(initial, rule);
    REQUIRE(result == expected);
}

void test_extreme_rule_execution(bool is_extinction_rule) {
    std::bitset<CELL_COUNT> initial;
    std::bitset<CELL_COUNT> expected;
    uint16_t rule = is_extinction_rule ? 0 : 65535;

    if (!is_extinction_rule) {
        expected.flip();
    }

    SECTION(is_extinction_rule ? "empty remains empty" : "empty becomes full") {
        test_rule_execution(initial, rule, expected);
    }

    SECTION(is_extinction_rule ? "full becomes empty" : "full remains full") {
        initial.flip();
        test_rule_execution(initial, rule, expected);
    }

    SECTION(is_extinction_rule ? "populated becomes empty"
                               : "populated becomes full") {
        for (unsigned row = 0; row < ROW_COUNT; row++) {
            for (unsigned col = 0; col < COL_COUNT; col++) {
                if ((row + col) % 3 == 0) {
                    initial.set(row * COL_COUNT + col);
                }
            }
        }

        test_rule_execution(initial, rule, expected);
    }
}

TEST_CASE("executes extinction rule correctly", "[execute_rule]") {
    test_extreme_rule_execution(/* is_extinction_rule= */ true);
}

TEST_CASE("executes saturation rule correctly", "[execute_rule]") {
    test_extreme_rule_execution(/* is_extinction_rule= */ false);
}

std::bitset<CELL_COUNT> get_test_pattern() {
    // clang-format off
    const char *rows[] = {
        "00001000001000010",
        "00000000101001000",
        "00101110010011101",
        "10100011100110110",
        "01001100011001010",
        "00010001101101010",
        "00111111010111111",
        "11100111110111110"
    };
    // clang-format on

    constexpr unsigned test_row_count = 8;
    constexpr unsigned test_col_count = 17;

    std::bitset<CELL_COUNT> test_pattern;
    for (unsigned row = 0; row < test_row_count; row++) {
        for (unsigned col = 0; col < test_col_count; col++) {
            if (rows[row][col] == '1') {
                test_pattern.set(row * COL_COUNT + col);
            }
        }
    }

    return test_pattern;
}
