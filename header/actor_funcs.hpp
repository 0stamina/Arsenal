#pragma once
#ifndef ACTOR_FUNCS_H
#define ACTOR_FUNCS_H

#include "actor.hpp"

static void empty_actor_init(Actor* actor){return;}
static void empty_actor_step(Actor* actor){return;}
static void empty_actor_swap(Actor* actor, int state){actor->state = state;}
static void empty_actor_draw(Actor* actor){DrawCircleV(actor->position, actor->size, WHITE);}
void player_init(Actor* actor);
void player_step(Actor* actor);
void player_swap(Actor* actor, int state);
void player_draw(Actor* actor);
void basic_enemy_init(Actor* actor);
void basic_enemy_step(Actor* actor);
void fish_init(Actor* actor);
void fish_step(Actor* actor);
void fish_draw(Actor* actor);

extern void(*(actor_init[]))(Actor*);
extern void(*(actor_step[]))(Actor*);
extern void(*(actor_swap[]))(Actor*, int);
extern void(*(actor_draw[]))(Actor*);

#endif
