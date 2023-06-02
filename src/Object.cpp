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

    spriteTexture = SDL_CreateTextureFromSurface(Game::instance.renderer, spriteSurface);
    if(spriteTexture == NULL)
    {
        std::cerr << "Failed to load texture from surface: " << IMG_GetError() << std::endl;
        return;
    }

    this->pos = pos;
    this->dims = dims;
    this->px_dims = (Vector2Int)(dims * Game::instance.ppm);
    this->px_pos = Game::instance.worldToPixel(pos) - Vector2Int(px_dims.x / 2, px_dims.y);

    SDL_FreeSurface(spriteSurface);
}

Object::~Object()
{
    SDL_DestroyTexture(spriteTexture);
}

void Object::draw()
{
    SDL_Rect spriteRect{px_pos.x, px_pos.y, px_dims.x, px_dims.y};

    SDL_RenderCopy(Game::instance.renderer, spriteTexture, NULL, &spriteRect);
}

void Object::update(float time)
{
    std::cout << time << std::endl;
    this->px_pos = Game::instance.worldToPixel(pos) - Vector2Int(px_dims.x / 2, px_dims.y);
}