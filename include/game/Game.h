#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <vector>
#include <map>
#include <mutex>
#include <queue>

#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "../SDL2/SDL_ttf.h"
#include "KeyboardHandler.h"
#include "Vector2.h"
#include "Object.h"
#include "Player.h"
#include "ContentManager.h"
#include "UIElement.h"

class Object;
class UIElement;
class KeyboardHandler;
class Player;

class Game
{
    private:
        const int UPDATES_PER_SEC = 60; // physics updates
        const int TARGET_FPS = 60;

        static Game* _instance;
        int fps = 0, ups = 0; // frames per sec, updates per sec

    public:
        std::mutex mutex_;
        std::vector<Object *> objs;
        std::vector<UIElement *> uiElements;
        std::map<std::string, SDL_Scancode> keybinds;
        std::queue<SDL_Event> inputEvents;

        ContentManager *pContentManager;
        KeyboardHandler keyboardHandler;

        int winWidth = 2500, winHeight = 1750;
        int ppm = 256; // pixels per meter, 128 by default
        SDL_Window* pWindow;
        SDL_Renderer* pRenderer;

        Vector2 cameraPos;
        bool running = true;

        static Game* getInstance();
        Game();
        int gameInit();
        void start();
        void runPhysics();
        void frameUpdate();
        void physicsUpdate();
        void draw();
        Vector2 pixelToWorld(Vector2Int px_pos_);
        Vector2Int worldToPixel(Vector2 pos);
        friend bool operator==(const Game &a, const Game &b);
};

#endif