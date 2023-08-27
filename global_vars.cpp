
#include "global_vars.hpp"

void(*(gun_shoot[]))(Gun*) = {single_shoot, auto_shoot};

void(*(bullet_step[]))(Bullet*) = {basic_bullet_step, slug_bullet_step, pierce_bullet_step};
void(*(bullet_draw[]))(Bullet*) = {basic_bullet_draw, basic_bullet_draw, pierce_bullet_draw};

void(*(actor_init[]))(Actor*) = {empty_actor_init, player_init, basic_enemy_init, fish_init};
void(*(actor_step[]))(Actor*) = {empty_actor_step, player_step, basic_enemy_step, fish_step};
void(*(actor_swap[]))(Actor*, int) = {empty_actor_swap, player_swap, empty_actor_swap, empty_actor_swap};
void(*(actor_draw[]))(Actor*) = {empty_actor_draw, player_draw, empty_actor_draw, fish_draw};

Vector2 cursor_pos;
Camera2D world_camera;
Texture bg_texture;
Texture arrow_texture;
std::vector<Actor> actor_list;
std::vector<Actor> pickup_list;
std::vector<Sprite> sprite_list;
std::vector<Bullet> bullet_list;
std::vector<Texture> bullet_sprite_list;
std::vector<Gun> gun_list;
std::vector<Hit> hit_data;

float delta = 0.0f;


float spawn_timer = SPAWN_TIME_MAX;
float spawn_time = SPAWN_TIME_MAX;

float pickup_timer;
float health_timer = HEALTH_TIME;

float threat = 1.0f;

int blood = 0;

int curr_gun = 0;
float gun_cooldown;
int gun_durability = 0;

int active_fish = 0;

int score;
std::vector<Hook> hook_list;

std::vector<Texture> spear_sprite_list;
Vector2 spear_head;
Vector2 spear_dir;
int speared_fish;
int spear_state; 
float spear_dist;


int num_crates = 0;
Vector2 crate_pos;
float crate_time;