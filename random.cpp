#include "random.hpp"

int randi(int lo, int hi)
{
    return lo + (rand())%(hi-lo);
}

float randf(float lo, float hi)
{
    return lo + (float)(rand()) / (float)(RAND_MAX/(hi-lo));
}