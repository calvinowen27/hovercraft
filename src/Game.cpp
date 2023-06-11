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

    keybinds =
    {
        {"up", SDL_SCANCODE_W},
        {"down", SDL_SCANCODE_S},
        {"left", SDL_SCANCODE_A},
        {"right", SDL_SCANCODE_D},
        {"boost", SDL_SCANCODE_LSHIFT},
        {"close", SDL_SCANCODE_ESCAPE}
    };

    Player* player = new Player();
    // objs.push_back(player);

    Object* block1 = new Object("./content/blueblock.png", Vector2(1, 1), Vector2(1, 1));
    Object* block2 = new Object("./content/blueblock.png", Vector2(2, 1), Vector2(1, 1));
    Object* block3 = new Object("./content/blueblock.png", Vector2(3, 1), Vector2(1, 1));
    Object* block4 = new Object("./content/blueblock.png", Vector2(4, 1), Vector2(1, 1));
    Object* block5 = new Object("./content/blueblock.png", Vector2(5, 1), Vector2(1, 1));
    Object* block6 = new Object("./content/blueblock.png", Vector2(6, 1), Vector2(1, 1));

    return 0;
}

void Game::go()
{
    thread updateThread([this]{runUpdates();});

    while(instance->running)
    {
        frameUpdate();
    }

    updateThread.join();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::runUpdates()
{
    while(instance->running)
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

    draw();

    execTime = duration_cast<nanoseconds>(high_resolution_clock::now() - startTime);

    // sleep for any extra time we have in the update
    sleepTime = timeDiff - execTime;

    lock_guard<mutex> guard(mutex_);

    fps = 1000000000 / (sleepTime.count() > 0 ? timeDiff.count() : execTime.count());

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
    for(Object *obj : instance->objs)
    {
        obj->update(updateTime);
    }

    execTime = duration_cast<nanoseconds>(high_resolution_clock::now() - startTime);

    // sleep for any extra time we have in the update
    sleepTime = timeDiff - execTime;

    lock_guard<mutex> guard(mutex_);

    ups = 1000000000 / (sleepTime.count() > 0 ? timeDiff.count() : execTime.count());

    if(sleepTime.count() > 0) this_thread::sleep_for(sleepTime);
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

    // draw fps and ups
    int fpsW, fpsH, upsW, upsH;
    char fpsText[10];
    sprintf(fpsText, "FPS %d", fps);
    char upsText[10];
    sprintf(upsText, "UPS %d", ups);
    TTF_Font* arial = TTF_OpenFont("./content/arial.ttf", 24);
    TTF_SizeUTF8(arial, fpsText, &fpsW, &fpsH);
    TTF_SizeUTF8(arial, upsText, &upsW, &upsH);
    SDL_Color black = {0, 0, 0, 255};
    SDL_Surface* fpsSurface = TTF_RenderText_Solid(arial, fpsText, black);
    SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderer, fpsSurface);
    SDL_Surface* upsSurface = TTF_RenderText_Solid(arial, upsText, black);
    SDL_Texture* upsTexture = SDL_CreateTextureFromSurface(renderer, upsSurface);

    SDL_RenderCopy(renderer, fpsTexture, NULL, new SDL_Rect{0, 0, fpsW, fpsH});
    SDL_RenderCopy(renderer, upsTexture, NULL, new SDL_Rect{0, fpsH, upsW, upsH});

    SDL_RenderPresent(renderer);

    SDL_FreeSurface(fpsSurface);
    SDL_FreeSurface(upsSurface);
    SDL_DestroyTexture(fpsTexture);
    SDL_DestroyTexture(upsTexture);
    TTF_CloseFont(arial);
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