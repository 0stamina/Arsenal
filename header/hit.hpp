#pragma once
#ifndef HIT_HPP
#define HIT_HPP
#include "global_vars.hpp"

struct Hit
{
    Actor* actor;
    int source;
    int time;
};


void add_hit(Actor*, int, int);
void proccess_hits();

#endif
