#include "global_vars.hpp"


void init_bullet(Bullet* bullet, float rot, Vector2 pos, int type)
{
    bullet->exists = true;
    bullet->rotation = rot;
    bullet->position = pos;
    bullet->type = type;
}