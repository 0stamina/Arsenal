#include "global_vars.hpp"

void basic_bullet_step(Bullet* bullet)
{
    if(bullet->from_player)
    {
        for(int i = 1; i < total_actors; i++)
        {
            if(!actor_list[i].exists){break;}
            if(actor_list[i].state <= 0){continue;}

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
    }else{
        if(PLAYER.damage_timer < -30 && Vector2Distance(PLAYER.position, bullet->position) <= PLAYER.size+bullet->size)
        {
            bullet->params[2]--;
            PLAYER.damage_timer = 10;
            damage_actor(&PLAYER, bullet->damage);
            apply_status(&PLAYER, bullet->params[0], bullet->params[1]);
        }
    }
    

    bullet->time--;
    if(bullet->time <= 0)
    {
        bullet->exists = false;
    }
    if(bullet->params[2] <= 0)
    {
        bullet->exists = false;
    }
}