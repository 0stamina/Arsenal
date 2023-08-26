#include "global_vars.hpp"

void player_init(Actor* actor)
{
    actor->sprite_idx = assign_sprite("resources/player.png");
    //this is temporary you should be loading from a file
    actor->region = { 0.0f, 0.0f, 24.0f, 24.0f };
    Animation idle = Animation();
    idle.start = 0;
    idle.end = 0;
    actor->animation_set.push_back(idle);
}

void player_step(Actor* actor)
{
    actor->move_dir = {0.0, 0.0};
    if(IsKeyDown(KEY_W)) actor->move_dir.y-=1.0f;
    if(IsKeyDown(KEY_S)) actor->move_dir.y+=1.0f;
    if(IsKeyDown(KEY_A)) actor->move_dir.x-=1.0f;
    if(IsKeyDown(KEY_D)) actor->move_dir.x+=1.0f;

    if(Vector2Length(actor->move_dir) > 0.05f)
    {
        Vector2 dir = Vector2Normalize(actor->move_dir);
        //atan2d(dir.x,y1*y2);
        float angle = atan2f(dir.x,dir.y)+TAU*(17.0f/16.0f);
        if(signbit(angle)){angle*=-1.0f;}
        actor->facing = floorf(fmodf(angle, TAU)/(TAU/8.0f));
    }


    float ele = (delta*1.5f)+*(float*)&actor->params[2];

    if(ele >= TAU){ele -= TAU;}

    actor->params[2] = *(int*)&ele;
}

void player_swap(Actor* actor, int state)
{
    if(actor->state == state){return;}
    actor->aframe = 0;
    actor->gframe = 0;
    actor->state = state;
}

void player_draw(Actor* actor)
{
    Rectangle region = actor->region;
    region.x = FACING_LUT[actor->facing]*region.width;

    Vector2 origin = Vector2Add(actor->position, { -region.width / 2.0f, -region.height / 2.0f });
    origin.x = (int)origin.x;
    origin.y = (int)origin.y;
    origin.y += sinf(*(float*)&actor->params[2])*2.0f-2.0f;
    if(actor->facing > 4){region.width*=-1.0f;}

    DrawTextureRec(sprite_list[actor->sprite_idx].texture, region, origin, WHITE);
}