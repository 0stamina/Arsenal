#pragma once
#ifndef HOOK_HPP
#define HOOK_HPP
#include "global_vars.hpp"

struct Hook
{
    Vector2 position = {0.0f,0.0f};
    int tier = 0;
    float amt;
};


void fill_hooks();
void new_hook();
void draw_hooks();

#endif