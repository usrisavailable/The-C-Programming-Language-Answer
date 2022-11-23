#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

void itoa(int n, char s[], int b);
void reverse(char s[], int len);

int main(int argc, char **argv)
{
    char s[MAX_LINE];
    itoa(-65536, s, 16);
    debug("%s", s);
    sprintf(s, "%x", -65536);
    debug("%s", s);
    return 0;
}

void itoa(int n, char s[], int b)
{
    int num = n;
    int temp = 0;
    int bit = 0;
    int nbit = 0;
    int i = 0;

    if (b == 2)
    {
        temp = 1;
        bit = 1;
        nbit = 1 << 31;
        nbit = ~nbit;
    }
    else if (b == 8)
    {
        temp = 7;
        bit = 3;
        nbit = 7 << 29;
        nbit = ~nbit;
    }
    else
    {
        temp = 15;
        bit = 4;
        nbit = 15 << 28;
        nbit = ~nbit;
    }
    
    do{
        int t = 0;
        t = num & temp;
        //debug("%d", t);
        if (t > 9)
            s[i++] = (t - 10) + 'a';
        else
            s[i++] = t + '0';
        num = num >> bit;
        num = num & nbit;
    }while(num);

    s[i] = '\0';
    reverse(s, i);
    return;
}

void reverse(char s[], int len)
{
    int i = 0;
    for (i; i < len / 2; i++)
    {
        int temp;
        temp = s[i];
        s[i] = s[len - i -1];
        s[len - i -1] = temp;
    }
    
    return;
}
