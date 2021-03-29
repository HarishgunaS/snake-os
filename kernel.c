void dummy()
{

}

void main()
{
    char* vga = (char*) 0xb8000;
    *vga = 'a';
}