#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <numbers>

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

// Configuration
constexpr unsigned WINDOW_WIDTH = 840;
constexpr unsigned WINDOW_HEIGHT = 840;
constexpr unsigned FPS = 60;
constexpr unsigned ROW_COUNT = 60;
constexpr bool DRAW_GRID = true;

// Derived
constexpr unsigned FRAME_DELAY = 1e9 / FPS;
constexpr double ROW_HEIGHT = WINDOW_HEIGHT / ROW_COUNT;
constexpr double COLUMN_WIDTH = 2 * ROW_HEIGHT / std::numbers::sqrt3;
constexpr double DIAGONAL_LINE_TRAVEL_X = COLUMN_WIDTH / 2 * ROW_COUNT;

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

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

void draw_grid() {
    // Use opaque grey colour
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, SDL_ALPHA_OPAQUE);

    // Draw horizontal lines
    for (double y = ROW_HEIGHT; y < WINDOW_HEIGHT; y += ROW_HEIGHT) {
        SDL_RenderLine(renderer, 0, y, WINDOW_WIDTH, y);
    }

    // Draw diagonal lines
    for (double x = -DIAGONAL_LINE_TRAVEL_X;
         x < WINDOW_WIDTH + DIAGONAL_LINE_TRAVEL_X; x += COLUMN_WIDTH) {
        SDL_RenderLine(renderer, x, 0, x - DIAGONAL_LINE_TRAVEL_X,
                       WINDOW_HEIGHT);
        SDL_RenderLine(renderer, x, 0, x + DIAGONAL_LINE_TRAVEL_X,
                       WINDOW_HEIGHT);
    }
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    // Start with a black canvas
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    if (DRAW_GRID) {
        draw_grid();
    }

    // Put everything onto the screen
    SDL_RenderPresent(renderer);

    // Wait before next frame
    SDL_DelayPrecise(FRAME_DELAY);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    // SDL will clean up the window/renderer
}
