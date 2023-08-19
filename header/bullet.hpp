#pragma once
#ifndef BULLET_HPP
#define BULLET_HPP

#include "global_vars.hpp"

struct Bullet
{
    bool exists = false;
    int type = -1;
    int spr_idx = 0;
    float size = 1.0f;
    int damage = 1;

    float time_limit = 1.0f;
    float time = 0.0f;

    float speed = 5.0f;
    float accel = 0.0f;
    float rotation = 0;
    Vector2 position = { 0.0f, 0.0f };
    Actor* parent = 0;

    int params[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
};

void init_bullet(Bullet*, float, Vector2, int);

#endif