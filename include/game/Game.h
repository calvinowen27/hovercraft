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
#include "ContentManager.h"

class Object;
class UIElement;
class Player;
class UIManager;
class Path;

class Game
{
    private:
        const int UPDATES_PER_SEC = 60; // physics updates
        const int TARGET_FPS = 120; // aim for this many fps

        static Game* _pInstance;
        int _fps = 0, _ups = 0; // frames per sec, updates per sec

    public:
        std::mutex mutex_;
        std::vector<Object *> objs;
        std::map<std::string, SDL_Scancode> keybinds;
        std::queue<SDL_Event> inputEvents;
        std::vector<Path *> paths;

        ContentManager *pContentManager;
        KeyboardHandler keyboardHandler;
        UIManager *pUIManager;

        Player *pPlayer;

        int winWidth = 1500, winHeight = 1000;
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
        inline int getFPS() { return _fps; }
        inline int getUPS() { return _ups; }
        inline void zoomIn() { ppm += ppm < 256 ? 8 : 0; }
        inline void zoomOut() { ppm -= ppm > 128 ? 8 : 0; }
};

#endif