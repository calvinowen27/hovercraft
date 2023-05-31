#define SDL_MAIN_HANDLED

#include "../include/SDL2/SDL.h"
#include <iostream>

using namespace std;

const int WIDTH = 800, HEIGHT = 600;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    
    if (window == NULL) {
        cout << "Could not create window: " << SDL_GetError() << endl;
        // SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Event windowEvent;

    while(true)
    {
        if(SDL_PollEvent(&windowEvent))
        {
            if(windowEvent.type == SDL_QUIT)
            {
                break;
            }
        }
    }

    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // if (!renderer) {
    //     SDL_Log("Failed to create renderer: %s", SDL_GetError());
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return 1;
    // }

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderClear(renderer);
    // SDL_RenderPresent(renderer);

    // SDL_Delay(2000);  // Delay for 2 seconds

    // SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}