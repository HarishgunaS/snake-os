#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "io.h"
void set_key(unsigned char key);
unsigned char get_key();
void init_keyboard();
int end, current;
unsigned char key_buffer[256];
unsigned char key;

#endif