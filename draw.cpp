#include "global_vars.hpp"

void draw_shadow(Actor actor);
void draw()
{
    //DrawRing({0.0f, 0.0f}, 1550.0f, 1540.0f, 0.0f, 360.0f, 100, RED);

    //DrawRectangleV(Vector2Scale(map_siz, -0.5f), map_siz, BLACK);
    DrawRectangleLinesEx(map_rect, 5.0f, BLACK);

    draw_hooks();
    
    //float max_dist = 100.0f * powf((threat*((float)blood+1.0f))*5.0f, 0.1f);
    //draw actors
    for(unsigned int i = 0; i < total_pickups; i++)
    {
        DrawCircleV(pickup_list[i], PICKUP_SIZE, {132, 228, 102, 255});
    }

    
    std::vector<int> actor_order;
    actor_order.push_back(0);
    for(int i = 1; i < total_actors; i++)
    {
        if(actor_list[i].exists){draw_shadow(actor_list[i]);}
        for(int j = 0; j < actor_order.size(); j++)
        {
            int o = actor_order[j];
            if(actor_list[i].position.y < actor_list[o].position.y && actor_list[i].state_timer >= 0)
            {
                actor_order.insert(actor_order.begin()+j, i);
                break;
            }
            if(j == actor_order.size()-1)
            {
                actor_order.push_back(i);
                break;
            }
        }
    }
    draw_shadow(PLAYER);

    for(int j = 0; j < actor_order.size(); j++)
    {
        int i = actor_order[j];
        Actor& actor = actor_list[i];
        if(!actor.exists){continue;}
        actor_draw[actor.type](&actor);
        
    }
    actor_order.clear();

    //draw projectiles
    for(unsigned int i = 0; i < total_bullets; i++)
    {
        bullet_draw[bullet_list[i].draw](&bullet_list[i]);
    }

    // Actor& actor = actor_list[0];
    // if(!actor.exists){return;}
    // actor_draw[actor.type](&actor);
    return;
}


void draw_shadow(Actor actor)
{
    switch(actor.type)
    {
        case 5:
            DrawEllipse(actor.position.x, actor.position.y+15.f/2.f, 15.f*1.5f, 15.f/2.f, {0, 0, 0, 100});
            break;
        default:
            DrawEllipse(actor.position.x, actor.position.y+actor.size/2.f, actor.size*1.5f, actor.size/2.f, {0, 0, 0, 100});
            break;
    }

}