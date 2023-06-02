#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>
#include <map>

#include "../include/game/Game.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/game/KeyboardHandler.h"
#include "../include/game/Vector2.h"
#include "../include/game/Object.h"
#include "../include/game/Game.h"

using namespace std;

KeyboardHandler keyboardHandler;
map<string, SDL_Scancode> keyControls = {
    {"up", SDL_SCANCODE_W},
    {"down", SDL_SCANCODE_S},
    {"left", SDL_SCANCODE_A},
    {"right", SDL_SCANCODE_D},
    {"close", SDL_SCANCODE_ESCAPE}
};

Object obj("../content/smiley.png", Vector2(0, 0), Vector2(1, 1));

int main()
{
    if(Game::instance.gameInit()) return EXIT_FAILURE;

    Game::instance.go();

    return 0;
}

Game::Game()
{
}

int Game::gameInit()
{
    if(!initialized)
    {
        instance = *this;
        initialized = true;
    }

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

    return 0;
}

void Game::go()
{
    while(running)
    {
        update();
        draw();
    }

    SDL_DestroyRenderer(instance.renderer);
    SDL_DestroyWindow(instance.window);
    IMG_Quit();
    SDL_Quit();
}

void Game::update()
{
    SDL_Event event;

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
            return;
        }

        // if(keyboardHandler.isPressed(keyControls["up"]))
        // {
        //     spriteRect.y--;
        // }
        // if(keyboardHandler.isPressed(keyControls["down"]))
        // {
        //     spriteRect.y++;
        // }

        // if(keyboardHandler.isPressed(keyControls["left"]))
        // {
        //     spriteRect.x--;
        // }
        // if(keyboardHandler.isPressed(keyControls["right"]))
        // {
        //     spriteRect.x++;
        // }
    }
}

void Game::draw()
{
    SDL_RenderClear(renderer);

    obj.draw();

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    SDL_RenderPresent(renderer);
}

Vector2 Game::pixelToWorld(Vector2Int px_pos)
{
    px_pos -= Vector2Int(winWidth / 2, winHeight / 2);
    px_pos /= ppm;
    return (Vector2)px_pos - cameraPos;
}

Vector2Int Game::worldToPixel(Vector2 pos)
{
    pos += cameraPos;
    pos *= ppm;
    return (Vector2Int)pos + Vector2Int(winWidth / 2, winHeight / 2);
}