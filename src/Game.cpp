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

    float ddpi, hdpi, vdpi;
    SDL_GetDisplayDPI(0, &ddpi, &hdpi, &vdpi);
    winWidth *= hdpi / 96.f;
    winHeight *= vdpi / 96.f;
    ppm *= ddpi / 96.f;

    Uint64 windowFlags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;

    pWindow = SDL_CreateWindow("hovercraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                        winWidth, winHeight, windowFlags);

    // SDL_DisplayMode DM;
    // SDL_GetCurrentDisplayMode(0, &DM);
    // winWidth = DM.w;
    // winHeight = DM.h;

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

    pKeyboardHandler = new KeyboardHandler();

    pContentManager = new ContentManager();
    pContentManager->loadContent();

    pUIManager = UIManager::getInstance();
    pUIManager->init();

    pPlayer = new Player(Vector2(0, 1));

    new Object("blueblock.png", Vector2(2, 1), Vector2(0.5, 0.5));

    Path *path = new Path();

    for(float x = -15; x < 15; x += 0.125)
    {
        path->addPoint(Vector2(x, SDL_sinf(x)));
    }

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
    chrono::system_clock::time_point startTime;
    nanoseconds timeDiff((int)(frameTime * 1000000000));
    nanoseconds execTime;
    nanoseconds sleepTime;

    startTime = high_resolution_clock::now();

    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT || pKeyboardHandler->getInputState(ACTION_CLOSE))
        {
            running = false;
        }

        if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            pKeyboardHandler->pushEvent(event);
        }

        if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            SDL_Window *win = SDL_GetWindowFromID(event.window.windowID);
            if(win == pWindow)
            {
                SDL_GetWindowSize(win, &winWidth, &winHeight);
            }
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

    chrono::system_clock::time_point startTime;
    nanoseconds timeDiff((int)(updateTime * 1000000000)); // convert updateTime to nanoseconds
    nanoseconds execTime;
    nanoseconds sleepTime;

    startTime = high_resolution_clock::now();

    pKeyboardHandler->processInputs();

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