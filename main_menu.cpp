#include "global_vars.hpp"

Vector2 start_game_pos = {320, 320};


void main_menu()
{
    Color col = WHITE;
    Vector2 button = MeasureTextEx(font_24, "Start Game", 24, 2.4f);
    Vector2 pos = GetMousePosition();

    float x_ratio = (float)res_x / (float)GetScreenWidth();
    float y_ratio = (float)res_y / (float)GetScreenHeight();
    float scale = x_ratio > y_ratio ? x_ratio : y_ratio;
    if (x_ratio > y_ratio)
    {
        pos = Vector2Scale(pos, x_ratio);
        pos.y += (res_y - GetScreenHeight() * x_ratio) / 2.0f;
    }
    else
    {
        pos = Vector2Scale(pos, y_ratio);
        pos.x += (res_x - GetScreenWidth() * y_ratio) / 2.0f;
    }

    if(
        pos.x > (start_game_pos.x-button.x/2.f) &&
        pos.x < (start_game_pos.x+button.x/2.f) &&
        pos.y > (start_game_pos.y-button.y/2.f) &&
        pos.y < (start_game_pos.y+button.y/2.f)
    )
    {
        col = SKYBLUE;
    }

    DrawTextEx(font_24, "Start Game", Vector2Subtract(start_game_pos, {button.x/2.f, button.y/2.f}), 24, 2.4f, col);

    if(IsMouseButtonPressed(0))
    {
        in_main_menu = false;
    }
    return;
}