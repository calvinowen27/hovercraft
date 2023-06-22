#define SDL_MAIN_HANDLED

#include "../include/game/Game.h"
#include "../include/game/TextElement.h"
#include "../include/game/Object.h"
#include "../include/game/Player.h"
#include "../include/game/UIElement.h"
#include "../include/game/UIManager.h"
#include "../include/game/Path.h"

#include <thread>
#include <chrono>

using namespace std;

Game* Game::_pInstance;

int main()
{
    if(Game::getInstance()->gameInit()) return EXIT_FAILURE;

    Game::getInstance()->start();

    return 0;
}

Game::Game()
{
}

Game* Game::getInstance()
{
    if(_pInstance == nullptr)
    {
        _pInstance = new Game();
    }

    return _pInstance;
}

int Game::gameInit()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

    if(!IMG_Init(IMG_INIT_PNG))
    {
        cerr << "Error with SDL_image initialization: " << IMG_GetError() << endl;
        return EXIT_FAILURE;
    }

    TTF_Init();

    pWindow = SDL_CreateWindow("hovercraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                        winWidth, winHeight, SDL_WINDOW_ALLOW_HIGHDPI);

    // SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    
    if (pWindow == NULL)
    {
        cerr << "Could not create window: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (pRenderer == NULL)
    {
        cerr << "Failed to create renderer " << SDL_GetError() << endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    keybinds =
    {
        {"up", SDL_SCANCODE_W},
        {"down", SDL_SCANCODE_S},
        {"left", SDL_SCANCODE_A},
        {"right", SDL_SCANCODE_D},
        {"boost", SDL_SCANCODE_LSHIFT},
        {"close", SDL_SCANCODE_ESCAPE},
        {"reset", SDL_SCANCODE_R}
    };

    pContentManager = new ContentManager();
    pContentManager->loadContent();

    pUIManager = UIManager::getInstance();
    pUIManager->init();

    pPlayer = new Player(Vector2(1, 1));

    Path *path = new Path(std::vector<Vector2>{Vector2::zero, Vector2(3, 0), Vector2(4, 0.5)});

    return 0;
}

void Game::start()
{
    thread updateThread([this]{runPhysics();});

    while(_pInstance->running)
    {
        frameUpdate();
    }

    updateThread.join();

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::runPhysics()
{
    while(_pInstance->running)
    {
        physicsUpdate();
    }
}

void Game::frameUpdate()
{
    using namespace chrono;
    float frameTime = 1 / (float)TARGET_FPS;
    chrono::_V2::system_clock::time_point startTime;
    nanoseconds timeDiff((int)(frameTime * 1000000000));
    nanoseconds execTime;
    nanoseconds sleepTime;

    startTime = high_resolution_clock::now();

    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT || keyboardHandler.isPressed(keybinds["close"]))
        {
            running = false;
        }

        if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            inputEvents.push(event);
        }
    }

    pUIManager->update();

    draw();

    execTime = duration_cast<nanoseconds>(high_resolution_clock::now() - startTime);

    // sleep for any extra time we have in the update
    sleepTime = timeDiff - execTime;

    lock_guard<mutex> guard(mutex_);

    _fps = 1000000000 / (sleepTime.count() > 0 ? timeDiff.count() : execTime.count());

    if(sleepTime.count() > 0) this_thread::sleep_for(sleepTime);
}

void Game::physicsUpdate()
{
    using namespace chrono;
    float updateTime = 1 / (float)UPDATES_PER_SEC; // seconds

    chrono::_V2::system_clock::time_point startTime;
    nanoseconds timeDiff((int)(updateTime * 1000000000)); // convert updateTime to nanoseconds
    nanoseconds execTime;
    nanoseconds sleepTime;

    startTime = high_resolution_clock::now();

    // obj.update();
    for(Object *obj : _pInstance->objs)
    {
        obj->update(updateTime);
    }

    execTime = duration_cast<nanoseconds>(high_resolution_clock::now() - startTime);

    // sleep for any extra time we have in the update
    sleepTime = timeDiff - execTime;

    lock_guard<mutex> guard(mutex_);

    _ups = 1000000000 / (sleepTime.count() > 0 ? timeDiff.count() : execTime.count());

    if(sleepTime.count() > 0) this_thread::sleep_for(sleepTime);
}

void Game::draw()
{
    SDL_RenderClear(pRenderer);

    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);

    pUIManager->draw(pRenderer);

    // obj.draw();
    for(Object *obj : objs)
    {
        obj->draw(pRenderer);
    }

    for(Path *path : paths)
    {
        path->draw(pRenderer);
    }

    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);

    SDL_RenderPresent(pRenderer);
}

Vector2 Game::pixelToWorld(Vector2Int pxPos)
{
    pxPos -= Vector2Int(winWidth / 2, winHeight / 2);
    pxPos.y -= winHeight;
    pxPos /= ppm;
    return (Vector2)pxPos + cameraPos;
}

Vector2Int Game::worldToPixel(Vector2 pos)
{
    pos -= cameraPos;
    pos *= ppm;
    pos.y = winHeight - pos.y;
    return (Vector2Int)pos + Vector2Int(winWidth / 2, -winHeight / 2);
}