#include "global_vars.hpp"


void init()
{
    song = LoadMusicStream("resources/song.mp3");
    SetMusicVolume(song, 0.3f);

    bg_texture = LoadTexture("resources/bg.png");
    arrow_texture = LoadTexture("resources/test_arrow.png");
    font_12 = LoadFontEx("resources/Kaph-Regular.ttf", 12, NULL, 0);
    font_18 = LoadFontEx("resources/Kaph-Regular.ttf", 18, NULL, 0);
    font_24 = LoadFontEx("resources/Kaph-Regular.ttf", 24, NULL, 0);

    sfx.push_back(LoadSound("resources/heal.wav"));
    sfx.push_back(LoadSound("resources/hurt.wav"));
    sfx.push_back(LoadSound("resources/reload.wav"));
    sfx.push_back(LoadSound("resources/rifle_shoot.wav"));
    sfx.push_back(LoadSound("resources/shotgun_shoot.wav"));
    sfx.push_back(LoadSound("resources/flamethrower_shoot.wav"));
    sfx.push_back(LoadSound("resources/grenade_shoot.wav"));
    sfx.push_back(LoadSound("resources/explosion.wav"));
    sfx.push_back(LoadSound("resources/enemy_shoot.wav"));
    //sfx.push_back(LoadSound("resources/bomber_shoot.wav"));

    actor_sprite_list.push_back(LoadTexture("resources/player0.png"));
    actor_sprite_list.push_back(LoadTexture("resources/enemyguy.png"));
    actor_sprite_list.push_back(LoadTexture("resources/gunenemy.png"));
    actor_sprite_list.push_back(LoadTexture("resources/bombguy.png"));

    SetSoundVolume(sfx[3], 0.75f);
    SetSoundVolume(sfx[4], 0.5f);
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
    SetMasterVolume(0.15f);
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
        UpdateMusicStream(song);

        
        if(!in_main_menu)
        {
            step();
        }
        
        BeginTextureMode(target);

            ClearBackground(BLACK);
            float base_w = bg_texture.width*4.0;
            float scale = 1.0f;
            Rectangle bg_src = {world_camera.target.x, world_camera.target.y, base_w, base_w};
            Rectangle bg_dest = {0.0f, 0.0f, base_w, base_w};
            
            
            if(in_main_menu)
            {
                main_menu();
            }
            else
            {

                DrawTexturePro(bg_texture, bg_src, bg_dest, Vector2Zero(), 0.0f, WHITE);

                BeginMode2D(world_camera);

                    draw();
                    int cost_w = MeasureTextEx(font_12, std::to_string(_g.min_cost).c_str(), 12, 1.2f).x;
                    DrawTextEx(font_12, std::to_string(_g.min_cost).c_str(), {-(cost_w/2.f), -1.f}, 12, 1.f, BLACK);

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
                int score_width = MeasureTextEx(font_24, std::to_string(_g.score).c_str(), 24, 2.4f).x;
                
                DrawTextEx(font_24, std::to_string(_g.score).c_str(), {res_x-score_width-30.f, 10.f}, 24, 2.4f, BLACK);

                //health
                int health_width = MeasureTextEx(font_12, std::to_string(PLAYER.health).c_str(), 12, 1.2f).x;
                DrawRectangle(20, 20, PLAYER.health / 1.0f, 15, {132, 228, 102, 255});
                DrawTextEx(font_12, std::to_string(PLAYER.health).c_str(), {70.f-(health_width/2), 23.f}, 12, 1.2f, BLACK);

                //gun and durability
                Color col = {255, 223, 50, 255};
                float percent = (float)_g.gun_durability/(float)gun_list[_g.curr_gun].durability*100.0f;
                char ammo_text [5];
                itoa((int)percent, ammo_text, 10);
                strcat(ammo_text, "%");

                int ammo_width = MeasureTextEx(font_12, ammo_text, 12, 1.2f).x;

                if(percent > 100.0f){col = {253, 0, 187, 255};percent = 100.0f;}
                if(percent <= 20.0f){col = RED;}

                DrawRectangle(20, 40, percent, 15, col);
                DrawTextEx(font_12, ammo_text, {70.f-(ammo_width/2), 43.f}, 12, 1.2f, BLACK);

                DrawTextEx(font_12, gun_list[_g.curr_gun].name, {20, 60}, 12, 1.2f, BLACK);


                //blood
                DrawTextEx(font_12, std::to_string((int)_g.blood).c_str(), {175, 20}, 12, 1.2f, BLACK);

                if(_g.multikill_timer > 0)
                {
                    DrawRectangle(175, 40, 50*(_g.multikill_timer/MULTIKILL_TIME), 10, BLACK);
                    DrawTextEx(font_12, "+", {175, 60}, 12, 1.2f, BLACK);
                    DrawTextEx(font_12, std::to_string((int)(_g.point_stash*(1+_g.multikills/15.f))).c_str(), {185, 60}, 12, 1.2f, BLACK);
                }

                if(!PLAYER.exists){DrawTextEx(font_18, "Press R to Restart", {res_x/2.f-(MeasureTextEx(font_18, "Press R to Restart", 18, 1.8f).x)/2.f, (res_y/2)-30}, 18, 1.8f, BLACK);}

            }
        EndTextureMode();

        BeginDrawing();
        BeginBlendMode(BLEND_ALPHA_PREMULTIPLY);
            ClearBackground(BLACK);
            DrawTexturePro(target.texture, screen_source, screen_dest, Vector2Zero(), 0.0f, WHITE);
        EndBlendMode();
        EndDrawing();

    }

    CloseWindow();

    return 0;
}

void load_bullets()
{
    bullet_sprite_list.push_back(LoadTexture("resources/test_projectile.png"));
    bullet_sprite_list.push_back(LoadTexture("resources/test_projectile2.png"));
    bullet_sprite_list.push_back(LoadTexture("resources/bomb.png"));
    bullet_sprite_list.push_back(LoadTexture("resources/player_projectile.png"));
}

void load_guns()
{
    gun_sprite_list.push_back(LoadTexture("resources/gun.png"));

    Gun rifle = Gun();
    rifle.name = "Rifle";
    rifle.shoot_func = 1;
    rifle.damage = 55;
    rifle.bullet_type = 0;
    rifle.bullet_time = 300;
    rifle.bullet_speed = 6.0f;
    rifle.fire_rate = 8;
    rifle.spread = 0.1f;
    rifle.durability = 75;
    gun_list.push_back(rifle);
    
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
    shotgun.durability = 45;
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
    bow.durability = 30;
    gun_list.push_back(bow);
    
    Gun flamethrower = Gun();
    flamethrower.name = "Flamethrower";
    flamethrower.shoot_func = 1;
    flamethrower.damage = 5;
    flamethrower.bullet_type = 3;
    flamethrower.bullet_size = 8.0f;
    flamethrower.bullet_time = 100;
    flamethrower.bullet_amt = 5;
    flamethrower.bullet_speed = 3.5f;
    flamethrower.fire_rate = 5;
    flamethrower.spread = 0.2f;
    flamethrower.durability = 60;
    gun_list.push_back(flamethrower);
    
    
    Gun grenade_launcher = Gun();
    grenade_launcher.name = "G. Launcher";
    grenade_launcher.shoot_func = 0;
    grenade_launcher.damage = 800;
    grenade_launcher.bullet_type = 6;
    grenade_launcher.bullet_size = 8.0f;
    grenade_launcher.bullet_time = 200;
    grenade_launcher.bullet_speed = 7.f;
    grenade_launcher.fire_rate = 20;
    grenade_launcher.spread = 0.f;
    grenade_launcher.durability = 40;
    gun_list.push_back(grenade_launcher);
}

void restart()
{
    for(int i = 0; i < 500; i++)
    {
        hit_data_list[i] = Hit();
    }
    for(int i = 0; i < 500; i++)
    {
        actor_list[i] = Actor();
    }
    for(int i = 0; i < 500; i++)
    {
        bullet_list[i] = Bullet();
    }
    
    srand(time(0));

    total_hits = 0;
    total_bullets = 0;
    total_pickups = 0;
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
    PlayMusicStream(song);
}