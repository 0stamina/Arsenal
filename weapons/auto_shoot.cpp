#include "global_vars.hpp"

void auto_shoot(Gun* gun)
{
	if(_g.gun_cooldown > 0)
	{
		_g.gun_cooldown--;
		return;
	}
    if(IsMouseButtonDown(0))
    {
        _g.walk_timer = WALK_TIME_MAX;
        for(int i = 0; i < gun->bullet_amt; i++)
        {
            Bullet bullet = Bullet();
            bullet.from_player = true;
            bullet.damage = gun->damage;
            bullet.speed = gun->bullet_speed;
            bullet.size = gun->bullet_size;
            bullet.time = gun->bullet_time;
            if(i > 0){bullet.speed+=randf(-1, 1);}

            Vector2 aim_dir = Vector2Normalize(cursor_pos);

            Vector2 pos = Vector2Add(PLAYER.position, Vector2Scale(aim_dir, 12.0f));

            float angle = acosf(Vector2DotProduct({1.0f, 0.0f}, aim_dir))+randf(0.0f, gun->spread)-gun->spread/2.0f;
            float spread = 0.0f;
            if(gun->bullet_amt > 1){spread+=gun->spread*randf(i/(float)gun->bullet_amt, (i+1.0f)/(float)gun->bullet_amt);}
            else{spread+=randf(0.0f, gun->spread);}
            if(rand()%2){spread*=-1.0f;}

            if(aim_dir.y > 0.0f){angle*=-1.0f;}
            angle+=spread;

            init_bullet(&bullet, angle, pos, gun->bullet_type);

            bullet_list.push_back(bullet);
            _g.gun_cooldown = gun->fire_rate;
        }
        if(_g.gun_durability > 0){_g.gun_durability--;}
        else{damage_actor(&PLAYER, 1);}
    }
}