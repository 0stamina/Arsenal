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
#include "gameplay_vars.hpp"
#include "hook.hpp"

#define blood_value params[23]


#define WALK_TIME_MAX 0.2f

#define MULTIKILL_TIME 0.5f

#define TAU 6.283185307179586
#define PICKUP_SIZE 5.f
#define PICKUP_RATE 0.02f

#define res_x 640
#define res_y 480

const int max_actor_types[] = {0, 1, 200, 100, 20, 50};
const int FACING_LUT[] = {0,1,2,3,4,3,2,1};
const float map_siz = 1200.0f;
const Rectangle map_rect = {-map_siz/2.0f, -map_siz/2.0f, map_siz, map_siz};

#define BLOOD_THREAT Clamp(((float)_g.total_kills)/10.0f, 0.0f, 50.0f)

#define SPAWN_TIME_MAX 0.7f
extern float spawn_time;
extern float spawn_timer;

#define BASIC_ENEMY_MAX 131
extern int basic_enemy_timer;
#define BASIC_SHOOTER_MAX 251
extern int basic_shooter_timer;
#define RANDOM_SPAWN_MAX 449
extern int random_spawn_timer;

#define HEALTH_TIME 1.0f;
extern float health_timer;

#define CRATE_RADIUS 50.0f
#define CRATE_TIME_MAX 10.0f

#define PLAYER actor_list[0]

extern Vector2 cursor_pos;
extern Camera2D world_camera;
extern Texture bg_texture;
extern Texture arrow_texture;
extern Font font_12;
extern Font font_18;
extern Font font_24;
extern std::vector<Sound> sfx;
extern Music song;


extern int total_actors;
extern int total_actor_types[];
extern Actor actor_list[];
extern int total_bullets;
extern Bullet bullet_list[];
extern int total_hits;
extern Hit hit_data_list[];
extern int total_pickups;
extern Vector2 pickup_list[];

extern std::vector<Texture> actor_sprite_list;
extern std::vector<Texture> bullet_sprite_list;
extern std::vector<Texture> gun_sprite_list;
extern std::vector<Gun> gun_list;

extern unsigned int animation_timer;
extern float delta;

extern GameplayVars _g;

void restart();
void init();
void step();
void draw();
void draw_line_round(float, float, float, float, float, Color);
void cursor_set();
void load_bullets();
void load_guns();
void new_crate();
void spawn_enemies();
void swap_gun();

#endif