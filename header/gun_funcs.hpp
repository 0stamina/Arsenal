#pragma once
#ifndef GUN_FUNCS_HPP
#define GUN_FUNCS_HPP

#include "global_vars.hpp"

void single_shoot(Gun*);
void auto_shoot(Gun*);
void charge_shoot(Gun*);
extern void(*(gun_shoot[]))(Gun*);

#endif
