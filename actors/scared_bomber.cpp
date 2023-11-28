
#include "global_vars.hpp"

namespace scared_bomber
{
    const int DIE = -2;
    const int SPAWN = -1;
    const int FOLLOW = 1;
    const int MOVE = 2;
    const int THROW = 3;
    const int RUN = 4;

    const float min_range = 50.f;
    const float max_range = 250.f;

    const float max_size = 15.f;

    void follow_player(Actor* actor);
    void spawning(Actor* actor);
    void dying(Actor* actor);
    void throw_bombs(Actor* actor);
    void reposition(Actor* actor);
    void run_away(Actor* actor);
}

using namespace scared_bomber;

void scared_bomber_init(Actor* actor)
{
    actor->sprite_idx = 3;
    actor->params[4] = -1;
    actor->size = 1.0f;
    actor->max_speed = 2.0f;
    actor->cur_speed = actor->max_speed;

    actor->health = 90;
    actor->health *= 1+0.5*(BLOOD_THREAT/50);

    actor->blood_value = 2;

    actor->state = SPAWN;
    actor->state_timer = randi(0,15);
}

void scared_bomber_step(Actor* actor)
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
        case THROW:
            throw_bombs(actor);
            break;
        case MOVE:
            reposition(actor);
            break;
        case RUN:
            run_away(actor);
            break;
        default:
            break;
    }

    if(actor->state > 0 && Vector2Distance(actor->position, PLAYER.position) < min_range*0.5f)
    {
        actor->state = RUN;
        actor->state_timer = 0;
    }
}

void scared_bomber_draw(Actor* actor)
{
    if(actor->state == DIE){return;}
    Texture texture = actor_sprite_list[actor->sprite_idx];
    Rectangle source = {0.0f, texture.height-(texture.height*(actor->size/max_size)), texture.width, (int)(texture.height*(actor->size/max_size))};

    draw_status(actor);


    Rectangle dest;
    dest.width = 47;
    dest.height = 38*(actor->size/max_size);
    dest.x = actor->position.x;
    dest.y = actor->position.y;

    //if(actor->move_dir.y < 0){source.x = texture.width/2;}
    DrawTexturePro(texture, source, dest, {dest.width/2.f, dest.height*0.75f}, 0, actor->draw_col);
}

void scared_bomber::dying(Actor* actor)
{
    if(actor->state_timer > 0)
    {
        _g.point_stash += actor->blood_value;
        _g.total_kills++;
        _g.multikills++;
        _g.multikill_timer = MULTIKILL_TIME;

        if(randf(0.f, 1.f) <= PICKUP_RATE){pickup_list[total_pickups++] = actor->position;}
        actor->exists = false;

        Bullet explo = Bullet();
        explo.from_player = true;
        explo.damage = 50;

        init_bullet(&explo, 0, actor->position, 5);
        bullet_list[total_bullets++] = explo;
    }
}

void scared_bomber::spawning(Actor* actor)
{
    if(actor->state_timer < 15){return;}
    actor->size += 0.2f;
    if(actor->size >= max_size)
    {
        actor->size = max_size;
        actor->state = FOLLOW;
        actor->state_timer = 0;
    }
}

void scared_bomber::follow_player(Actor* actor)
{
    Vector2 heading = Vector2Subtract(PLAYER.position, actor->position);
    actor->move_dir = Vector2Normalize(heading);

    actor->cur_speed += 1.f;
    actor->cur_speed = Clamp(actor->cur_speed, 0, actor->max_speed);


    actor->velocity = Vector2Add(actor->velocity,Vector2Scale(actor->move_dir, actor->cur_speed));
    if(actor->cur_speed > Vector2Length(actor->velocity)){actor->cur_speed = Vector2Length(actor->velocity);}


    if(Vector2Length(heading) <= (min_range+max_range)/2.f)
    {
        actor->state = THROW;
        actor->state_timer = 0;
    }
}

void scared_bomber::reposition(Actor* actor)
{
    if(actor->state_timer == 1)
    {
        // angle from the player to this actor(radians)
        Vector2 dir = Vector2Normalize(Vector2Subtract(actor->position, PLAYER.position));
        float angle = acosf(Vector2DotProduct({1.0f, 0.0f}, dir));
        if(dir.y > 0.0f){angle*=-1.0f;}

        //add random offset to angle
        angle += randf(-0.8,0.8);

       actor->target_pos = Vector2Scale({cosf(angle), -sinf(angle)}, randf(min_range, max_range));
    }

    Vector2 heading = Vector2Subtract(actor->target_pos, actor->position);
    actor->move_dir = Vector2Normalize(heading);
    
    actor->cur_speed += 1.f;
    actor->cur_speed = Clamp(actor->cur_speed, 0, actor->max_speed);
    
    
    actor->velocity = Vector2Add(actor->velocity,Vector2Scale(actor->move_dir, actor->cur_speed));
    if(actor->cur_speed > Vector2Length(actor->velocity)){actor->cur_speed = Vector2Length(actor->velocity);}

    if(Vector2Length(heading) <= 1.f)
    {
        actor->state = THROW;
        actor->state_timer = 0;
    }
}

void scared_bomber::throw_bombs(Actor* actor)
{
    if(actor->state_timer >= 120)
    {
        actor->state = MOVE;
        actor->state_timer = 0;
        return;
    }
    if(actor->state_timer > 105){return;}
    if(actor->state_timer % 35 == 0)
    {
        Bullet bullet = Bullet();
        bullet.damage = 10;
        bullet.size = 8.f;
        bullet.speed = randf(2.f, 4.f);

        SetSoundVolume(sfx[8], 1.f/(1.f+(Vector2Distance(actor->position, PLAYER.position)/200.f)));
        PlaySound(sfx[8]);
        init_bullet(&bullet, randf(0, TAU), actor->position, 6);
        bullet_list[total_bullets++] = bullet;
    }
}

void scared_bomber::run_away(Actor* actor)
{
    Vector2 heading = Vector2Subtract(actor->position, PLAYER.position);
    actor->move_dir = Vector2Normalize(heading);

    actor->cur_speed += 5.f;
    actor->cur_speed = Clamp(actor->cur_speed, 0, actor->max_speed*2.f);


    actor->velocity = Vector2Add(actor->velocity,Vector2Scale(actor->move_dir, actor->cur_speed));
    if(actor->cur_speed > Vector2Length(actor->velocity)){actor->cur_speed = Vector2Length(actor->velocity);}

    if(actor->state_timer % 50 == 0)
    {
        Bullet bullet = Bullet();
        bullet.damage = 10;
        bullet.size = 8.f;
        bullet.speed = randf(1.f, 2.f);

        init_bullet(&bullet, randf(0, TAU), actor->position, 6);
        bullet_list[total_bullets++] = bullet;
    }

    if(Vector2Length(heading) >= max_range*1.25f)
    {
        actor->state = MOVE;
        actor->state_timer = 0;
    }
}