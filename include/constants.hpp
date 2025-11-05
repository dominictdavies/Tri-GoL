#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <numbers>

// Configuration
constexpr unsigned WINDOW_WIDTH = 840;
constexpr unsigned WINDOW_HEIGHT = 840;
constexpr unsigned FPS = 60;
constexpr unsigned ROW_COUNT = 60;
constexpr bool SHOW_GRID = true; // TODO: Not working with odd row counts

// Derived
constexpr unsigned FRAME_DELAY = 1e9 / FPS;
constexpr double ROW_HEIGHT = static_cast<double>(WINDOW_HEIGHT) / ROW_COUNT;
constexpr double COL_WIDTH = 2 * ROW_HEIGHT / std::numbers::sqrt3;
constexpr unsigned COL_COUNT = WINDOW_WIDTH / (COL_WIDTH / 2);
constexpr unsigned CELL_COUNT = ROW_COUNT * COL_COUNT;
constexpr unsigned MIDDLE_ROW = (ROW_COUNT / 2) - 1;
constexpr unsigned MIDDLE_COL = (COL_COUNT / 2) - 1;
constexpr double DIAGONAL_LINE_X = COL_WIDTH / 2 * ROW_COUNT;

#endif
