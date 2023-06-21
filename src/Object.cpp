#include "../include/game/Object.h"
#include "../include/game/Game.h"
#include "../include/game/ContentManager.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"

Object::Object(std::string textureName, Vector2 pos, Vector2 dims, bool doCollisions)
{
    _pGame = Game::getInstance();
    _pContentManager = _pGame->pContentManager;
    
    _pTexture = _pContentManager->getTexture(textureName);

    _pos = pos;
    _dims = dims;
    _pxDims = (Vector2Int)(dims * _pGame->ppm);
    _pxPos = _pGame->worldToPixel(pos) - Vector2Int(_pxDims.x / 2, _pxDims.y);
    _doCollisions = doCollisions;

    _spriteRect = SDL_Rect{_pxPos.x, _pxPos.y, _pxDims.x, _pxDims.y};

    _pGame->objs.push_back(this);
}

void Object::draw(SDL_Renderer *pRenderer)
{
    _spriteRect.x = _pxPos.x;
    _spriteRect.y = _pxPos.y;

    SDL_RenderCopy(pRenderer, _pTexture, NULL, &_spriteRect);
}

void Object::update(float time)
{
    _pxPos = _pGame->worldToPixel(_pos) - Vector2Int(_pxDims.x / 2, _pxDims.y);

    Vector2 nextPos = _pos + _velocity * time;

    for(auto other : _pGame->objs)
    {
        if(other == this || !other->_doCollisions) continue;

        if(willTouch(nextPos, *other))
        {
            _velocity = _velocity.normalized() * (Vector2::distance(_pos, other->_pos) - Vector2::distance(nextPos, other->_pos));
            nextPos = _pos + _velocity * time;
        }
    }

    _pos += _velocity * time;

    _velocity += _acceleration * time;
}

void Object::addForce(Vector2 force)
{
    _acceleration += force / _mass;
}

bool Object::isTouching(const Object other) const
{
    return !(_pos.x > other._pos.x + other._dims.x || _pos.x + _dims.x < other._pos.x ||
            _pos.y > other._pos.y + other._dims.y || _pos.y + _dims.y < other._pos.y);
}

bool Object::willTouch(Vector2 newPos, const Object& other) const
{
    return !(newPos.x > other._pos.x + other._dims.x || newPos.x + _dims.x < other._pos.x ||
            newPos.y > other._pos.y + other._dims.y || newPos.y + _dims.y < other._pos.y);
}