#include "global_vars.hpp"
#include "random.hpp"
#include "sprite.hpp"
#include "animation.hpp"
#include "bullet_funcs.hpp"
#include "bullet.hpp"
#include "actor_funcs.hpp"
#include "actor.hpp"


void draw()
{
    float fill_ratio = crate_time/CRATE_TIME_MAX;
    fill_ratio = fill_ratio>=0.5f?fill_ratio*0.5f:fill_ratio*2.0f;
    DrawCircleV(crate_pos, fill_ratio*CRATE_RADIUS, {245, 245, 245, 100});
    DrawRing(crate_pos, CRATE_RADIUS-2.0f, CRATE_RADIUS, 0.0f, 360.0f, 100, {245, 245, 245, 255});

    //darw actors
    for(unsigned int i = 0; i < actor_list.size(); i++)
    {
        Actor& actor = actor_list[i];
        if(!actor_list[i].exists){continue;}


        Animation& anim = actor.animation_set[actor.state];
        AnimationFrame& frame = anim.frame_set[actor.aframe];
        Vector2 offset = {-frame.region.width/2.0f, -frame.region.height/2.0f};
        Rectangle region = frame.region;
        if(actor.facing == 1){region.width = -region.width;}

        Vector2 a_pos = actor.position;
        a_pos.x = (int)a_pos.x;
        a_pos.y = (int)a_pos.y;

        DrawTextureRec(sprite_list[actor.sprite_idx].texture, region, Vector2Add(actor.position, offset), WHITE);
        
        if(!actor_list[0].exists){continue;}
        actor.gframe++;
        if(actor.gframe >= frame.frame_time)
        {
            actor.gframe = 0;
            actor.aframe++;
        }
        if(actor.aframe >= anim.frame_set.size())
        {
            actor.aframe = 0;
        }
    }

    //draw projectiles
    for(unsigned int i = 0; i < bullet_list.size(); i++)
    {
        bullet_draw[bullet_list[i].type](&bullet_list[i]);
    }





    return;
}