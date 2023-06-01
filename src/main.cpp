#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>
#include <map>

#include "../include/game/Game.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/game/KeyboardHandler.h"
#include "../include/game/Vector2.h"

using namespace std;

KeyboardHandler keyboardHandler;
map<string, SDL_Scancode> keyControls = {
    {"up", SDL_SCANCODE_W},
    {"down", SDL_SCANCODE_S},
    {"left", SDL_SCANCODE_A},
    {"right", SDL_SCANCODE_D},
    {"close", SDL_SCANCODE_ESCAPE}
};

int main()
{
    if(!SDL_Init(SDL_INIT_EVERYTHING))
    {
        cerr << "Error with SDL initialization: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        cerr << "Error with SDL_image initialization: " << IMG_GetError() << endl;
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("hovercraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                        winWidth, winHeight, SDL_WINDOW_ALLOW_HIGHDPI);
    
    if (window == NULL)
    {
        cerr << "Could not create window: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cerr << "Failed to create renderer " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
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
            // may want to use this for checking keypressed later when adding ability to change controls
            // if(event.type == SDL_KEYDOWN)
            // {
            //     pseudo
            //     keyControls[whatever control is being changed] = detected scancode            
            // }

            if(event.type == SDL_QUIT || keyboardHandler.isPressed(keyControls["close"]))
            {
                break;
            }

            if(keyboardHandler.isPressed(keyControls["up"]))
            {
                spriteRect.y--;
            }
            if(keyboardHandler.isPressed(keyControls["down"]))
            {
                spriteRect.y++;
            }

            if(keyboardHandler.isPressed(keyControls["left"]))
            {
                spriteRect.x--;
            }
            if(keyboardHandler.isPressed(keyControls["right"]))
            {
                spriteRect.x++;
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