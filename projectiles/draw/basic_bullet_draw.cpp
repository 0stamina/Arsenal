
#include "global_vars.hpp"

void basic_bullet_draw(Bullet* bullet)
{
    Texture texture;
    Rectangle source;
    
    if(bullet->from_player)
    {
        texture = bullet_sprite_list[3];
        source = {0.0f, 0.0f, (float)texture.width/4, (float)texture.height};
        source.x = (texture.width/4)*(bullet->time/3);
    }
    else
    {
        texture = bullet_sprite_list[1];
        source = {0.0f, 0.0f, (float)texture.width/4, (float)texture.height};
        source.x = (texture.width/4)*(bullet->time/10);
    }

    Rectangle dest = source;
    dest.x = bullet->position.x;
    dest.y = bullet->position.y;
    dest.width = bullet->size*2;
    dest.height = ((float)texture.height/((float)texture.width/4))*bullet->size*2;

    DrawTexturePro(texture, source, dest, {dest.width/2.0f, dest.height/2.0f}, -bullet->rotation*(360.0f/TAU), WHITE);
}