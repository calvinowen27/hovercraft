#ifndef UIELEMENT_INCLUDE
#define UIELEMENT_INCLUDE

#include <string.h>
#include "Vector2.h"
#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "../SDL2/SDL_ttf.h"
#include "Game.h"

class UIElement
{
    protected:
        Game *_pGame;
        ContentManager *_pContentManager;
        Vector2 _relativePos;
        Vector2 _relativeDims;
        Vector2Int _pxPos;
        Vector2Int _pxDims;

        SDL_Texture *_pTexture;
        SDL_Rect _drawRect;

    public:
        UIElement(std::string textureName, Vector2 relativePos, Vector2 relativeDims);
        virtual void draw(SDL_Renderer* pRenderer);
        virtual void update();
};

#endif