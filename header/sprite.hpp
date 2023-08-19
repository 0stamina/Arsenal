#pragma once

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "global_vars.hpp"

struct Sprite
{
    std::string file_name;
    Texture texture;
    unsigned int loaded_users;
};

unsigned int assign_sprite(const char*);
void unassign_sprite(unsigned int);


#endif