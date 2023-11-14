#include "global_vars.hpp"

int spawn_amt(int);
void spawn_enemies()
{
    basic_enemy_timer--;
    basic_shooter_timer--;
    random_spawn_timer--;
    for(int o = 0; o < 2; o++)
    {
        if(basic_enemy_timer <= 0)
        {
            Vector2 p = {0.0f, 0.0f};
            do
            {
                p.x = randf(map_rect.x+100, -map_rect.x-100);
                p.y = randf(map_rect.y+100, -map_rect.y-100);
            }
            while(Vector2Distance(p, PLAYER.position) <= 100.0f || Vector2Length(p) <= 100.0f);
            int type = 2;
            int num = spawn_amt(type);
            for(int i = 0; i < num; i++)
            {
                Vector2 offset = {randi(-50, 50), randi(-50, 50)};
                init_actor(Vector2Add(p, offset), type);
            }

            basic_enemy_timer = BASIC_ENEMY_MAX;
        }
        
        if(basic_shooter_timer <= 0)
        {
            Vector2 p = {0.0f, 0.0f};
            do
            {
                p.x = randf(map_rect.x+100, -map_rect.x-100);
                p.y = randf(map_rect.y+100, -map_rect.y-100);
            }
            while(Vector2Distance(p, PLAYER.position) <= 100.0f || Vector2Length(p) <= 100.0f);
            int type = 3;
            int num = spawn_amt(type);
            for(int i = 0; i < num; i++)
            {
                Vector2 offset = {randi(-50, 50), randi(-50, 50)};
                init_actor(Vector2Add(p, offset), type);
            }

            basic_shooter_timer = BASIC_SHOOTER_MAX;
        }
        
        if(random_spawn_timer <= 0)
        {
            int type = 0;
            do
            {
                type = randi(4,6);
            }
            while(type == 0);
            

            Vector2 p = {0.0f, 0.0f};
            do
            {
                p.x = randf(map_rect.x+100, -map_rect.x-100);
                p.y = randf(map_rect.y+100, -map_rect.y-100);
            }
            while(Vector2Distance(p, PLAYER.position) <= 150.0f || Vector2Length(p) <= 150.0f);
            int num = spawn_amt(type);
            for(int i = 0; i < num; i++)
            {
                Vector2 offset = {randi(-50, 50), randi(-50, 50)};
                init_actor(Vector2Add(p, offset), type);
            }

            random_spawn_timer = RANDOM_SPAWN_MAX;
        }
    }
}

int spawn_amt(int type)
{
    switch(type)
    {
        case 2:
            return randi(3, 5);
        case 3:
            return randi(2, 3);
        case 4:
            return 1;
        case 5:
            return randi(1, 3);
        default:
            return 0;
    }
}