#include "../include/game/Object.h"
#include "../include/game/Game.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"

Object::Object(std::string texture_path, Vector2 pos, Vector2 dims)
{
    game = Game::getInstance();
    SDL_Surface* spriteSurface = IMG_Load(texture_path.c_str());
    // SDL_Surface* spriteSurface = IMG_Load("./content/smiley.png");
    if(spriteSurface == NULL)
    {
        std::cerr << "Failed to load image to surface: " << IMG_GetError() << std::endl;
        return;
    }

    spriteTexture = SDL_CreateTextureFromSurface(game->renderer, spriteSurface);
    if(spriteTexture == NULL)
    {
        std::cerr << "Failed to load texture from surface: " << IMG_GetError() << std::endl;
        return;
    }

    this->pos = pos;
    this->dims = dims;
    this->px_dims = (Vector2Int)(dims * game->ppm);
    this->px_pos = game->worldToPixel(pos) - Vector2Int(px_dims.x / 2, px_dims.y);

    SDL_FreeSurface(spriteSurface);

    game->objs.push_back(this);
}

Object::~Object()
{
    SDL_DestroyTexture(spriteTexture);
}

void Object::draw()
{
    SDL_Rect spriteRect{px_pos.x, px_pos.y, px_dims.x, px_dims.y};

    SDL_RenderCopy(game->renderer, spriteTexture, NULL, &spriteRect);
}

void Object::update(float time)
{
    px_pos = game->worldToPixel(pos) - Vector2Int(px_dims.x / 2, px_dims.y);

    pos += velocity * time;

    velocity += acceleration * time;
}