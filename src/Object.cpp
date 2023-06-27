#include "../include/game/Object.h"
#include "../include/game/Game.h"
#include "../include/game/ContentManager.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/game/Path.h"

Object::Object(std::string textureName, Vector2 pos, Vector2 dims, bool doCollisions)
{
    _pGame = Game::getInstance();
    _pContentManager = _pGame->pContentManager;
    
    _pTexture = _pContentManager->getTexture(textureName);

    _pos = pos;
    _dims = dims;
    _pxDims = (Vector2Int)(dims * _pGame->ppm);
    _pxPos = _pGame->worldToPixel(pos) - Vector2Int(0, _pxDims.y);
    _doCollisions = doCollisions;

    _spriteRect = SDL_Rect{_pxPos.x, _pxPos.y, _pxDims.x, _pxDims.y};

    _pGame->objs.push_back(this);
}

void Object::draw(SDL_Renderer *pRenderer)
{
    _spriteRect = SDL_Rect{_pxPos.x, _pxPos.y, _pxDims.x, _pxDims.y};

    // SDL_RenderCopy(pRenderer, _pTexture, NULL, &_spriteRect);

    SDL_RenderCopyEx(pRenderer, _pTexture, NULL, &_spriteRect, _textureAngle, NULL, _velocity.x < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Object::update(float time)
{
    addForce(Vector2(0, -9.8*_mass)); // apply gravity

    _pCurrPath = handlePathCollisions(time);

    _pxPos = _pGame->worldToPixel(_pos) - Vector2Int(_pxDims.x / 2, _pxDims.y);
    _pxDims = (Vector2Int)(_dims * _pGame->ppm);

    _acceleration = _netForce / _mass;
    if(SDL_fabsf(_acceleration.x) < 0.0625) _acceleration.x = 0;
    if(SDL_fabsf(_acceleration.x) < 0.0625) _acceleration.x = 0;

    _velocity += _acceleration * time;
    if(SDL_fabsf(_velocity.x) < 0.0625) _velocity.x = 0;
    if(SDL_fabsf(_velocity.y) < 0.0625) _velocity.y = 0;

    _pos += _velocity * time;
    
    _netForce = Vector2::zero;
}

Path *Object::handlePathCollisions(float time)
{
    Vector2 tentAccel = _netForce / _mass;
    Vector2 tentVel = _velocity + ((tentAccel) * time);
    Vector2 nextPos = _pos + (tentVel * time);

    Vector2 currPoint;
    Vector2 prevPoint;
    std::vector<Vector2> points;
    float slope;
    float checkY;
    Vector2 surfaceNorm;
    // Vector2 slopeNorm;

    float frictionCoeff = 0.9;

    float temp;

    Vector2 driveForce;
    Vector2 revSlope;

    for(Path *path : _pGame->paths)
    {
        points = path->getPoints();
        prevPoint = points[0];

        for(int i = 1; i < points.size(); i++)
        {
            currPoint = points[i];

            slope = (currPoint.y - prevPoint.y) / (currPoint.x - prevPoint.x);
            _currPathSlopeNorm = Vector2(1, slope).normalized();

            // y that player should be at if on path
            checkY = slope*(nextPos.x + (_dims.magnitude() * slope / TWO_PI) - prevPoint.x) + prevPoint.y;

            // check if player is supposed to be on path
            // to stick to track make first condition nextPos.y - (_dims.magnitude() * SDL_fabsf(_currPathSlopeNorm.y)) <= checkY
            if(nextPos.y <= checkY && (nextPos.y + (_dims.magnitude() * SDL_fabsf(_currPathSlopeNorm.y)) >= checkY || _pos.y > checkY) &&
                nextPos.x <= currPoint.x && nextPos.x + (_dims.magnitude() * _currPathSlopeNorm.x / TWO_PI) >= prevPoint.x)
            {
                surfaceNorm = Vector2(-_currPathSlopeNorm.y, _currPathSlopeNorm.x);
                surfaceNorm.normalize();

                addForce(surfaceNorm * _netForce.magnitude()); // stopping force on collision

                addForce(_velocity.normalized() * -_mass * 0.5 * 9.8);

                _textureAngle = -SDL_atanf(slope) * RAD_TO_DEGS; // for rotating texture

                // recalculate next position and set velocity accordingly
                tentAccel = _netForce / _mass;
                tentVel = _velocity + (tentAccel * time);
                nextPos = _pos + (tentVel * time);

                nextPos.y = checkY;

                _velocity = (nextPos - _pos) / time;

                return path;
            }

            prevPoint = currPoint;
        }
    }

    return nullptr;
}

void Object::addForce(Vector2 force)
{
    // _acceleration += force / _mass;
    _netForce += force;
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