#include "timer.h"

void init_timer()
{
    ticks = 0;
    currentFunctionIndex = 0;
}

void tick()
{
    ticks++;
    int i;
    for (i = 0; i < currentFunctionIndex; i++)
    {
        if (lastTime[i] + delays[i] <= ticks)
        {
            (*functions[i])();
            lastTime[i] = ticks;
        }
    }
}

void add_function(unsigned long func, unsigned long delay)
{
    functions[currentFunctionIndex] = (void *)func;
    delays[currentFunctionIndex] = delay;
    lastTime[currentFunctionIndex++] = get_ticks();
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