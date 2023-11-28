#include "global_vars.hpp"

void add_hit(Actor* actor, int source, int time)
{
    Hit hit = Hit();
    hit.actor = actor;
    actor->damage_timer = 10;
    hit.source = source;
    hit.time = time;
    hit_data_list[total_hits] = hit;
    total_hits++;
    if(!IsSoundPlaying(sfx[1])){PlaySound(sfx[1]);}
}

void proccess_hits()
{
    for(int i = total_hits-1; i >= 0; i--)
    {
        hit_data_list[i].time--;
        if(hit_data_list[i].time <= 0)
        {
            total_hits--;
            hit_data_list[i] = hit_data_list[total_hits];
        }
    }
}