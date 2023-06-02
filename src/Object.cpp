#include <iostream>

#include "../include/game/Game.h"
#include "../include/game/Object.h"

Object::Object(std::string texture_path, Vector2 pos, Vector2 dims)
{
    // SDL_Surface* spriteSurface = IMG_Load(texture_path.c_str());
    SDL_Surface* spriteSurface = IMG_Load("./content/smiley.png");
    if(spriteSurface == NULL)
    {
        std::cerr << "Failed to load image to surface: " << IMG_GetError() << std::endl;
        return;
    }

    spriteTexture = SDL_CreateTextureFromSurface(Game::instance->renderer, spriteSurface);
    if(spriteTexture == NULL)
    {
        std::cerr << "Failed to load texture from surface: " << IMG_GetError() << std::endl;
        return;
    }

    this->pos = pos;
    this->dims = dims;
    this->px_dims = (Vector2Int)(dims * Game::instance->ppm);
    // this->px_dims = Vector2Int(dims.x * Game::instance->ppm, dims.y * Game::instance->ppm);
    // this->px_pos = Game::instance->worldToPixel(pos) - Vector2Int(px_dims.x / 2, px_dims.y);
    this->px_pos = Vector2Int(100, 100);

    std::cout << this->pos << std::endl;
    std::cout << this->px_pos << std::endl;
    std::cout << this->dims << std::endl;
    std::cout << this->px_dims << std::endl;

    SDL_FreeSurface(spriteSurface);

    Game::instance->objs.push_back(*this);
}

Object::~Object()
{
    SDL_DestroyTexture(spriteTexture);
}

void Object::draw()
{
    SDL_Rect spriteRect{px_pos.x, px_pos.y, px_dims.x, px_dims.y};
    // std::cout << px_pos << std::endl;
    // std::cout << px_dims << std::endl;
    // std::cout << spriteRect.x << std::endl;
    // std::cout << spriteRect.y << std::endl;
    // std::cout << spriteRect.w << std::endl;
    // std::cout << spriteRect.h << std::endl << std::endl;


    // SDL_RenderCopy(Game::instance->renderer, spriteTexture, NULL, &spriteRect);

    SDL_Surface* spriteSurface = IMG_Load("./content/smiley.png");
    if(spriteSurface == NULL)
    {
        std::cerr << "Failed to load image to surface: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Texture* spriteTexture1 = SDL_CreateTextureFromSurface(Game::instance->renderer, spriteSurface);
    if(spriteTexture1 == NULL)
    {
        std::cerr << "Failed to load texture from surface: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(spriteSurface);

    SDL_RenderCopy(Game::instance->renderer, spriteTexture, NULL, &spriteRect);
}

void Object::update(float time)
{
    std::cout << time << std::endl;
    this->px_pos = Game::instance->worldToPixel(pos) - Vector2Int(px_dims.x / 2, px_dims.y);
}