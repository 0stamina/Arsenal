#include "global_vars.hpp"


void init_actor(Actor* actor, Vector2 pos, int type)
{
    actor->state = 0;
    actor->type = type;

    actor->position.x = pos.x;
    actor->position.y = pos.y;

    actor->exists = true;
    actor_init[actor->type](actor);
    actor_list.push_back(*actor);
}

void destroy_actor(Actor* actor)
{
    unassign_sprite(actor->sprite_idx);
    delete actor;
}

void move_actor(Actor* actor, Vector2 dir)
{
    actor->position = Vector2Add(actor->position, dir);
}

void push_actor(Actor* a1, Actor* a2, float dist)
{
    Vector2 dir = Vector2Scale(Vector2Normalize(Vector2Subtract(a2->position, a1->position)), dist/2.0f);

    move_actor(a1, Vector2Scale(dir, -1.0f));
    //player damage
    
        
    if(a2 == &actor_list[0])
    {
        int j = 0;
        for(j = 0; j < hit_data.size(); j++)
        {
            if(hit_data[j].source == (int)a1 && hit_data[j].actor == a2){j = -1;break;}
        }

        if (j != -1)
        {
            add_hit(a2, (int)a1);
            damage_actor(a2, 1);
        }
        
    }
}

void damage_actor(Actor* actor, int damage)
{
    actor->health -= damage;
    if(actor->health <= 0)
    {
        actor->exists = false;
    }
}