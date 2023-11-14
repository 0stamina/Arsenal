#pragma once
#ifndef ACTOR_HPP
#define ACTOR_HPP
#include "global_vars.hpp"

struct Actor
{
    bool exists = false;
    int health = 100;
    int type = -1;
    int state = -1;
    int state_timer = 0;
    int facing = 0;

    Color draw_col = WHITE;

    int damage_timer = 0;

    float size = 15.0f;
    bool pushable = true;
    bool touch_damage = false;
    Vector2 position = { 0.0f, 0.0f };
    float max_speed = 0.0f;
    float cur_speed = 0.0f;
    Vector2 move_dir = { 0.0f, 0.0f };
    Vector2 velocity = { 0.0f, 0.0f };
    Vector2 target_pos = { 0.0f, 0.0f };

    unsigned int sprite_idx = -1;
    unsigned int aframe = 0;
    unsigned int gframe = 0;
    int curr_status = 0;
    int status_timer = 0;

    Rectangle region = {0.0f,0.0f,0.0f,0.0f};

    std::vector<Animation> animation_set;
    int params[24] = {};
};

int init_actor(Vector2, int);
void destroy_actor(int);
void move_actor(Actor*);
void push_actor(Actor*, Actor*, float);
void damage_actor(Actor*, int);
void collision(Actor*);
void wall_collision(Actor*);

void apply_status(Actor*, int, int);
void process_status(Actor*);
void draw_status(Actor*);

#define BURN_IDX 1


#endif
