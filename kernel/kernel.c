#define GREEN 0x02
#define RED 0x04
#define BLACK 0x00
#define MIN_X 1
#define MAX_X 321 //exclusive
#define MIN_Y 0
#define MAX_Y 200 //exclusive

#include "screen.h"

int kernel_main()
{
    square(10, 10, 5, RED);
    
    return 0;
}
