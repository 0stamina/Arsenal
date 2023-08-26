#include "global_vars.hpp"


void step()
{
    if((!PLAYER.exists||IsKeyDown(KEY_RIGHT_CONTROL)||IsKeyDown(KEY_LEFT_CONTROL)) && IsKeyPressed(KEY_R)){
        restart();
    }
    if(!PLAYER.exists){return;}

    
    if(IsKeyPressed(KEY_RIGHT)){curr_gun++; swap_gun();}
    if(IsKeyPressed(KEY_LEFT)){curr_gun--; swap_gun();}

    if(curr_gun < 0){curr_gun = gun_list.size()-1;}
    if(curr_gun >= gun_list.size()){curr_gun = 0;}
    
    //run projectile code
    for(int i = bullet_list.size()-1; i >= 0; i--)
    {
        Bullet& bullet = bullet_list[i];
        if(!bullet.exists)
        {
            bullet_list.erase(bullet_list.begin()+i);
            continue;
        }
        bullet.position = Vector2Add(bullet.position, Vector2Scale({cosf(bullet.rotation), -sinf(bullet.rotation)}, bullet.speed));
        bullet_step[bullet.type](&bullet);
    }

    //run actor code
    for(int i = actor_list.size()-1; i >= 0; i--)
    {

        Actor& actor = actor_list[i];
        if(!actor.exists)
        {
            if(i)
            {
                destroy_actor(&actor_list[i]);
                actor_list.erase(actor_list.begin()+i);
            }
            continue;
        }

        actor_step[actor.type](&actor);
        actor.move_dir = Vector2Normalize(actor.move_dir);

        move_actor(&actor, Vector2Scale(actor.move_dir, actor.speed));
        if(i){collision(&actor);}
    }


    //camera follow player
    world_camera.target.x = (int)PLAYER.position.x;
    world_camera.target.y = (int)PLAYER.position.y;
    
    //get cursor position in scaled screenspace
    cursor_set();

    //camera follow cursor
    world_camera.target = Vector2Add(world_camera.target , Vector2Scale(cursor_pos, 0.2f));

    //spawn new enemy
    if(spawn_timer <= 0.0f)
    {
        float angle = 0.0f;
        if(Vector2Length(actor_list[0].move_dir) < 0.5f){angle = randf(0.0f, TAU);}
        else{angle = acosf(Vector2DotProduct({1.0f, 0.0f}, actor_list[0].move_dir))+randf(0.0f, 0.6f)-0.3f;}
        float dist = randf(400.0f, 450.0f);
        Vector2 offset = {cosf(angle)*dist, sinf(angle)*dist};
        if(actor_list[0].move_dir.y < 0.0f){offset.y*=-1;}

        Vector2 pos = Vector2Add(offset, actor_list[0].position);

        Actor enemy = Actor();
        init_actor(&enemy, pos, 2);

        spawn_time = Clamp(spawn_time-SPAWN_TIME_DELTA, SPAWN_TIME_MIN, SPAWN_TIME_MAX);
        spawn_timer = spawn_time;
    }
    else
    {
        spawn_timer -= delta;
    }
    
    if(pickup_timer <= 0.0f && active_fish < 50)
    {
        float angle = randf(0.0f, TAU);
        float dist = randf(400.0f, 500.0f);
        Vector2 offset = {cosf(angle)*dist, -sinf(angle)*dist};

        Vector2 pos = Vector2Add(offset, actor_list[0].position);

        Actor fish = Actor();
        init_actor(&fish, pos, 3);

        pickup_timer = PICKUP_TIME;
    }
    else
    {
        pickup_timer -= delta;
    }

    //box unlock
    fill_hooks();


    //shoot
    gun_shoot[gun_list[curr_gun].shoot_func](&gun_list[curr_gun]);
    if(gun_durability <= 0)
    {
        curr_gun = 0;
    }
    process_spear();
    proccess_hits();

    if(health_timer <= 0.0f)
    {
        damage_actor(&PLAYER, 2);
        health_timer = HEALTH_TIME;
    }
    else
    {
        health_timer -= delta;
    }

    return;
}

void collision(Actor* actor)
{
    for(int j = actor_list.size()-1; j >= 0; j--)
    {
        float dist = Vector2Distance(actor->position, actor_list[j].position);
        if(dist <= actor->size + actor_list[j].size)
        {
            push_actor(actor, &actor_list[j], (actor->size+actor_list[j].size)-dist);
        }
    }
}

void cursor_set()
{
    if(Vector2Length(GetMouseDelta()) <= 0.0f){return;}

    cursor_pos = GetMousePosition();
    float x_ratio = (float)res_x / (float)GetScreenWidth();
    float y_ratio = (float)res_y / (float)GetScreenHeight();
    float scale = x_ratio > y_ratio ? x_ratio : y_ratio;
    if (x_ratio > y_ratio)
    {
        cursor_pos = Vector2Scale(cursor_pos, x_ratio);
        cursor_pos.y += (res_y - GetScreenHeight() * x_ratio) / 2.0f;
    }
    else
    {
        cursor_pos = Vector2Scale(cursor_pos, y_ratio);
        cursor_pos.x += (res_x - GetScreenWidth() * y_ratio) / 2.0f;
    }
    cursor_pos = GetScreenToWorld2D(cursor_pos, world_camera);

    cursor_pos = Vector2Subtract(cursor_pos, world_camera.target);
    cursor_pos.x = Clamp(cursor_pos.x, -res_x/2.0f,res_x/2.0f);
    cursor_pos.y = Clamp(cursor_pos.y, -res_y/2.0f,res_y/2.0f);
}

void swap_gun()
{
    if(curr_gun < 0){curr_gun = gun_list.size()-1;}
    if(curr_gun >= gun_list.size()){curr_gun = 0;}
    gun_durability = gun_list[curr_gun].durability;
}