#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

// #include "Game.h"
#include "Object.h"
#include <map>

class Player : public Object
{
    public:
        float thrust = 1000; // N
        float dragCoeff = 81.6; // scalar

        float angle = 0;

        Player(Vector2 pos);
        void draw(SDL_Renderer *pRenderer) override;
        void update(float time) override;
        void processInputs();
};

#endif