#include "global_vars.hpp"

int prev_gun = -1;

void fill_hooks()
{
    float fill_delta = delta*5.0f;

    for(int i = hook_list.size()-1; i >= 0; i--)
    {
        //box unlock
        if(Vector2Distance(actor_list[0].position, hook_list[i].position) < CRATE_RADIUS)
        {
            hook_list[i].amt += fill_delta;
            if(hook_list[i].amt >= blood)
            {
                hook_list[i].amt = blood;
            }

            if(hook_list[i].amt >= CRATE_TIME_MAX)
            {
                int tier = blood/10;
                PLAYER.health += blood*2;
                if (PLAYER.health >= 100) { PLAYER.health = 100; }
                blood = 0;
                
                score += powf(2.0f, tier-1);

                hook_list.erase(hook_list.begin()+i);

                do
                {
                    curr_gun = randi(1, gun_list.size());
                }
                while(prev_gun == curr_gun);
                prev_gun = curr_gun;
                swap_gun();

                new_hook();
            }
        }
        else
        {
            hook_list[i].amt -= fill_delta;
        }

        
        
        // //this is out of the if because of enemies
        // if(hook_list[i].amt >= CRATE_TIME_MAX)
        // {
        //     blood -= CRATE_TIME_MAX;
        //     hook_list[i].tier ++;
        //     hook_list[i].amt = 0;
        // }
        if(hook_list[i].amt < 0)
        {
            hook_list[i].amt = 0;
        }
        //     if(hook_list[i].tier != 0)
        //     {
        //         score += powf(2.0f, hook_list[i].tier-1);

        //         PLAYER.health += 10*(int)(hook_list[i].tier);
        //         if (PLAYER.health >= 100) { PLAYER.health = 100; }

        //         hook_list.erase(hook_list.begin()+i);

        //         do
        //         {
        //             curr_gun = randi(1, gun_list.size());
        //         }
        //         while(prev_gun == curr_gun);
        //         prev_gun = curr_gun;
        //         swap_gun();

        //         new_hook();
        //     }
        // }
    }
}


void new_hook()
{
    Hook h = Hook();

    float angle = randf(0.0f,TAU);
    float dist = randf(100.0f, 2000.0f);
    h.position = {cosf(angle)*dist, -sinf(angle)*dist};

    for(int i = 0; i < hook_list.size(); i++)
    {
        if(Vector2Distance(h.position, hook_list[i].position) < CRATE_RADIUS*4.0f)
        {
            angle = randf(0.0f,TAU);
            dist = randf(100.0f, 2000.0f);
            h.position = {cosf(angle)*dist, -sinf(angle)*dist};

            i = -1;
        }
    }

    hook_list.push_back(h);
}

void draw_hooks()
{
    for(int i = 0; i < hook_list.size(); i++)
    {
        float fill_ratio = hook_list[i].amt/CRATE_TIME_MAX;
        //fill_ratio = 0.5f-sinf(asinf(1.0f-2.0f*fill_ratio)/3.0f);
        DrawCircleV(hook_list[i].position, fill_ratio*CRATE_RADIUS, {245, 245, 245, 100});
        DrawRing(hook_list[i].position, CRATE_RADIUS-2.0f, CRATE_RADIUS, 0.0f, 360.0f, 100, {245, 245, 245, 255});
    }
}