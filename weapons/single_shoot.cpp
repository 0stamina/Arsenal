#include "global_vars.hpp"

void single_shoot(Gun* gun)
{
	if(gun_cooldown > 0.0f)
	{
		gun_cooldown -= delta;
		return;
	}
    if(IsMouseButtonPressed(0))
    {
        for(int i = 0; i < gun->bullet_amt; i++)
        {
            Bullet bullet = Bullet();
            bullet.damage = gun->damage;
            bullet.speed = gun->bullet_speed;
            bullet.size = gun->bullet_size;
            bullet.time_limit = gun->bullet_time;
            if(i > 0){bullet.speed+=randf(-1, 1);}

            Vector2 aim_dir = Vector2Normalize(cursor_pos);

            Vector2 pos = Vector2Add(actor_list[0].position, Vector2Scale(aim_dir, 12.0f));

            float angle = acosf(Vector2DotProduct({1.0f, 0.0f}, aim_dir));
            float spread = 0.0f;
            if(gun->bullet_amt > 1){spread+=gun->spread*randf(i/(float)gun->bullet_amt, (i+1.0f)/(float)gun->bullet_amt);}
            else{spread+=randf(0.0f, gun->spread);}
            if(rand()%2){spread*=-1.0f;}

            if(aim_dir.y > 0.0f){angle*=-1.0f;}
            angle+=spread;

            init_bullet(&bullet, angle, pos, gun->bullet_type);

            bullet_list.push_back(bullet);
            gun_cooldown = gun->fire_rate;
            gun_durability--;
        }
    }
}