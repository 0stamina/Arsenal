#include "global_vars.hpp"
void new_crate()
{
    crate_pos = Vector2Add(actor_list[0].position, {randf(0.0f,1000.0f)-500.0f, randf(0.0f,1000.0f)-500.0f});
    crate_pos.x = Clamp(crate_pos.x, -100000.0f, 100000.0f);
    crate_pos.y = Clamp(crate_pos.y, -100000.0f, 100000.0f);
    
    crate_time = 0.0f;
}