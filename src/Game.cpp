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
    // if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
    // {
    //     cerr << "Error with SDL initialization: " << SDL_GetError() << endl;
    //     return EXIT_FAILURE;
    // }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        cerr << "Error with SDL_image initialization: " << IMG_GetError() << endl;
        return EXIT_FAILURE;
    }

    TTF_Init();

    // if(!TTF_Init())
    // {
    //     cerr << "Error with SDL_ttf initialization: " << TTF_GetError() << endl;
    //     return EXIT_FAILURE;
    // }

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
    thread updateThread([this]{update();});

    SDL_Event event;

    while(running)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || keyboardHandler.isPressed(keyControls["close"]))
            {
                running = false;
            }
        }
        draw();
    }

    updateThread.join();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::update()
{
    using namespace chrono;
    float timeMult = 1 / (float)UPDATES_PER_SEC;

    chrono::_V2::system_clock::time_point startTime;
    milliseconds timeDiff(1000 / UPDATES_PER_SEC);
    milliseconds execTime;
    milliseconds sleepTime;

    while(instance->running)
    {
        startTime = high_resolution_clock::now();
        // obj.update();
        for(Object *obj : instance->objs)
        {
            obj->update(timeMult);
        }

        execTime = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);

        sleepTime = timeDiff - execTime;
        this_thread::sleep_for(sleepTime);
    }

    // ups = 1000 / sleepTime.count();
}

void Game::draw()
{
    using namespace chrono;

    auto startTime = high_resolution_clock::now();

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // obj.draw();
    for(Object *obj : objs)
    {
        obj->draw();
    }

    auto execTime = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);

    // lock_guard<mutex> guard(mutex_);
    // fps = 1000 / execTime.count();

    // draw fps and ups
    // TTF_Font* arial = TTF_OpenFont("./content/arial.ttf", 24);
    // SDL_Color white = {255, 255, 255, 255};
    // SDL_Surface* fpsSurface = TTF_RenderText_Solid(arial, to_string(fps).c_str(), white);
    // SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderer, fpsSurface);
    // SDL_Surface* upsSurface = TTF_RenderText_Solid(arial, to_string(ups).c_str(), white);
    // SDL_Texture* upsTexture = SDL_CreateTextureFromSurface(renderer, upsSurface);

    // SDL_RenderCopy(renderer, fpsTexture, NULL, new SDL_Rect{0, 0, 100, 100});
    // SDL_RenderCopy(renderer, upsTexture, NULL, new SDL_Rect{0, 100, 100, 100});

    SDL_RenderPresent(renderer);

    // SDL_FreeSurface(fpsSurface);
    // SDL_FreeSurface(upsSurface);
    // SDL_DestroyTexture(fpsTexture);
    // SDL_DestroyTexture(upsTexture);
    // TTF_CloseFont(arial);
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