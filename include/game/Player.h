#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

// #include "Game.h"
#include "Object.h"
#include <map>

class Player : public Object
{
    public:
        float moveSpeed;
        float runSpeed = 7.5;
        float walkSpeed = 3.5;

        Player();
        void draw() override;
        void update(float time) override;
        void processInputs();
};

#endif