#include<stdio.h>
#include<limits.h>
#include<ctype.h>
#include<string.h>

#include "debug.h"

int nbits(int x);
int invert(unsigned int x, unsigned int p, unsigned int n);
int main(int argc, char *argv[])
{
    unsigned int x = invert(123u, 3u, 3u);
    printf("%x\n", 123);
    printf("%x\n", x);

    return 0;
}

int nbits(unsigned int x)
{
    int len = 0;
    while (x)
    {
        len++;
        x = x >> 1;
    }
    return len;
}
int invert(unsigned int x, unsigned int p, unsigned int n)
{
    int lenx = nbits(x);
    if (p + n > x)
        printf("%s\n", "bad argument");
    
    unsigned int tail = x & ~(~0 << (lenx - p -n));
    x = x >> (lenx - p - n);
    unsigned int middle = x & ~(~0 << n);
    middle = ~middle << (32 - n) >> (32 - n); //固定成32位的话，容错性不足
    x = x >> n;
    x = x << n;
    x = x | middle;
    x = x << (lenx - p - n);
    x = x | tail;
    return x;
}
