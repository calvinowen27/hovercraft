#include <iostream>

#include "../include/game/Game.h"
#include "../include/game/Object.h"

Object::Object(std::string texture_path, Vector2 pos, Vector2 dims)
{
    SDL_Surface* spriteSurface = IMG_Load(texture_path.c_str());
    if(spriteSurface == NULL)
    {
        std::cerr << "Failed to load image to surface: " << IMG_GetError() << std::endl;
        return;
    }

    spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
    if(spriteTexture == NULL)
    {
        std::cerr << "Failed to load texture from surface: " << IMG_GetError() << std::endl;
        return;
    }

    this->pos = pos;
    this->dims = dims;
    this->px_dims = dims * ppm;

    SDL_FreeSurface(spriteSurface);
}

void Object::draw()
{
    SDL_Rect spriteRect;
    spriteRect.x = 100;
    spriteRect.y = 100;
    spriteRect.w = 100;
    spriteRect.h = 100;
}

void Object::update(float time)
{
    
}