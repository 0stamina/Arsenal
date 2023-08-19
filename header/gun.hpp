#pragma once
#ifndef GUN_HPP
#define GUN_HPP

#include "global_vars.hpp"

struct Gun
{
    char* name = "none";
    int damage = 0;
    int shoot_func = 0;
    int durability = 1;
    int bullet_amt = 1;
    int bullet_type = -1;
    float bullet_speed = 1.0f;
    float bullet_size = 1.0f;
    float bullet_time = 1.0f;
    float fire_rate = 0.2f;
    float spread = 0.0f;
};

#endif
