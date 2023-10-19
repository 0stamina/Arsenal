#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP
#include "global_vars.hpp"

struct GameplayVars
{
    int blood = 0;
    int highest_blood = 0;
    int total_blood = 0;
    int total_kills = 0;

    int curr_gun = randi(0, 4);
    int gun_durability = 0;
    float gun_cooldown = 0.f;
    int gun_charge = 0.f;
    float walk_timer = 0.f;

    bool swap_bonus = false;
    int min_cost = 100;
    int times_swapped = 0;
    int score = 0;
    float threat = 0.f;

    int point_stash = 0;
    int multikills = 0;
    float multikill_timer = 0.f;
};

#endif