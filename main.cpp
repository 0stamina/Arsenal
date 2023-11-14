#include "global_vars.hpp"

/*
    TODO

    <--UI-->
    set up ui function
    multikill indicator

    <--MISC-->
    particle system
    hit effect
    sound manager

    <--ENEMIES-->
    X enemy with projectile
    X spawn enemies in groups

    <--WEAPONS-->
    X add limited pierce to rifle and shotgun
    X make flamethrower apply burn status
    make player slow down while shooting

    <--CODE POLISH-->
    put guns in an array instead of vector
    compile sprite and sfx info into arrays
    change all timers to frame based
*/


void init()
{
    bg_texture = LoadTexture("resources/bg.png");
    arrow_texture = LoadTexture("resources/test_arrow.png");

    load_bullets();
    load_guns();

    restart();

    return;
}

int main(void)
{
    SetExitKey(KEY_NULL);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(960, 720, "Arsenal");
    InitAudioDevice();
    RenderTexture2D target = LoadRenderTexture(res_x, res_y);

    // The target's height is flipped (in the source Rectangle), due to OpenGL reasons
    Rectangle screen_source = { 0.0f, 0.0f, (float)res_x, -(float)res_y};

    SetTargetFPS(60);
    init();
    while (!WindowShouldClose())
    {
        int scr_w = GetScreenWidth();
        int scr_h = GetScreenHeight();
        Rectangle screen_dest = { 0.0f, 0.0f, scr_w, scr_h};
        
        float x_ratio = (float)scr_w / (float)res_x;
        float y_ratio = (float)scr_h / (float)res_y;

        if(y_ratio > x_ratio)
        {
            screen_dest.height*=(x_ratio/y_ratio);
            screen_dest.y = (scr_h-screen_dest.height)/2.0f;
        }
        else
        {
            screen_dest.width*=(y_ratio/x_ratio);
            screen_dest.x = (scr_w-screen_dest.width)/2.0f;
        }


        delta = GetFrameTime();
        step();
        
        BeginTextureMode(target);

            ClearBackground(BLACK);
            float base_w = bg_texture.width*4.0;
            float scale = 1.0f;
            Rectangle bg_src = {world_camera.target.x, world_camera.target.y, base_w, base_w};
            Rectangle bg_dest = {0.0f, 0.0f, base_w, base_w};
            DrawTexturePro(bg_texture, bg_src, bg_dest, Vector2Zero(), 0.0f, WHITE);

            DrawText(std::to_string(random_spawn_timer).c_str(), 0, 0, 10, BLACK);
            
            
            BeginMode2D(world_camera);

                draw();
                int cost_w = MeasureText(std::to_string(_g.min_cost).c_str(), 10);
                DrawText(std::to_string(_g.min_cost).c_str(), -(cost_w/2), -1, 10, BLACK);

            EndMode2D();

            //ui should go here
            bool crate_on_screen = true;
            Vector2 cam_center = Vector2Subtract(world_camera.target, world_camera.offset);
            if(0.0f > cam_center.y+res_y){crate_on_screen=false;}
            if(0.0f < cam_center.y){crate_on_screen=false;}
            if(0.0f > cam_center.x+res_x){crate_on_screen=false;}
            if(0.0f < cam_center.x){crate_on_screen=false;}
            if(!crate_on_screen)
            {
                float siz = 30.0f;
                Vector2 heading = Vector2Subtract({0.0f, 0.0f}, Vector2Add(cam_center,{res_x/2.0f, res_y/2.0f}));
                heading.x = Clamp(heading.x, -res_x/2.0f+siz, res_x/2.0f-siz);
                heading.y = Clamp(heading.y, -res_y/2.0f+siz, res_y/2.0f-siz);

                Vector2 dir = Vector2Normalize(heading);
                float angle = acosf(Vector2DotProduct({0.0f, -1.0f}, dir));
                if(dir.x > 0.0f){angle*=-1.0f;}

                Rectangle arrow_source = {0.0f, 0.0f, (float)arrow_texture.width, (float)arrow_texture.height};
                Rectangle arrow_dest = {res_x/2.0f+heading.x, res_y/2.0f+heading.y, siz, siz};

                DrawTexturePro(arrow_texture, arrow_source, arrow_dest, {siz/2.0f, siz/2.0f}, -angle*(360.0f/TAU), { 255, 255, 255, 60 });
            }

            //DrawText(std::to_string(spawn_time).c_str(), 10, 10, 10, WHITE);
            //DrawText(std::to_string(actor_list.size()).c_str(), 10, 25, 10, WHITE);
            int score_width = MeasureText(std::to_string(_g.score).c_str(), 35);
            
            DrawText(std::to_string(_g.score).c_str(), res_x-score_width-30, 10, 40, BLACK);

            //health
            int health_width = MeasureText(std::to_string(PLAYER.health).c_str(), 10);
            DrawRectangle(20, 20, PLAYER.health / 1.0f, 15, MAROON);
            DrawText(std::to_string(PLAYER.health).c_str(), 70-(health_width/2), 23, 10, BLACK);


            //blood
            DrawText(std::to_string((int)_g.blood).c_str(), 20, 40, 20, DARKBROWN);

            if(_g.multikill_timer > 0)
            {
                DrawRectangle(20, 65, 50*(_g.multikill_timer/MULTIKILL_TIME), 10, DARKBROWN);
                DrawText("+", 20, 80, 20, DARKBROWN);
                DrawText(std::to_string((int)(_g.point_stash*(1+_g.multikills/15.f))).c_str(), 32, 80, 20, DARKBROWN);
            }

            //gun and durability
            DrawText(gun_list[_g.curr_gun].name, 20, res_y-70, 20, BLACK);
            
            Color col = BLACK;
            float percent = (float)_g.gun_durability/(float)gun_list[_g.curr_gun].durability*100.0f;

            if(percent > 100.0f){col = GOLD;percent = 100.0f;}
            if(percent <= 20.0f){col = RED;}

            DrawRectangle(20, res_y-20, percent, 10, col);

            if(!PLAYER.exists){DrawText("Press R to Restart", res_x/2-(MeasureText("Press R to Restart", 20))/2, (res_y/2)-30, 20, BLACK);}

        EndTextureMode();

        BeginDrawing();
        BeginBlendMode(BLEND_ALPHA_PREMULTIPLY);
            ClearBackground(BLACK);
            DrawTexturePro(target.texture, screen_source, screen_dest, Vector2Zero(), 0.0f, WHITE);
        EndBlendMode();
        DrawFPS(0,0);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}

void load_bullets()
{
    bullet_sprite_list.push_back(LoadTexture("resources/test_projectile.png"));
}

void load_guns()
{
    Gun rifle = Gun();
    rifle.name = "Rifle";
    rifle.shoot_func = 1;
    rifle.damage = 55;
    rifle.bullet_type = 0;
    rifle.bullet_time = 300;
    rifle.bullet_speed = 6.0f;
    rifle.fire_rate = 8;
    rifle.spread = 0.1f;
    rifle.durability = 100;
    gun_list.push_back(rifle);
    gun_sprite_list.push_back(LoadTexture("resources/gun.png"));
    
    Gun shotgun = Gun();
    shotgun.name = "Shotgun";
    shotgun.shoot_func = 0;
    shotgun.damage = 65;
    shotgun.bullet_type = 1;
    shotgun.bullet_time = 35;
    shotgun.bullet_amt = 5;
    shotgun.bullet_speed = 6.0f;
    shotgun.fire_rate = 15;
    shotgun.spread = 0.3f;
    shotgun.durability = 40;
    gun_list.push_back(shotgun);

    Gun bow = Gun();
    bow.name = "Charge Gun";
    bow.shoot_func = 2;
    bow.damage = 300;
    bow.bullet_type = 4;
    bow.bullet_time = 70;
    bow.bullet_size = 25.0f;
    bow.bullet_speed = 15.0f;
    bow.fire_rate = 25;
    bow.spread = 0.0f;
    bow.durability = 20;
    gun_list.push_back(bow);
    
    Gun flamethrower = Gun();
    flamethrower.name = "Flamethrower";
    flamethrower.shoot_func = 1;
    flamethrower.damage = 2;
    flamethrower.bullet_type = 3;
    flamethrower.bullet_size = 8.0f;
    flamethrower.bullet_time = 100;
    flamethrower.bullet_amt = 5;
    flamethrower.bullet_speed = 3.5f;
    flamethrower.fire_rate = 5;
    flamethrower.spread = 0.2f;
    flamethrower.durability = 80;
    gun_list.push_back(flamethrower);
    
    
    Gun grenade_launcher = Gun();
    grenade_launcher.name = "G. Launcher";
    grenade_launcher.shoot_func = 0;
    grenade_launcher.damage = 200;
    grenade_launcher.bullet_type = 6;
    grenade_launcher.bullet_size = 8.0f;
    grenade_launcher.bullet_time = 200;
    grenade_launcher.bullet_speed = 3.5f;
    grenade_launcher.fire_rate = 20;
    grenade_launcher.spread = 0.f;
    grenade_launcher.durability = 30;
    gun_list.push_back(grenade_launcher);
}

void restart()
{
    for(int i = hit_data.size()-1; i >= 0; i--)
    {
        hit_data.erase(hit_data.begin()+i);
    }
    for(int i = sprite_list.size()-1; i >= 0; i--)
    {
        UnloadTexture(sprite_list[i].texture);
        sprite_list.erase(sprite_list.begin()+i);
    }
    for(int i = 0; i < 500; i++)
    {
        actor_list[i] = Actor();
    }
    for(int i = bullet_list.size()-1; i >= 0; i--)
    {
        bullet_list.erase(bullet_list.begin()+i);
    }
    for(int i = pickup_list.size()-1; i >= 0; i--)
    {
        pickup_list.erase(pickup_list.begin()+i);
    }
    srand(time(0));


    
    total_actors = 0;
    std::fill(total_actor_types, total_actor_types+50, 0);
    spawn_timer = SPAWN_TIME_MAX*2.0f;
    health_timer = HEALTH_TIME;
    basic_enemy_timer = BASIC_ENEMY_MAX;
    basic_shooter_timer = BASIC_SHOOTER_MAX;

    world_camera = { 0 };
    world_camera.zoom = 1.0f;
    world_camera.offset = Vector2Scale({(float)res_x, (float)res_y}, 1.0f/(2.0f));
    init_actor({0.0f, 0.0f}, 1);

    _g = GameplayVars();
    swap_gun();

    cursor_pos = {0.0f, 0.0f};

    
    for(int i = 0; i < 10; i++)
    {
        Vector2 p = {0.0f, 0.0f};
        do
        {
            p.x = randf(map_rect.x+100, -map_rect.x-100);
            p.y = randf(map_rect.y+100, -map_rect.y-100);
        }
        while(Vector2Length(p) <= 300.0f);
        init_actor(p, 2);
    }
}