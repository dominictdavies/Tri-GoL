#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <numbers>

// Configuration
constexpr unsigned FPS = 60;
constexpr unsigned ROW_COUNT = 60;
constexpr unsigned COL_COUNT = 120;
constexpr double COL_WIDTH = 16.0;
constexpr bool SHOW_GRID = true; // TODO: Not working with odd row counts

// Derived
constexpr unsigned FRAME_DELAY = 1e9 / FPS;
constexpr unsigned CELL_COUNT = ROW_COUNT * COL_COUNT;
constexpr double ROW_HEIGHT = COL_WIDTH * std::numbers::sqrt3 / 2;
constexpr unsigned RENDER_WIDTH = (COL_WIDTH / 2) * (COL_COUNT + 1);
constexpr unsigned RENDER_HEIGHT = ROW_HEIGHT * ROW_COUNT;
constexpr unsigned MIDDLE_ROW = (ROW_COUNT / 2) - 1;
constexpr unsigned MIDDLE_COL = (COL_COUNT / 2) - 1;
constexpr double DIAGONAL_LINE_X = COL_WIDTH / 2 * ROW_COUNT;

#endif
