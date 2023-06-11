#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

// #include "Game.h"
#include "Object.h"
#include <map>

class Player : public Object
{
    public:
        float baseSpeed = 3.5;
        float boostSpeed = 7.5;
        float accelerationRate = 10;
        float drag = 81.6;

        Player();
        void draw() override;
        void update(float time) override;
        void processInputs();
};

#endif