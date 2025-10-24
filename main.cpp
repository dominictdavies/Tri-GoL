#include <SDL3/SDL.h>
#include <iostream>

// Configuration
const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 840;
const int FPS = 60;

// Derived
const int FRAME_DELAY = 1000 / FPS;

struct SDLContext {
    SDL_Window *window;
    SDL_Surface *surface;
};

SDLContext setupSDL() {
    // Pointers to our window and surface
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;

    // Initialize SDL, SDL_Init will return false if it fails
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create our window
    window = SDL_CreateWindow("Tri-GoL", WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // Make sure creating the window succeeded
    if (!window) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get the surface from the window
    surface = SDL_GetWindowSurface(window);

    // Make sure getting the surface succeeded
    if (!surface) {
        std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    return {window, surface};
}

void closeSDL(SDLContext sdl) {
    // Destroy the window, also destroys the surface
    SDL_DestroyWindow(sdl.window);

    // Quit SDL
    SDL_Quit();
}

int main() {
    auto sdl = setupSDL();

    SDL_Event event;
    bool running = true;

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            }
        }

        // Fill the window with a colour
        SDL_FillSurfaceRect(sdl.surface, NULL,
                            SDL_MapSurfaceRGB(sdl.surface, 0, 0, 0));

        // Update the window display
        SDL_UpdateWindowSurface(sdl.window);

        // Wait before next frame
        SDL_Delay(FRAME_DELAY);
    }

    closeSDL(sdl);

    return EXIT_SUCCESS;
}
