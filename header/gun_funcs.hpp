#pragma once
#ifndef GUN_FUNCS_HPP
#define GUN_FUNCS_HPP

#include "global_vars.hpp"

bool single_shoot(Gun*);
bool auto_shoot(Gun*);
bool charge_shoot(Gun*);
extern bool(*(gun_shoot[]))(Gun*);

#endif
