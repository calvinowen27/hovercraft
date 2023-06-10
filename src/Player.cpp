#include "../include/game/Player.h"
#include "../include/game/Game.h"

std::map<SDL_Scancode, bool> inputState;

Player::Player() : Object("./content/smiley.png", Vector2(0, 0), Vector2(0.5, 0.5))
{
}

void Player::update(float time)
{
    Vector2 dir;

    processInputs();

    if(inputState[SDL_SCANCODE_W]) dir.y += 1; // up
    if(inputState[SDL_SCANCODE_S]) dir.y -= 1; // down
    if(inputState[SDL_SCANCODE_D]) dir.x += 1; // right
    if(inputState[SDL_SCANCODE_A]) dir.x -= 1; // left
    
    moveSpeed = walkSpeed;
    if(inputState[SDL_SCANCODE_LSHIFT]) moveSpeed = runSpeed; // run

    dir.normalize();
    velocity = dir * moveSpeed;

    this->Object::update(time);

    game->cameraPos = pos + Vector2(0, dims.y / 2);
}

void Player::draw()
{
    Object::draw();
}

void Player::processInputs()
{
    SDL_Event event;
    while(game->inputEvents.size())
    {
        event = game->inputEvents.front();

        inputState[event.key.keysym.scancode] = (event.type == SDL_KEYDOWN);

        game->inputEvents.pop();
    }
}