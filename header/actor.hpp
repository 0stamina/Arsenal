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
    int facing = 0;

    float size = 7.5f;
    Vector2 position = { 0.0f, 0.0f };
    float speed = 2.0;
    Vector2 move_dir = { 0.0f, 0.0f };

    unsigned int sprite_idx = -1;
    unsigned int aframe = 0;
    unsigned int gframe = 0;

    Rectangle region = {0.0f,0.0f,0.0f,0.0f};

    std::vector<Animation> animation_set;
    int params[24] = {};
};

void init_actor(Actor*, Vector2, int);
void destroy_actor(Actor*);
void move_actor(Actor*, Vector2);
void push_actor(Actor*, Actor*, float);
void damage_actor(Actor*, int);

#endif
