#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

// #include "Game.h"
#include "Object.h"

class Player : public Object
{
    public:
        float moveSpeed = 5;

        Player();
        void draw();
        void update(float time);
};

#endif