
#include "global_vars.hpp"
void process_spear()
{
    switch (spear_state)
    {
        case 0:
            if(IsMouseButtonPressed(1))
            {
                spear_dir = Vector2Normalize(cursor_pos);
                spear_head = Vector2Add(PLAYER.position, Vector2Scale(spear_dir, 40.0f));
                spear_state = 1;
                for(int i = actor_list.size()-1; i >= 0; i--)
                {
                    Actor& actor = actor_list[i];
                    if(actor.type != 3){continue;}
                    if(Vector2Distance(Vector2Add(PLAYER.position, Vector2Scale(spear_dir, 20.0f)), actor.position) > actor.size+20.0f){continue;}

                    actor.exists = false;
                    speared_fish++;
                }
            }
            break;
        case 1:
            shoot_spear();
            break;
        case 2:
            retract_spear();
            break;
    }
}

void shoot_spear()
{
    float speed = 10.0f;
    spear_head = Vector2Add(Vector2Scale(spear_dir,speed), spear_head);
    spear_dist += speed;


    for(int i = actor_list.size()-1; i >= 0; i--)
    {
        Actor& actor = actor_list[i];
        if(actor.type != 3){continue;}
        if(Vector2Distance(spear_head, actor.position) > actor.size+5.0f){continue;}

        actor.exists = false;
        speared_fish++;
    }

    if((!IsMouseButtonDown(1) && spear_dist >= 300.0f) || spear_dist >= 600.0f)
    {
        spear_state = 2;
    }
}

void retract_spear()
{
    float speed = 5.0f;

    Vector2 heading = Vector2Subtract(spear_head, PLAYER.position);

    if(Vector2Length(heading) < 40.0f)
    {
        blood += speared_fish;
        spear_state = 0;
        spear_dist = 0.0f;
        speared_fish = 0;
        return;
    }

    spear_dir = Vector2Normalize(heading);
    spear_head = Vector2Add(Vector2Scale(spear_dir,-speed), spear_head);
}