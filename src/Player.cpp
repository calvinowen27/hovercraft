#include "../include/game/Player.h"
#include "../include/game/Game.h"
#include "../include/game/Path.h"

std::map<SDL_Scancode, bool> inputState;

Player::Player(Vector2 pos) : Object("player.png", pos, Vector2(0.5, 0.5))
{
}

void Player::update(float time)
{
    // _acceleration = Vector2::zero;

    Vector2 dir;

    processInputs();

    // if(inputState[_pGame->keybinds["up"]]) dir.y += 1; // up
    // if(inputState[_pGame->keybinds["down"]]) dir.y -= 1; // down
    if(inputState[_pGame->keybinds["right"]]) dir.x += 1; // right
    if(inputState[_pGame->keybinds["left"]]) dir.x -= 1; // left
    if(inputState[_pGame->keybinds["reset"]])
    {
        _pos = Vector2(0, 2);
        _velocity = Vector2::zero;
        _acceleration = Vector2::zero;
    }
    if(inputState[_pGame->keybinds["zoom in"]]) _pGame->zoomIn();
    if(inputState[_pGame->keybinds["zoom out"]]) _pGame->zoomOut();

    bool boost = inputState[_pGame->keybinds["boost"]];
    
    // dir.normalize();

    

    // if(Vector2::distance(_acceleration, Vector2(0, -9.8)) > 0.5)
    // {
    //     Vector2 newVel = _velocity + _acceleration * time;
    //     Vector2 dragForce = _velocity.getDir() * -0.5 * newVel * newVel * dragCoeff;
    //     dragForce.y = 0;
    //     addForce(dragForce);
    // }

    addForce(Vector2(0, -9.8*_mass));

    Vector2 tentAccel = _netForce / _mass;
    Vector2 tentVel = _velocity + ((tentAccel) * time);
    Vector2 nextPos = _pos + (tentVel * time);

    Vector2 currPoint;
    Vector2 prevPoint;
    std::vector<Vector2> points;
    float slope;
    float checkY;
    Vector2 surfaceNorm;
    Vector2 slopeNorm;

    float frictionCoeff = 0.9;

    float temp;

    Vector2 thrustForce;

    bool attached = false;

    for(Path *path : _pGame->paths)
    {
        points = path->getPoints();
        for(int i = 1; i < points.size(); i++)
        {
            currPoint = points[i];

            slope = (currPoint.y - prevPoint.y) / (currPoint.x - prevPoint.x);
            slopeNorm = Vector2(slope, 1);
            slopeNorm.normalize();
            checkY = slope*(nextPos.x + (_dims.magnitude() * slopeNorm.x / 4) - prevPoint.x) + prevPoint.y;

            if(nextPos.y <= checkY && nextPos.y + (_dims.magnitude() * SDL_fabsf(slopeNorm.y) / 4) >= checkY &&
                nextPos.x <= currPoint.x && nextPos.x + (_dims.magnitude() * SDL_fabsf(slopeNorm.x) / 4) >= prevPoint.x)
            {
                surfaceNorm = Vector2(slopeNorm.x == 0 ? 0 : (-slopeNorm.y / slopeNorm.x), 1);
                surfaceNorm.normalize();

                attached = true;

                Vector2 asdf = surfaceNorm * _netForce.magnitude() * 2;

                addForce(asdf);

                if(dir != Vector2::zero)
                {
                    Vector2 revSlope(dir.x, slope);
                    revSlope.normalize();
                    if(boost)
                        thrustForce = revSlope * thrust * 2;
                    else
                        thrustForce = revSlope * thrust;

                    addForce(thrustForce);
                }

                angle = -SDL_atanf(slope) * (180 / 3.14);

                tentAccel = _netForce / _mass;
                tentVel = _velocity + (tentAccel * time);
                nextPos = _pos + (tentVel * time);

                nextPos.y = checkY;

                _velocity = (nextPos - _pos) / time;

                break;
            }

            prevPoint = currPoint;
        }
    }

    if(attached) _velocity *= frictionCoeff;

    this->Object::update(time);
    
    if(dir.x == 0 && _velocity.x > -0.125 && _velocity.x < 0.125) _velocity.x = 0;
    if(dir.y == 0 && _velocity.y > -0.125 && _velocity.y < 0.125) _velocity.y = 0;

    _pGame->cameraPos = _pos + Vector2(_dims.x / 2, _dims.y / 2);
}

void Player::draw(SDL_Renderer *pRenderer)
{
    _spriteRect = SDL_Rect{_pxPos.x, _pxPos.y, _pxDims.x, _pxDims.y};

    // SDL_RenderCopy(pRenderer, _pTexture, NULL, &_spriteRect);

    SDL_RenderCopyEx(pRenderer, _pTexture, NULL, &_spriteRect, angle, NULL, _velocity.x < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(pRenderer, &_spriteRect);
    SDL_RenderDrawLine(pRenderer, _pxPos.x + _pxDims.x / 2, _pxPos.y, _pxPos.x + _pxDims.x / 2, _pxPos.y + _pxDims.y);
}

void Player::processInputs()
{
    SDL_Event event;
    while(_pGame->inputEvents.size())
    {
        event = _pGame->inputEvents.front();

        inputState[event.key.keysym.scancode] = (event.type == SDL_KEYDOWN);

        _pGame->inputEvents.pop();
    }
}