#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <bitset>
#include <numbers>

// Configuration
constexpr unsigned WINDOW_WIDTH = 840;
constexpr unsigned WINDOW_HEIGHT = 840;
constexpr unsigned FPS = 60;
constexpr unsigned ROW_COUNT = 60;
constexpr bool DRAW_GRID = true;

// Derived
constexpr unsigned FRAME_DELAY = 1e9 / FPS;
constexpr double ROW_HEIGHT = static_cast<double>(WINDOW_HEIGHT) / ROW_COUNT;
constexpr double COLUMN_WIDTH = 2 * ROW_HEIGHT / std::numbers::sqrt3;
constexpr unsigned COLUMN_COUNT = WINDOW_WIDTH / (COLUMN_WIDTH / 2);
constexpr double DIAGONAL_LINE_TRAVEL_X = COLUMN_WIDTH / 2 * ROW_COUNT;

static std::bitset<ROW_COUNT * COLUMN_COUNT> is_alive;
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

void initialise_game_state() {
    unsigned middle_row = (ROW_COUNT / 2) - 1;
    unsigned middle_column = (COLUMN_COUNT / 2) - 1;
    size_t index = middle_row * COLUMN_COUNT + middle_column;
    is_alive[index] = true;
}

void draw_triangle(unsigned row, unsigned column) {
    // Increment row to correct origin for up-triangles
    bool is_up_triangle = (row + column) & 1;
    if (is_up_triangle) {
        row += 1;
    }

    // Use leftmost corner as positional origin
    float origin_x = column * ((float)COLUMN_WIDTH / 2);
    float origin_y = row * (float)ROW_HEIGHT;

    // Set vertex positions
    SDL_Vertex vertices[3];
    SDL_zeroa(vertices);
    vertices[0].position = {origin_x, origin_y};
    vertices[1].position = {origin_x + (float)COLUMN_WIDTH, origin_y};
    vertices[2].position = {
        origin_x + ((float)COLUMN_WIDTH / 2),
        origin_y + (is_up_triangle ? -(float)ROW_HEIGHT : (float)ROW_HEIGHT)};

    // Set triangle colour to white
    vertices[0].color = {1.0f, 1.0f, 1.0f};
    vertices[1].color = {1.0f, 1.0f, 1.0f};
    vertices[2].color = {1.0f, 1.0f, 1.0f};

    // Render the triangle
    SDL_RenderGeometry(renderer, nullptr, vertices, 3, nullptr, 0);
}

void draw_game() {
    for (unsigned row = 0; row < ROW_COUNT; row++) {
        for (unsigned column = 0; column < COLUMN_COUNT; column++) {
            size_t index = row * COLUMN_COUNT + column;
            if (is_alive[index]) {
                draw_triangle(row, column);
            }
        }
    }
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
    // Start with a black canvas
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    draw_game();
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
