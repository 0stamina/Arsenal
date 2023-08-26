#include "global_vars.hpp"

void draw_line_round(float x1, float y1, float x2, float y2, float w, Color col)
{
    DrawCircleV({x1,y1},w/2.0f,col);
    DrawLineEx({x1,y1},{x2,y2},w,col);
    DrawCircleV({x2,y2},w/2.0f,col);
}