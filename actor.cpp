#include "global_vars.hpp"


int init_actor(Vector2 pos, int type)
{
    if(total_actors >= 500){return -1;}
    if(total_actor_types[type] >= max_actor_types[type]){return -2;}

    Actor &actor = actor_list[total_actors];
    actor = Actor();
    actor.state = 0;
    actor.type = type;

    actor.position.x = pos.x;
    actor.position.y = pos.y;


    actor.exists = true;

    actor_init[actor.type](&actor);
    total_actors++;
    total_actor_types[type]++;
}

void destroy_actor(int idx)
{
    Actor actor = actor_list[idx];
    unassign_sprite(actor.sprite_idx);

    actor_list[idx] = actor_list[total_actors-1];
    total_actors--;
    total_actor_types[actor.type]--;
}

void move_actor(Actor* actor)
{
    actor->position = Vector2Add(actor->position, actor->velocity);
    actor->velocity = {0.0f,0.0f};    
}

void push_actor(Actor* a1, Actor* a2, float dist)
{
    if(a1->pushable && a2->pushable)
    {
        Vector2 dir = Vector2Scale(Vector2Normalize(Vector2Subtract(a2->position, a1->position)), -dist/2.0f);
        a1->velocity = Vector2Add(a1->velocity, dir);
    }
    else if(a1->pushable)
    {
        Vector2 dir = Vector2Scale(Vector2Normalize(Vector2Subtract(a2->position, a1->position)), -dist);
        a1->velocity = Vector2Add(a1->velocity, dir);
    }



    //touch damage
    if(a2 == &PLAYER && PLAYER.damage_timer < -30 && a1->touch_damage)
    {
        PLAYER.damage_timer = 10;
        damage_actor(&PLAYER, 3);
        if(!IsSoundPlaying(sfx[1])){PlaySound(sfx[1]);}
    }
}

void damage_actor(Actor* actor, int damage)
{
    actor->health -= damage;
    if(actor->health <= 0)
    {
        actor->state = -2;
        actor->state_timer = 0;
    }
}

void collision(Actor* actor)
{
    if(actor == &PLAYER)
    {
        for(int j = total_actors-1; j >= 0; j--)
        {
            if(actor_list[j].pushable){continue;}
            if(actor_list[j].state < 0){continue;}
            float dist = Vector2Distance(
                Vector2Add(actor->position, actor->velocity), 
                Vector2Add(actor_list[j].position, actor_list[j].velocity)
                );
            if(dist <= actor->size + actor_list[j].size)
            {
                push_actor(actor, &actor_list[j], ((actor->size+actor_list[j].size)-dist)/2.0f);
            }
        }
        return;
    }

    for(int j = total_actors-1; j >= 0; j--)
    {
        if(actor_list[j].state < 0){continue;}
        float dist = Vector2Distance(
            Vector2Add(actor->position, actor->velocity), 
            Vector2Add(actor_list[j].position, actor_list[j].velocity)
            );
        if(dist <= actor->size + actor_list[j].size)
        {
            push_actor(actor, &actor_list[j], ((actor->size+actor_list[j].size)-dist)/2.0f);
        }
    }
}

void wall_collision(Actor* actor)
{
    float dist_x = 0;
    float dist_y = 0;

    if(actor->position.x > map_siz/2.f-actor->size){dist_x = map_siz/2.f-actor->position.x-actor->size;}
    if(actor->position.x < -map_siz/2.f+actor->size){dist_x = (-map_siz/2.f)-actor->position.x+actor->size;}
    if(actor->position.y > map_siz/2.f-actor->size){dist_y = map_siz/2.f-actor->position.y-actor->size;}
    if(actor->position.y < -map_siz/2.f+actor->size){dist_y = (-map_siz/2.f)-actor->position.y+actor->size;}

    actor->velocity = Vector2Add(actor->velocity, {dist_x, dist_y});
}

void apply_status(Actor* actor, int status, int time)
{
    //if(actor->curr_status > -1){return;}

    actor->curr_status = status;
    actor->status_timer = time;
}

void process_status(Actor* actor)
{
    switch(actor->curr_status)
    {
        case BURN_IDX:
            if(actor->status_timer%20 == 0)
            {
                damage_actor(actor, 5);
            }
            break;
    }
    

    if(actor->curr_status != -1)
    {
        actor->status_timer--;
        if(actor->status_timer <= 0)
        {
            actor->curr_status = -1;
        }
    }
}

void draw_status(Actor* actor)
{
    actor->draw_col = WHITE;
    switch(actor->curr_status)
    {
        case BURN_IDX:
            actor->draw_col = ORANGE;
            break;
    }

    if(actor->damage_timer > 0){actor->draw_col = {230, 21, 142, 255};}
}

