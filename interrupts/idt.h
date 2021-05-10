struct IDT_entry {
    unsigned short offset_lower;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_higher;
};

struct __attribute__((__packed__)) IDT_register {
    unsigned short size;
    unsigned long address;
};

void initialize_idt(void);
void isr0(void);
void isr1(void);
void set_idt_entry(int index, unsigned long address);
struct IDT_entry IDT[256];
