#include "global_vars.hpp"


void draw()
{
    //DrawRing({0.0f, 0.0f}, 1550.0f, 1540.0f, 0.0f, 360.0f, 100, RED);

    //DrawRectangleV(Vector2Scale(map_siz, -0.5f), map_siz, BLACK);
    DrawRectangleLinesEx(map_rect, 5.0f, BLACK);

    draw_hooks();
    
    //float max_dist = 100.0f * powf((threat*((float)blood+1.0f))*5.0f, 0.1f);
    //draw actors
    for(unsigned int i = 0; i < pickup_list.size(); i++)
    {
        DrawCircleV(pickup_list[i], PICKUP_SIZE, RED);
    }
    for(int i = total_actors-1; i >= 1; i--)
    {
        Actor& actor = actor_list[i];
        if(!actor.exists){continue;}
        actor_draw[actor.type](&actor);
        
    }
    //draw projectiles
    for(unsigned int i = 0; i < bullet_list.size(); i++)
    {
        bullet_draw[bullet_list[i].draw](&bullet_list[i]);
    }

    Actor& actor = actor_list[0];
    if(!actor.exists){return;}
    actor_draw[actor.type](&actor);
    return;
}