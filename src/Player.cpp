#include "../include/game/Player.h"
#include "../include/game/Game.h"

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

    this->Object::update(time);

    if(_pos.y < -10)
    {
        _pos.y = -10;
        _velocity.y = 0;
    }

    if(_pos.y < -9 && _pos.x > 2)
    {
        _pos.y = -9;
        _velocity.y = 0;
    }

    // if(Vector2::distance(_acceleration, Vector2(0, -9.8)) < 0.5)
    // {
    //     if(dir.x == 0) _velocity.x *= 0.9;
    //     if(dir.y == 0) _velocity.y *= 0.9;
    // }
        
    if(_velocity.x > -0.05 && _velocity.x < 0.05) _velocity.x = 0;
    if(_velocity.y > -0.05 && _velocity.y < 0.05) _velocity.y = 0;

    _pGame->cameraPos = _pos + Vector2(0, _dims.y / 2);
}

void Player::draw(SDL_Renderer *pRenderer)
{
    Object::draw(pRenderer);

    // draw pos, velocity, and acceleration
    // int posW, posH, velW, velH, accW, accH;
    // char posText[50];
    // sprintf(posText, "pos: (%f, %f)", _pos.x, _pos.y);
    // char velText[50];
    // sprintf(velText, "vel: (%f, %f)", _velocity.x, _velocity.y);
    // char accText[50];
    // sprintf(accText, "acc: (%f, %f)", _acceleration.x, _acceleration.y);
    // TTF_Font *arial = TTF_OpenFont("./content/arial.ttf", 24);
    // TTF_SizeUTF8(arial, posText, &posW, &posH);
    // TTF_SizeUTF8(arial, velText, &velW, &velH);
    // TTF_SizeUTF8(arial, accText, &accW, &accH);
    // SDL_Color black = {0, 0, 0, 255};
    // SDL_Surface* posSurface = TTF_RenderText_Solid(arial, posText, black);
    // SDL_Texture* posTexture = SDL_CreateTextureFromSurface(_pGame->pRenderer, posSurface);
    // SDL_Surface* velSurface = TTF_RenderText_Solid(arial, velText, black);
    // SDL_Texture* velTexture = SDL_CreateTextureFromSurface(_pGame->pRenderer, velSurface);
    // SDL_Surface* accSurface = TTF_RenderText_Solid(arial, accText, black);
    // SDL_Texture* accTexture = SDL_CreateTextureFromSurface(_pGame->pRenderer, accSurface);

    // SDL_RenderCopy(_pGame->pRenderer, posTexture, NULL, new SDL_Rect{300, 0, posW, posH});
    // SDL_RenderCopy(_pGame->pRenderer, velTexture, NULL, new SDL_Rect{300, posH, velW, velH});
    // SDL_RenderCopy(_pGame->pRenderer, accTexture, NULL, new SDL_Rect{300, posH+velH, accW, accH});

    // SDL_FreeSurface(posSurface);
    // SDL_FreeSurface(velSurface);
    // SDL_FreeSurface(accSurface);
    // SDL_DestroyTexture(posTexture);
    // SDL_DestroyTexture(velTexture);
    // SDL_DestroyTexture(accTexture);
    // TTF_CloseFont(arial);
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