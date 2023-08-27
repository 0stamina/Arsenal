#pragma once
#ifndef GLOBAL_VARS_HPP
#define GLOBAL_VARS_HPP

#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "structs.hpp"
#include "random.hpp"
#include "sprite.hpp"
#include "animation.hpp"
#include "gun_funcs.hpp"
#include "gun.hpp"
#include "bullet_funcs.hpp"
#include "bullet.hpp"
#include "actor_funcs.hpp"
#include "actor.hpp"
#include "hit.hpp"
#include "hook.hpp"


#define TAU 6.283185307179586

#define res_x 480
#define res_y 360
const int FACING_LUT[] = {0,1,2,3,4,3,2,1};

extern float threat;

#define SPAWN_TIME_MIN 1.0f
#define SPAWN_TIME_MAX 5.0f
#define SPAWN_TIME_DELTA 0.5f
extern float spawn_time;
extern float spawn_timer;
#define PICKUP_TIME 0.5f
extern float pickup_timer;

#define HEALTH_TIME 1.0f;
extern float health_timer;

extern Vector2 cursor_pos;
extern Camera2D world_camera;
extern Texture bg_texture;
extern Texture arrow_texture;
extern std::vector<Actor> actor_list;
extern std::vector<Sprite> sprite_list;
extern std::vector<Bullet> bullet_list;
extern std::vector<Texture> bullet_sprite_list;
extern std::vector<Gun> gun_list;
extern std::vector<Hit> hit_data;
extern float delta;

#define PLAYER actor_list[0]

extern int active_fish;

extern int blood;

extern int curr_gun;
extern int gun_durability;
extern float gun_cooldown;



#define CRATE_RADIUS 70.0f
#define CRATE_TIME_MAX 10.0f
extern int num_crates;
extern Vector2 crate_pos;
extern float crate_time;

extern int score;
extern std::vector<Hook> hook_list;

extern std::vector<Texture> spear_sprite_list;
extern Vector2 spear_head;
extern Vector2 spear_dir;
extern int speared_fish;
extern int spear_state; 
extern float spear_dist;

void restart();
void init();
void step();
void draw();
void draw_line_round(float, float, float, float, float, Color);
void collision(Actor*);
void cursor_set();
void load_bullets();
void load_guns();
void new_crate();
void swap_gun();

void process_spear();
void shoot_spear();
void retract_spear();

#endif