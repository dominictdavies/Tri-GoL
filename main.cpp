#include <SDL2/SDL.h>
#include <iostream>

// Configuration
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 1280;
const int FPS = 60;

// Derived
const int FRAME_DELAY = 1000 / FPS;

struct SDLContext {
    SDL_Window *window;
    SDL_Surface *surface;
};

SDLContext setupSDL() {
    // Pointers to our window and surface
    SDL_Surface *winSurface = NULL;
    SDL_Window *window = NULL;

    // Initialize SDL, SDL_Init will return -1 if it fails
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create our window
    window = SDL_CreateWindow("Tri-GoL", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Make sure creating the window succeeded
    if (!window) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get the surface from the window
    winSurface = SDL_GetWindowSurface(window);

    // Make sure getting the surface succeeded
    if (!winSurface) {
        std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    return {window, winSurface};
}

int main() {
    auto sdl = setupSDL();

    SDL_Event event;
    bool running = true;

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            }
        }

        // Fill the window with a coloured rectangle
        SDL_FillRect(sdl.surface, NULL,
                     SDL_MapRGB(sdl.surface->format, 0, 0, 0));

        // Update the window display
        SDL_UpdateWindowSurface(sdl.window);

        // Wait before next frame
        SDL_Delay(FRAME_DELAY);
    }

    // Destroy the window, also destroys the surface
    SDL_DestroyWindow(sdl.window);

    // Quit SDL
    SDL_Quit();

    // End the program
    return EXIT_SUCCESS;
}
