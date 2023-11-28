#include "global_vars.hpp"

void init_bullet(Bullet* bullet, float rot, Vector2 pos, int type)
{
    bullet->exists = true;
    bullet->rotation = rot;
    bullet->position = pos;
    switch(type)
    {
        //basic
        case 0:
            bullet->logic = 0;
            bullet->draw = 0;
            bullet->params[2] = 5;
            break;
        //slug
        case 1:
            bullet->logic = 1;
            bullet->draw = 0;
            bullet->params[2] = 2;
            break;
        //melee
        case 2:
            bullet->logic = 2;
            bullet->draw = 1;
            break;
        //fireball
        case 3:
            bullet->logic = 2;
            bullet->draw = 2;
            bullet->params[0] = BURN_IDX;
            bullet->params[1] = 300;
            break;
        //charge shot
        case 4:
            bullet->logic = 2;
            bullet->draw = 0;
            break;
        //explosion
        case 5:
            bullet->logic = 2;
            bullet->draw = 4;
            bullet->size = 50.f;
            bullet->speed = 0;
            bullet->time = 10;
            SetSoundVolume(sfx[7], 1.f/(1.f+(Vector2Distance(bullet->position, PLAYER.position)/200.f)));
            PlaySound(sfx[7]);
            break;
        //thrown bomb
        case 6:
            bullet->logic = 3;
            bullet->draw = 3;
            bullet->params[2] = 20;
            break;
    }
}