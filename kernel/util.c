void memory_copy(char *source, char *destination, int num)
{
    int i;
    for (i = 0; i < num; i++)
    {
        *(destination + i) = *(source + i);
    }
}

void int_to_ascii(int i, char str[])
{
    int n = 0;
    int nexti, x;
    while (i > 0)
    {
        nexti = i / 10;
        x = i - (nexti * 10);
        i = nexti;
        str[n] = (char)(x + 48);
        n += 1;
    }

    char temp;
    int j = n-1;
    while (j >= n / 2)
    {
        temp = str[j];
        str[j] = str[n - j - 1];
        str[n - j - 1] = temp;
        j -= 1;
    }
    str[n] = 0;

}