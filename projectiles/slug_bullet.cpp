
#include "global_vars.hpp"

void slug_bullet_step(Bullet* bullet)
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
        return;
    }

    float decel = (bullet->time/bullet->time_limit);
    bullet->speed = Clamp(bullet->speed-decel*0.2f, 2.0f, bullet->speed);
}