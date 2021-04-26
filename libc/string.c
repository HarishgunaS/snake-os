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

int strlen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

int strcmp(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] == s2[i])
    {
        if (s1[i] == '\0')
            return 0;
        i++;
    }
    return (s1[i] > s2[i]) ? 1 : -1;
}

void backspace(char s[])
{
    int n = strlen(s);
    s[n-1] = '\0';
}

void reverse(char s[])
{
    int n = strlen(s);
    int i;
    char temp;
    for (i = 0; i < n/2; i++)
    {
        temp = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = temp;
    }
}

void append(char s[], char n)
{
    int i = strlen(s);
    s[i] = n;
    s[i + 1] = '\0';
}

