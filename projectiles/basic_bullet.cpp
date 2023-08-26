#include "global_vars.hpp"

void basic_bullet_step(Bullet* bullet)
{
    for(unsigned int i = 1; i < actor_list.size(); i++)
    {
        if(actor_list[i].type == 3){continue;}
        if(Vector2Distance(actor_list[i].position, bullet->position) <= actor_list[i].size+2.0f)
        {
            bullet->exists = false;
            add_hit(&actor_list[i], (int)bullet);
            damage_actor(&actor_list[i], bullet->damage);
            return;
        }
    }

    bullet->time += delta;
    if(bullet->time >= bullet->time_limit)
    {
        bullet->exists = false;
    }
}

void basic_bullet_draw(Bullet* bullet)
{
    Texture texture = bullet_sprite_list[bullet->spr_idx];
    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};

    Rectangle dest = source;
    dest.x = bullet->position.x;
    dest.y = bullet->position.y;
    dest.width *= bullet->size;
    dest.height *= bullet->size;
    DrawTexturePro(texture, source, dest, {dest.width/2.0f, dest.height/2.0f}, -bullet->rotation*(360.0f/TAU), WHITE);
}