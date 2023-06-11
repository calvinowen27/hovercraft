#ifndef OBJECT_INCLUDE
#define OBJECT_INCLUDE

#include "../SDL2/SDL.h"
#include "Vector2.h"

class Game;

class Object
{
    protected:
        Game* game;
        Vector2 pos_; // m --> 128 pixels/m default
                    // position is at bottom center of object
        Vector2Int pxPos_; // pixel position, at top left of object
        Vector2 velocity_; // m/s
        Vector2 acceleration_; // m/(s^2)
        Vector2 dims_; // dimensions (m)
        Vector2Int pxDims_; // pixel dimensions

        float mass_ = 50; // kg

        bool doCollisions_ = true;

        SDL_Texture* texture_;
        SDL_Rect spriteRect_;

    public:
        Object(std::string texturePath, Vector2 pos, Vector2 dims, bool doCollisions=true);
        ~Object();
        virtual void draw();
        virtual void update(float time);
        void addForce(Vector2 force);
        Vector2 pos();
        Vector2Int pxPos();
        Vector2 dims();
        Vector2Int pxDims();
        SDL_Texture* texture();
        bool isTouching(const Object other) const;
        bool willTouch(Vector2 newPos, const Object& other) const;
};

#endif