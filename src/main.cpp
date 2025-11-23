#define SDL_MAIN_USE_CALLBACKS 1
#include "utils.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Globals
static std::bitset<CELL_COUNT> is_alive;
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

void initialise_game_state() {
    for (unsigned row = 0; row < ROW_COUNT; row++) {
        for (unsigned col = 0; col < COL_COUNT; col++) {
            unsigned index = row * COL_COUNT + col;
            if (index % 3 == 0) {
                is_alive.set(index);
            }
        }
    }
}

void render_triangle(unsigned row, unsigned col) {
    // Increment row to correct origin for up-triangles
    bool is_up_triangle = check_is_up_triangle(row, col);
    if (is_up_triangle) {
        row += 1;
    }

    // Use leftmost corner as positional origin
    float origin_x = col * ((float)COL_WIDTH / 2);
    float origin_y = row * (float)ROW_HEIGHT;

    // Set vertex positions
    SDL_Vertex vertices[3];
    SDL_zeroa(vertices);
    vertices[0].position = {origin_x, origin_y};
    vertices[1].position = {origin_x + (float)COL_WIDTH, origin_y};
    vertices[2].position = {
        origin_x + ((float)COL_WIDTH / 2),
        origin_y + (is_up_triangle ? -(float)ROW_HEIGHT : (float)ROW_HEIGHT)};

    // Set triangle colour to white
    vertices[0].color = {1.0f, 1.0f, 1.0f};
    vertices[1].color = {1.0f, 1.0f, 1.0f};
    vertices[2].color = {1.0f, 1.0f, 1.0f};

    // Render the triangle
    SDL_RenderGeometry(renderer, nullptr, vertices, 3, nullptr, 0);
}

void render_grid() {
    // Use opaque grey colour
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, SDL_ALPHA_OPAQUE);

    // Render horizontal lines
    for (double y = ROW_HEIGHT; y < WINDOW_HEIGHT; y += ROW_HEIGHT) {
        SDL_RenderLine(renderer, 0, y, WINDOW_WIDTH, y);
    }

    // Render diagonal lines
    for (double x = -DIAGONAL_LINE_X; x < WINDOW_WIDTH + DIAGONAL_LINE_X;
         x += COL_WIDTH) {
        SDL_RenderLine(renderer, x, 0, x - DIAGONAL_LINE_X, WINDOW_HEIGHT);
        SDL_RenderLine(renderer, x, 0, x + DIAGONAL_LINE_X, WINDOW_HEIGHT);
    }
}

void render_frame() {
    // Start with a black canvas
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render the triangles
    for (unsigned row = 0; row < ROW_COUNT; row++) {
        for (unsigned col = 0; col < COL_COUNT; col++) {
            size_t index = row * COL_COUNT + col;
            if (is_alive[index]) {
                render_triangle(row, col);
            }
        }
    }

    // Optionally render the grid
    if (SHOW_GRID) {
        render_grid();
    }

    // Present everything on the screen
    SDL_RenderPresent(renderer);

    // Wait before the next frame
    SDL_DelayPrecise(FRAME_DELAY);
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Tri-GoL", "0.1", "dev.dominictdavies.trigol");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialise SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Tri-GoL", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                     &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);

    initialise_game_state();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    render_frame();
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    // SDL will clean up the window/renderer
}
