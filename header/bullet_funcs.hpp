#pragma once
#ifndef BULLET_FUNCS_HPP
#define BULLET_FUNCS_HPP

#include "global_vars.hpp"

void basic_bullet_step(Bullet*);
void slug_bullet_step(Bullet*);
void pierce_bullet_step(Bullet*);
void bomb_step(Bullet*);

void basic_bullet_draw(Bullet*);
void melee_draw(Bullet*);
void fireball_draw(Bullet*);
void bomb_draw(Bullet*);
void explosion_draw(Bullet*);


extern void(*(bullet_step[]))(Bullet*);
extern void(*(bullet_draw[]))(Bullet*);

#endif
