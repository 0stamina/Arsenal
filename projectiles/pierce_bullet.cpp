#include "global_vars.hpp"

void pierce_bullet_step(Bullet* bullet)
{
    
    for(unsigned int i = 1; i < actor_list.size(); i++)
    {
        int j = 0;
        for(j = 0; j < hit_data.size(); j++)
        {
            if(hit_data[j].source == (int)bullet && hit_data[j].actor == &actor_list[i]){j = -1;break;}
        }
        if (j == -1) { continue; };

        if(Vector2Distance(actor_list[i].position, bullet->position) <= actor_list[i].size+2.0f)
        {
            add_hit(&actor_list[i], (int)bullet);
            damage_actor(&actor_list[i], bullet->damage);
        }
    }

    bullet->time += delta;
    if(bullet->time >= bullet->time_limit)
    {
        bullet->exists = false;
    }
}

void pierce_bullet_draw(Bullet* bullet)
{
    // Texture texture = bullet_sprite_list[bullet->spr_idx];
    // Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};

    // Rectangle dest = source;
    // dest.x = bullet->position.x;
    // dest.y = bullet->position.y;
    // dest.width *= bullet->size;
    // dest.height *= bullet->size;
    // DrawTexturePro(texture, source, dest, {dest.width/2.0f, dest.height/2.0f}, -bullet->rotation*(360.0f/TAU), WHITE);
    DrawCircleV(bullet->position, 7.0f*bullet->size, ORANGE);
}