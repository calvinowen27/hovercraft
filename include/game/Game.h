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

class Object;
class KeyboardHandler;
class Player;

class Game
{
    private:
        static Game* instance;
        const int UPDATES_PER_SEC = 60; // physics updates
        const int TARGET_FPS = 120;
        int fps = 0, ups = 0; // frames per sec, updates per sec

    public:
        std::mutex mutex_;
        std::vector<Object *> objs;
        std::map<std::string, SDL_Scancode> keybinds;
        std::queue<SDL_Event> inputEvents;

        KeyboardHandler keyboardHandler;

        int winWidth = 800, winHeight = 600;
        int ppm = 128; // pixels per meter, 128 by default
        SDL_Window* window;
        SDL_Renderer* renderer;

        Vector2 cameraPos;
        bool running = true;

        Game();
        int gameInit();
        void go();
        void runUpdates();
        void frameUpdate();
        void physicsUpdate();
        void draw();
        static Game* getInstance();
        Vector2 pixelToWorld(Vector2Int px_pos_);
        Vector2Int worldToPixel(Vector2 pos_);
        friend bool operator==(const Game &a, const Game &b);
};

#endif