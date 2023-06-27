#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

// #include "Game.h"
#include "Object.h"
#include "KeyboardHandler.h"
#include <map>

class Path;

class Player : public Object
{
    private:
        // Path *_pCurrPath;
        // Vector2 _currPathSlopeNorm;
        bool _isBoosting;
        Vector2 _moveDir;

        KeyboardHandler *_pKeyboardHandler;

    public:
        float driveForceMag = 1250; // N
        float dragCoeff = 81.6; // scalar

        Player(Vector2 pos);
        void draw(SDL_Renderer *pRenderer) override;
        void update(float time) override;
        Path *handlePathCollisions(float time) override;
};

#endif