#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

// #include "Game.h"
#include "Object.h"

class Player : public Object
{
    public:
        float moveSpeed = 5;

        Player();
        void draw() override;
        void update(float time) override;
};

#endif