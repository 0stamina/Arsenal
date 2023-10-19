
#include "global_vars.hpp"

void basic_bullet_draw(Bullet* bullet)
{
    Texture texture = bullet_sprite_list[bullet->spr_idx];
    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};

    Rectangle dest = source;
    dest.x = bullet->position.x;
    dest.y = bullet->position.y;
    dest.width = bullet->size;
    dest.height = (texture.width/texture.height)*bullet->size;
    DrawTexturePro(texture, source, dest, {dest.width/2.0f, dest.height/2.0f}, -bullet->rotation*(360.0f/TAU), WHITE);
}