#include "../include/game/Player.h"
#include "../include/game/Game.h"

std::map<std::string, int> inputs;

Player::Player() : Object("./content/smiley.png", Vector2(0, 0), Vector2(0.5, 0.5))
{

}

void Player::update(float time)
{
    Vector2 dir;

    SDL_Event event;
    while(game->inputEvents.size())
    {
        event = game->inputEvents.front();

        if(event.key.keysym.scancode == game->keybinds["up"])
        {
            inputs["up"] = event.type == SDL_KEYDOWN?1:0;
        }
        if(event.key.keysym.scancode == game->keybinds["down"])
        {
            inputs["down"] = event.type == SDL_KEYDOWN?1:0;
        }

        if(event.key.keysym.scancode == game->keybinds["right"])
        {
            inputs["right"] = event.type == SDL_KEYDOWN?1:0;
        }
        if(event.key.keysym.scancode == game->keybinds["left"])
        {
            inputs["left"] = event.type == SDL_KEYDOWN?1:0;
        }

        game->inputEvents.pop();
    }

    if(inputs["up"])
    {
        dir.y += 1;
    }
    if(inputs["down"])
    {
        dir.y -= 1;
    }

    if(inputs["right"])
    {
        dir.x += 1;
    }
    if(inputs["left"])
    {
        dir.x -= 1;
    }

    // std::cout << dir << std::endl;

    dir.normalize();
    velocity = dir * moveSpeed;

    this->Object::update(time);

    game->cameraPos = pos + Vector2(0, dims.y / 2);
}

void Player::draw()
{
    Object::draw();
}