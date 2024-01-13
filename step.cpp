#include "global_vars.hpp"


void step()
{
    if(!PLAYER.exists && IsKeyPressed(KEY_R)){
        restart();
    }
    if(!PLAYER.exists){return;}
    
    if(_g.walk_timer > 0.f){_g.walk_timer -= delta;}

    //run projectile code
    for(int i = total_bullets-1; i >= 0; i--)
    {
        Bullet& bullet = bullet_list[i];
        bullet.position = Vector2Add(bullet.position, Vector2Scale({cosf(bullet.rotation), -sinf(bullet.rotation)}, bullet.speed));
        if(!bullet.exists)
        {
            total_bullets--;
            bullet_list[i] = bullet_list[total_bullets];
            continue;
        }
        bullet_step[bullet.logic](&bullet);
    }

    //run actor code
    for(int i = total_actors-1; i >= 0; i--)
    {

        Actor& actor = actor_list[i];
        if(!actor.exists)
        {
            if(i)
            {
                destroy_actor(i);
            }
            continue;
        }
        

        actor_step[actor.type](&actor);
        actor.state_timer++;

        if(actor.state < 0){continue;}
        actor.damage_timer--;
        process_status(&actor);

        collision(&actor);
        wall_collision(&actor);
        move_actor(&actor);
    }


    //camera follow player
    world_camera.target.x = (int)PLAYER.position.x;
    world_camera.target.y = (int)PLAYER.position.y;
    
    //get cursor position in scaled screenspace
    cursor_set();

    //camera follow cursor
    world_camera.target = Vector2Add(world_camera.target , Vector2Scale(cursor_pos, 0.2f));

    //spawn new enemy
    spawn_enemies();

    //box unlock
    fill_hooks();


    //shoot
    if(gun_shoot[gun_list[_g.curr_gun].shoot_func](&gun_list[_g.curr_gun]))
    {
        switch(_g.curr_gun)
        {
            case 1:
                PlaySound(sfx[4]);
                break;
            case 3:
                if(!IsSoundPlaying(sfx[5])){PlaySound(sfx[5]);}
                break;
            case 4:
                PlaySound(sfx[6]);
                break;
            default:
                PlaySound(sfx[3]);
                break;
        }
    }

    //process_spear();
    proccess_hits();

    _g.threat += delta;
    if (_g.threat > 10.0f) { _g.threat = 10.0f; }

    if(_g.blood > _g.highest_blood){_g.highest_blood = _g.blood;}


    //multikill
    if(_g.multikill_timer <= 0.f)
    {
        _g.blood += _g.point_stash*(1+_g.multikills/15.f);
        _g.multikills = 0;
        _g.point_stash = 0;
    }
    else{_g.multikill_timer -= delta;}

    return;
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
    if(_g.curr_gun < 0){_g.curr_gun = 0;}
    if(_g.curr_gun >= gun_list.size()){_g.curr_gun = gun_list.size()-1;}

    _g.gun_durability = gun_list[_g.curr_gun].durability;
    if(_g.swap_bonus){_g.gun_durability *= 1.5;}
}