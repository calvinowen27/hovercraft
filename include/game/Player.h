#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

// #include "Game.h"
#include "Object.h"
#include <map>

class Player : public Object
{
    public:
        float thrust_ = 750; // N
        float dragCoeff_ = 81.6; // scalar

        Player();
        void draw() override;
        void update(float time) override;
        void processInputs();
};

#endif