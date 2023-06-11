#include "../include/game/Player.h"
#include "../include/game/Game.h"

std::map<SDL_Scancode, bool> inputState;

Player::Player() : Object("./content/player.png", Vector2::zero, Vector2(1, 1))
{
}

void Player::update(float time)
{
    Vector2 dir;
    float moveSpeed = baseSpeed;

    processInputs();

    if(inputState[game->keybinds["up"]]) dir.y += 1; // up
    if(inputState[game->keybinds["down"]]) dir.y -= 1; // down
    if(inputState[game->keybinds["right"]]) dir.x += 1; // right
    if(inputState[game->keybinds["left"]]) dir.x -= 1; // left
    if(inputState[game->keybinds["boost"]]) moveSpeed = boostSpeed;
    
    dir.normalize();

    Vector2 thrust;
    
    if(dir != Vector2::zero)
    {
        thrust = dir * accelerationRate * mass;
        addForce(thrust);
    }
    
    // acceleration = dir * accelerationRate;
    // std::cout << thrust << std::endl;
    
    // Vector2 dragForce = velocity.normalized()*(float)(-0.5)*velocity*velocity*drag;


    if(acceleration.x != 0)
    {
        float newVelX = velocity.x + acceleration.x * time;
        Vector2 dragForce = Vector2((acceleration.x / abs(acceleration.x)) * -0.5 * newVelX * newVelX * drag, 0);
        // if(thrust.x < 0 && dragForce.x > -thrust.x) dragForce.x = -thrust.x;
        // if(thrust.x > 0 && dragForce.x < -thrust.x) dragForce.x = -thrust.x;

        addForce(dragForce);

        // std::cout << thrust << " " << dragForce << std::endl;
        // std::cout << acceleration << std::endl;
    }

    // if(acceleration.x < 0.5 && acceleration.x > -0.5) acceleration.x = 0;

    // if(velocity.x < baseSpeed && velocity.x + acceleration.x * time > baseSpeed) acceleration.x = (baseSpeed - velocity.x) / time;

    this->Object::update(time);



    if(dir != Vector2::zero)
    {
        // if(velocity.x > moveSpeed) velocity.x = moveSpeed;
        // if(velocity.x < -moveSpeed) velocity.x = -moveSpeed;
        // if(velocity.y > moveSpeed) velocity.y = moveSpeed;
        // if(velocity.y < -moveSpeed) velocity.y = -moveSpeed;

        if(dir.x == 0) velocity.x *= 0.9;
        if(dir.y == 0) velocity.y *= 0.9;
        if(velocity.x > -0.1 && velocity.x < 0.1) velocity.x = 0;
        if(velocity.y > -0.1 && velocity.y < 0.1) velocity.y = 0;
    }
    else
    {
        velocity *= velocity.magnitude() > 0.2 ? 0.9 : 0;
    }

    game->cameraPos = pos + Vector2(0, dims.y / 2);
}

void Player::draw()
{
    Object::draw();

    // draw pos, velocity, and acceleration
    int posW, posH, velW, velH, accW, accH;
    char posText[50];
    sprintf(posText, "pos: (%f, %f)", pos.x, pos.y);
    char velText[50];
    sprintf(velText, "vel: (%f, %f)", velocity.x, velocity.y);
    char accText[50];
    sprintf(accText, "acc: (%f, %f)", acceleration.x, acceleration.y);
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