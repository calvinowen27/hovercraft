#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "Vector2.h"

int winWidth = 800, winHeight = 600;
SDL_Window* window;
SDL_Renderer* renderer;
Vector2 cameraPos;

Vector2 pixelToWorld(Vector2Int px_pos);
Vector2Int worldToPixel(Vector2 pos);

#endif