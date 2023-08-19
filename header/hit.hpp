#pragma once
#ifndef HIT_HPP
#define HIT_HPP
#include "global_vars.hpp"

struct Hit
{
    Actor* actor;
    int source;
    float time;
};


void add_hit(Actor*, int);
void proccess_hits();

#endif
