
#include "global_vars.hpp"

float spawn_timer = SPAWN_TIME_MAX;
float spawn_time = SPAWN_TIME_MAX;

void(*(gun_shoot[2]))(Gun*) = {single_shoot, auto_shoot};

void(*(bullet_step[3]))(Bullet*) = {basic_bullet_step, slug_bullet_step, pierce_bullet_step};
void(*(bullet_draw[3]))(Bullet*) = {basic_bullet_draw, basic_bullet_draw, pierce_bullet_draw};

void(*(actor_init[3]))(Actor*) = {empty_actor_init, player_init, basic_enemy_init};
void(*(actor_step[3]))(Actor*) = {empty_actor_step, player_step, basic_enemy_step};
void(*(actor_swap[3]))(Actor*, int) = {empty_actor_swap, player_swap, empty_actor_swap};

Vector2 cursor_pos;
Camera2D world_camera;
Texture bg_texture;
Texture arrow_texture;
std::vector<Actor> actor_list;
std::vector<Sprite> sprite_list;
std::vector<Bullet> bullet_list;
std::vector<Texture> bullet_sprite_list;
std::vector<Gun> gun_list;
std::vector<Hit> hit_data;


float delta = 0.0f;

float blood = 0.0f;

int curr_gun = 0;
float gun_cooldown;
int gun_durability = 0;

int num_crates = 0;
Vector2 crate_pos;
float crate_time;