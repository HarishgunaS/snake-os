#include "random.h"

//from C standard and wiki.osdev.org

static unsigned long int next = 1;
 
int rand( void ) // RAND_MAX assumed to be 32767
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}
 
void srand( unsigned int seed )
{
    next = seed;
}

int randint(int min, int max)
{
    if (max <= min)
    {
        return max;
    }
    int s = max - min;
    return (rand() % s) + min;
}