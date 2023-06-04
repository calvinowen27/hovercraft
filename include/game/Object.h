#ifndef OBJECT_INCLUDE
#define OBJECT_INCLUDE

#include "../SDL2/SDL.h"
// #include "Game.h"
#include "Vector2.h"

const Vector2 GRAVITY = Vector2(0, -9.8); // m/(s^2)

class Game;

class Object
{
    protected:
        Game* game;
        Vector2 pos; // m --> 128 pixels/m default
                    // position is at bottom center of object
        Vector2Int px_pos; // pixel position, at top left of object
        Vector2 velocity; // m/s
        Vector2 dims; // dimensions (m)
        Vector2Int px_dims; // pixel dimensions

        SDL_Texture* spriteTexture;

    public:
        Object(std::string texture_path, Vector2 pos, Vector2 dims);
        ~Object();
        virtual void draw();
        virtual void update(float time);
        void addForce(Vector2 force);
        Vector2 getPos();
        Vector2Int getPxPos();
        Vector2 getVelocity();
        Vector2 getDims();
        Vector2Int getPxDims();
        SDL_Texture* getTexture();
};

#endif