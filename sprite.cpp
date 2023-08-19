#include "global_vars.hpp"


unsigned int assign_sprite(const char* file_name)
{
    for(int i = sprite_list.size()-1; i >= 0; i--)
    {
        if(sprite_list[i].file_name.compare(file_name) == 0)
        {
            sprite_list[i].loaded_users++;
            return i;
        }
    }

    Sprite spr = Sprite();
    spr.file_name = file_name;
    spr.loaded_users = 1;
    spr.texture = LoadTexture(file_name);
    sprite_list.push_back(spr);
    
    return sprite_list.size()-1;
}

void unassign_sprite(unsigned int idx)
{
    if(--sprite_list[idx].loaded_users == 0)
    {
        UnloadTexture(sprite_list[idx].texture);
        sprite_list.erase(sprite_list.begin()+idx);
    }
}