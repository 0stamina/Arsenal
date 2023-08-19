#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

struct AnimationFrame
{
    unsigned int frame_time;
    Rectangle region;
};
struct Animation
{
    std::vector<AnimationFrame> frame_set;
};

#endif