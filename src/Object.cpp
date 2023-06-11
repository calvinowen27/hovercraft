#include "../include/game/Object.h"
#include "../include/game/Game.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"

Object::Object(std::string texturePath, Vector2 pos, Vector2 dims, bool doCollisions)
{
    game = Game::getInstance();
    SDL_Surface* spriteSurface = IMG_Load(texturePath.c_str());
    // SDL_Surface* spriteSurface = IMG_Load("./content/smiley.png");
    if(spriteSurface == NULL)
    {
        std::cerr << "Failed to load image to surface: " << IMG_GetError() << std::endl;
        return;
    }

    texture_ = SDL_CreateTextureFromSurface(game->renderer, spriteSurface);
    if(texture_ == NULL)
    {
        std::cerr << "Failed to load texture from surface: " << IMG_GetError() << std::endl;
        return;
    }

    this->pos_ = pos;
    this->dims_ = dims;
    this->pxDims_ = (Vector2Int)(dims * game->ppm);
    this->pxPos_ = game->worldToPixel(pos_) - Vector2Int(pxDims_.x / 2, pxDims_.y);
    this->doCollisions_ = doCollisions;

    spriteRect_ = SDL_Rect{pxPos_.x, pxPos_.y, pxDims_.x, pxDims_.y};

    SDL_FreeSurface(spriteSurface);

    game->objs.push_back(this);
}

Object::~Object()
{
    SDL_DestroyTexture(texture_);
}

void Object::draw()
{
    spriteRect_.x = pxPos_.x;
    spriteRect_.y = pxPos_.y;

    SDL_RenderCopy(game->renderer, texture_, NULL, &spriteRect_);
}

void Object::update(float time)
{
    pxPos_ = game->worldToPixel(pos_) - Vector2Int(pxDims_.x / 2, pxDims_.y);

    Vector2 nextPos = pos_ + velocity_ * time;

    for(auto other : game->objs)
    {
        if(other == this || !other->doCollisions_) continue;

        if(willTouch(nextPos, *other))
        {
            velocity_ = velocity_.normalized() * (Vector2::distance(pos_, other->pos_) - Vector2::distance(nextPos, other->pos_));
            nextPos = pos_ + velocity_ * time;
        }
    }

    pos_ += velocity_ * time;

    velocity_ += acceleration_ * time;
}

void Object::addForce(Vector2 force)
{
    acceleration_ += force / mass_;
}

bool Object::isTouching(const Object other) const
{
    return !(pos_.x > other.pos_.x + other.dims_.x || pos_.x + dims_.x < other.pos_.x ||
            pos_.y > other.pos_.y + other.dims_.y || pos_.y + dims_.y < other.pos_.y);
}

bool Object::willTouch(Vector2 newPos, const Object& other) const
{
    return !(newPos.x > other.pos_.x + other.dims_.x || newPos.x + dims_.x < other.pos_.x ||
            newPos.y > other.pos_.y + other.dims_.y || newPos.y + dims_.y < other.pos_.y);
}