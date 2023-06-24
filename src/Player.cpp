#include "../include/game/Player.h"
#include "../include/game/Game.h"
#include "../include/game/Path.h"

std::map<SDL_Scancode, bool> inputState;

Player::Player(Vector2 pos) : Object("player.png", pos, Vector2(0.5, 0.5))
{
}

void Player::update(float time)
{
    _acceleration = Vector2::zero;

    Vector2 dir;

    processInputs();

    if(inputState[_pGame->keybinds["up"]]) dir.y += 1; // up
    if(inputState[_pGame->keybinds["down"]]) dir.y -= 1; // down
    if(inputState[_pGame->keybinds["right"]]) dir.x += 1; // right
    if(inputState[_pGame->keybinds["left"]]) dir.x -= 1; // left
    if(inputState[_pGame->keybinds["reset"]])
    {
        _pos = Vector2(1, 1);
        _velocity = Vector2::zero;
        _acceleration = Vector2::zero;
    }
    if(inputState[_pGame->keybinds["zoom in"]]) _pGame->zoomIn();
    if(inputState[_pGame->keybinds["zoom out"]]) _pGame->zoomOut();

    bool boost = inputState[_pGame->keybinds["boost"]];
    
    // dir.normalize();

    Vector2 thrustForce;
    
    if(dir != Vector2::zero)
    {
        if(boost)
            thrustForce = dir * thrust * 5.17;
        else
            thrustForce = dir * thrust;

        addForce(thrustForce);
    }

    if(Vector2::distance(_acceleration, Vector2(0, -9.8)) > 0.5)
    {
        Vector2 newVel = _velocity + _acceleration * time;
        Vector2 dragForce = _velocity.getOne() * -0.5 * newVel * newVel * dragCoeff;
        dragForce.y = 0;
        addForce(dragForce);
    }

    addForce(Vector2(0, -9.8*_mass));

    Vector2 nextPos = _pos + _velocity * time;
    Vector2 snapPos;
    for(Path *path : _pGame->paths)
    {
        snapPos = path->pathSnap(this, time);
        if(snapPos != nextPos)
        {
            nextPos = snapPos;
            break;
        }
    }

    _velocity = (nextPos - _pos) / time;

    this->Object::update(time);
    
    if(dir.x == 0 && _velocity.x > -0.125 && _velocity.x < 0.125) _velocity.x = 0;
    if(dir.y == 0 && _velocity.y > -0.125 && _velocity.y < 0.125) _velocity.y = 0;

    _pGame->cameraPos = _pos + Vector2(_dims.x / 2, _dims.y / 2);
}

void Player::draw(SDL_Renderer *pRenderer)
{
    Object::draw(pRenderer);
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