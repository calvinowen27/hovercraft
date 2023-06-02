#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <list>

#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "Vector2.h"
#include "Object.h"

class Game
{
    public:
        static Game* instance;
        static bool initialized;
        std::list<Object> objs;
        int winWidth = 800, winHeight = 600;
        int ppm = 128; // pixels per meter, 128 by default
        SDL_Window* window;
        SDL_Renderer* renderer;
        Vector2 cameraPos;
        bool running = true;

        Game();
        int gameInit();
        void go();
        void update();
        void draw();
        Vector2 pixelToWorld(Vector2Int px_pos);
        Vector2Int worldToPixel(Vector2 pos);
        friend bool operator==(const Game &a, const Game &b);
};

#endif