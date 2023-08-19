#pragma once
#ifndef ACTOR_FUNCS_H
#define ACTOR_FUNCS_H

#include "actor.hpp"

static void empty_actor_init(Actor* actor){return;}
static void empty_actor_step(Actor* actor){return;}
static void empty_actor_swap(Actor* actor, int state){actor->state = state;}
void player_init(Actor* actor);
void player_step(Actor* actor);
void player_swap(Actor* actor, int state);
void basic_enemy_init(Actor* actor);
void basic_enemy_step(Actor* actor);

extern void(*(actor_init[3]))(Actor*);
extern void(*(actor_step[3]))(Actor*);
extern void(*(actor_swap[3]))(Actor*, int);

#endif
