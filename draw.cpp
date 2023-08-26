#include "global_vars.hpp"


void draw()
{
    draw_hooks();
    
    //draw actors
    for(unsigned int i = 0; i < actor_list.size(); i++)
    {
        Actor& actor = actor_list[i];
        if(!actor_list[i].exists){continue;}
        actor_draw[actor.type](&actor);
    }
    //draw projectiles
    for(unsigned int i = 0; i < bullet_list.size(); i++)
    {
        bullet_draw[bullet_list[i].type](&bullet_list[i]);
    }

    if(spear_state)
    {
        Rectangle src = {0.0f, 0.0f, spear_sprite_list[0].width, spear_sprite_list[0].height};
        Rectangle dest = {spear_head.x, spear_head.y, spear_sprite_list[0].width, spear_sprite_list[0].height};
        float angle = atan2f(-spear_dir.y,spear_dir.x);

        DrawTexturePro(spear_sprite_list[0], src, dest, {dest.width, dest.height/2.0f}, -angle*RAD2DEG, WHITE);
    }





    return;
}