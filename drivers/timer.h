void init_timer();
void tick();
unsigned long get_ticks();
void sleep_ms(int milliseconds);
void add_function(unsigned long func, unsigned long delay);

unsigned long ticks;
int currentFunctionIndex;
void (*functions[256]) (void);
unsigned short delays[256];
unsigned long lastTime[256];