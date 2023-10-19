
#include "global_vars.hpp"

namespace basic_shooter
{

    const int SPAWN = -1;
    const int FOLLOW = 1;
    const int AIM = 2;
    const int SHOOT = 3;
    const int RELOAD = 4;

    float max_size = 10.f;

    void follow_player(Actor* actor);
    void spawning(Actor* actor);
    void shoot(Actor* actor);
    void aim(Actor* actor);
    void shoot_idle(Actor* actor);
}

using namespace basic_shooter;

void basic_shooter_init(Actor* actor)
{
    actor->sprite_idx = assign_sprite("resources/gunenemy.png");
    actor->params[4] = -1;
    actor->size = 1.0f;
    actor->max_speed = 1.0f;
    actor->cur_speed = actor->max_speed;

    actor->health = 90;
    actor->health *= 1+0.5*(BLOOD_THREAT/50);

    actor->blood_value = 1;

    actor->state = SPAWN;
    actor->state_timer = randi(0,8);
}

void basic_shooter_step(Actor* actor)
{
    switch(actor->state)
    {
        case SPAWN:
            spawning(actor);
            break;
        case FOLLOW:
            follow_player(actor);
            break;
        case SHOOT:
            shoot(actor);
            break;
        case AIM:
            aim(actor);
            break;
        case RELOAD:
            shoot_idle(actor);
            break;
    }
}

void basic_shooter_draw(Actor* actor)
{
    Texture texture = sprite_list[actor->sprite_idx].texture;
    Rectangle source = {0.0f, 0.0f, texture.width/2, texture.height};
    Vector2 dir = Vector2Normalize(Vector2Subtract(PLAYER.position, actor->position));

    draw_status(actor);

    if(actor->damage_timer > 0){actor->draw_col = RED;}

    Rectangle dest = source;
    dest.width = 32*(actor->size/max_size);
    dest.height = 32;
    dest.x = actor->position.x;
    dest.y = actor->position.y;

    if(dir.y < 0){source.x = texture.width/2;}
    if(dir.x < 0){source.width*=-1;}
    DrawTexturePro(texture, source, dest, {dest.width/2.f, dest.height*0.75f}, 0, actor->draw_col);
}

void basic_shooter::spawning(Actor* actor)
{
    if(actor->state_timer < 8){return;}
    actor->size += 0.25f;
    if(actor->size >= max_size)
    {
        actor->size = max_size;
        actor->state = FOLLOW;
        actor->state_timer = 0;
    }
}

void basic_shooter::aim(Actor* actor)
{
    if(actor->state_timer >= 60)
    {
        actor->state = SHOOT;
        actor->state_timer = 0;
    }
}

void basic_shooter::shoot(Actor* actor)
{
    Vector2 dir = Vector2Normalize(Vector2Subtract(PLAYER.position, actor->position));
    Vector2 pos = Vector2Add(actor->position, Vector2Scale(dir, 20.f));
    float angle = acosf(Vector2DotProduct({1.0f, 0.0f}, dir));
    if(dir.y > 0.0f){angle*=-1.0f;}

    Bullet bullet = Bullet();
    bullet.parent_idx = ((int)actor-(int)actor_list)/sizeof(Actor);
    bullet.damage = 3;
    bullet.size = 15.f;
    bullet.speed = 3.f;

    init_bullet(&bullet, angle, pos, 0);
    bullet_list.push_back(bullet);

    actor->state = RELOAD;
    actor->state_timer = 0;
}

void basic_shooter::shoot_idle(Actor* actor)
{
    if(actor->state_timer >= 150)
    {
        actor->state = AIM;
        if(Vector2Distance(PLAYER.position, actor->position) > 300.f)
        {
            actor->state = FOLLOW;
            actor->state_timer = 0;
        }
        actor->state_timer = 0;
    }
}

void basic_shooter::follow_player(Actor* actor)
{   
    Vector2 heading = Vector2Subtract(PLAYER.position, actor->position);
    actor->move_dir = Vector2Normalize(heading);

    actor->cur_speed += 0.2f;
    actor->cur_speed = Clamp(actor->cur_speed, 0, actor->max_speed);


    actor->velocity = Vector2Add(actor->velocity,Vector2Scale(actor->move_dir, actor->cur_speed));
    if(actor->cur_speed > Vector2Length(actor->velocity)){actor->cur_speed = Vector2Length(actor->velocity);}


    if(Vector2Length(heading) <= 200.f)
    {
        actor->state = AIM;
        actor->state_timer = 0;
    }
}