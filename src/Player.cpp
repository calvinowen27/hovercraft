#include "../include/game/Player.h"
#include "../include/game/Game.h"
#include "../include/game/Path.h"

std::map<SDL_Scancode, bool> inputState;

Player::Player(Vector2 pos) : Object("player.png", pos, Vector2(0.5, 0.5))
{
    _pKeyboardHandler = _pGame->pKeyboardHandler;
}

void Player::update(float time)
{
    Vector2 moveDir;
    _moveDir = Vector2::zero;
    // if(inputState[_pGame->keybinds["up"]]) moveDir.y += 1; // up
    // if(inputState[_pGame->keybinds["down"]]) moveDir.y -= 1; // down
    if(_pKeyboardHandler->getInputState(ACTION_MOVE_RIGHT)) _moveDir.x += 1; // right
    if(_pKeyboardHandler->getInputState(ACTION_MOVE_LEFT)) _moveDir.x -= 1; // left
    if(_pKeyboardHandler->getInputState(ACTION_RESET))
    {
        _pos = Vector2(0, 1);
        _velocity = Vector2::zero;
        _acceleration = Vector2::zero;
    }
    if(_pKeyboardHandler->getInputState(ACTION_ZOOM_IN)) _pGame->zoomIn();
    if(_pKeyboardHandler->getInputState(ACTION_ZOOM_OUT)) _pGame->zoomOut();

    _isBoosting = _pKeyboardHandler->getInputState(ACTION_BOOST);

    // addForce(Vector2(0, -9.8*_mass)); // apply gravity

    // apply drag
    if(Vector2::distance(_acceleration, Vector2(0, -9.8)) > 0.5)
    {
        Vector2 newVel = _velocity + _acceleration * time;
        Vector2 dragForce = _velocity.getDir() * -0.5 * newVel * newVel * dragCoeff;
        dragForce.y = 0;
        addForce(dragForce);
    }

    // _pCurrPath = handlePathCollisions(time);

    this->Object::update(time);

    _pGame->cameraPos = _pos + Vector2(_dims.x / 2, _dims.y / 2);
}

void Player::draw(SDL_Renderer *pRenderer)
{
    Object::draw(pRenderer);
}

Path *Player::handlePathCollisions(float time)
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
    Vector2 slopeNorm;

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
            slopeNorm = Vector2(1, slope).normalized();

            // y that player should be at if on path
            checkY = slope*(nextPos.x + (_dims.magnitude() * slope / TWO_PI) - prevPoint.x) + prevPoint.y;

            // check if player is supposed to be on path
            // to stick to track make first condition nextPos.y - (_dims.magnitude() * SDL_fabsf(slopeNorm.y)) <= checkY
            if(nextPos.y <= checkY && (nextPos.y + (_dims.magnitude() * SDL_fabsf(slopeNorm.y)) >= checkY || _pos.y > checkY) &&
                nextPos.x <= currPoint.x && nextPos.x + (_dims.magnitude() * slopeNorm.x / TWO_PI) >= prevPoint.x)
            {
                surfaceNorm = Vector2(-slopeNorm.y, slopeNorm.x);
                surfaceNorm.normalize();

                addForce(surfaceNorm * _netForce.magnitude()); // stopping force on collision

                if(_moveDir != Vector2::zero)
                {
                    // driving force applied in direction parallel to slope
                    if(_isBoosting)
                        driveForce = slopeNorm * _moveDir * driveForceMag * 2;
                    else
                        driveForce = slopeNorm * _moveDir * driveForceMag;

                    addForce(driveForce);
                }

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