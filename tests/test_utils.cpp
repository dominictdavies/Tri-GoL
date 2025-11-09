#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>
#include <limits>

TEST_CASE("gets all neighbourhoods correctly", "[get_neighbourhood]") {
    std::bitset<CELL_COUNT> is_alive;

    bool is_up_triangle = (MIDDLE_ROW + MIDDLE_COL) & 1;
    unsigned left_col = is_up_triangle ? MIDDLE_COL - 1 : MIDDLE_COL + 1;
    unsigned right_col = is_up_triangle ? MIDDLE_COL + 1 : MIDDLE_COL - 1;
    unsigned down_row = is_up_triangle ? MIDDLE_ROW + 1 : MIDDLE_ROW - 1;

    SECTION("dead-empty neighbourhood is 0") {
        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 0);
    }

    SECTION("dead-left neighbourhood is 1") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 1);
    }

    SECTION("dead-right neighbourhood is 2") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 2);
    }

    SECTION("dead-down neighbourhood is 3") {
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 3);
    }

    SECTION("dead-left-right neighbourhood is 4") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 4);
    }

    SECTION("dead-left-down neighbourhood is 5") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 5);
    }

    SECTION("dead-right-down neighbourhood is 6") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 6);
    }

    SECTION("dead-full neighbourhood is 7") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 7);
    }

    SECTION("live-empty neighbourhood is 8") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 8);
    }

    SECTION("live-left neighbourhood is 9") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 9);
    }

    SECTION("live-right neighbourhood is 10") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 10);
    }

    SECTION("live-down neighbourhood is 11") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 11);
    }

    SECTION("live-left-right neighbourhood is 12") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 12);
    }

    SECTION("live-left-down neighbourhood is 13") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 13);
    }

    SECTION("live-right-down neighbourhood is 14") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 14);
    }

    SECTION("live-full neighbourhood is 15") {
        is_alive.set(MIDDLE_ROW * COL_COUNT + MIDDLE_COL);
        is_alive.set(MIDDLE_ROW * COL_COUNT + left_col);
        is_alive.set(MIDDLE_ROW * COL_COUNT + right_col);
        is_alive.set(down_row * COL_COUNT + MIDDLE_COL);

        REQUIRE(static_cast<unsigned>(
                    get_neighbourhood(is_alive, MIDDLE_ROW, MIDDLE_COL)) == 15);
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
    uint16_t rule = is_extinction_rule ? std::numeric_limits<uint16_t>::min()
                                       : std::numeric_limits<uint16_t>::max();

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

void test_pattern_rule_execution(uint16_t rule) {
    // clang-format off
    const std::pair<unsigned, unsigned> test_cells[] = {
        {0, 1}, {1, 3},
        {0, 5}, {1, 7},
        {0, 9}, {1, 11},
        {0, 13}, {1, 15},
        {2, 3}, {3, 1},
        {2, 7}, {3, 5},
        {2, 11}, {3, 9},
        {2, 15}, {3, 13},
        {4, 1}, {5, 3},
        {4, 5}, {5, 7},
        {4, 9}, {5, 11},
        {4, 13}, {5, 15},
        {6, 3}, {7, 1},
        {6, 7}, {7, 5},
        {6, 11}, {7, 9},
        {6, 15}, {7, 13},
    };
    // clang-format on

    std::bitset<CELL_COUNT> initial = get_test_pattern();
    auto result = execute_rule(initial, rule);

    unsigned test_index = 0;
    unsigned position = 1;
    while (position < std::numeric_limits<uint16_t>::max()) {
        bool expected_alive = (rule & position) != 0;
        auto cell = test_cells[test_index];

        REQUIRE(result[cell.first * COL_COUNT + cell.second] == expected_alive);

        test_index += 1;
        if (test_index % 2 == 0) {
            position *= 2;
        }
    }
}

TEST_CASE("executes all neighbourhood rules correctly", "[execute_rule]") {
    for (uint16_t rule = std::numeric_limits<uint16_t>::min();
         rule <= std::numeric_limits<uint16_t>::max(); rule++) {
        test_pattern_rule_execution(rule);
    }
}
