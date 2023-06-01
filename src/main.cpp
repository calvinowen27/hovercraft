#define SDL_MAIN_HANDLED

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include <iostream>
#include "KeyboardHandler.h"

using namespace std;

const int WIDTH = 800, HEIGHT = 600;
KeyboardHandler keyboardHandler;

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if(!IMG_Init(IMG_INIT_PNG))
    {
        cout << "error img initialization: " << IMG_GetError() << endl;
    }

    SDL_Window* window = SDL_CreateWindow("hovercraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    
    if (window == NULL)
    {
        cout << "Could not create window: " << SDL_GetError() << endl;
        // SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* spriteSurface = IMG_Load("./content/smiley.png");
    if(spriteSurface == NULL)
    {
        cout << "surface null: " << IMG_GetError() << endl;
        return 1;
    }
    SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
    if(spriteTexture == NULL)
    {
        cout << "texture null: " << IMG_GetError() << endl;
        return 1;
    }
    SDL_FreeSurface(spriteSurface);
    SDL_Rect spriteRect;
    spriteRect.x = 100;
    spriteRect.y = 100;
    spriteRect.w = 100;
    spriteRect.h = 100;

    int r = 0, g = 0, b = 0;

    SDL_Event event;

    while(true)
    {
        SDL_RenderClear(renderer);
        
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                break;
            }

            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_r)
                {
                    r++;
                }

                if(keyboardHandler.isPressed(SDL_SCANCODE_W))
                {
                    spriteRect.y--;
                }

                if(keyboardHandler.isPressed(SDL_SCANCODE_A))
                {
                    spriteRect.x--;
                }
            }

            if(event.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&g, &b);
            }
        }

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);

        SDL_RenderCopy(renderer, spriteTexture, NULL, &spriteRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}