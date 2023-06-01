#include "../include/game/Game.h"

Vector2 pixelToWorld(Vector2Int px_pos)
{
    px_pos - Vector2(winWidth / 2, winHeight / 2);
    px_pos /= ppm;
}

Vector2Int worldToPixel(Vector2 pos)
{

}