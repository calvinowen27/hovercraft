#ifndef PATH_INCLUDE
#define PATH_INCLUDE

#include <vector>
#include "Vector2.h"
#include "../SDL2/SDL.h"

class Game;

class Path
{
    private:
        std::vector<Vector2> _points;
        Game *_pGame;

    public:
        Path();
        Path(std::vector<Vector2> points);
        void draw(SDL_Renderer *pRenderer);
        void addPoint(Vector2 newPoint);

        // removePoint()
        // returns an int, either 0 or 1
        // 0: successfully removed point, 1: point does not exist in vector
        int removePoint(Vector2 point);
        inline std::vector<Vector2> getPoints() { return _points; }
};

#endif