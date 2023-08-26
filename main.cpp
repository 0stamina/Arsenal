#include "global_vars.hpp"

void init()
{
    bg_texture = LoadTexture("resources/bg.png");
    arrow_texture = LoadTexture("resources/test_arrow.png");
    spear_sprite_list.push_back(LoadTexture("resources/spear.png"));

    load_bullets();
    load_guns();

    restart();

    return;
}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(960, 720, "Arsenal");
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
        for(int n = 0; n < 1; n++)
        {
            step();
        }
        
        BeginTextureMode(target);

            ClearBackground(BLACK);
            float base_w = bg_texture.width*4.0;
            float scale = 1.0f;
            Rectangle bg_src = {world_camera.target.x, world_camera.target.y, base_w, base_w};
            Rectangle bg_dest = {0.0f, 0.0f, base_w, base_w};
            DrawTexturePro(bg_texture, bg_src, bg_dest, Vector2Zero(), 0.0f, WHITE);
            
            
            BeginMode2D(world_camera);

                draw();

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
            int score_width = MeasureText(std::to_string(score).c_str(), 35);
            
            DrawText(std::to_string(score).c_str(), res_x-score_width-30, 10, 40, BLACK);

            DrawRectangle(20, 20, PLAYER.health / 1.0f, 15, MAROON);
            DrawText(std::to_string((int)blood).c_str(), 20, 40, 40, DARKBROWN);

            DrawText(gun_list[curr_gun].name, 20, res_y-70, 40, BLACK);
            if(curr_gun > 0)
            {
                DrawRectangle(20, res_y-20, (float)gun_durability/(float)gun_list[curr_gun].durability*100.0f, 10, BLACK);
            }

            if(!PLAYER.exists){DrawText("Press R to Restart", res_x/2-(MeasureText("Press R to Restart", 20))/2, (res_y/2)-30, 40, BLACK);}

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
    // Gun basic_melee = Gun();
    // basic_melee.damage = 5;
    // basic_melee.bullet_type = 0;
    // basic_melee.bullet_time = 0.5f;
    // basic_melee.bullet_speed = 3.0f;
    // basic_melee.fire_rate = 0.5f;
    // basic_melee.spread = 0.0f;
    // gun_list.push_back(basic_melee);

    Gun pistol = Gun();
    pistol.name = "Pistol";
    pistol.damage = 34;
    pistol.bullet_type = 0;
    pistol.bullet_speed = 6.0f;
    pistol.fire_rate = 0.1f;
    pistol.spread = 0.05f;
    pistol.durability = 0;
    gun_list.push_back(pistol);

    Gun rifle = Gun();
    rifle.name = "Rifle";
    rifle.shoot_func = 1;
    rifle.damage = 34;
    rifle.bullet_type = 0;
    rifle.bullet_speed = 6.0f;
    rifle.fire_rate = 0.05f;
    rifle.spread = 0.075f;
    rifle.durability = 100;
    gun_list.push_back(rifle);
    

    Gun shotgun = Gun();
    shotgun.name = "Shotgun";
    shotgun.damage = 34;
    shotgun.bullet_time = 0.5;
    shotgun.bullet_amt = 5;
    shotgun.bullet_type = 1;
    shotgun.bullet_speed = 6.0f;
    shotgun.fire_rate = 0.4f;
    shotgun.spread = 0.3f;
    shotgun.durability = 150;
    gun_list.push_back(shotgun);
    
    Gun flamethrower = Gun();
    flamethrower.name = "Flamethrower";
    flamethrower.damage = 5;
    flamethrower.shoot_func = 1;
    flamethrower.bullet_time = 1.0f;
    flamethrower.bullet_amt = 5;
    flamethrower.bullet_type = 2;
    flamethrower.bullet_speed = 3.0f;
    flamethrower.fire_rate = 0.05f;
    flamethrower.spread = 0.3f;
    flamethrower.durability = 400;
    gun_list.push_back(flamethrower);
    
}

void restart()
{
    for(int i = hit_data.size()-1; i >= 0; i--)
    {
        hit_data.erase(hit_data.begin()+i);
        continue;
    }
    for(int i = sprite_list.size()-1; i >= 0; i--)
    {
        UnloadTexture(sprite_list[i].texture);
        sprite_list.erase(sprite_list.begin()+i);
        continue;
    }
    for(int i = actor_list.size()-1; i >= 0; i--)
    {
        actor_list.erase(actor_list.begin()+i);
        continue;
    }
    for(int i = bullet_list.size()-1; i >= 0; i--)
    {
        bullet_list.erase(bullet_list.begin()+i);
        continue;
    }
    for (int i = bullet_list.size() - 1; i >= 0; i--)
    {
        bullet_list.erase(bullet_list.begin() + i);
        continue;
    }
    for (int i = hook_list.size() - 1; i >= 0; i--)
    {
        hook_list.erase(hook_list.begin() + i);
    }
    srand(time(0));

    spawn_timer = SPAWN_TIME_MAX;
    spawn_time = SPAWN_TIME_MAX;

    world_camera = { 0 };
    world_camera.zoom = 1.0f;
    world_camera.offset = Vector2Scale({(float)res_x, (float)res_y}, 1.0f/(2.0f));

    Actor player = Actor();
    init_actor(&player, {0.0f, 0.0f}, 1);
    //PLAYER.health = 1;

    score = 0;
    for(int i = 0; i < 50; i++)
    {
        new_hook();
    }

    for(int i = 0; i < 15; i++)
    {
        float angle = randf(0.0f, TAU);
        float dist = randf(100.0f, 300.0f);

        Actor fish = Actor();
        init_actor(&fish, {cosf(angle)*dist, -sinf(angle)*dist}, 3);
    }

    //blood = 100;

    curr_gun = 0;
    gun_cooldown = 0.0f;
    swap_gun();

    cursor_pos = {0.0f, 0.0f};
}