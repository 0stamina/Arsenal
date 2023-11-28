
#include "global_vars.hpp"

void fireball_draw(Bullet* bullet)
{
    Texture texture;
    Rectangle source;
    
    if(bullet->from_player)
    {
        texture = bullet_sprite_list[0];
        source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    }
    else
    {
        texture = bullet_sprite_list[0];
        source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    }

    Rectangle dest = source;
    dest.x = bullet->position.x;
    dest.y = bullet->position.y;
    dest.width = bullet->size*2;
    dest.height = ((float)texture.height/(float)texture.width)*bullet->size*2;
    DrawTexturePro(texture, source, dest, {dest.width/2.0f, dest.height/2.0f}, -(bullet->rotation+(bullet->time/5))*(360.0f/TAU), WHITE);
}