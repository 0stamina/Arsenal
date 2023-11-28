
#include "global_vars.hpp"
namespace basic_enemy
{
    const int DIE = -2;
    const int SPAWN = -1;
    const int FOLLOW = 1;
    const int AIM = 2;
    const int SHOOT = 3;
    const int RELOAD = 4;

    float max_size = 10.f;

    void follow_player(Actor* actor);
    void spawning(Actor* actor);
    void dying(Actor* actor);
}

using namespace basic_enemy;

void basic_enemy_init(Actor* actor)
{
    actor->sprite_idx = 1;
    actor->params[4] = -1;
    actor->size = 1.0f;
    actor->max_speed = 1.2f;
    actor->cur_speed = actor->max_speed;

    actor->health = 100;
    actor->health *= 1+0.5*(BLOOD_THREAT/50);

    actor->blood_value = 1;

    actor->state = SPAWN;
    actor->state_timer = randi(0,20);

    actor->touch_damage = true;
}

void basic_enemy_step(Actor* actor)
{



    switch(actor->state)
    {
        case DIE:
            dying(actor);
            break;
        case SPAWN:
            spawning(actor);
            break;
        case FOLLOW:
            follow_player(actor);
            break;
    }
}

void basic_enemy_draw(Actor* actor)
{
    if(actor->state == DIE){return;}
    Texture texture = actor_sprite_list[actor->sprite_idx];
    Rectangle source = {0.0f, 0.0f, texture.width/2, (int)(texture.height*(actor->size/max_size))};

    draw_status(actor);

    Rectangle dest;
    dest.width = 32;
    dest.height = 26*(actor->size/max_size);
    dest.x = actor->position.x;
    dest.y = actor->position.y;

    //if(actor->move_dir.y < 0){source.x = texture.width/2;}
    DrawTexturePro(texture, source, dest, {dest.width/2.f, dest.height*0.75f}, 0, actor->draw_col);
}

void basic_enemy::dying(Actor* actor)
{
    if(actor->state_timer > 0)
    {
        
        _g.point_stash += actor->blood_value;
        _g.total_kills++;
        _g.multikills++;
        _g.multikill_timer = MULTIKILL_TIME;

        if(randf(0.f, 1.f) <= PICKUP_RATE){pickup_list[total_pickups++] = actor->position;}
        actor->exists = false;
    }
}

void basic_enemy::spawning(Actor* actor)
{
    if(actor->state_timer < 20){return;}
    actor->size += 0.25f;
    if(actor->size >= max_size)
    {
        actor->size = max_size;
        actor->state = FOLLOW;
        actor->state_timer = 0;
    }
}

void basic_enemy::follow_player(Actor* actor)
{
    actor->move_dir = Vector2Normalize(Vector2Subtract(PLAYER.position, actor->position));

    actor->cur_speed += 0.2f;
    actor->cur_speed = Clamp(actor->cur_speed, 0, actor->max_speed);

    actor->velocity = Vector2Add(actor->velocity,Vector2Scale(actor->move_dir, actor->cur_speed));
    if(actor->cur_speed > Vector2Length(actor->velocity)){actor->cur_speed = Vector2Length(actor->velocity);}
}