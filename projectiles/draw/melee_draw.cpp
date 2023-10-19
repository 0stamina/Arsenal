
#include "global_vars.hpp"

void melee_draw(Bullet* bullet)
{
    Vector2 dir = {cosf(bullet->rotation), -sinf(bullet->rotation)};

    Vector2 edge_dir = {-dir.y, dir.x};

    Vector2 point = Vector2Add(Vector2Scale(dir, bullet->size), bullet->position);
    Vector2 edge_1 = Vector2Add(Vector2Add(Vector2Scale(edge_dir, bullet->size), {-(dir.x*bullet->size*0.5f), -(dir.y*bullet->size*0.5f)}), bullet->position);
    Vector2 edge_2 = Vector2Add(Vector2Add(Vector2Scale(edge_dir, -bullet->size), {-(dir.x*bullet->size*0.5f), -(dir.y*bullet->size*0.5f)}), bullet->position);


    DrawTriangle(point, edge_1, bullet->position, WHITE);
    DrawTriangle(point, edge_2, bullet->position, WHITE);
    DrawTriangle(edge_1, point, bullet->position, WHITE);
    DrawTriangle(edge_2, point, bullet->position, WHITE);
    //DrawCircleV(bullet->position, bullet->size, WHITE);
    
    // Texture texture = bullet_sprite_list[bullet->spr_idx];
    // Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};

    // Rectangle dest = source;
    // dest.x = bullet->position.x;
    // dest.y = bullet->position.y;
    // dest.width *= bullet->size;
    // dest.height *= bullet->size;
    // DrawTexturePro(texture, source, dest, {dest.width/2.0f, dest.height/2.0f}, -bullet->rotation*RAD2DEG, WHITE);
}