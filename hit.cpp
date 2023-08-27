#include "global_vars.hpp"

void add_hit(Actor* actor, int source, float time)
{
    Hit hit = Hit();
    hit.actor = actor;
    hit.source = source;
    hit.time = time;
    hit_data.push_back(hit);
}

void proccess_hits()
{
    for(int i = hit_data.size()-1; i >= 0; i--)
    {
        hit_data[i].time-=delta;
        if(hit_data[i].time <= 0.0f)
        {
            hit_data.erase(hit_data.begin()+i);
        }
    }
}