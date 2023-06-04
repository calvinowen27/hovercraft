#define SDL_MAIN_HANDLED

#include "../include/game/Game.h"
#include <thread>
#include <chrono>

using namespace std;

Game* Game::instance = nullptr;

int main()
{
    if(Game::getInstance()->gameInit()) return EXIT_FAILURE;

    Game::getInstance()->go();

    return 0;
}

Game::Game()
{
}

Game* Game::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Game();
    }

    return instance;
}

int Game::gameInit()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

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

    keyControls =
    {
        {"up", SDL_SCANCODE_W},
        {"down", SDL_SCANCODE_S},
        {"left", SDL_SCANCODE_A},
        {"right", SDL_SCANCODE_D},
        {"close", SDL_SCANCODE_ESCAPE}
    };

    Player* player = new Player();
    // objs.push_back(player);

    Object* block1 = new Object("./content/blueblock.png", Vector2(1, 1), Vector2(0.25, 0.25));
    Object* block2 = new Object("./content/blueblock.png", Vector2(-2, -3), Vector2(1, 1));

    return 0;
}

void Game::go()
{
    while(running)
    {
        SDL_Event event;

        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || keyboardHandler.isPressed(keyControls["close"]))
            {
                running = false;
            }
        }

        update();
        draw();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Game::update()
{
    float time = 0.02;

    // obj.update();
    for(Object *obj : objs)
    {
        obj->update(time);
    }

    this_thread::sleep_for(chrono::milliseconds((int)(time * 1000)));
}

void Game::draw()
{
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // obj.draw();
    for(Object *obj : objs)
    {
        obj->draw();
    }

    SDL_RenderPresent(renderer);
}

Vector2 Game::pixelToWorld(Vector2Int px_pos)
{
    px_pos -= Vector2Int(winWidth / 2, winHeight / 2);
    px_pos.y -= winHeight;
    px_pos /= ppm;
    return (Vector2)px_pos + cameraPos;
}

Vector2Int Game::worldToPixel(Vector2 pos)
{
    pos -= cameraPos;
    pos *= ppm;
    pos.y = winHeight - pos.y;
    return (Vector2Int)pos + Vector2Int(winWidth / 2, -winHeight / 2);
}