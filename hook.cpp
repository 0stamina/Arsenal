#include "global_vars.hpp"

void fill_hooks()
{
    if(!IsKeyPressed(KEY_SPACE)){return;}
    if(Vector2Length(PLAYER.position) <= CRATE_RADIUS)
    {
        if(_g.blood >= _g.min_cost)
        {
            _g.score += (int)pow(15.0f,log10(_g.blood));
            double percent = (double)_g.gun_durability/(double)gun_list[_g.curr_gun].durability*100.0;
            _g.swap_bonus = false;
            if(percent <= 20.0f && percent > 0.0f){_g.swap_bonus = true;}
            
            int prev_gun = _g.curr_gun;
            for(int prev_gun = _g.curr_gun; prev_gun == _g.curr_gun; _g.curr_gun = randi(0, gun_list.size())){}
            swap_gun();
            
            _g.times_swapped++;

            //_g.min_cost += ((_g.blood-_g.min_cost)/10)+pow(2.5,_g.times_swapped);

            _g.blood = 0;
        }
    }
}

void draw_hooks()
{
    // for(int i = 0; i < hook_list.size(); i++)
    // {
    //     float fill_ratio = hook_list[i].amt/CRATE_TIME_MAX;
    //     //fill_ratio = 0.5f-sinf(asinf(1.0f-2.0f*fill_ratio)/3.0f);
    //     DrawCircleV(hook_list[i].position, fill_ratio*CRATE_RADIUS, {245, 245, 245, 100});
    //     DrawRing(hook_list[i].position, CRATE_RADIUS-2.0f, CRATE_RADIUS, 0.0f, 360.0f, 100, {245, 245, 245, 255});
    // }
    DrawRing({0.0f, 0.0f}, CRATE_RADIUS-2.0f, CRATE_RADIUS, 0.0f, 360.0f, 100, BLACK);
    
}