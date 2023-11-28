#include "global_vars.hpp"

void bomb_step(Bullet* bullet)
{

    
    if(bullet->from_player)
    {
        for(int i = 1; i < total_actors; i++)
        {
            if(!actor_list[i].exists){break;}
            if(actor_list[i].state <= 0){continue;}

            if(Vector2Distance(actor_list[i].position, bullet->position) <= actor_list[i].size+bullet->size)
            {
                bullet->exists = false;
                Bullet explo1 = Bullet();
                explo1.from_player = true;
                explo1.damage = bullet->damage;
                init_bullet(&explo1, 0, bullet->position, 5);
                bullet_list[total_bullets++] = explo1;
                

                Bullet explo2 = Bullet();
                explo2.from_player = false;
                explo2.damage = bullet->damage/50;

                init_bullet(&explo2, 0, bullet->position, 5);
                bullet_list[total_bullets++] = explo2;
                return;
            }
        }
    }else{
        if(Vector2Distance(PLAYER.position, bullet->position) <= PLAYER.size+bullet->size)
        {
            bullet->exists = false;
            Bullet explo = Bullet();
            explo.from_player = false;
            explo.damage = bullet->damage;

            init_bullet(&explo, 0, bullet->position, 5);
            bullet_list[total_bullets++] = explo;
            return;
        }
    }

    
    if(bullet->params[2] > 0)
    {
        bullet->params[2]--;
        return;
    }

    bullet->speed = 0;

    bullet->time--;
    if(bullet->time <= 0)
    {
        bullet->exists = false;

        Bullet explo1 = Bullet();
        explo1.from_player = bullet->from_player;
        explo1.damage = bullet->damage;

        init_bullet(&explo1, 0, bullet->position, 5);
        bullet_list[total_bullets++] = explo1;

        Bullet explo2 = Bullet();
        explo2.from_player = false;
        explo2.damage = bullet->damage/50;

        init_bullet(&explo2, 0, bullet->position, 5);
        bullet_list[total_bullets++] = explo2;
        return;
    }
}