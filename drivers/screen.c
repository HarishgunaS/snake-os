#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"

int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);


int get_offset(int col, int row)
{
    return 2 * (col + MAX_COLS * row);
}

int get_offset_col(int offset)
{
    return (offset - get_offset_row(offset) * MAX_COLS * 2) / 2;
}

int get_offset_row(int offset)
{
    return offset / (MAX_COLS * 2);
}

int get_cursor_offset()
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int position = port_byte_in(REG_SCREEN_DATA);
    position = position << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    position += port_byte_in(REG_SCREEN_DATA);

    int offset_from_vga = (position) * 2;
    return offset_from_vga;
}

void set_cursor_offset(int offset)
{
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, offset >> 8);
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, offset & 0xFF);
    
}

void clear_screen()
{
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    for (i = 0; i < screen_size; i++)
    {
        vidmem[2 * i] = ' ';
        vidmem[2 * i + 1] = WHITE_ON_BLACK; 
    }
    set_cursor_offset(get_offset(0,0));
}

int print_char(char c, int col, int row, char attr)
{
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;
    int offset;

    if (col >= MAX_COLS || row >= MAX_ROWS)
    {
        // vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        // vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        // return get_offset(col, row);
        memory_copy(vidmem + MAX_COLS * 2, vidmem, 2 * MAX_COLS * MAX_ROWS);
        offset = get_offset(0, MAX_ROWS-1);
        set_cursor_offset(offset);
        col = 0; 
        row = MAX_ROWS - 1;
    }

    
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n')
    {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    }
    else if (c == 0x08)
    {
        vidmem[offset] = c;
        vidmem[offset + 1] = attr;
    }
    else
    {
        vidmem[offset] = c;
        vidmem[offset + 1] = attr;
        offset += 2;
    }
    if (offset >= 2 * MAX_COLS * MAX_ROWS)
    {
        memory_copy(vidmem + MAX_COLS * 2, vidmem, 2 * MAX_COLS * MAX_ROWS);
    }
    set_cursor_offset(offset);

    return offset;
}

void kprint_at(char* message, int col, int row)
{
    
    int offset;

    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else
    {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
    int i = 0;

    while (message[i] != 0)
    {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

}

void kprint(char* message)
{
    kprint_at(message, -1, -1);
}

void kprint_backspace()
{
    int offset = get_cursor_offset() - 2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row, WHITE_ON_BLACK);
}