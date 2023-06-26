#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

// #include "Game.h"
#include "Object.h"
#include <map>

class Path;

class Player : public Object
{
    private:
        Path *_pCurrPath;
        bool _isBoosting;

    public:
        float driveForceMag = 2500; // N
        float dragCoeff = 81.6; // scalar

        Player(Vector2 pos);
        void draw(SDL_Renderer *pRenderer) override;
        void update(float time) override;
        void processInputs();
        Path *handlePathInteractions(Vector2 moveDir, float time);
};

#endif