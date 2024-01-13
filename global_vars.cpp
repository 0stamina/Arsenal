
#include "global_vars.hpp"

bool(*(gun_shoot[]))(Gun*) = {single_shoot, auto_shoot, charge_shoot};

void(*(bullet_step[]))(Bullet*) = {basic_bullet_step, slug_bullet_step, pierce_bullet_step, bomb_step};
void(*(bullet_draw[]))(Bullet*) = {basic_bullet_draw, melee_draw, fireball_draw, bomb_draw, explosion_draw};

void(*(actor_init[]))(Actor*) = {empty_actor_init, player_init, basic_enemy_init, basic_shooter_init, wall_slime_init, scared_bomber_init};
void(*(actor_step[]))(Actor*) = {empty_actor_step, player_step, basic_enemy_step, basic_shooter_step, wall_slime_step, scared_bomber_step};
void(*(actor_draw[]))(Actor*) = {empty_actor_draw, player_draw, basic_enemy_draw, basic_shooter_draw, wall_slime_draw, scared_bomber_draw};

bool in_main_menu = true;

Vector2 cursor_pos;
Camera2D world_camera;
Texture bg_texture;
Texture arrow_texture;
Font font_12;
Font font_18;
Font font_24;
std::vector<Sound> sfx;
Music song;

int total_actors = 0;
int total_actor_types[50];
Actor actor_list[500] = {};
int total_bullets = 0;
Bullet bullet_list[500] = {};
int total_hits = 0;
Hit hit_data_list[500] = {};
int total_pickups = 0;
Vector2 pickup_list[500] = {};

std::vector<Texture> actor_sprite_list;
std::vector<Texture> bullet_sprite_list;
std::vector<Texture> gun_sprite_list;
std::vector<Gun> gun_list;


float delta = 0.0f;


int basic_enemy_timer = BASIC_ENEMY_MAX;
int basic_shooter_timer = BASIC_SHOOTER_MAX*4;
int random_spawn_timer = RANDOM_SPAWN_MAX*2;

float spawn_timer = SPAWN_TIME_MAX;
float spawn_time = SPAWN_TIME_MAX;

float pickup_timer;
float health_timer = HEALTH_TIME;

GameplayVars _g = GameplayVars();