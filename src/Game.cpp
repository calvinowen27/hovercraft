#define SDL_MAIN_HANDLED

#include "../include/game/Game.h"
#include <thread>
#include <chrono>

using namespace std;

bool Game::initialized = false;
Game* Game::instance = nullptr;

int main()
{
    Game game;
    // Game::instance = nullptr;
    // Game::initialized = false;
    // Game::instance = new Game();
    if(Game::instance->gameInit()) return EXIT_FAILURE;

    Game::instance->go();

    return 0;
}

Game::Game()
{
    if(instance == nullptr)
    {
        instance = this;
    }
    // instance = this;
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

    Object::setGame(instance);

    return 0;
}

void Game::go()
{
    // Object obj("./content/smiley.png", Vector2(0, 0), Vector2(1, 1));

    // Player player;
    // player = Player();

    thread updateThread([this]() {update();});

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

        // update();
        draw();
    }

    updateThread.join();

    // SDL_DestroyRenderer(instance->renderer);
    // SDL_DestroyWindow(instance->window);
    IMG_Quit();
    SDL_Quit();
}

void Game::update()
{
    float time = 0.02;

    Player player;

    while(running)
    {
        // obj.update();
        // for(list<Object>::iterator it = instance->objs.begin(); it != instance->objs.end(); it++)
        // {
        //     (*it).update(time);
        // }

        player.update(time);

        this_thread::sleep_for(chrono::milliseconds((int)(time * 1000)));
    }
}

void Game::draw()
{
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // obj.draw();
    for(list<Object>::iterator it = objs.begin(); it != objs.end(); it++)
    {
        (*it).draw();
    }

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