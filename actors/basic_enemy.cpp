
#include "bullet_funcs.hpp"
#include "bullet.hpp"
#include "actor_funcs.hpp"
#include "actor.hpp"
#include "random.hpp"
#include "global_vars.hpp"


void basic_enemy_init(Actor* actor)
{
    actor->params[4] = -1;
    actor->size = 10.0f;
    actor->speed = 2.15f;
}

void basic_enemy_step(Actor* actor)
{
    float max_dist = 100.0f * powf((threat*((float)blood+1.0f))+1.0f, 0.2f);
    if(Vector2Distance(PLAYER.position, actor->position) >= 550)
    {
        Vector2 dir = Vector2Normalize(Vector2Subtract(PLAYER.position, actor->position));
        actor->position = Vector2Add(PLAYER.position, Vector2Scale(dir, 400));
    }

    float accel = *(float*)&actor->params[2];

    float dif = *(float*)&actor->params[1]-*(float*)&actor->params[0];

    dif = fmod(dif+(TAU/2.0),TAU)-TAU/2.0;
    if(abs(dif) > TAU/2.0){dif = TAU+dif;}

    switch(actor->state)
    {

        //wander
        case 0:
        {

            if(dif > 0.0f){accel+=0.001f;}
            else{accel-=0.001f;}

            if(accel > 0.02f){accel = 0.02f;}
            if(accel < -0.02f){accel = -0.02f;}

            actor->params[2] = *(int*)&accel;

            if(Vector2Distance(PLAYER.position, actor->position) < max_dist)
            {
                actor->params[4] = (int)&PLAYER;
                actor->state = 1;
                break;
            }

            for(int i = actor_list.size()-1; i >= 1; i--)
            {
                if(actor_list[i].type != 2)
                {
                    if(Vector2Distance(actor_list[i].position, actor->position) < max_dist/2.0f)
                    {
                        actor->params[4] = (int)&actor_list[i];
                        actor->state = 1;
                        break;
                    }
                }
            }

            if (abs(accel) > abs(dif))
            {
                float f = randf(0, TAU);
                actor->params[1] = *(int*)&f;
            }
            break;
        }
        //chase
        case 1:
        {
            if(dif > 0.0f){accel+=0.005f;}
            else{accel-=0.005f;}

            if(accel > 0.1f){accel = 0.1f;}
            if(accel < -0.1f){accel = -0.1f;}

            actor->params[2] = *(int*)&accel;

            if(actor->params[4] != (int)&PLAYER && Vector2Distance(PLAYER.position, actor->position) < max_dist)
            {
                actor->params[4] = (int)&PLAYER;
                actor->state = 1;
                break;
            }
            if(!((Actor*)actor->params[4])->exists || Vector2Distance(((Actor*)actor->params[4])->position, actor->position) > max_dist*2.0f)
            {
                actor->params[4] = -1;
                actor->state = 0;
                break;
            }

            if (abs(accel) > abs(dif))
            {
                actor->params[0] = actor->params[1];
                actor->params[2] = 0;
            }
            
            Vector2 dir = Vector2Normalize(Vector2Subtract(((Actor*)actor->params[4])->position, actor->position));
            float angle = atan2f(-dir.y,dir.x);
            if(angle < 0){angle = TAU+angle;}
            if(angle > TAU){angle = TAU-angle;}
            actor->params[1] = *(int*)&angle;

            break;
        }
    }

    float a = accel+*(float*)&actor->params[0];
    if(a < 0){a = TAU+a;}
    if(a > TAU){a = TAU-a;}
    actor->params[0] = *(int*)&a;
    actor->move_dir = {cosf(*(float*)&actor->params[0]), -sinf(*(float*)&actor->params[0])};
    
}