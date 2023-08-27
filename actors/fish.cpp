#include "global_vars.hpp"

void fish_init(Actor* actor)
{
    actor->sprite_idx = assign_sprite("resources/fish.png");
    actor->region = { 0.0f, 0.0f, 24.0f, 24.0f };
    Animation idle = Animation();
    idle.start = 0;
    idle.end = 0;
    actor->animation_set.push_back(idle);

    active_fish++;
    float f;

    //curr angle
    f = randf(0, TAU);
    actor->params[0] = *(int*)&f;
    //targ angle
    f = randf(0, TAU);
    actor->params[1] = *(int*)&f;
    //angle accel
    f = 0.0f;
    actor->params[2] = *(int*)&f;

    actor->speed = 1.25f;
}

void fish_step(Actor* actor)
{
    if(Vector2Distance(PLAYER.position, actor->position) >= 550)
    {
        Vector2 dir = Vector2Normalize(Vector2Subtract(PLAYER.position, actor->position));
        actor->position = Vector2Add(PLAYER.position, Vector2Scale(dir, 400));
    }


    float accel = *(float*)&actor->params[2];
    for(int i = actor_list.size()-1; i >= 0; i--)
    {
        if(actor_list[i].type != 3)
        {
            if(Vector2Distance(actor_list[i].position, actor->position) < 100.0f)
            {
                Vector2 dir = Vector2Normalize(Vector2Subtract(actor->position, actor_list[i].position));
                //atan2d(x1*y2-y1*x2,x1*x2+y1*y2);
                float angle = atan2f(-dir.y,dir.x);
                //actor->params[0] = *(int*)&angle;
                if(angle < 0){angle = TAU+angle;}
                if(angle > TAU){angle = TAU-angle;}
                actor->params[1] = *(int*)&angle;

                float dif = angle-*(float*)&actor->params[0];
                dif = fmod(dif+TAU/2.0f,TAU)-TAU/2.0f;
                if(abs(dif) > TAU/2.0){dif = TAU+dif;}
                dif/=30.0f;
                float a = dif+*(float*)&actor->params[0];
                if(a < 0){a = TAU+a;}
                if(a > TAU){a = TAU-a;}

                actor->params[0] = *(int*)&a;

                

                //float dif = *(float*)&actor->params[0]-*(float*)&actor->params[1];

            }
        }
    }

    float dif = *(float*)&actor->params[1]-*(float*)&actor->params[0];
    dif = fmod(dif+TAU/2.0f,TAU)-TAU/2.0f;
    if(abs(dif) > TAU/2.0){dif = TAU+dif;}

    if(dif > 0.0f){accel+=0.005f;}
    else{accel-=0.005f;}

    if(accel > 0.02f){accel = 0.02f;}
    if(accel < -0.02f){accel = -0.02f;}

    actor->params[2] = *(int*)&accel;

    if (abs(accel) > abs(dif))
    {
        float f = randf(0, TAU);
        actor->params[1] = *(int*)&f;
    }

    float a = accel+*(float*)&actor->params[0];
    if(a < 0){a = TAU+a;}
    if(a > TAU){a = TAU-a;}
    actor->params[0] = *(int*)&a;
    actor->move_dir = {cosf(*(float*)&actor->params[0]), -sinf(*(float*)&actor->params[0])};
    
    
    if(Vector2Length(actor->move_dir) > 0.05f)
    {
        Vector2 dir = Vector2Normalize(actor->move_dir);
        float angle = atan2f(dir.x,dir.y)+TAU*(17.0f/16.0f);
        if(signbit(angle)){angle*=-1.0f;}
        actor->facing = floorf(fmodf(angle, TAU)/(TAU/8.0f));
    }
}


void fish_draw(Actor* actor)
{
    Rectangle region = actor->region;
    region.x = FACING_LUT[actor->facing]*region.width;

    Vector2 origin = Vector2Add(actor->position, { -region.width / 2.0f, -region.height / 2.0f });
    origin.x = (int)origin.x;
    origin.y = (int)origin.y;
    if(actor->facing > 4){region.width*=-1.0f;}

    DrawTextureRec(sprite_list[actor->sprite_idx].texture, region, origin, WHITE);
}