#include "../include/game/Player.h"
#include "../include/game/Game.h"

std::map<SDL_Scancode, bool> inputState;

Player::Player() : Object("./content/player.png", Vector2::zero, Vector2(1, 1))
{
}

void Player::update(float time)
{
    acceleration_ = Vector2::zero;

    Vector2 dir;

    processInputs();

    if(inputState[game->keybinds["up"]]) dir.y += 1; // up
    if(inputState[game->keybinds["down"]]) dir.y -= 1; // down
    if(inputState[game->keybinds["right"]]) dir.x += 1; // right
    if(inputState[game->keybinds["left"]]) dir.x -= 1; // left

    bool boost = inputState[game->keybinds["boost"]];
    
    // dir.normalize();

    Vector2 thrustForce;
    
    if(dir != Vector2::zero)
    {
        if(boost)
            thrustForce = dir * thrust_ * 5.17;
        else
            thrustForce = dir * thrust_;

        addForce(thrustForce);
    }

    if(acceleration_ != Vector2::zero)
    {
        Vector2 newVel = velocity_ + acceleration_ * time;
        Vector2 dragForce = velocity_.getOne() * -0.5 * newVel * newVel * dragCoeff_;
        addForce(dragForce);
    }

    this->Object::update(time);

    if(dir != Vector2::zero)
    {
        if(dir.x == 0) velocity_.x *= 0.9;
        if(dir.y == 0) velocity_.y *= 0.9;
        if(velocity_.x > -0.1 && velocity_.x < 0.1) velocity_.x = 0;
        if(velocity_.y > -0.1 && velocity_.y < 0.1) velocity_.y = 0;
    }
    else
    {
        velocity_ *= velocity_.magnitude() > 0.2 ? 0.9 : 0;
    }

    game->cameraPos = pos_ + Vector2(0, dims_.y / 2);
}

void Player::draw()
{
    Object::draw();

    // draw pos_, velocity_, and acceleration_
    int posW, posH, velW, velH, accW, accH;
    char posText[50];
    sprintf(posText, "pos: (%f, %f)", pos_.x, pos_.y);
    char velText[50];
    sprintf(velText, "vel: (%f, %f)", velocity_.x, velocity_.y);
    char accText[50];
    sprintf(accText, "acc: (%f, %f)", acceleration_.x, acceleration_.y);
    TTF_Font* arial = TTF_OpenFont("./content/arial.ttf", 24);
    TTF_SizeUTF8(arial, posText, &posW, &posH);
    TTF_SizeUTF8(arial, velText, &velW, &velH);
    TTF_SizeUTF8(arial, accText, &accW, &accH);
    SDL_Color black = {0, 0, 0, 255};
    SDL_Surface* posSurface = TTF_RenderText_Solid(arial, posText, black);
    SDL_Texture* posTexture = SDL_CreateTextureFromSurface(game->renderer, posSurface);
    SDL_Surface* velSurface = TTF_RenderText_Solid(arial, velText, black);
    SDL_Texture* velTexture = SDL_CreateTextureFromSurface(game->renderer, velSurface);
    SDL_Surface* accSurface = TTF_RenderText_Solid(arial, accText, black);
    SDL_Texture* accTexture = SDL_CreateTextureFromSurface(game->renderer, accSurface);

    SDL_RenderCopy(game->renderer, posTexture, NULL, new SDL_Rect{300, 0, posW, posH});
    SDL_RenderCopy(game->renderer, velTexture, NULL, new SDL_Rect{300, posH, velW, velH});
    SDL_RenderCopy(game->renderer, accTexture, NULL, new SDL_Rect{300, posH+velH, accW, accH});

    SDL_FreeSurface(posSurface);
    SDL_FreeSurface(velSurface);
    SDL_FreeSurface(accSurface);
    SDL_DestroyTexture(posTexture);
    SDL_DestroyTexture(velTexture);
    SDL_DestroyTexture(accTexture);
    TTF_CloseFont(arial);
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