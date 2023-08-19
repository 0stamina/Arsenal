
#include "bullet_funcs.hpp"
#include "bullet.hpp"
#include "actor_funcs.hpp"
#include "actor.hpp"
#include "random.hpp"
#include "global_vars.hpp"

void player_init(Actor* actor)
{
    actor->sprite_idx = assign_sprite("resources/test_player.png");
    //this is temporary you should be loading from a file
    Animation idle = Animation();
    AnimationFrame idle_frame_1 = AnimationFrame();
    idle_frame_1.frame_time = 10;
    idle_frame_1.region = {0, 0, 16, 16};
    idle.frame_set.push_back(idle_frame_1);
    AnimationFrame idle_frame_2 = AnimationFrame();
    idle_frame_2.frame_time = 10;
    idle_frame_2.region = {16, 0, 16, 16};
    idle.frame_set.push_back(idle_frame_2);
    AnimationFrame idle_frame_3 = AnimationFrame();
    idle_frame_3.frame_time = 10;
    idle_frame_3.region = {32, 0, 16, 16};
    idle.frame_set.push_back(idle_frame_3);
    actor->animation_set.push_back(idle);
    
    Animation run = Animation();
    AnimationFrame run_frame_1 = AnimationFrame();
    run_frame_1.frame_time = 10;
    run_frame_1.region = {0, 16, 16, 16};
    run.frame_set.push_back(run_frame_1);
    AnimationFrame run_frame_2 = AnimationFrame();
    run_frame_2.frame_time = 10;
    run_frame_2.region = {16, 16, 16, 16};
    run.frame_set.push_back(run_frame_2);
    AnimationFrame run_frame_3 = AnimationFrame();
    run_frame_3.frame_time = 10;
    run_frame_3.region = {32, 16, 16, 16};
    run.frame_set.push_back(run_frame_3);
    AnimationFrame run_frame_4 = AnimationFrame();
    run_frame_4.frame_time = 10;
    run_frame_4.region = {48, 16, 16, 16};
    run.frame_set.push_back(run_frame_4);
    actor->animation_set.push_back(run);
    
    Animation back_run = Animation();
    back_run.frame_set.push_back(run_frame_4);
    back_run.frame_set.push_back(run_frame_3);
    back_run.frame_set.push_back(run_frame_2);
    back_run.frame_set.push_back(run_frame_1);

    actor->animation_set.push_back(back_run);
}

void player_step(Actor* actor)
{
    actor->move_dir = {0.0, 0.0};
    if(IsKeyDown(KEY_W)) actor->move_dir.y-=1.0f;
    if(IsKeyDown(KEY_S)) actor->move_dir.y+=1.0f;
    if(IsKeyDown(KEY_A)) actor->move_dir.x-=1.0f;
    if(IsKeyDown(KEY_D)) actor->move_dir.x+=1.0f;

    int test_face = -1;
    if(actor->move_dir.x > 0.0f){test_face = 0;}
    if(actor->move_dir.x < 0.0f){test_face = 1;}

    if(Vector2Length(actor->move_dir) < 0.5f ){player_swap(actor, 0);}
    else if(test_face == actor->facing){player_swap(actor, 1);}
    else{player_swap(actor, 2);}
}

void player_swap(Actor* actor, int state)
{
    if(actor->state == state){return;}
    actor->aframe = 0;
    actor->gframe = 0;
    actor->state = state;
}