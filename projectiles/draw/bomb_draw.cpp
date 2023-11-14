
#include "global_vars.hpp"

void bomb_draw(Bullet* bullet)
{
    if(bullet->from_player)
    {
        float v = bullet->size;
        DrawCircleV(bullet->position, v, DARKBLUE);
        DrawCircleV(Vector2Add(bullet->position, {-v/3.f, -v/3.f}), v/4.f, SKYBLUE);
    }
    else
    {
        float v = bullet->size;
        DrawCircleV(bullet->position, v, DARKBROWN);
        DrawCircleV(Vector2Add(bullet->position, {-v/3.f, -v/3.f}), v/4.f, BEIGE);
    }
}