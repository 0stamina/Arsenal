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


#define TAU 6.283185307179586f

#define res_x 320
#define res_y 224

#define SPAWN_TIME_MIN 0.75f
#define SPAWN_TIME_MAX 1.5f
#define SPAWN_TIME_DELTA 0.1f
extern float spawn_time;
extern float spawn_timer;

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

extern float blood;

extern int curr_gun;
extern int gun_durability;
extern float gun_cooldown;

#define CRATE_RADIUS 100.0f
#define CRATE_TIME_MAX 50.0f
extern int num_crates;
extern Vector2 crate_pos;
extern float crate_time;

void restart();
void init();
void step();
void draw();
void collision(Actor*);
void cursor_set();
void load_bullets();
void load_guns();
void new_crate();
void swap_gun();

#endif