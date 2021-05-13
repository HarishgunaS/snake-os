#ifndef MEM_H
#define MEM_H
void* malloc(int num_bytes);
void init_heap();
void* base_address;
void* current_address;
void* max_address;
#endif