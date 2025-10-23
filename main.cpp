#include <SDL2/SDL.h>
#include <iostream>

// Configuration
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 1280;
const int FPS = 60;

// Derived
const int FRAME_DELAY = 1000 / FPS;

int main() {
    // Pointers to our window and surface
    SDL_Surface *winSurface = NULL;
    SDL_Window *window = NULL;

    // Initialize SDL, SDL_Init will return -1 if it fails
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create our window
    window = SDL_CreateWindow("Tri-GoL", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Make sure creating the window succeeded
    if (!window) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Get the surface from the window
    winSurface = SDL_GetWindowSurface(window);

    // Make sure getting the surface succeeded
    if (!winSurface) {
        std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event event;
    bool running = true;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    bool will_brighten = true;

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
        SDL_FillRect(winSurface, NULL,
                     SDL_MapRGB(winSurface->format, red, green, blue));

        // Update the window display
        SDL_UpdateWindowSurface(window);

        // Adjust colour values
        if (will_brighten) {
            if (red < 255) {
                red += 1;
            } else if (green < 255) {
                green += 1;
            } else if (blue < 255) {
                blue += 1;
            } else {
                will_brighten = false;
            }
        } else {
            if (red > 0) {
                red -= 1;
            } else if (green > 0) {
                green -= 1;
            } else if (blue > 0) {
                blue -= 1;
            } else {
                will_brighten = true;
            }
        }

        // Wait before next frame
        SDL_Delay(FRAME_DELAY);
    }

    // Destroy the window, also destroys the surface
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    // End the program
    return 0;
}
