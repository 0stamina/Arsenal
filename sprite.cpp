#include "global_vars.hpp"


unsigned int assign_sprite(const char* file_name)
{
    int empty_idx = -1;
    for(int i = sprite_list.size()-1; i >= 0; i--)
    {
        if(sprite_list[i].file_name.compare(file_name) == 0)
        {
            sprite_list[i].loaded_users++;
            return i;
        }
        if(empty_idx == -1 && sprite_list[i].loaded_users == 0)
        {
            empty_idx = i;
        }
    }

    Sprite spr = Sprite();
    spr.file_name = file_name;
    spr.loaded_users = 1;
    spr.texture = LoadTexture(file_name);
    if(empty_idx == -1)
    {
        sprite_list.push_back(spr);
    }
    else
    {
        sprite_list[empty_idx] = spr;
    }
    
    return sprite_list.size()-1;
}

void unassign_sprite(unsigned int idx)
{
    if(idx == -1){return;}
    if(sprite_list.size() <= idx){return;}
    if(--sprite_list[idx].loaded_users == 0)
    {
        UnloadTexture(sprite_list[idx].texture);
        sprite_list[idx].file_name = "";
        if(sprite_list.size()-1 == idx)
        {
            sprite_list.erase(sprite_list.begin()+idx);
        }
        
    }
}