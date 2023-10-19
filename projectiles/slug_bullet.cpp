#include "global_vars.hpp"

void slug_bullet_step(Bullet* bullet)
{
    for(unsigned int i = 0; i < total_actors; i++)
    {
        if(!actor_list[i].exists){continue;}
        if(actor_list[i].state <= 0){continue;}
        if(i == 0 && bullet->parent_idx == 0){continue;}
        if(i != 0 && bullet->parent_idx != 0){continue;}

        if(Vector2Distance(actor_list[i].position, bullet->position) <= actor_list[i].size+bullet->size)
        {
            int j = 0;
            for(j = 0; j < hit_data.size(); j++)
            {
                if(hit_data[j].source == (int)bullet && hit_data[j].actor == &actor_list[i])
                {
                    j = -1;
                    break;
                }
            }
            if (j == -1) { continue; }
            bullet->params[2]--;
            add_hit(&actor_list[i], (int)bullet, 30);
            damage_actor(&actor_list[i], bullet->damage);
            apply_status(&actor_list[i], bullet->params[0], bullet->params[1]);
        }
    }

    bullet->time++;
    if(bullet->time >= bullet->time_limit)
    {
        bullet->exists = false;
        return;
    }
    if(bullet->params[2] <= 0)
    {
        bullet->exists = false;
    }

    float decel = (bullet->time/(float)bullet->time_limit);
    bullet->speed = Clamp(bullet->speed-decel*0.25f, 2.0f, bullet->speed);
}