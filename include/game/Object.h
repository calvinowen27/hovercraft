#ifndef OBJECT_INCLUDE
#define OBJECT_INCLUDE

#include "../SDL2/SDL.h"
#include "Vector2.h"

class Game;
class ContentManager;

class Object
{
    protected:
        Game *_pGame;
        ContentManager *_pContentManager;
        Vector2 _pos; // m --> 128 pixels/m default
                    // position is at bottom center of object
        Vector2Int _pxPos; // pixel position, at top left of object
        Vector2 _velocity; // m/s
        Vector2 _acceleration; // m/(s^2)
        Vector2 _dims; // dimensions (m)
        Vector2Int _pxDims; // pixel dimensions

        Vector2 _netForce; // N

        float _mass = 50; // kg

        bool _doCollisions = true;

        float _textureAngle = 0; // degrees

        SDL_Texture *_pTexture;
        SDL_Rect _spriteRect;

    public:
        Object(std::string textureName, Vector2 pos, Vector2 dims, bool doCollisions=true);
        virtual void draw(SDL_Renderer *pRenderer);
        virtual void update(float time);
        void addForce(Vector2 force);
        inline Vector2 getPos() { return _pos; }
        inline Vector2 getVelocity() { return _velocity; }
        inline Vector2 getAcceleration() { return _acceleration; }
        inline Vector2 getNetForce() { return _netForce; }
        inline float getMass() { return _mass; }
        inline Vector2Int getPxPos() { return _pxPos; }
        inline Vector2 getDims() { return _dims; }
        inline Vector2Int getPxDims() { return _pxDims; }
        inline SDL_Texture* getTexture() { return _pTexture; }
        bool isTouching(const Object other) const;
        bool willTouch(Vector2 newPos, const Object& other) const;
};

#endif