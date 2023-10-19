
#include "global_vars.hpp"
namespace wall_slime
{

    const int SPAWN = -1;
    const int WAIT = 1;
    const int BIRTH = 2;

    float max_size = 40.f;

    void idle(Actor* actor);
    void spawn_slime(Actor* actor);
    void spawning(Actor* actor);
}

using namespace wall_slime;

void wall_slime_init(Actor* actor)
{
    actor->sprite_idx = assign_sprite("resources/enemyguy.png");
    actor->params[4] = -1;
    actor->size = 1.0f;
    actor->max_speed = 1.0f;
    actor->cur_speed = actor->max_speed;

    actor->health = 1000;
    actor->health *= 1+1*(BLOOD_THREAT/50);

    actor->blood_value = 3;

    actor->state = SPAWN;
    actor->state_timer = randi(0,20);

    actor->pushable = false;
}

void wall_slime_step(Actor* actor)
{
    switch(actor->state)
    {
        case SPAWN:
            spawning(actor);
            break;
        case WAIT:
            idle(actor);
            break;
        case BIRTH:
            spawn_slime(actor);
            break;
    }
}

void wall_slime_draw(Actor* actor)
{
    Texture texture = sprite_list[actor->sprite_idx].texture;
    Rectangle source = {texture.width/2, 0.0f, texture.width/2, (int)(texture.height*(actor->size/max_size))};

    draw_status(actor);

    if(actor->damage_timer > 0){actor->draw_col = RED;}

    Rectangle dest = source;
    dest.width = 160;
    dest.height = 120*(actor->size/max_size);
    dest.x = actor->position.x;
    dest.y = actor->position.y;

    DrawTexturePro(texture, source, dest, {dest.width/2.f, dest.height*0.75f}, 0, actor->draw_col);
}

void wall_slime::spawning(Actor* actor)
{
    if(actor->state_timer < 20){return;}
    actor->size += 1.f;
    if(actor->size >= max_size)
    {
        actor->size = max_size;
        actor->state = WAIT;
        actor->state_timer = 0;
    }
}

void wall_slime::idle(Actor* actor)
{
    if(actor->state_timer >= 50)
    {
        actor->state = BIRTH;
        actor->state_timer = 0;
    }
}

void wall_slime::spawn_slime(Actor* actor)
{
    Vector2 offset = {randi(-5, 5), randi(-5, 5)};
    init_actor(Vector2Add(actor->position, offset), 2);
    actor->state = WAIT;
    actor->state_timer = 0;
}