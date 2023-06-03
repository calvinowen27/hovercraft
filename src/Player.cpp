#include "../include/game/Player.h"
#include "../include/game/Game.h"

Player::Player() : Object("./content/smiley.png", Vector2(0, 0), Vector2(0.5, 0.5))
{

}

void Player::update(float time)
{
    Vector2 dir;

    if(game->keyboardHandler.isPressed(game->keyControls["up"]))
    {
        dir.y = 1;
    }
    if(game->keyboardHandler.isPressed(game->keyControls["down"]))
    {
        dir.y = -1;
    }

    if(game->keyboardHandler.isPressed(game->keyControls["left"]))
    {
        dir.x = -1;
    }
    if(game->keyboardHandler.isPressed(game->keyControls["right"]))
    {
        dir.x = 1;
    }

    // std::cout << dir << std::endl;

    dir.normalize();
    velocity = dir * moveSpeed;

    this->Object::update(time);
}

void Player::draw()
{
    Object::draw();
}