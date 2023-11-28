#include "global_vars.hpp"

void player_init(Actor* actor)
{
    actor->sprite_idx = 0;
    //this is temporary you should be loading from a file
    actor->region = { 0.0f, 0.0f, 24.0f, 24.0f };
    Animation idle = Animation();
    idle.start = 0;
    idle.end = 0;
    actor->max_speed = 3.0f;
    actor->animation_set.push_back(idle);

    actor->state = 1;
}

void player_step(Actor* actor)
{

    if(actor->state == -2)
    {
        actor->exists = false;
        return;
    }
    for(int i = total_pickups-1; i >= 0; i--)
    {
        if(Vector2Distance(pickup_list[i],actor->position) <= actor->size+PICKUP_SIZE)
        {
            total_pickups--;
            pickup_list[i] = pickup_list[total_pickups];
            actor->health += 5;
            PlaySound(sfx[0]);
            if(actor->health >= 100){actor->health = 100;}
        }
    }

    Vector2 dir = {0.0, 0.0};
    if(IsKeyDown(KEY_W)) dir.y-=1.0f;
    if(IsKeyDown(KEY_S)) dir.y+=1.0f;
    if(IsKeyDown(KEY_A)) dir.x-=1.0f;
    if(IsKeyDown(KEY_D)) dir.x+=1.0f;
    dir = Vector2Normalize(dir);


    if(Vector2Length(dir) > 0.05f)
    {
        actor->cur_speed += 0.2f;
        actor->move_dir = dir;
        //atan2d(dir.x,y1*y2);
        float angle = atan2f(dir.x,dir.y)+TAU*(17.0f/16.0f);
        if(signbit(angle)){angle*=-1.0f;}
        actor->facing = floorf(fmodf(angle, TAU)/(TAU/8.0f));
    }
    else
    {
        actor->cur_speed -= 0.6f;
    }

    float max = actor->max_speed;
    if(_g.walk_timer > 0.f){max *= 0.75f;}
    actor->cur_speed = Clamp(actor->cur_speed, 0, max);
    actor->velocity = Vector2Add(actor->velocity,Vector2Scale(actor->move_dir, actor->cur_speed));
    if(actor->cur_speed > Vector2Length(actor->velocity)){actor->cur_speed = Vector2Length(actor->velocity);}

    float ele = (delta*1.5f)+*(float*)&actor->params[2];

    if(ele >= TAU){ele -= TAU;}

    actor->params[2] = *(int*)&ele;
}

// void player_swap(Actor* actor, int state)
// {
//     if(actor->state == state){return;}
//     actor->aframe = 0;
//     actor->gframe = 0;
//     actor->state = state;
// }

void draw_gun();
void player_draw(Actor* actor)
{
    Texture texture = actor_sprite_list[actor->sprite_idx];
    Rectangle source = {0.0f, 0.0f, (float)texture.width/4, (float)texture.height/2};

    draw_status(actor);

    Rectangle dest = source;
    dest.width = 48;
    dest.height = 48;
    dest.x = actor->position.x;
    dest.y = actor->position.y;

    if(cursor_pos.x < 0){source.width *= -1.f;}

    if(cursor_pos.y <= 0){draw_gun();}

    if(actor->cur_speed > 0)
    {
        actor->params[7]++;
        source.x = (texture.width/4)*(actor->params[7]/10);
        source.y = texture.height/2;
    }
    else
    {
        actor->params[7] = 0;
    }

    DrawTexturePro(texture, source, dest, {dest.width/2.f, dest.height*0.75f}, 0, actor->draw_col);
    if(cursor_pos.y >= 0){draw_gun();}
}

void draw_gun()
{
    Vector2 aim_dir = Vector2Normalize(cursor_pos);
    Texture texture = gun_sprite_list[0];
    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle dest = source;
    dest.width/=5;
    dest.height/=5;
    dest.x = PLAYER.position.x + aim_dir.x*2;
    dest.y = PLAYER.position.y + aim_dir.y*2;

    
    float angle = acosf(Vector2DotProduct({1.0f, 0.0f}, aim_dir));
    if(aim_dir.y < 0.0f){angle*=-1.0f;}

    if(aim_dir.x < 0){source.height *= -1;}

    DrawTexturePro(texture, source, dest, {0, dest.height/2}, angle*RAD2DEG, WHITE);
    
}