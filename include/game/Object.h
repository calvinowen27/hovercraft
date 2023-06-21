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

        float _mass = 50; // kg

        bool _doCollisions = true;

        SDL_Texture *_pTexture;
        SDL_Rect _spriteRect;

    public:
        Object(std::string textureName, Vector2 pos, Vector2 dims, bool doCollisions=true);
        virtual void draw(SDL_Renderer *pRenderer);
        virtual void update(float time);
        void addForce(Vector2 force);
        Vector2 getPos();
        Vector2Int getPxPos();
        Vector2 getDims();
        Vector2Int getPxDims();
        SDL_Texture* getTexture();
        bool isTouching(const Object other) const;
        bool willTouch(Vector2 newPos, const Object& other) const;
};

#endif