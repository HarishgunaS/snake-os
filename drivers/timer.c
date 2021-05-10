#include "timer.h"

void init_timer()
{
    ticks = 0;
}

void tick()
{
    ticks++;
}

unsigned long get_ticks()
{
    return ticks;
}

void sleep_ms(int milliseconds)
{
    unsigned long initial_time = get_ticks();
    unsigned long long final_time = initial_time + milliseconds;
    while (final_time > get_ticks())
    {
        // do nothing
    }
}