#pragma once
#ifndef BULLET_HPP
#define BULLET_HPP

#include "global_vars.hpp"

struct Bullet
{
    bool exists = false;
    int logic = -1;
    int draw = -1;
    int spr_idx = 0;
    float size = 20.0f;
    int damage = 1;

    int time = 100;

    float speed = 5.0f;
    float accel = 0.0f;
    float rotation = 0;
    Vector2 position = { 0.0f, 0.0f };
    bool from_player = false;

    int params[8] = {};
};

void init_bullet(Bullet*, float, Vector2, int);

#endif