
#include "bullet_funcs.hpp"
#include "bullet.hpp"
#include "actor_funcs.hpp"
#include "actor.hpp"
#include "random.hpp"
#include "global_vars.hpp"


void basic_enemy_init(Actor* actor)
{
    // actor->sprite_idx = assign_sprite("resources/test_enemy.png");
    // //this is temporary you should be loading from a file
    // Animation walk = Animation();
    // AnimationFrame walk_frame_1 = AnimationFrame();
    // walk_frame_1.frame_time = 10;
    // walk_frame_1.region = {0, 0, 16, 20};
    // walk.frame_set.push_back(walk_frame_1);
    // AnimationFrame walk_frame_2 = AnimationFrame();
    // walk_frame_2.frame_time = 10;
    // walk_frame_2.region = {16, 0, 16, 20};
    // walk.frame_set.push_back(walk_frame_2);
    // AnimationFrame walk_frame_3 = AnimationFrame();
    // walk_frame_3.frame_time = 10;
    // walk_frame_3.region = {32, 0, 16, 20};
    // walk.frame_set.push_back(walk_frame_3);
    // AnimationFrame walk_frame_4 = AnimationFrame();
    // walk_frame_4.frame_time = 10;
    // walk_frame_4.region = {48, 0, 16, 20};
    // walk.frame_set.push_back(walk_frame_4);
    // actor->animation_set.push_back(walk);

    actor->size = 10.0f;
    actor->speed = 1.5f;
}

void basic_enemy_step(Actor* actor)
{
    if(Vector2Distance(PLAYER.position, actor->position) >= 500)
    {
        Vector2 dir = Vector2Normalize(Vector2Subtract(PLAYER.position, actor->position));
        actor->position = Vector2Add(PLAYER.position, Vector2Scale(dir, 400));
    }

    actor->move_dir = Vector2Subtract(actor_list[0].position, actor->position);

    if(actor->move_dir.x > 0.0f){actor->facing = 0;}
    if(actor->move_dir.x < 0.0f){actor->facing = 1;}
}